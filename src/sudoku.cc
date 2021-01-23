#include <algorithm>
#include <iostream>

#include "parser.h"
#include "types.h"

bool isValidInRow(const su::BoardRow& board_row, const int val) {
  auto res = std::find(board_row.begin(), board_row.end(), val);
  if (res == board_row.end()) {
    return true;
  }
  return false;
}

su::BoardRow getColInRowFormat(const su::Board& board, const std::size_t col_idx) {
  su::BoardRow board_row;
  for (std::size_t idx = 0; idx < su::SIZE; ++idx) {
    board_row[idx] = board[idx][col_idx];
  }
  return board_row;
}

bool isValidInCol(const su::Board& board, const std::size_t col_idx, const int val) {
  const auto board_col = getColInRowFormat(board, col_idx);
  return isValidInRow(board_col, val);
}

su::BoardRow getSquareInRowFormat(const su::Board& board, const std::size_t row_idx, const std::size_t col_idx) {
  su::BoardRow board_row;
  int row_square_idx = row_idx / su::SQUARE_SIZE;
  int col_square_idx = col_idx / su::SQUARE_SIZE;

  std::size_t i = 0;
  for (std::size_t idx_r = 0; idx_r < su::SQUARE_SIZE; ++idx_r) {
    // row_square_idx = 0, 0, 1, 2 -> 0, 1, 2
    // row_square_idx = 1, 0, 1, 2 -> 3, 4, 5
    std::size_t row = 3 * row_square_idx + idx_r;
    for (std::size_t idx_c = 0; idx_c < su::SQUARE_SIZE; ++idx_c) {
      std::size_t col = 3 * col_square_idx + idx_c;
      board_row[i++] = board[row][col];
    }
  }
  return board_row;
}

bool isValidInSquare(const su::Board& board, const std::size_t row_idx, const std::size_t col_idx, const int val) {
  const auto board_col = getSquareInRowFormat(board, row_idx, col_idx);
  std::cout << "SQUARE: " << board_col << "\n";
  return isValidInRow(board_col, val);
}

void sudoku_solve(const su::Board& board) {
  // your logic here
  std::cout << board;
}

int main(void) {
  int n = 1;
  su::Board board;
  su::readFile("/home/keivan/playground/sudoku/sudoku_input_2.txt");

  // std::cout << "9 valid in row 2 " << isValidInRow(board[2], 9) << "\n";
  // std::cout << "5 valid in row 2 " << isValidInRow(board[2], 5) << "\n";
  // std::cout << "3 valid in row 1 " << isValidInRow(board[1], 3) << "\n";
  // std::cout << "5 valid in col 3 " << isValidInCol(board, 3, 5) << "\n";
  // std::cout << "8 valid in col 3 " << isValidInCol(board, 3, 8) << "\n";

  // std::cout << "8 valid in sq 4,4 " << isValidInSquare(board, 4, 4, 8) << "\n";
  // std::cout << "5 valid in sq 4,4 " << isValidInSquare(board, 4, 4, 5) << "\n";
  sudoku_solve(board);
  return 0;
}
