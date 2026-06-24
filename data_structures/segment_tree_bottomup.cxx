

// interactive segment tree implementation, 1-based indexing, bottom-up
// @brief
//

#include <bits/stdc++.h>
#include <ios>

using i64 = long long;


template <typename T>
struct Monoid
{
  T (*operation)(T, T);
  T identity;
};


template <typename T, typename Container>
class SegmentTreeBoUp
{

public:
  const size_t tree_size;
  const size_t original_size;
  Container tree;
  Monoid<T> monoid;
  SegmentTreeBoUp(const size_t sz, Container array, Monoid<T> m)
      : tree_size(sz), original_size(sz / 2), tree(std::move(array)), monoid(m)
  {

    // 'create' the tree
    for (auto i{original_size - 1}; i > 0; i--)
    {
      tree[i] = monoid.operation(tree[i << 1], tree[(i << 1) + 1]);
    }

  }


  // Expects 1-based index of original array
  // [L, R)
  T query(size_t L, size_t R)
  {
    T right_res = monoid.identity;
    T left_res = monoid.identity;

    size_t l = L + original_size - 1;
    size_t r = R + original_size - 1;
    while (l < r)
    {
      if (l & 1)
      {
        left_res = monoid.operation(left_res, tree[l]);
        l++;
      }
      if (!(r & 1))
      {
        right_res = monoid.operation(right_res, tree[r]);
        r--;
      }
      l >>= 1;
      r >>= 1;
    }

    return monoid.operation(left_res, right_res);
  }


  void update(size_t idx, T val)
  {
    size_t i = idx + original_size - 1;

    tree[i] = val;

    for (i >>= 1; i > 0; i >>= 1)
    {
      tree[i] = monoid.operation(tree[i << 1], tree[i << 1 | 1]);
    }
  }


};
