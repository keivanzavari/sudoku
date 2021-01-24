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

  std::cout << board;
  ASSERT_TRUE(isValidInRow(board[1], 3));
  ASSERT_FALSE(isValidInRow(board[2], 9));
  ASSERT_TRUE(isValidInRow(board[2], 5));

  ASSERT_FALSE(isValidInCol(board, 3, 8));
  ASSERT_TRUE(isValidInCol(board, 3, 5));

  ASSERT_FALSE(isValidInSquare(board, 4, 4, 8));
  ASSERT_TRUE(isValidInSquare(board, 4, 4, 5));
}
}  // namespace su

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
