	.data
array:	.word	7,6,5,9,8
size:	.word	5
maxS: .asciiz  "Maximum:"
next: .asciiz  "\n"
minS: .asciiz  "Minimum:"
aveS: .asciiz  "Average:"
	.text
	la   $s0, array
	la   $s4, size
	lw   $s5, 0($s0)
	lw   $s6, 0($s0)
	li   $s7, 0
	lw   $s1, 0($s4)
	li   $s4, 0
loop:	lw   $s3, 0($s0)
	add  $s7, $s7, $s3
	sub  $s4, $s3, $s6
	bgtz $s4, bigger
	sub  $s4, $s3, $s5
	bltz $s4, less
	j finish
bigger: move $s6, $s3
	j finish
less:	move $s5, $s3
finish: sub  $s1, $s1, 1
	addi $s0, $s0, 4
	bgtz $s1, loop
print:	add  $t0, $zero, $a0  # starting address of array of data to be printed
	add  $t1, $zero, $a1  # initialize loop counter to array size
	la   $a0, maxS        # load address of the print heading string
	li   $v0, 4          # specify Print String service
	syscall          
	move $a0, $s6     
	li   $v0, 1          
	syscall 
	la   $a0, next      
	li   $v0, 4         
	syscall  
	la   $a0, minS  
	li   $v0, 4        
	syscall          
	move $a0, $s5     
	li   $v0, 1          
	syscall 
	la   $a0, next
	li   $v0, 4         
	syscall  
	la   $a0, aveS   
	li   $v0, 4      
	syscall          
	move $a0, $s5 
	la   $s1, size
	lw   $s1, 0($s1)
	div  $a0, $s7, $s1
	li   $v0, 1          
	syscall 
