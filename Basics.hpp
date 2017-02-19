//
// Created by Kampersanda on 2017/02/08.
//

#ifndef BONSAIS_BASICS_HPP
#define BONSAIS_BASICS_HPP

#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stdlib.h>
#include <stdint.h>
#include <sstream>
#include <cmath>
#include <memory>

#include <sdsl/int_vector.hpp>

namespace bonsais {

template<typename T>
inline constexpr bool Is_pod() { return std::is_pod<T>::value; }

constexpr uint64_t kNotFound = UINT64_MAX;

struct HashValue {
  uint64_t rem;
  uint64_t quo;
};

inline uint8_t num_bits(uint64_t n) {
  return static_cast<uint8_t>(sdsl::bits::hi(n) + 1);
}

inline bool is_prime(uint64_t n) {
  if (n == 2) {
    return true;
  }

  if (n % 2 == 0 || n <= 1) {
    return false;
  }

  auto max = static_cast<uint64_t>(std::sqrt(n));
  for (uint64_t i = 3; i <= max; i += 2) {
    if (n % i == 0) {
      return false;
    }
  }

  return true;
}

inline uint64_t greater_prime(uint64_t n) {
  assert(n != 0);

  auto ret = n + 1;
  if (ret % 2 == 0 && ret != 2) {
    ret += 1;
  }
  while (!is_prime(ret)) {
    ret += 2;
  }
  return ret;
}

}

#endif //BONSAIS_BASICS_HPP