#pragma once

#include <cstddef>
template <class T> class MyAllocator {
public:
  using size_type = std::size_t;
  using differnce_type = std::ptrdiff_t;
  using pointer = T *;
  using value_type = T;

  static pointer allocate(size_type count) {
    return operator new(count * sizeof(value_type));
  }
  static void deallocate(pointer p) { operator delete(p); }
};
