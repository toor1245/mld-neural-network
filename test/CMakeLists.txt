#
# add include for tests
#

include_directories(../include)

add_library(all_libraries
	../src/mld_matrix_i64_riscv.S
)

#
# tests
#
link_libraries(gtest gmock_main)

##------------------------------------------------------------------------------
## mld_matrix_i64_riscv_test.cc 
add_executable(mld_matrix_i64_riscv_test mld_matrix_i64_riscv_test.cc)
target_link_libraries(mld_matrix_i64_riscv_test all_libraries)
add_test(NAME mld_matrix_i64_riscv_test COMMAND mld_matrix_i64_riscv_test)
