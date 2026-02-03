# Testing if it can perform arthematic

addi $t0, $zero, 7 
addi $t1, $zero, 3
add  $t2, $t0, $t1 #adding 7 and 3 that were stored in t0 and t1 registers and storing to t2

addi $v0, $zero, 1 # print syscall
add  $a0, $t2, $zero
syscall

addi $v0, $zero, 10
syscall
