#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define TWO_YEARS 63072000
#define HOUR_SEC 3600

typedef enum {fp, cp, ap, p, esa, u} machine_type_id;

typedef enum {c, f, mb} product_type_id;

typedef enum {
    CHICKEN_COST = 80,
    FISH_COST = 70,
    MEATBALL_COST = 40
} prod_cost;

typedef enum {
    CHICKEN_PRICE = 145,
    FISH_PRICE = 200,
    MEATBALL_PRICE = 80
} prod_price;

typedef enum {
    CHICKEN_TIME = 50,
    FISH_TIME = 20,
    MEATBALL_TIME = 90
} prod_time;

typedef enum {
    CHICKEN_PROB = 50,
    FISH_PROB = 30,
    MEATBALL_PROB = 20
} prod_prob;

typedef enum {
    CP_TIME = 16,
    CP_E_CONS = 20,
    CP_COST = 100000
} chickenpak;

typedef enum {
    FP_TIME = 10,
    FP_E_CONS = 20,
    FP_COST = 100000
} fishpak;

typedef enum {
    P_TIME = 25,
    P_E_CONS = 35,
    P_COST = 60000
} plastific;

typedef enum {
    ESA_TIME = 30,
    ESA_E_CONS = 40,
    ESA_COST = 50000
} ensacall;

typedef enum {
    U_TIME = 35,
    U_E_CONS = 35,
    U_COST = 30000
} universal;

typedef enum {
    AP_CHICKEN_TIME = 18,
    AP_FISH_TIME = 12,
    AP_MEATBALL_TIME = 12,
    AP_E_CONS = 22,
    AP_COST = 150000
} allpak;

typedef struct product
{
    int product_t_id, time_to_exp;
    struct product *next;
} product;

typedef struct queue
{
    int size;
    product *first;
} queue;

typedef struct machine
{
    int machine_t_id, product_t_id, time_prod_arr, time_prod_done;
    double cost;
    struct machine *next;
    queue *q;
} machine;

typedef struct packaging
{
    double cost, profit;
    int time, size;
    int c_done, f_done, mb_done;
    int c_wasted, f_wasted, mb_wasted;
    machine *first;
} packaging;

// ----------------------------------------------------------------------------------
// PROTOTYPES IN TREE OF EXECUTION -----------------------------------------
// ----------------------------------------------------------------------------------

void        start();                                                       

void        create_psector(int size, int *list);                           
void            allocate_machine(packaging *p_sector, int size, int *list);    
void                allocate_queue(machine *m);
void                gen_machine_cost(packaging *p_sector);                     

void        sim(packaging *p_sector);
void            gen_queue(packaging *p_sector);
int                 gen_product();
void                gen_product_cost(packaging *p_sector, int prod_type);
bool                prod_fits_machine(int prod_type, machine *m);
void                gen_queue_prod(machine *m, int prod_type);
product*                allocate_prod(int prod_type);
void            process(packaging *p_sector, machine *m);
void                update_prod_time(machine *m);
void                remove_prod_machine(packaging *p_sector, machine *m);
void                    handle_done(packaging *p_sector, int prod_type);
void                remove_prod_queue(packaging *p_sector, machine *m);
void                    remove_exp_products(packaging *p_sector, machine *m);
void                        handle_waste(packaging *p_sector, int prod_type);
void                     gen_machine_done_time(machine *m, int time_offset);
float                       ml_10();
void                gen_e_cost(packaging *p_sector, machine *m);

