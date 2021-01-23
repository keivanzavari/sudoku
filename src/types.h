
#pragma once

#include <array>
#include <ostream>

namespace su {
constexpr int SQUARE_SIZE = 3;
constexpr int SIZE = 9;
using BoardRow = std::array<int, SIZE>;
using Board = std::array<BoardRow, SIZE>;

}  // namespace su

std::ostream &operator<<(std::ostream &os, const su::BoardRow &row) {
  os << "| ";
  std::size_t idx = 0;
  for (const auto &v : row) {
    if (v != 0) {
      os << "\033[31m" << v << "\033[0m ";
    } else {
      os << v << " ";
    }
    if (++idx % 3 == 0) {
      os << "| ";
    }
  }
  return os;
}

std::ostream &operator<<(std::ostream &os, const su::Board &board) {
  std::size_t idx = 0;
  os << "-------------------------\n";
  for (const auto &row : board) {
    os << row << "\n";
    if (++idx % 3 == 0) {
      os << "-------------------------\n";
    }
  }
  return os;
}
