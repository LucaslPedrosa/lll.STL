

template <typename T> inline T abs(const T &x) {
  T mask = x >> (sizeof(T) * 8 - 1);
  return x ^ mask - mask;
}

inline int bit_mod(int v) {
  int const mask = v >> (sizeof(int) * 8 - 1);
  return (v + mask) ^ mask;
}
