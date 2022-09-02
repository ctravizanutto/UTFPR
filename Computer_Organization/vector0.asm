.data:
	A: .word 1, 1, 2, 3, 4, 5, 6, 7, 8, 9
	A_size: .word 10
	endl: .asciiz "\n"

.macro new_line
	li $v0, 4
	la $a0, endl
	syscall
.end_macro

.text:
_main:
	la $s0, A
	
	jal _sum
	add $a0, $zero, $v0
	li $v0, 1		# print result from sum
	syscall
	new_line
	
	jal _sub
	add $a0, $zero, $v0
	li $v0, 1		# print result from sum
	syscall
	new_line
	
	jal _mul
	add $a0, $zero, $v0
	li $v0, 1		# print result from sum
	syscall
		
	li $v0, 10		# exits
	syscall
	
_sum:
	li $v0, 0
	lw $t0, A_size 
	
	sum_loop:
		lw $t1, ($s0)		# loads value from vector to t1
		add $v0, $v0, $t1	# adds to v0
		la $s0, 4($s0)		# vector jumps to next value
		subi $t0, $t0, 1	# iterates
		bnez $t0, sum_loop	# if t0 != 10 jumps to loop
	
	la $s0, A
	jr $ra
		
_sub:
	addi $v0, $zero, 0
	lw $t0, A_size 
	
	sub_loop:
		lw $t1, ($s0)		# loads value from vector to t1
		sub $v0, $v0, $t1	# subs to v0
		la $s0, 4($s0)		# vector jumps to next value
		subi $t0, $t0, 1	# iterates
		bnez $t0, sub_loop	# if t0 != 10 jumps to loop
	
	la $s0, A
	jr $ra
	
_mul:
	addi $v0, $zero, 1
	lw $t0, A_size 
	
	mul_loop:
		lw $t1, ($s0)		# loads value from vector to t1
		mul $v0, $v0, $t1	# mult to v0
		la $s0, 4($s0)		# vector jumps to next value
		subi $t0, $t0, 1	# iterates
		bnez $t0, mul_loop	# if t0 != 10 jumps to loop
	
	la $s0, A
	jr $ra
	