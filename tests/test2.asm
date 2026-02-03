# Tests if a number can be taken as input and printed back

addi $v0, $zero, 5 # reading in the input in v0
syscall            # execute syscall to read integer

add $t0, $v0, $zero # storing input value in temporary register t0

addi $v0, $zero, 1  # print integer = syscall (1)
add  $a0, $t0, $zero # move value from $t0 to $a0 (argument register)
syscall             # execute syscall to print integer as it prints the value in a0

addi $v0, $zero, 10 # set syscall code to 10 (exit program)
syscall             # execute syscall to exit