void        end(packaging **p_sector);
void            print(packaging *p_sector);
char*               get_machine_name(machine *m);
void            free_sim(packaging **p_sector);
void                free_machine(machine **m);
void                    free_queue(queue **q);
//----------------------------------------------------------------------------------
// input do usuario
void start()
{
    // seeda a funcao rand com o tempo do sistema
    srand(time(0));
    int qt, op;
    printf("Quantas maquinas: ");
    scanf("%d", &qt);
    if (qt == 0)
        exit(0);
    
    int list[qt];
    for(int i = 0; i < qt; i++) {
        printf("\n1 - FishPak\n2 - chickenPak\n3 - AllPak\n4 - Plastific\n5 - EnSacAll\n6 - Universal\nEscolha: ");
        scanf("%i", &op);
        
        switch (op) {
            case 1:
                list[i] = fp;
                break;
            case 2:
                list[i] = cp;
                break;
            case 3:
                list[i] = ap;
                break;
            case 4:
                list[i] = p;
                break;
            case 5:
                list[i] = esa;
                break;
            case 6:
                list[i] = u;
                break;
            default:
                printf("Invalido\n");
                i--;
                break;
        }
    }
    create_psector(qt, list);
}

// aloca o setor
void create_psector(int size, int *list)
{
    packaging *p_sector = calloc(1, sizeof(packaging));
    if (p_sector == NULL)
        exit(1);
    p_sector->size = size;
    allocate_machine(p_sector, size, list);
}

// aloca as maquinas do setor na forma de lista circular
void allocate_machine(packaging *p_sector, int size, int *list)
{
    p_sector->first = malloc(sizeof(machine));
    if (p_sector->first == NULL)
        exit(1);
    // aloca o primeiro elemento da lista na variavel first
    machine *tmp = p_sector->first;
    tmp->machine_t_id = list[0];
    tmp->product_t_id = -1;
    allocate_queue(tmp);
    for (int i = 1; i < size; i++) {
        tmp->next = malloc(sizeof(machine));
        if (tmp->next == NULL)
            exit(1);
        tmp = tmp->next;
        tmp->machine_t_id = list[i];
        tmp->product_t_id = -1;
        allocate_queue(tmp);
    }
    tmp->next = p_sector->first;
    gen_machine_cost(p_sector);
}

// aloca as filas das maquinas
void allocate_queue(machine *m)
{
    m->q = malloc(sizeof(queue));
    if (m->q == NULL)
        exit(1);
    m->q->size = 0;
    m->q->first = NULL;
}

// gera o custo da base das maquinas
void gen_machine_cost(packaging *p_sector)
{
    machine *tmp = p_sector->first;
    do {
        switch (tmp->machine_t_id) {
            case fp:
            case cp:
                tmp->cost = CP_COST;
                p_sector->cost += CP_COST;
                break;
            case ap:
                tmp->cost = CP_COST;
                p_sector->cost += AP_COST;
                break;
            case p:
                tmp->cost = P_COST;
                p_sector->cost += P_COST;
                break;
            case esa:
                tmp->cost = ESA_COST;
                p_sector->cost += ESA_COST;
                break;
            case u:
                tmp->cost = U_COST;
                p_sector->cost += U_COST;
                break;
        }
        tmp = tmp->next;
    } while (tmp != p_sector->first);
    sim(p_sector);
}

// loop da simulacao, que gera os produtos e os coloca na fila de producao, e depois executa a producao 
// ao sair do loop com lucro maior que o custo ou ao passar dois anos chama a funcao de saida
void sim(packaging *p_sector)
{ 
    for(;p_sector->cost > p_sector->profit && p_sector->time < TWO_YEARS; p_sector->time++) {
        // novos produtos chegam a cada dois segundos
        if (p_sector->time % 2 == 0)
            gen_queue(p_sector);
        machine *tmp = p_sector->first;
        do {
            process(p_sector, tmp);
            tmp = tmp->next;
        } while (tmp != p_sector->first);
    }
    end(&p_sector);
}

// gera um produto e coloca na fila de producao caso seja compativel com a maquina
// se nao, descarta o produto
void gen_queue(packaging *p_sector)
{
    int prod_type = gen_product();
    gen_product_cost(p_sector, prod_type);
    machine *tmp = p_sector->first;
    for (int i = 0; i < p_sector->size; i++) {
        if (tmp->q->size > tmp->next->q->size)
            tmp = tmp->next;
            if (!prod_fits_machine(prod_type, tmp))
                tmp = tmp->next;
    }
    if (prod_fits_machine(prod_type, tmp)) {
        gen_queue_prod(tmp, prod_type);
        tmp->q->size++;
        return;
    }
    handle_waste(p_sector, prod_type);
}

