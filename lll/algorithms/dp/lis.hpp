// Check ✅

#include <algorithm>
#include <concepts>
#include <functional>
#include <ranges>
#include <span>
#include <vector>


// LIS algorithm requires an strict weak ordering in order to function
template <typename T, typename Compare = std::less<T>>
  requires std::strict_weak_order<Compare, T, T>
[[nodiscard]]
std::size_t longest_subsequence(std::span<const T> array, Compare compare = {})
{
  std::vector<T> lis;
  lis.reserve(array.size());
  for (const auto &value : array)
  {
    auto it = std::ranges::lower_bound(lis, value, compare);
    if (it == lis.end())
    {
      lis.push_back(value);
    }
    else
    {
      *it = value;
    }
  }

  return lis.size();
}

/**
 * @tparam Comparison A comparison function that defines the ordering
 * @tparam T The type of the elements in the input array.
 *
 * @brief A class that computes the length of the longest subsequence (LIS)
 * algorithm runs in O(n log n) time complexity.
 *
 *
 */
template <typename T, typename Compare = std::less<>>
  requires std::strict_weak_order<Compare, const T &, const T &>
[[nodiscard]]
std::size_t lis_length(std::span<const T> array, Compare compare = {})
{
  std::vector<std::size_t> tails;
  tails.reserve(array.size());

  for (std::size_t i = 0; i < array.size(); ++i)
  {
    auto it = std::ranges::lower_bound(tails, array[i], compare, [&](std::size_t index) -> const T &
                                       { return array[index]; });

    if (it == tails.end())
      tails.push_back(i);
    else
      *it = i;
  }

  return tails.size();
}
