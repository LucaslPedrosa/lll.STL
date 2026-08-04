

// O(n) if the input is 0 to n
#include <alloca.h>
#include <cstring>
#include <malloc.h>

template <typename T>
inline void counting_sort(T *start, T *end, int m)
{
  if (m > 100000 || m < 0)
  {
    return;
  }

  int *count = (int *)alloca(sizeof(int) * m); // stack alloc, faster than heap
  memset(count, 0, sizeof(int) * m);

  int n = end - start;
  for (int i = 0; i < n; ++i)
  {
    ++count[start[i]];
  }

  int p = 0;
  for (int i = 0; i < m; ++i)
  {
    int cnt = count[i];
    while (cnt--)
    {
      start[p++] = i;
    }
  }
}

template <typename T>
inline void radixSort(T *start, T *end)
{
  const int exp = 16;
  const int base = (1 << exp);
  int size = end - start;
  T output[size];
  int push = 0;

  for (int reps = 0; reps < 2; reps++)
  {
    int count[base] = {0};
    for (int i = 0; i < size; i++)
    {
      count[((start[i] >> (exp * reps)) & (base - 1))]++;
    }

    for (int i = 1; i < base; i++)
    {
      count[i] += count[i - 1];
    }
    for (int i = size - 1; i >= 0; i--)
    {
      count[((start[i] >> (exp * reps)) & (base - 1))]--;
      output[count[((start[i] >> (exp * reps)) & (base - 1))]] = start[i];
    }

    for (int i = 0; i < size; i++)
    {
      start[i] = output[i];
    }
  }
}

#include <bits/stdc++.h>
using namespace std;

template <const bool negative = true, const int BITS = 9, typename _Iterator>
inline void radix_sort(_Iterator _first, _Iterator _last, const bool reverse = false)
{
  typedef typename iterator_traits<_Iterator>::value_type value_type;
  if (negative)
  {
    if (!reverse)
    {
      _Iterator _middle = partition(_first, _last, [](value_type a) -> bool { return a < 0; });
      for (auto it = _first; it != _middle; it++)
        *it *= -1;
      radix_sort<false>(_first, _middle, true);
      for (auto it = _first; it != _middle; it++)
        *it *= -1;
      radix_sort<false>(_middle, _last);
    }
    else
    {
      _Iterator _middle = partition(_first, _last, [](value_type a) -> bool { return a >= 0; });
      radix_sort<false>(_first, _middle, true);
      for (auto it = _middle; it != _last; it++)
        *it *= -1;
      radix_sort<false>(_middle, _last);
      for (auto it = _middle; it != _last; it++)
        *it *= -1;
    }
    return;
  }
  constexpr int PART = (1 << BITS);
  constexpr int FULL = (1 << BITS) - 1;
  int shift = 0;
  auto MAX = *max_element(_first, _last);
  vector<value_type> P[PART];
  while (log2(MAX) >= shift)
  {
    for (auto it = _first; it != _last; it++)
      P[(((*it) >> shift) & FULL) ^ (reverse ? FULL : 0)].push_back(*it);
    auto it = _first;
    for (int i = 0; i < PART; i++)
    {
      for (auto u : P[i])
        *it++ = u;
      P[i].clear();
    }
    shift += BITS;
  }
}

// Tim Sort