// gera um produto aleatorio baseado nas probabilidades
int gen_product()
{
    int x = rand() % 10;
    if (x > 4) // 50% -> 9 - 4 = 5;
        return c;
    else if (x > 1) // 30% -> 4 - 1 = 3;
        return f;
    return mb;
}

// checa se o produto e compativel com a maquina
bool prod_fits_machine(int prod_type, machine *m)
{
    if (prod_type == c && m->machine_t_id != 0)
        return true;
    if (prod_type == f && m->machine_t_id != 1)
        return true;
    if (prod_type == mb && m->machine_t_id != 0 && m->machine_t_id != 1)
        return true;
    return false;
}

// coloca o produto no lugar correto na fila de producao
void gen_queue_prod(machine *m, int prod_type)
{
    queue *q_tmp = m->q;
    // caso seja o primeiro produto da fila
    if (q_tmp->size == 0) {
        q_tmp->first = allocate_prod(prod_type);
        return;
    }
    product *p_tmp = q_tmp->first;
    while (p_tmp->next != NULL)
        p_tmp = p_tmp->next;
    p_tmp->next = allocate_prod(prod_type);
}

// gera o tempo de vencimento do produto
int get_prod_exp_time(int prod_type)
{
    switch (prod_type) {
        case c:
            return CHICKEN_TIME;
        case f:
            return FISH_TIME;
        case mb:
            return MEATBALL_TIME;
    }
}

// aloca um produto 
product *allocate_prod(int prod_type)
{
    product *tmp = malloc(sizeof(product));
    if (tmp == NULL)
        exit(1);
    tmp->time_to_exp = get_prod_exp_time(prod_type);
    tmp->product_t_id = prod_type;
    tmp->next = NULL;
    return tmp;
}

// gera o custo do produto
void gen_product_cost(packaging *p_sector, int prod_type)
{
    if (prod_type == c)
        p_sector->cost += CHICKEN_COST / (double) 100;
    else if (prod_type == f)
        p_sector->cost += FISH_COST / (double) 100;
    else
        p_sector->cost += MEATBALL_COST / (double) 100;
}

// processa o produto na fila de producao, removendo da fila se estiver vazia
// removendo da maquina se pronto e removendo da fila, atualiza o tempo dos produtos
// e gera o custo energetico de cada maquina
void process(packaging *p_sector, machine *m)
{
    if (m->q->size != 0) {
        if (m->product_t_id == -1)
            remove_prod_queue(p_sector, m);
        else if (m->time_prod_done <= p_sector->time) {
            remove_prod_machine(p_sector, m);
            remove_prod_queue(p_sector, m);
        }
        update_prod_time(m);
    }
    gen_e_cost(p_sector, m);
}

// atualiza o tempo de vencimento do produto
void update_prod_time(machine *m)
{
    product *tmp_prod = m->q->first;
    while (tmp_prod != NULL) {
        tmp_prod->time_to_exp--;
        tmp_prod = tmp_prod->next;
    }
}

// remove o produto da fila de producao
void remove_prod_machine(packaging *p_sector, machine *m)
{
    handle_done(p_sector, m->product_t_id);
    m->product_t_id = -1;
}

// adiciona as informações de produto pronto no setor
void handle_done(packaging *p_sector, int prod_type)
{
    if (prod_type == c) {
        p_sector->c_done++;
        p_sector->profit += CHICKEN_PRICE / (double) 100;
    } else if (prod_type == f) {
        p_sector->f_done++;
        p_sector->profit += FISH_PRICE / (double) 100;
    } else {
        p_sector->mb_done++;
        p_sector->profit += MEATBALL_PRICE / (double) 100;
    }
}

