# testing Memory operations

addi $t0, $zero, 0 # adding 0 to t0
addi $t1, $zero, 7 # setting t1 equal to 7

sw $t1, 0($t0) #storing t1 in t0 address 
lw $t2, 0($t0) #loading value in t0 address to t2

addi $v0, $zero, 1 #printing syscall
add  $a0, $t2, $zero #printing the value in t2 (so in this case 7)
syscall

addi $v0, $zero, 10 # exit
syscall