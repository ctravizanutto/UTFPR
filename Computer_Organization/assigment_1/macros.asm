.macro open_file (%file_name, %flags) # returns fd at $a0
	li   $v0, 13
	la   $a0, %file_name
	li   $a1, %flags				  # 0 - read; 1 - write
	syscall
	move $a0, $v0
.end_macro

.macro read_file (%fd, %buffer, %len)
	li   $v0, 14
	move $a0, %fd
	la $a1, (%buffer)
	la   $a2, (%len)
	syscall
.end_macro

.macro read_filer (%fd, %buffer, %len)
	li   $v0, 14
	move $a0, %fd
	move $a1, (%buffer)
	move   $a2, (%len)
	syscall
.end_macro

.macro write_file (%fd, %buffer, %len)
	li   $v0, 15
	move $a0, %fd
	la   $a1, %buffer
	li   $a2, %len
	syscall
.end_macro

.macro write_filer (%fd, %buffer, %len)
	li   $v0, 15
	move $a0, %fd
	move   $a1, %buffer
	move   $a2, %len
	syscall
.end_macro

.macro close_file (%fd)
	li   $v0, 16
	move $a0, %fd
	syscall
.end_macro

.macro for (%iterator, %from, %to, %func)
	li %iterator, %from
	lw $t9, %to
	addi $t9, $t9, -1
	loop:
		jal	 %func
		addi %iterator, %iterator, 1
		bne  %iterator, $t9, loop
.end_macro

.macro print_msg(%msg)
	la $a0, %msg
	li $v0 4
	syscall
.end_macro

.macro end_program
	li $v0, 10
	syscall
.end_macro

.macro read_int
	li $v0, 5
	syscall
.end_macro

.macro print_int(%int)
	lw $a0, %int
	li $v0, 1
	syscall
.end_macro

