#ifndef MLD_INCLUDE_COMMON_H
#define MLD_INCLUDE_COMMON_H

#include <stdint.h>

#include "mld_macros.h"

MLD_START_CPP_NAMESPACE

enum MldResult {
	MLD_RESULT_SUCCESS = 0,
	MLD_RESULT_FAILURE = 1,
	MLD_RESULT_UNABLE_ALLOCATE_MEMORY = 2,
	MLD_RESULT_INVALID_ARGUMENT = 3,
};

MLD_END_CPP_NAMESPACE

#endif // MLD_INCLUDE_COMMON_H
