#ifndef MLD_INCLUDE_ASMDEFS_H
#define MLD_INCLUDE_ASMDEFS_H

// MLD Result Status Codes
#define MLD_SUCCESS			0
#define MLD_FAILURE			1
#define MLD_UNABLE_ALLOCATE_MEMORY	2
#define MLD_INVALID_ARGUMENT		3

// MLD Exit Status Codes
#define MLD_EXIT_SUCCESS	0
#define MLD_EXIT_FAILURE	1

// MLD MatrixInt64 Offsets
#define MLD_MATRIX_ROWS_OFFSET		0
#define MLD_MATRIX_COLUMNS_OFFSET	8
#define MLD_MATRIX_LENGTH_OFFSET	16
#define MLD_MATRIX_ARRAY_OFFSET		24
#define MLD_MATRIX_SIZE			32

// Assembly linkage declaration
#define ENTRY_ALIGN(name, alignment)	\
	.global	name;			\
	.type name, %function;		\
	.align	alignment;		\
	name:

#define ENTRY(name)	ENTRY_ALIGN(name, 6)

#define END(name) \
	.size	name, (. - name)

#define L(l) .L ## l

#endif // MLD_INCLUDE_ASMDEFS_H
