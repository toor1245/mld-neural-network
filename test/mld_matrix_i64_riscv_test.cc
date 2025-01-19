#include "mld_matrix.h"

#include <stdint.h>

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

}  // namespace
}  // namespace mld
