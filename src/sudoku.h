#pragma once

#include <algorithm>
#include <iostream>

#include "parser.h"
#include "types.h"

namespace su {

bool isValidInRow(const su::BoardRow& board_row, const int val) {
  auto res = std::find(board_row.begin(), board_row.end(), val);
  if (res == board_row.end()) {
    return true;
  }
  return false;
}

bool isValidInRow(const su::Board& board, const std::size_t row_idx, const int val) {
  return isValidInRow(board[row_idx], val);
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
  return isValidInRow(board_col, val);
}

}  // namespace su
