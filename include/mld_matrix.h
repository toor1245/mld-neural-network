#ifndef MLD_INCLUDE_MATRIX_H
#define MLD_INCLUDE_MATRIX_H

#include <stdint.h>

#include "mld_common.h"
#include "mld_macros.h"
#include "mld_asmdefs.h"

MLD_START_CPP_NAMESPACE

struct MldMatrixInt64 {
	uint64_t rows;
	uint64_t columns;
	uint64_t length;
	int64_t *array;
};

_Static_assert(sizeof(MldMatrixInt64) == MLD_MATRIX_SIZE,
	"MldMatrixInt64 size is not equal to assembly matrix size");

MldResult mldCreateMatrixInt64(uint64_t rows, uint64_t columns, MldMatrixInt64 *matrix);

uint64_t mldGetItemMatrixInt64(MldMatrixInt64 *matrix, uint64_t row, uint64_t column);

uint64_t mldSetItemMatrixInt64(MldMatrixInt64 *matrix, uint64_t row, uint64_t column,
	int64_t value);

MldResult mldGetRowMatrixInt64(MldMatrixInt64 *matrix, uint64_t row,
	MldMatrixInt64 *output);

MldResult mldAddMatrixInt64(MldMatrixInt64 *left, MldMatrixInt64 *right,
	MldMatrixInt64 *output);

MldResult mldSubMatrixInt64(MldMatrixInt64 *left, MldMatrixInt64 *right,
	MldMatrixInt64 *output);

void mldPrintMatrixInt64(MldMatrixInt64 *matrix);

MLD_END_CPP_NAMESPACE

#endif // MLD_INCLUDE_MATRIX_H
