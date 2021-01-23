#pragma once

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "types.h"

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec) {
  os << "[";
  for (const auto &v : vec) {
    os << v << " ";
  }
  os << "]";
  return os;
}

namespace su {
std::vector<std::size_t> findDelimiters(const std::string &long_string, const char delimiter) {
  std::vector<std::size_t> delimiter_positions = {};
  for (std::size_t idx = 0; idx < long_string.size(); ++idx) {
    if (long_string.at(idx) == delimiter) {
      delimiter_positions.push_back(idx);
    }
  }

  return delimiter_positions;
}

std::vector<std::string> split(const std::string &long_string, const char delimiter) {
  const auto delimiter_positions = findDelimiters(long_string, delimiter);

  std::vector<std::string> substrings = {};
  std::size_t pos = 0;
  std::size_t idx_start = 0;

  for (std::size_t i = 0; i < delimiter_positions.size(); ++i) {
    std::size_t length = delimiter_positions.at(i) - idx_start;
    substrings.push_back(long_string.substr(idx_start, length));
    idx_start = delimiter_positions.at(i) + 1;
  }

  if (!delimiter_positions.empty() && delimiter_positions.back() == long_string.size() - 1) {
    return substrings;
  }

  substrings.push_back(long_string.substr(idx_start, std::string::npos));

  return substrings;
}

su::BoardRow fillRow(const std::string &line) {
  su::BoardRow row_or_col;
  const auto values = split(line, ' ');
  if (values.size() != su::SIZE) {
    throw std::runtime_error("Line size is incorrect, size is " + std::to_string(values.size()));
  }
  for (std::size_t idx = 0; idx < su::SIZE; ++idx) {
    row_or_col[idx] = std::stoi(values[idx]);
  }
  return row_or_col;
}

su::Board readFile(const std::filesystem::path &file_path) {
  su::Board board;
  if (!std::filesystem::exists(file_path)) {
    throw std::runtime_error("File not found");
  }
  std::ifstream file(file_path.c_str());
  if (file.is_open()) {
    std::string line;
    for (std::size_t row = 0; row < su::SIZE; ++row) {
      std::string line;
      if (std::getline(file, line)) {
        board[row] = fillRow(line);
      }
    }
    file.close();
  }

  return board;
}
}  // namespace su
