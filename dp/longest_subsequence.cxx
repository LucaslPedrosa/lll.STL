// Check ✅

#include <algorithm>
#include <span>
#include <vector>

template <typename T, typename Compare = std::less<T>>
  requires std::strict_weak_order<Compare, T, T>
[[nodiscard]]
std::size_t longest_subsequence(std::span<const T> array,
                                Compare compare = {}) {
  std::vector<T> lis;
  lis.reserve(array.size());
  for (const auto &value : array) {
    auto it = std::ranges::lower_bound(lis, value, compare);
    if (it == lis.end()) {
      lis.push_back(value);
    } else {
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
template <typename T, typename Comparison = std::less<T>>
class LongestSubsequence {
public:
  std::span<const T> array;
  std::vector<T> lis;
  std::size_t lis_size{0};

  Comparison comp{};

  LongestSubsequence(std::span<int> array, Comparison comp)
      : array(array), comp(comp) {
    lis.resize(array.size());
  }

  [[nodiscard]]
  int compute() {
    if (array.empty()) {
      return 0;
    }

    lis[0] = array[0];
    lis_size = 1;

    for (std::size_t i = 1; i < array.size(); i++) {
      if (comp(array[i], lis[lis_size - 1])) {
        lis[lis_size] = array[i];
        lis_size++;
      } else {
        int l = 0;
        int r = lis_size - 1;

        while (l <= r) {
          int mid = l + (r - l) / 2;

          if (comp(array[i], lis[mid])) {
            l = mid + 1;
          } else {
            r = mid - 1;
          }
        }

        lis[l] = array[i];
      }
    }

    return lis_size;
  }
};
