#include "mld_matrix.h"

#include <stdint.h>
#include <string.h>

#include "mld_common.h"
#include "gtest/gtest.h"

namespace mld {
namespace {

void setupMatrixInt64(MldMatrixInt64 *matrix) {
    for (int i = 0; i < matrix->length; i++) {
        matrix->array[i] = i;
    }
}

TEST(MldMatrixInt64Test, CreateMatrixInt64_Success_ReturnsSuccessAndMatrix) {
    // Arrange
    const uint64_t rows = 5;
    const uint64_t columns = 5;
    const uint64_t expectedLength = rows * columns;
    enum MldResult expectedResult = MldResult::MLD_RESULT_SUCCESS;
    struct MldMatrixInt64 matrix;
    
    // Act
    enum MldResult actualResult = mldCreateMatrixInt64(rows, columns, &matrix);

    // Assert
    EXPECT_EQ(actualResult, expectedResult);
    EXPECT_EQ(matrix.rows, rows);
    EXPECT_EQ(matrix.columns, columns);
    EXPECT_EQ(matrix.length, expectedLength);
}

struct GetItemInt64Param {
    uint64_t rows;
    uint64_t columns;
    uint64_t rowIndex;
    uint64_t columnIndex;
    int64_t expectedValue;
};

class GetItemInt64Suit
    : public testing::TestWithParam<GetItemInt64Param> {};

struct GetItemInt64Param getItemInt64Params[] = {
    (GetItemInt64Param){
        .rows = 3,
        .columns = 3,
        .rowIndex = 0,
        .columnIndex = 0,
        .expectedValue = 0,
    },
    (GetItemInt64Param){
        .rows = 3,
        .columns = 3,
        .rowIndex = 1,
        .columnIndex = 1,
        .expectedValue = 4,
    },
    (GetItemInt64Param){
        .rows = 3,
        .columns = 3,
        .rowIndex = 2,
        .columnIndex = 2,
        .expectedValue = 8,
    },
};

TEST_P(GetItemInt64Suit, GetItemInt64_Success_ReturnsAssignedValue) {
    // Arrange
    struct GetItemInt64Param param = GetParam();
    uint64_t rows = param.rows;
    uint64_t columns = param.columns;
    uint64_t row = param.rowIndex;
    uint64_t column = param.columnIndex;
    uint64_t expectedValue = param.expectedValue;
    MldMatrixInt64 matrix;
    mldCreateMatrixInt64(rows, columns, &matrix);
    setupMatrixInt64(&matrix);

    // Act
    int64_t actualValue = mldGetItemMatrixInt64(&matrix, row, column);

    // Assert
    EXPECT_EQ(actualValue, expectedValue);
}

INSTANTIATE_TEST_SUITE_P(MldMatrixGetItemInt64Suit,
                         GetItemInt64Suit,
                         ::testing::ValuesIn(getItemInt64Params));

struct SetItemInt64Param {
    uint64_t rows;
    uint64_t columns;
    uint64_t rowIndex;
    uint64_t columnIndex;
    int64_t setValue;
    int64_t expectedValue;
};

class SetItemInt64Suit
    : public testing::TestWithParam<SetItemInt64Param> {};

struct SetItemInt64Param setItemInt64Params[] = {
    (SetItemInt64Param){
        .rows = 3,
        .columns = 3,
        .rowIndex = 0,
        .columnIndex = 0,
        .setValue = 1,
        .expectedValue = 1,
    },
    (SetItemInt64Param){
        .rows = 3,
        .columns = 3,
        .rowIndex = 1,
        .columnIndex = 1,
        .setValue = 5,
        .expectedValue = 5,
    },
    (SetItemInt64Param){
        .rows = 3,
        .columns = 3,
        .rowIndex = 2,
        .columnIndex = 2,
        .setValue = 3,
        .expectedValue = 3,
    },
};

TEST_P(SetItemInt64Suit, SetItemInt64_Success_ReturnsAssignedValue) {
    // Arrange
    struct SetItemInt64Param param = GetParam();
    uint64_t rows = param.rows;
    uint64_t columns = param.columns;
    uint64_t row = param.rowIndex;
    uint64_t column = param.columnIndex;
    uint64_t setValue = param.setValue;
    uint64_t expectedValue = param.expectedValue;
    MldMatrixInt64 matrix;
    mldCreateMatrixInt64(rows, columns, &matrix);

    // Act
    mldSetItemMatrixInt64(&matrix, row, column, setValue);
    int64_t actualValue = mldGetItemMatrixInt64(&matrix, row, column);

    // Assert
    EXPECT_EQ(actualValue, expectedValue);
}

INSTANTIATE_TEST_SUITE_P(MldMatrixSetItemInt64Suit,
                         SetItemInt64Suit,
                         ::testing::ValuesIn(setItemInt64Params));

TEST(MldMatrixInt64Test, AddMatrixInt64_AddTwoMatrices_AssertMustBeEqual) {
    // Arrange
    const uint64_t rows = 3;
    const uint64_t columns = 3;
    enum MldResult expectedResult = MldResult::MLD_RESULT_SUCCESS;
    struct MldMatrixInt64 matrixA;
    struct MldMatrixInt64 matrixB;
    struct MldMatrixInt64 matrixC;
    struct MldMatrixInt64 matrixExpected;

    mldCreateMatrixInt64(rows, columns, &matrixA);
    mldCreateMatrixInt64(rows, columns, &matrixB);
    mldCreateMatrixInt64(rows, columns, &matrixC);
    mldCreateMatrixInt64(rows, columns, &matrixExpected);

    int64_t arrayA[] = {
	1, 5, 8,
	3, 5, 6,
	4, 8, 9,
    };

    int64_t arrayB[] = {
	1, 2, 4,
	3, 4, 6,
	4, 8, 9,
    };

    int64_t arrayExpected[] = {
	2, 7, 12,
	6, 9, 12,
	8, 16, 18,
    };

    memcpy(matrixA.array, arrayA, matrixA.length * sizeof(int64_t));
    memcpy(matrixB.array, arrayB, matrixB.length * sizeof(int64_t));
    memcpy(matrixExpected.array, arrayExpected, matrixExpected.length * sizeof(int64_t));

    // Act
    enum MldResult actualResult = mldAddMatrixInt64(&matrixA, &matrixB, &matrixC);

    // Assert
    EXPECT_EQ(actualResult, expectedResult);
    EXPECT_EQ(matrixC.rows, matrixExpected.rows);
    EXPECT_EQ(matrixC.columns, matrixExpected.columns);
    EXPECT_EQ(matrixC.length, matrixExpected.length);
    
    for (size_t i = 0; i < matrixExpected.length; ++i) {
	EXPECT_EQ(matrixExpected.array[i], matrixC.array[i]);
    }
}

TEST(MldMatrixInt64Test, SubMatrixInt64_AddTwoMatrices_AssertMustBeEqual) {
    // Arrange
    const uint64_t rows = 3;
    const uint64_t columns = 3;
    enum MldResult expectedResult = MldResult::MLD_RESULT_SUCCESS;
    struct MldMatrixInt64 matrixA;
    struct MldMatrixInt64 matrixB;
    struct MldMatrixInt64 matrixC;
    struct MldMatrixInt64 matrixExpected;

    mldCreateMatrixInt64(rows, columns, &matrixA);
    mldCreateMatrixInt64(rows, columns, &matrixB);
    mldCreateMatrixInt64(rows, columns, &matrixC);
    mldCreateMatrixInt64(rows, columns, &matrixExpected);

    int64_t arrayA[] = {
	1, 5, 8,
	3, 5, 6,
	4, 8, 11,
    };

    int64_t arrayB[] = {
	1, 2, 4,
	3, 4, 6,
	4, 8, 9,
    };

    int64_t arrayExpected[] = {
	0, 3, 4,
	0, 1, 0,
	0, 0, 2,
    };

    memcpy(matrixA.array, arrayA, matrixA.length * sizeof(int64_t));
    memcpy(matrixB.array, arrayB, matrixB.length * sizeof(int64_t));
    memcpy(matrixExpected.array, arrayExpected, matrixExpected.length * sizeof(int64_t));

    // Act
    enum MldResult actualResult = mldSubMatrixInt64(&matrixA, &matrixB, &matrixC);

    // Assert
    EXPECT_EQ(actualResult, expectedResult);
    EXPECT_EQ(matrixC.rows, matrixExpected.rows);
    EXPECT_EQ(matrixC.columns, matrixExpected.columns);
    EXPECT_EQ(matrixC.length, matrixExpected.length);
    
    for (size_t i = 0; i < matrixExpected.length; ++i) {
	EXPECT_EQ(matrixExpected.array[i], matrixC.array[i]);
    }
}

}  // namespace
}  // namespace mld
