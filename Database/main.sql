-- Cainan Travizanutto e Silva
-- Pablo Juan Tadini
-- Gabriel Maestre

CREATE DATABASE FORMULAMAGISTRAL;
USE FORMULAMAGISTRAL;

CREATE TABLE CLIENTE (
    IDCliente INTEGER PRIMARY KEY AUTO_INCREMENT,
    Nome VARCHAR(200),
    CPF VARCHAR(11),
    RG VARCHAR(14),
    DataNascimento DATE
);

CREATE TABLE MEDICO (
    IDMedico INTEGER PRIMARY KEY AUTO_INCREMENT,
    Nome VARCHAR(200),
    CRM INTEGER
);

CREATE TABLE INSUMO (
    IDInsumo INTEGER PRIMARY KEY AUTO_INCREMENT,
    Nome VARCHAR(200),
    FatorCorrecao REAL,
    FatorEquivalencia REAL,
    Bula VARCHAR(200),
    DCB INTEGER,
    NroPortaria INTEGER,
    CustoAquisicao REAL,
    MargemLucro REAL
);

CREATE TABLE ESTOQUE (
    IDInsumo INTEGER,
    IDLote INTEGER,
    QuantEstoque INTEGER,
    UnidadeMedida ENUM('g', 'mg'),
    FOREIGN KEY(IDInsumo) REFERENCES INSUMO(IDInsumo) ON UPDATE RESTRICT ON DELETE RESTRICT,
    PRIMARY KEY(IDLote, IDInsumo)
);

CREATE TABLE RESTRICAO (
    IDInsumo INTEGER,
    IDRestricao INTEGER,
    FOREIGN KEY(IDInsumo) REFERENCES INSUMO(IDInsumo) ON UPDATE RESTRICT ON DELETE RESTRICT,
    FOREIGN KEY(IDRestricao) REFERENCES INSUMO(IDInsumo) ON UPDATE RESTRICT ON DELETE RESTRICT,
    PRIMARY KEY(IDInsumo, IDRestricao)
);

CREATE TABLE VENDA (
    IDVenda INTEGER PRIMARY KEY AUTO_INCREMENT,
    DataVenda DATE,
    DataPrevEntrega DATE,
    FormaPgto ENUM('debito', 'credito'),
    IDCliente INTEGER,
    FOREIGN KEY(IDCliente) REFERENCES CLIENTE(IDCliente) ON UPDATE RESTRICT ON DELETE RESTRICT
);

CREATE TABLE FORMULA (
    IDFormula INTEGER PRIMARY KEY AUTO_INCREMENT,
    Dose VARCHAR(250),
    QuantBase INTEGER,
    UnidadeBase ENUM('capsulas'),
    NroNotifacao INTEGER,
    DataValidade DATE,
    IDVenda INTEGER,
    IDMedico INTEGER,
    FOREIGN KEY(IDVenda) REFERENCES VENDA(IDVenda) ON UPDATE RESTRICT ON DELETE RESTRICT,
    FOREIGN KEY(IDMedico) REFERENCES MEDICO(IDMedico) ON UPDATE RESTRICT ON DELETE RESTRICT
);

CREATE TABLE ITEMFORMULA (
    IDFormula INTEGER,
    IDInsumo INTEGER,
    IDLote INTEGER,
    QuantPrescrita INTEGER,
    UnidadePrescrita ENUM('g', 'mg'),
    FOREIGN KEY(IDFormula) REFERENCES FORMULA(IDFormula) ON UPDATE RESTRICT ON DELETE RESTRICT,
    FOREIGN KEY(IDInsumo) REFERENCES ESTOQUE(IDInsumo) ON UPDATE RESTRICT ON DELETE RESTRICT,
    FOREIGN KEY(IDLote) REFERENCES ESTOQUE(IDLote) ON UPDATE RESTRICT ON DELETE RESTRICT,
    PRIMARY KEY(IDFormula, IDInsumo, IDLote)
);