// remove o produto da fila de producao se estiver vencido e desaloca o produto
void remove_exp_products(packaging *p_sector, machine *m)
{
    if (m->q->size == 0)
        return;

    product *tmp = m->q->first;
    // caso o produto vencido esteja na first da queue
    do {
        if (tmp->time_to_exp <= 0)
        {
            m->q->first = tmp->next;
            handle_waste(p_sector, tmp->product_t_id);
            free(tmp);
            m->q->size--;
        }
        tmp = m->q->first;
        if (tmp == NULL)
            return;
    } while(tmp->time_to_exp <= 0);

    for (int i = 0; i <= m->q->size; i++)
    {
        if (tmp->next == NULL)
            return;
        if (tmp->next->time_to_exp <= 0) {
            product *tmp2 = tmp->next->next;
            handle_waste(p_sector, tmp->next->product_t_id);
            free(tmp->next);
            tmp->next = tmp2;
            m->q->size--;
        }
    }
}

// remove os vencidos, remove da fila e coloca na maquina e desaloca a struct do produto
void remove_prod_queue(packaging *p_sector, machine *m) 
{
    remove_exp_products(p_sector, m);
    product *tmp_p = m->q->first;
    if (m->q->size == 0)
        return;
    
    m->product_t_id = tmp_p->product_t_id;
    m->time_prod_arr = p_sector->time;
    if (m->q->size == 1)
        m->q->first = NULL;
    else
        m->q->first = m->q->first->next;
    m->q->size--;
    free(tmp_p);
    gen_machine_done_time(m, p_sector->time);
}

// coloca informações de produtos descartados do setor
void handle_waste(packaging *p_sector, int prod_type)
{
    if (prod_type == c)
        p_sector->c_wasted++;
    else if (prod_type == f)
        p_sector->f_wasted++;
    else
        p_sector->mb_wasted++;
}

// gera o tempo ate o produto ficar pronto
void gen_machine_done_time(machine *m, int time_offset)
{
    // se maquinar for allpak
    if (m->machine_t_id == ap) {
       int ap_done_time;
        if (m->product_t_id == c)
            ap_done_time = AP_CHICKEN_TIME;
        else if(m->product_t_id == f)
            ap_done_time = AP_FISH_TIME;
        else
            ap_done_time = AP_MEATBALL_TIME;
        
        m->time_prod_done = time_offset + ceil(ap_done_time * ml_10());
        return;
    }
    switch (m->machine_t_id) {
        case fp:
            m->time_prod_done = time_offset + ceil(FP_TIME * ml_10());
            return;
        case cp:
            m->time_prod_done = time_offset + ceil(CP_TIME * ml_10());
            return;
        case p:
            m->time_prod_done = time_offset + ceil(P_TIME * ml_10());
            return;
        case esa:
            m->time_prod_done = time_offset + ceil(ESA_TIME * ml_10());
            return;
        case u:
            m->time_prod_done = time_offset + ceil(U_TIME * ml_10());
            return;                                               
    }
}

// 10% +-
float ml_10()
{
    int n = rand() % 3;
    if (n == 0)
        return 0.9;
    if (n == 1)
        return 1;
    return 1.1;
}

// gera o custo energetico da maquina
void gen_e_cost(packaging *p_sector, machine *m)
{
    switch (m->machine_t_id) {
        case fp:
        case cp:
            m->cost += FP_E_CONS / (double) HOUR_SEC;
            p_sector->cost += FP_E_CONS / (double) HOUR_SEC;
            break;
        case ap:
            m->cost += AP_E_CONS / (double) HOUR_SEC;
            p_sector->cost += AP_E_CONS / (double) HOUR_SEC;
            break;
        case p:
            m->cost += P_E_CONS / (double) HOUR_SEC;
            p_sector->cost += P_E_CONS / (double) HOUR_SEC;
            break;
        case esa:
            m->cost += ESA_E_CONS / (double) HOUR_SEC;
            p_sector->cost += ESA_E_CONS / (double) HOUR_SEC;
            break;
        case u:
            m->cost += U_E_CONS / (double) HOUR_SEC;
            p_sector->cost += U_E_CONS / (double) HOUR_SEC;
            break;
    }
}

