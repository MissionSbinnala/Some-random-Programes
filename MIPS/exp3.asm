	.data
array:	.word	3, 10, 8, 6, 5, 4, 9
size:	.word	7
MESG1: .asciiz  "old array:\n"
ENTER: .asciiz  "\n"
MESG2: .asciiz  "new array:\n"
space: .asciiz  " "
	.text
	la   $s6, size
	lw   $s7, 0($s6)
	addi $s7, $s7, -1
	addi $s1, $s1, 4
	la   $s4, array
	la   $a0, MESG1        # load address of the print heading string
	li   $v0, 4          # specify Print String service
	syscall
	la   $s6, size
	lw   $s6, 0($s6)
	la   $s0, array
print1:	lw   $a0, 0($s0)      # load the integer to be printed (the current Fib. number)
      	li   $v0, 1           # specify Print Integer service
      	syscall               # print fibonacci number
      	la   $a0, space       # load address of spacer for syscall
	li   $v0, 4           # specify Print String service
	syscall
      	addi $s6, $s6, -1
      	addi $s0, $s0, 4
      	bgtz $s6, print1
      	la   $a0, ENTER       # load address of spacer for syscall
	li   $v0, 4           # specify Print String service
	syscall
loop1:	move $s6, $s7
	move $s0, $s4
	move $s1, $s4
	addi $s1, $s1, 4
loop2:	lw   $s2, 0($s0)
	lw   $s3, 0($s1)
	sub  $s5, $s2, $s3
	bltz $s5, finish
	sw   $s2, 0($s1)
	sw   $s3, 0($s0)
finish: sub  $s6, $s6, 1
	addi $s0, $s0, 4
	addi $s1, $s1, 4
	bgtz $s6, loop2
	subi $s7, $s7, 1
	bgtz $s7, loop1
	la   $a0, MESG2        # load address of the print heading string
	li   $v0, 4          # specify Print String service
	syscall
	la   $s6, size
	lw   $s6, 0($s6)
	la   $s0, array
print2:	lw   $a0, 0($s0)      # load the integer to be printed (the current Fib. number)
      	li   $v0, 1           # specify Print Integer service
      	syscall               # print fibonacci number
      	la   $a0, space       # load address of spacer for syscall
	li   $v0, 4           # specify Print String service
	syscall
      	addi $s6, $s6, -1
      	addi $s0, $s0, 4
      	bgtz $s6, print2
      	li   $v0, 10          # system call for exit
	syscall               # Exit!



      
      
