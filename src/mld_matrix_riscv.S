#include "mld_matrix.h"
#include "mld_asmdefs.h"
#include "mld_common.h"
#include "mld_matrix_macros_riscv.S"

	.section .data
fmt_newline:
	.string "\n"

fmt_print_i64:
	.string "%d "

	.section .text	

// Create matrix MldMatrixInt64 with size rows * columns
//
// Parameters:
// 	a0 - holds rows value to create matrix, input parameter
// 	a1 - holds columns value to create matrix, input parameter
//	a2 - holds MldMatrix pointer to initialize, in-out parameter
//
// Valid Usage:
// 	* a0 must be greater than 0
// 	* a1 must be greater than 0
//	* a2 must be not NULL address
//
// Return Codes:
// 	* On success, this command returns:
//	    - MLD_SUCCESS 
//	* On failurre, this command returns:
//	    - MLD_INVALID_ARGUMENT
//	    - MLD_UNABLE_TO_ALLOCATE_MEMORY
ENTRY(mldCreateMatrixInt64)	
	addi	sp, sp, -48
	sd	ra, 40(sp)
	sd	fp, 32(sp)
	sd	s1, 24(sp)
	sd	s2, 16(sp)
	sd	s3, 8(sp)
	addi	fp, sp, 48

	// Validate input arguments
	blez	a0, L(arg_err)
	blez	a1, L(arg_err)
	blez	a2, L(arg_err)

	// Reserve input arguments to save registers
	mv	s1, a0
	mv	s2, a1
	mv	s3, a2

	// Allocate memory for matrix array with size
	// rows * columns * 8 (64 bit size)
	mul	a0, s1, s2
	li	a1, 8
	call	calloc

	// Check allocated memory on NULL
	beqz	a0, L(mem_err)

	// Save rows, columns and allocated array to MldMatrix output parameter
	mul	t0, s1, s2
	sd	t0, MLD_MATRIX_LENGTH_OFFSET(s3)
	sd	a0, MLD_MATRIX_ARRAY_OFFSET(s3)
	sd	s1, MLD_MATRIX_ROWS_OFFSET(s3)
	sd	s2, MLD_MATRIX_COLUMNS_OFFSET(s3)

	li	a0, MLD_SUCCESS
	mv	a1, s3
	
L(out):
	ld	ra, 40(sp)
	ld	fp, 32(sp)
	ld	s1, 24(sp)
	ld	s2, 16(sp)
	ld	s3, 8(sp)
	addi	sp, sp, 48
	ret

L(mem_err):
	li	a0, MLD_UNABLE_ALLOCATE_MEMORY
	j	L(out)

L(arg_err):
	li	a0, MLD_INVALID_ARGUMENT
	j	L(out)
END(mldCreateMatrixInt64)

// Gets matrix item of MldMatrixInt64 by row and column indexes
//
// Parameters:
// 	a0 - holds address of MldMatrixInt64
//	a1 - holds row index
//	a2 - holds column index
//
// Valid Usage:
// 	* a0 - must be valid address of MldMatrixInt64
//	* a1 - row index must be greater than 0
//	* a2 - column index must be greater that 0
//
// Returns:
//	* Matrix value by index row and column
ENTRY(mldGetItemMatrixInt64)
	ld	t0, MLD_MATRIX_ARRAY_OFFSET(a0)
	ld	t1, MLD_MATRIX_COLUMNS_OFFSET(a0)
	mul	t2, a1, t1
	add	t2, t2, a2
	sll	t2, t2, 3
	add	t3, t0, t2
	ld	a0, 0(t3)
	ret
END(mldGetItemMatrixInt64)

// Sets matrix item of MldMatrixInt64 by row and column indexes
//
// Parameters:
// 	a0 - holds address of MldMatrixInt64
//	a1 - holds row index
//	a2 - holds column index
//	a3 - holds value to store
//
// Valid Usage:
// 	* a0 - must be valid address of MldMatrixInt64
//	* a1 - row index must be greater than 0
//	* a2 - column index must be greater that 0
ENTRY(mldSetItemMatrixInt64)
	ld	t0, MLD_MATRIX_ARRAY_OFFSET(a0)
	ld	t1, MLD_MATRIX_COLUMNS_OFFSET(a0)
	mul	t2, a1, t1
	add	t2, t2, a2
	sll	t2, t2, 3
	add	t3, t0, t2
	sd	a3, 0(t3)
	ret
END(mldSetItemMatrixInt64)

