.data
arr1:   .word 1, 2, 3, 4, 5          # 第一个数组
len1:   .word 5                      # 第一个数组长度
arr2:   .word 2, 4, 3, 5, 1          # 第二个数组
len2:   .word 5                      # 第二个数组长度
lcs:    .space 144                 # 用于存储动态规划表（6*6，因为长度+1）

.text
.globl main

main:
    # 加载数组长度
    la $t0, len1
    lw $t1, 0($t0)           # $t1 = len1
    la $t0, len2
    lw $t2, 0($t0)           # $t2 = len2
    
    # 初始化LCS表格
    la $t3, lcs              # $t3 指向 LCS 表格
    li $t4, 0
init_lcs:
    beq $t4, $t1_plus1, end_init_lcs
    li $t5, 0
init_lcs_inner:
    beq $t5, $t2_plus1, end_init_lcs_inner
    sw $zero, 0($t3)
    addi $t3, $t3, 4
    addi $t5, $t5, 1
    j init_lcs_inner
end_init_lcs_inner:
    addi $t4, $t4, 1
    j init_lcs
end_init_lcs:
    
    # 计算LCS
    la $t6, arr1
    li $t7, 1                # i = 1
outer_loop:
    bgt $t7, $t1, end_outer_loop
    la $t8, arr2
    li $t9, 1                # j = 1
inner_loop:
    bgt $t9, $t2, end_inner_loop
    
    # 读取 arr1[i-1] 和 arr2[j-1]
    lw $t10, 0($t6)
    lw $t11, 0($t8)
    beq $t10, $t11, match_case
    
    # 如果不相等，LCS[i][j] = max(LCS[i-1][j], LCS[i][j-1])
    la $t12, lcs
    mul $t13, $t7, $t2_plus1
    add $t13, $t13, $t9
    sub $t13, $t13, $t2_plus1
    lw $t14, 0($t12)  # LCS[i-1][j]
    
    la $t12, lcs
    mul $t13, $t7, $t2_plus1
    sub $t13, $t13, 1
    lw $t15, 0($t12)  # LCS[i][j-1]
    
    blt $t14, $t15, update_lcs
    sw $t14, 0($t12)
    j next_inner
update_lcs:
    sw $t15, 0($t12)
    j next_inner
    
match_case:
    # 如果相等，LCS[i][j] = LCS[i-1][j-1] + 1
    la $t12, lcs
    mul $t13, $t7, $t2_plus1
    sub $t13, $t13, $t2_plus1
    sub $t13, $t13, 1
    lw $t14, 0($t12)
    addi $t14, $t14, 1
    la $t12, lcs
    mul $t13, $t7, $t2_plus1
    add $t13, $t13, $t9
    sw $t14, 0($t12)
    
next_inner:
    addi $t8, $t8, 4
    addi $t9, $t9, 1
    j inner_loop
end_inner_loop:
    addi $t6, $t6, 4
    addi $t7, $t7, 1
    j outer_loop
end_outer_loop:

    # 结果存储在 LCS[len1][len2]
    la $t12, lcs
    mul $t13, $t1, $t2_plus1
    add $t13, $t13, $t2
    lw $t3, 0($t12)          # $t3 存储LCS的长度
    
    # 结束程序
    li $v0, 10               # 系统调用代码10（退出程序）
    syscall
