#include <numeric>

#include "parser.h"
#include "sudoku.h"
#include "types.h"

bool solve(su::Board& board) {
  int row = 0;
  int col = 0;
  su::BoardRow valid_values;
  std::iota(valid_values.begin(), valid_values.end(), 1);
  for (int i = 0; i < su::SIZE * su::SIZE; ++i) {
    row = i / su::SIZE;
    col = i % su::SIZE;
    if (board[row][col] == 0) {
      for (const auto value : valid_values) {
        // Check that this value has not already be used in this row, col or square.
        if (su::isValidInRow(board, row, value) && su::isValidInCol(board, col, value) &&
            su::isValidInSquare(board, row, col, value)) {
          board[row][col] = value;
          if (su::isBoardComplete(board)) {
            return true;
          } else {
            if (solve(board)) {
              return true;
            }
          }
        }
      }
      break;
    }
  }
  // Backtrack
  board[row][col] = 0;
  return false;
}

int main(int argc, char** argv) {
  std::filesystem::path file_path;
  if (argc < 2) {
    std::cout << "Usage: backtracking_solver /absolute/file_path.txt\n";
    return 1;
  }

  su::Board board = su::readFile(file_path);
  std::cout << board;
  solve(board);
  std::cout << board;

  return 0;
}
