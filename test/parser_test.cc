#include "parser.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <string>
#include <vector>

#include "gmock/gmock.h"

namespace su {
template <class ForwardIt, class T>
constexpr void iota(ForwardIt first, ForwardIt last, T value) {
  while (first != last) {
    *first++ = value;
    ++value;
  }
}

TEST(String, Split) {
  std::vector<std::string> numbers{"1", "2", "3", "4", "5", "6", "7", "8", "9"};

  auto res = su::split("1 2 3 4 5 6 7 8 9", ' ');
  EXPECT_THAT(res, ::testing::ContainerEq(numbers));
  res = su::split("1,2,3,4,5,6,7,8,9", ',');
  EXPECT_THAT(res, ::testing::ContainerEq(numbers));
}

TEST(SudokuTest, FillRow) {
  su::BoardRow numbers;
  iota(numbers.begin(), numbers.end(), 1);

  auto res = su::fillRow("1 2 3 4 5 6 7 8 9");
  EXPECT_THAT(res, ::testing::ContainerEq(numbers));
}

TEST(SudokuTest, LoadBoard1) {
  auto curr_path = std::filesystem::current_path();
  auto file_path = curr_path.parent_path() / "test" / "sudoku_input_1.txt";
  auto board = su::readFile(file_path);
  su::BoardRow middle_row, last_row;
  std::fill(last_row.begin(), last_row.end(), 0);
  middle_row = last_row;

  last_row.back() = 5;

  // last row: : 0 0 0 0 0 0 0 0 5
  // middle row all zero.
  EXPECT_THAT(board[su::SIZE / 2], ::testing::ContainerEq(middle_row));
  EXPECT_THAT(board.back(), ::testing::ContainerEq(last_row));
}

TEST(SudokuTest, LoadBoard2) {
  auto curr_path = std::filesystem::current_path();
  auto file_path = curr_path.parent_path() / "test" / "sudoku_input_2.txt";
  auto board = su::readFile(file_path);
  su::BoardRow first_row{5, 3, 0, 0, 7, 0, 0, 0, 0};
  su::BoardRow last_row{0, 0, 0, 0, 8, 0, 0, 7, 9};

  EXPECT_THAT(board.front(), ::testing::ContainerEq(first_row));
  EXPECT_THAT(board.back(), ::testing::ContainerEq(last_row));
}

}  // namespace su

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
