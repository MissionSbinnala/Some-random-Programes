	.data
MESG1:	.asciiz	"Enter the length of array A:"
MESG2:	.asciiz	"Input array A:"
MESG3:	.asciiz	"Enter the length of array B:"
MESG4:	.asciiz	"Input array B:"
MESG5:	.asciiz	"Length of the Longest Common Subsequence:"
MESG6:	.asciiz	"Longest Common Subsequence:"
ENTER:	.asciiz	"\n"
SPACE:	.asciiz	" "
	.text
	la	$a0, MESG1       # load address of spacer for syscall
	li	$v0, 4           # specify Print String service
	syscall
	li 	$v0, 5
	syscall
	move 	$s0, $v0
	move 	$s4, $v0
	li 	$v0, 9           # 使用系统调用功能号9表示申请内存
    	move 	$a0, $s4        # 要申请的内存大小存储在$a0寄存器中
   	syscall    
   	move	$s1, $v0
   	move	$s5, $v0
	jal	Input
	move	$s3, $s5
	la	$a0, MESG2       # load address of spacer for syscall
	li	$v0, 4           # specify Print String service
	syscall
	li 	$v0, 5
	syscall
	move 	$s2, $v0
	move 	$s4, $v0
	jal	Input
	li	$s4, 0
	li	$s5, 0
	li	$t3, 0
	li	$t4, 0
	li	$t5, 0
	li	$t6, 0
	move	$t1, $s1
	move	$t2, $s3
comp:	
	bge	$s4, $s0, array1_ends
	bge	$s5, $s2, array2_ends
	lw	$s7, 0($t1)
	lw	$t7, 0($t2)
	bne	$s7, $t7 diff
same:	addi	$t1, $t1, 4
	addi	$t2, $t2, 4
	addi	$t3, $t3, 1
	addi	$s5, $s5, 1
	blt	$t3, $t4, comp
more:	move	$t4, $t3
	move	$t6, $t5
	j	comp
diff:	sll	$t7, $s4, 2
	add	$t1, $s1, $t7
	addi	$t2, $t2, 4
	addi	$s5, $s5, 1
	li	$t3, 0
	move	$t5, $s5
	j	comp
array2_ends:	move	$t2, $s2
		addi	$s4, $s4, 1
		sll	$t7, $s4, 2
		move	$t1, $s1
		add	$t1, $t1, $t7
		move	$s5, $s4
		move	$t2, $s3
		li	$t3, 0
		j	comp
array1_ends:	
		la	$a0, MESG3       # load address of spacer for syscall
		li	$v0, 4           # specify Print String service
		syscall
		move	$a0, $t4       # load address of spacer for syscall
		li	$v0, 1           # specify Print String service
		syscall
		la	$a0, ENTER       # load address of spacer for syscall
		li	$v0, 4           # specify Print String service
		syscall
		move	$s6, $s3
		la	$a0, MESG4       # load address of spacer for syscall
		li	$v0, 4           # specify Print String service
		syscall
output:		lw	$a0, 0($s6)
		li	$v0, 1
		syscall
		la	$a0, SPACE       # load address of spacer for syscall
		li	$v0, 4           # specify Print String service
		syscall
		subi	$t4, $t4, 1
		addi	$s6, $s6, 4
		bgtz	$t4, output
		li   $v0, 10          # system call for exit
		syscall               # Exit!
###############################################################
# Subroutine to print the numbers on one line.
      .text   	
Input:	li 	$v0, 5
	syscall
	sw	$v0, 0($s5)
	addi	$s5, $s5, 4
	addi	$s4, $s4, -1
	bgtz	$s4, Input
	
      
      	jr   $ra              # return from subroutine
# End of subroutine to print the numbers on one line
###############################################################