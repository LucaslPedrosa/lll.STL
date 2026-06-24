#include <concepts>
#include <cstddef>
#include <cstdio>
#include <string>
namespace fastIO
{

// constexpr size_t BUFFER_EXAMPLE_SIZES[5] = {
// 0,                 // 0,
// 1024,              // 1KB
// 1 << 20,           // 1MB
// (1 << 30),         // 2^30 = 1GB
// 1024 * 1024 * 1024 // 1GB
// };
constexpr size_t BUFFER_SIZE = 1024 * 1024;
size_t idx{};
size_t size{};
char buffer[BUFFER_SIZE];

inline char gc()
{
  if (idx == size)
  {
    size = fread(buffer, 1, BUFFER_SIZE, stdin);
    idx = 0;
    if (!size)
      return EOF;
  }
  return buffer[idx++];
}

inline bool is_space(char c)
{
  return c == 0 || c == '\n' || c == ' ' || c == '\r' || c == '\t';
}

template <typename T>
concept Number = std::integral<T>;

template <typename T>
concept Flow = std::floating_point<T>;


template <Number T>
inline T read()
{
  T toReturn = 0;
  char c = gc();

  while (is_space(c))
    c = gc();

  bool negative = 0;
  if constexpr (std::signed_integral<T>)
  {
    if (c == '-')
    {
      negative = 1;
    }
  }
  while (c < '0' || c > '9')
  {
    c = gc();
  }

  while (c >= '0' && c <= '9')
  {
    toReturn = toReturn * 10 + c - '0';
    c = gc();
  }

  if constexpr (std::signed_integral<T>)
    return negative ? -toReturn : toReturn;
  else
    return toReturn;
}

inline void read(std::string &s)
{
  s.clear();
  char c = gc();
  while (is_space(c))
    c = gc();
  while (!is_space(c))
  {
    s += c;
    c = gc();
  }
}


} // namespace fastIO
