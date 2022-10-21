#	$s0 input buffer
#	$s1 output buffer
#	$s2 header offster
# 	$s7 file size

#	$t8 iterator
#	$t9 to




.globl main
.include "macros.asm"


.data
	file_out:   	.asciiz "output_pgm/output.pgm"
  	file_in:	.asciiz "input_pgm/file001.pgm"
	msg0: 		.asciiz "Todas as imagens devem estar em um diretório input_pgm na pasta raiz do MARS e com nome formatado em conforme file_in"	
	msg1:		.asciiz "\nNùmero de arquivos: "
	msg2:		.asciiz "\nLargura das imagens: "
	msg3:		.asciiz "\nAltura das imagens: "
	
	n_files:	.word 0	# n de arquivos
	files_w: 	.word 0 # largura da imagem
	files_h:	.word 0 # altura da imagem
	dir_size:	.word 16 # offset para mudar o numero do arquivo de entrada

.text
main:
	# printa as mensagems de inicio e prompta o usuario por input
	print_msg(msg0) 
	print_msg(msg1)
	read_int
#	addi $v0, $v0, -1
	sw $v0, n_files
	
	print_msg(msg2)
	read_int
	sw $v0, files_w
	
	print_msg(msg3)
	read_int
	sw $v0, files_h
	
	# cria buffer para a entrada e saida dos arquivos
	jal create_buffer
	
	# lida com o primeiro arquivo de entrada, que diferente dos outros
	# (é lido no buffer de saida) 
	jal process_file0
	
	# parte que controla o header
	jal header_control
	
	# loop para abrir todos os arquivos e executa o  algoritmo de sáida
	for ($t8, 0, n_files, process_buffer)
	jal save_buffer_to_output
	
	end_program

create_buffer: # creates buffer at v0
	# multiplica os tamanhos da imagem para descobrir a "area" e aloca
	# buffer de entrada e saida tem mesmo tamanho
	lw $t0, files_w
	lw $t1, files_h
	mul $t0, $t0, $t1
	move $s7, $t0
	
	li $v0, 9
	move $a0, $t0
	syscall
	move $s0, $v0 # buffer de input
	
	li $v0, 9
	move $a0, $t0
	syscall
	move $s1, $v0 # buffer de output

	jr $ra


process_file0:
	open_file(file_in, 0)
	read_file($a0, $s1, $s7)         
	close_file($a0)
	jr $ra

header_control:
	nop 		# debug
	li $t0, 0	# contador de \n
	li $s2, 0	# offset do header
	loop_hc:
		lb $t1, ($s1)
		addi $s1, $s1, 1
		addi $s2, $s2, 1
		bne $t1, 0xa, else # if t0 == \n
			addi $t0, $t0, 1
		else:
		bne $t0, 4, loop_hc

	jr $ra

process_buffer:
	# (comeca pelo arquivo fileXXX + 1)
	# ele abre um arquivo e le o conteudo no buffer de entrada
	# ele pega o conteudo do buffer de saida byte a byte, e multiplica pelo numero de arquivos
	# lidos até agora - 1, soma com o byte do buffer de entrada
	# e divide pelo numero de arquivos lidos
	# e grava no buffer de saida
	addi $sp, $sp, -4
	sw $ra, ($sp)
	
	jal increase_file			
	
	open_file(file_in, 0)
	read_file($a0, $s0, $s7)
	close_file($a0)
	
	la $t6, ($s0)
	add $t6, $t6, $s2
	la $t7, ($s1)
	
	li $t4, 0
	sub $t5, $s7, $s2
	loop_pb:
		lb $t0, ($t6)
		lb $t1, ($t7)
		li $t2, 0
		li $t3, 0
		

		addi $t2, $t8, 1
		mul $t1, $t1, $t2
		
		add $t3, $t0, $t1
		addi $t2, $t2, 1
		div $t3, $t3, $t2
		sb $t3, ($t7)
		
		addi $t7, $t7, 1
		addi $t6, $t6, 1
		
		addi $t4, $t4, 1
		bne $t4, $t5, loop_pb	

	lw $ra, ($sp)
	addi $sp, $sp, 4
	jr $ra	

increase_file:
	# pula para a parte numerica da string do arquivo de entrada
	# e adiciona 1 de forma aritmetica
	la $t0, file_in 
	lw $t1, dir_size
	add $t0, $t0, $t1
	loop_if:
		lb $t1, ($t0)
		addi $t1, $t1, 1
		bne $t1, 0x3a, change_number     
		sub $t1, $t1, 10
		sb $t1, ($t0)
		subi $t0, $t0, 1
		j loop_if
	change_number:
		sb $t1, ($t0)

	jr $ra

save_buffer_to_output:
	sub $s1, $s1, $s2
	open_file(file_out, 1)
	write_filer($a0, $s1, $s7)
	close_file($a0)

	jr $ra
	

