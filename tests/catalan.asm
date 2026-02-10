############################
# main
############################
main:
    addi $a0, $zero, 5
    jal fun

    add  $a0, $v0, $zero
    addi $v0, $zero, 1
    syscall

    addi $v0, $zero, 10
    syscall


############################
# int fun(int n)
############################
fun:
    addi $sp, $sp, -24
    sw   $ra, 20($sp)
    sw   $a0, 16($sp)
    sw   $s0, 12($sp)
    sw   $s1, 8($sp)
    sw   $s2, 4($sp)
    sw   $s3, 0($sp)

    lw   $t0, 16($sp)
    beq  $t0, $zero, base

    addi $s0, $zero, 0
    addi $s1, $zero, 0
    sw   $s1, 8($sp)       # store i

loop:
    lw   $t0, 16($sp)      # n
    lw   $t1, 8($sp)       # i
    beq  $t1, $t0, loop_end

    # x = fun(i)
    add  $a0, $t1, $zero
    jal  fun
    add  $s2, $v0, $zero

    # y = fun(n - 1 - i)
    lw   $t0, 16($sp)
    addi $t0, $t0, -1
    lw   $t1, 8($sp)
    sub  $t0, $t0, $t1
    add  $a0, $t0, $zero
    jal  fun
    add  $s3, $v0, $zero

    # sum += x * y
    mul  $t2, $s2, $s3
    add  $s0, $s0, $t2

    # i++
    lw   $t1, 8($sp)
    addi $t1, $t1, 1
    sw   $t1, 8($sp)
    j loop

loop_end:
    add  $v0, $s0, $zero
    j end

base:
    addi $v0, $zero, 1

end:
    lw   $s3, 0($sp)
    lw   $s2, 4($sp)
    lw   $s1, 8($sp)
    lw   $s0, 12($sp)
    lw   $a0, 16($sp)
    lw   $ra, 20($sp)
    addi $sp, $sp, 24
    jr   $ra