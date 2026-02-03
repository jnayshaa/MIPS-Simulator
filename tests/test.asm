# Tests if print works

# print 42
addi $v0, $zero, 1   # syscall code 1: print_int
addi $a0, $zero, 42  # value to print
syscall

# exit
addi $v0, $zero, 10 # exit code = 10
syscall