DELIMITER ;;
CREATE PROCEDURE INSERIR_ITEM_FORMULA(IN pIDFormula INTEGER, pIDInsumo INTEGER, pIDLote INTEGER, pQuantPrescrita INTEGER, pUnidadePrescrita ENUM('g', 'mg'), OUT pmsg VARCHAR(65))
BEGIN
    
    IF (pIDFormula IN (
        SELECT IDFormula FROM ITEMFORMULA
        WHERE ITEMFORMULA.IDInsumo IN (
            SELECT IDRestricao FROM RESTRICAO
            WHERE pIDInsumo = IDInsumo
        )
    )) THEN
        SET pmsg = 'Nao foi possivel incluir o insumo devido a restricao mediamentosa';
    ELSE 
        INSERT INTO ITEMFORMULA values(pIDFormula, pIDFormula, pIDLote, pQuantPrescrita, pUnidadePrescrita);
    END IF;

END ;;
DELIMITER ;

DELIMITER ;;
CREATE PROCEDURE INSERIR_FORMULA(IN Dose VARCHAR(200), QuantBase INTEGER, UnidadeBase ENUM('g', 'mg'), NroNotifacao INTEGER, DataValidade DATE, IDVenda INTEGER, IDMedico INTEGER)
BEGIN
    
    INSERT INTO FORMULA values(UUID(), QuantBase, UnidadeBase, NroNotifacao, DataValidade, IDVenda, IDMedico);
    
END ;;
DELIMITER ;

DELIMITER ;;
CREATE TRIGGER VERIFICA_ESTOQUE
BEFORE INSERT ON ITEMFORMULA FOR EACH ROW
BEGIN
    DECLARE UnidadeConvertida REAL;
    DECLARE QuantFinal REAL;
    DECLARE EstoqueTotal REAL;
    DECLARE EstoqueLote REAL;
    DECLARE EstoqueLoteTMP REAL;

    SET UnidadeConvertida = NEW.QuantPrescrita;
    --  CONSIDERANDO QUE O ESTOQUE, IDEPENDENTE DO LOTE, É SEMPRE A MESMA UNIDADE BASE
    IF (SELECT UnidadeBase FROM ESTOQUE WHERE ESTOQUE.IDInsumo = NEW.IDInsumo AND UnidadeBase = 'g') THEN
            IF NEW.UnidadePrescrita = 'mg' THEN
                SET UnidadeConvertida = NEW.QuantPrescrita / 1000;
            END IF;
    ELSE
            IF NEW.UnidadePrescrita = 'g' THEN
                SET UnidadeConvertida = NEW.QuantPrescrita * 1000;
            END IF;
    END IF;
    
    SET UnidadeConvertida = (SELECT UnidadeConvertida * FatorEquivalencia FROM INSUMO
                                                WHERE INSUMO.IDInsumo = NEW.IDInsumo);

    SET UnidadeConvertida = (SELECT UnidadeConvertida * (FatorCorrecao / 100 + 1) FROM INSUMO
                                                WHERE INSUMO.IDInsumo = NEW.IDInsumo);  

    SET QuantFinal = (SELECT UnidadeConvertida * QuantBase FROM FORMULA
                                        WHERE FORMULA.IDFormula = NEW.IDFormula);
    SET QuantFinal = TRUNCATE(QuantFinal, 4);
    
    SELECT SUM(QuantEstoque) 
    INTO EstoqueTotal
    FROM ESTOQUE WHERE
    ESTOQUE.IDInsumo = NEW.IDInsumo;

    IF (QuantFinal > EstoqueTotal) THEN
        SIGNAL SQLSTATE '45000' SET MESSAGE_TEXT = 'Quantidade insuficiente no estoque, operação cancelada';
    ELSE
        WHILE QuantFinal > 0 DO
                SELECT QuantEstoque INTO EstoqueLote FROM ESTOQUE WHERE ESTOQUE.IDInsumo = NEW.IDInsumo ORDER BY IDInsumo DESC LIMIT 1;
                SET QuantFinal = QuantFinal - EstoqueLote;
                SET EstoqueLoteTMP = EstoqueLote - QuantFinal;
                IF (EstoqueLoteTMP <= 0) THEN
                    DELETE FROM ESTOQUE WHERE ESTOQUE.IDInsumo = NEW.IDInsumo ORDER BY IDInsumo DESC LIMIT 1;
                ELSE
                    UPDATE ESTOQUE SET QuantEstoque = EstoqueLoteTMP WHERE ESTOQUE.IDInsumo = NEW.IDInsumo ORDER BY IDInsumo DESC LIMIT 1;
                END IF;
            END WHILE;
    END IF;
END;;
DELIMITER ;