// Sets matrix item of MldMatrixInt64 by row and column indexes
//
// Parameters:
// 	a0 - holds address of left MldMatrixInt64 (MldMatrixInt64*)
//	a1 - holds address of right MldMatrixInt64 (MldMatrixInt64*)
//	a2 - holds address to address of output MldMatrixInt64
//	     (MldMatrixInt64**)
//
// Valid Usage:
// 	* a0 - must be valid address of MldMatrixInt64
//	* a1 - must be valid address of MldMatrixInt64
//	* a2 - must be valid address of MldMatrixInt64
//	* Rows left and right matrices must be the same
//	* Columns left and right matrices must be the same
//
// Return Codes:
// 	* On success, this command returns:
//	    - MLD_SUCCESS 
//	* On failurre, this command returns:
//	    - MLD_INVALID_ARGUMENT
//	    - MLD_UNABLE_TO_ALLOCATE_MEMORY
ENTRY(mldAddMatrixInt64)
	addi	sp, sp, -48
	sd	s0, 0(sp)
	sd	ra, 8(sp)
	sd	s1, 16(sp)
	sd	s2, 24(sp)
	sd	s3, 32(sp)

	mv	s0, a0  
	mv	s1, a1
	mv	s2, a2

	li	a0, MLD_MATRIX_SIZE
	call	malloc

	// Create output MldMatrixInt64
	mv	a2, a0
	ld	a0, MLD_MATRIX_ROWS_OFFSET(s0)
	ld	a1, MLD_MATRIX_COLUMNS_OFFSET(s0)
	call	mldCreateMatrixInt64
	mv	s3, a1

	li	t4, 0		// i-counter
	ld	t5, MLD_MATRIX_LENGTH_OFFSET(s0)
0:
	beq	t4, t5, 1f

	// Get element of left matrix
	mv	a0, s0
	mv	a1, t4
	mldGetItemByIdxMatrixInt64Inline
	mov	t6, a0

	// Get element of right matrix
	mv	a0, s1
	mv	a1, t4
	mldGetItemByIdxMatrixInt64Inline
	mov	a3, a0

	mv	a0, s3
	mv	a1, t4
	add	a2, t6, a3
	mldSetItemByIdxMatrixInt64Inline

	addi	t0, t0, 1
	j	0b
1:
	ld	s0, 0(sp)
	ld	ra, 8(sp)
	ld	s1, 16(sp)
	ld	s2, 24(sp)
	ld	s3, 32(sp)
	addi	sp, sp, 48
	ret
END(mldAddMatrixInt64)

// Prints matrix of MldMatrixInt64
//
// Parameters:
// 	a0 - holds address of MldMatrixInt64
//
// Valid Usage:
// 	* a0 must be valid address of MldMatrixInt64
//
// Return Codes:
// 	* On success, this command returns:
//	    - MLD_SUCCESS 
//	* On failurre, this command returns:
//	    - MLD_INVALID_ARGUMENT
ENTRY(mldPrintMatrixInt64)
	addi	sp, sp, -64
	sd	s1, 56(sp)
	sd	s2, 48(sp)
	sd	s3, 40(sp)
	sd	s4, 32(sp)
	sd	s5, 24(sp)
	sd	s6, 16(sp)
	sd	ra, 8(sp)
	sd	fp, 0(sp)

	mv	s1, a0
	ld	s2, MLD_MATRIX_ROWS_OFFSET(s1)
	ld	s3, MLD_MATRIX_COLUMNS_OFFSET(s1)
	ld	s4, MLD_MATRIX_ARRAY_OFFSET(s1)

	li	s5, 0			// i-counter
1:
	beq	s2, s5, 4f		// rows == i then end rows walk
	li	s6, 0			// j-counter
2:
	beq	s6, s3,	3f		// columns == j then end column walk

	// Print array[i * columns + j]
	mul	t0, s5, s3		// t0 = i * columns
	add	t0, t0, s6		// t0 = t0 + j
	sll	t0, t0, 3		// t0 = t0 << 3
	add	t0, s4, t0		// t0 = array_addr + t0

L(rel):
	auipc	a0, %pcrel_hi(fmt_print_i64)
	addi	a0, a0, %pcrel_lo(L(rel))
	ld	a1, 0(t0)
	call	printf

	addi	s6, s6, 1		// j++, next column
	j	2b
3:
	auipc	a0, %pcrel_hi(fmt_newline)
	addi	a0, a0, %pcrel_lo(3b)
	call	printf
	addi	s5, s5, 1		// i++, next row
	j	1b
4:
	ld	fp, 0(sp)
	ld	ra, 8(sp)
	ld	s6, 16(sp)
	ld	s5, 24(sp)
	ld	s4, 32(sp)
	ld	s3, 40(sp)
	ld	s2, 48(sp)
	ld	s1, 56(sp)
	addi	sp, sp, 64
	ret
END(mldPrintMatrixInt64)
