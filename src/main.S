#include "mld_matrix.h"
#include "mld_asmdefs.h"
#include "mld_common.h"

	.section .text
ENTRY(main)
	addi	sp, sp, -48
	sd	fp, 0(sp)
	sd	ra, 8(sp)
	sd	s1, 16(sp)
	sd	s2, 24(sp)
	sd	s3, 32(sp)
	sd	s4, 48(sp)

	li	a0, MLD_MATRIX_SIZE
	call	malloc
	beqz	a0, L(err)

	mv	a2, a0
	li	a0, 5
	li	a1, 5
	call	mldCreateMatrixInt64
	bnez	a0, L(err)

	li	s1, 0		// i-counter
	ld	s2, MLD_MATRIX_LENGTH_OFFSET(a1)
	ld	s3, MLD_MATRIX_ARRAY_OFFSET(a1)
	ld	s5, MLD_MATRIX_ROWS_OFFSET(a1)
	ld	s6, MLD_MATRIX_COLUMNS_OFFSET(a1)

0:
	beq	s1, s2, 1f

	// arr[i] = i
	sll	t3, s1, 3
	add	t3, s3, t3

	sd	s1, 0(t3)

	addi	s1, s1, 1	// i++
	j	0b
1:

	mv	a0, a1
	call	mldPrintMatrixInt64

	li	a0, MLD_EXIT_SUCCESS
	j	L(out)

L(err):
	li	a0, MLD_EXIT_FAILURE

L(out):
	ld	fp, 0(sp)
	ld	ra, 8(sp)
	ld	s1, 16(sp)
	ld	s2, 24(sp)
	ld	s3, 32(sp)
	ld	s4, 48(sp)
	addi	sp, sp, 16
	ret
END(main)
