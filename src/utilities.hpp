#pragma once

#include <sstream>

template <typename T> T getNextToken(std::stringstream &stream) {
  T token;
  stream >> token;
  return token;
}
