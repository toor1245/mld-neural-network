#include "mld_asmdefs.h"

// Gets matrix item of MldMatrixInt64 by row and column indexes, inline
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
// Affects registers:
//	* t0, t1, t2, t3, a0
//
// Returns:
//	* Matrix value by index row and column
.macro mldGetItemMatrixInt64Inline
	ld	t0, MLD_MATRIX_ARRAY_OFFSET(a0)
	ld	t1, MLD_MATRIX_COLUMNS_OFFSET(a0)
	mul	t2, a1, t1
	add	t2, t2, a2
	sll	t2, t2, 3
	add	t3, t0, t2
	ld	a0, 0(t3)
.endm

// Gets matrix item of MldMatrixInt64 by array index, inline
//
// Parameters:
// 	a0 - holds address of MldMatrixInt64
//	a1 - holds array index
//
// Valid Usage:
// 	* a0 - must be valid address of MldMatrixInt64
//	* a1 - array index must be greater or equal 0
//
// Affects registers:
//	* t0, t1, t2, a0
//
// Returns:
//	* Matrix value by array index
.macro mldGetItemByIdxMatrixInt64Inline
	ld	t0, MLD_MATRIX_ARRAY_OFFSET(a0)
	sll	t1, a1, 3
	add	t2, t0, t1
	ld	a0, 0(t2)
.endm

// Sets matrix item of MldMatrixInt64 by row and column indexes, inline
//
// Parameters:
// 	a0 - holds address of MldMatrixInt64
//	a1 - holds row index
//	a2 - holds column index
//	a3 - holds value to store
//
// Affects registers:
//	* t0, t1, t2, t3
//
// Valid Usage:
// 	* a0 - must be valid address of MldMatrixInt64
//	* a1 - row index must be greater than 0
//	* a2 - column index must be greater that 0
.macro mldSetItemMatrixInt64Inline
	ld	t0, MLD_MATRIX_ARRAY_OFFSET(a0)
	ld	t1, MLD_MATRIX_COLUMNS_OFFSET(a0)
	mul	t2, a1, t1
	add	t2, t2, a2
	sll	t2, t2, 3
	add	t3, t0, t2
	sd	a3, 0(t3)
.endm

// Sets matrix item of MldMatrixInt64 by array index, inline
//
// Parameters:
// 	a0 - holds address of MldMatrixInt64
//	a1 - holds array index
//	a2 - holds value to store
//
// Affects registers:
//	* t0, t1, t2
//
// Valid Usage:
// 	* a0 - must be valid address of MldMatrixInt64
//	* a1 - array index must be greater or equal 0
.macro mldSetItemByIdxMatrixInt64Inline
	ld	t0, MLD_MATRIX_ARRAY_OFFSET(a0)
	sll	t1, a1, 3
	add	t2, t0, t1
	sd	a2, 0(t2)
.endm
