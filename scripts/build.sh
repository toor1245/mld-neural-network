#
# Script to build project without build system to investigate corectness of program
#

clang -Iinclude -g -O0 -c src/mld_matrix_riscv.S -o build/mld_matrix_riscv.S.o
clang -Iinclude -g -O0 -c src/main.S -o build/main.S.o
clang -g -O0 -o mld_mnist build/mld_matrix_riscv.S.o build/main.S.o