// funcao de saida
void end(packaging **p_sector)
{
    print(*p_sector);
    free_sim(p_sector);
}

// printa todas as informações relevantes da simulação
void print(packaging *p_sector)
{
    printf("\n-----------------------------------\n");
    printf("Tempo total: %i segundos.\n", p_sector->time);
    if (p_sector->time < TWO_YEARS / 2)
        printf("Esse tempo foi menor que um ano.\n");
    else if (p_sector->time < TWO_YEARS)
        printf("Esse tempo foi menor que dois anos.\n");
    else
        printf("Esse tempo é dois anos.\n");
    
    printf("\nTotal de gastos: R$%.2lf\nTotal de ganhos: R$%.2lf\n", p_sector->cost, p_sector->profit);
    printf("Total de lotes empacotados: %i\nTotal de lotes descartados: %i\n", (p_sector->c_done + p_sector->f_done + p_sector->mb_done), (p_sector->c_wasted + p_sector->f_wasted + p_sector->mb_wasted));
    
    printf("\nCOXINHAS:\n");
    printf("Total de coxinhas empacotadas: %i, total de coxinhas descartadas: %i\n", p_sector->c_done, p_sector->c_wasted);
    printf("O gasto com coxinhas foi de: R$%.2f\nO ganho com coxinhas foi de: R$%.2f\n", (p_sector->c_wasted + p_sector->c_done) * CHICKEN_COST / (double) 100, p_sector->c_done * CHICKEN_PRICE / (double) 100);

    printf("\nPEIXE:\n");
    printf("Total de peixes empacotados: %i, total de peixes descartados: %i\n", p_sector->f_done, p_sector->f_wasted);
    printf("O gasto com peixe foi de: R$%.2f\nO ganho com peixe foi de: R$%.2f\n", (p_sector->f_wasted + p_sector->f_done) * FISH_COST / (double) 100, p_sector->f_done * FISH_PRICE / (double) 100);

    printf("\nALMONDEGA:\n");
    printf("Total de almondegas empacotadas: %i, total de almondegas descartadas: %i\n", p_sector->mb_done, p_sector->mb_wasted);
    printf("O gasto com almondegas foi de: R$%.2f\nO ganho com almondegas foi de: R$%.2f\n", (p_sector->mb_wasted + p_sector->mb_done) * MEATBALL_COST / (double) 100, p_sector->mb_done * MEATBALL_PRICE / (double) 100);

    printf("\nMAQUINAS:\n");
    for (int i = 0; i < p_sector->size; i++, p_sector->first = p_sector->first->next)
        printf("O gasto da maquina %i do tipo %s foi de: R$%.2lf\n", i + 1, get_machine_name(p_sector->first), p_sector->first->cost);
}

// retorna o nome da maquina
char *get_machine_name(machine *m)
{
    switch(m->machine_t_id) {
        case fp:
            return "FishPak";
        case cp:
            return "chickenPak";
        case ap:
            return "AllPak";
        case p:
            return "Plastific";
        case esa:
            return "EnSacAll";
        case u:
            return "Universal";
    }
    return "";
}

// libera a memoria alocada para a simulação
void free_sim(packaging **p_sector)
{
    free_machine(&(*p_sector)->first);
    free(*p_sector);
    *p_sector = NULL;
}

// libera a memoria alocada para fila
void free_queue(queue **q)
{   
    product *free_p = (*q)->first;
    while (free_p != NULL)
    {
        product *tmp_p = free_p->next;
        free(free_p);
        free_p = tmp_p;
    }
    free(*q);
    *q = NULL;
}

// libera a memoria alocada para maquina
void free_machine(machine **m)
{
    machine *tmp_m = *m;
    do {
        free_queue(&tmp_m->q);
        machine *free_m = tmp_m;
        tmp_m = tmp_m->next;
        free(free_m);
    } while (tmp_m != *m);
    *m = NULL;
}