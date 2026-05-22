

#include <cstdlib>
template <typename T> inline T max(T a, T b) {
  return (a + b + std::abs(a - b)) / 2;
}
