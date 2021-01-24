#include "sudoku.h"

#include <gtest/gtest.h>

#include <filesystem>

#include "parser.h"
// #include <string>
// #include <vector>

// #include "gmock/gmock.h"

namespace su {
TEST(Sudoku, ValidInRowCol) {
  auto curr_path = std::filesystem::current_path();
  auto file_path = curr_path.parent_path() / "test" / "sudoku_input_2.txt";

  su::Board board = su::readFile(file_path);

  std::size_t row_idx = 1;
  ASSERT_TRUE(isValidInRow(board[row_idx], 3));
  row_idx = 2;
  ASSERT_FALSE(isValidInRow(board[row_idx], 9));
  ASSERT_TRUE(isValidInRow(board[row_idx], 5));

  row_idx = 3;
  std::size_t col_idx = 3;
  ASSERT_FALSE(isValidInCol(board, col_idx, 8));
  ASSERT_TRUE(isValidInCol(board, col_idx, 5));

  row_idx = col_idx = 4;
  ASSERT_FALSE(isValidInSquare(board, row_idx, col_idx, 8));
  ASSERT_TRUE(isValidInSquare(board, row_idx, col_idx, 5));

  ASSERT_FALSE(isBoardComplete(board));
}
}  // namespace su

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
