

// interactive segment tree implementation, 1-based indexing, bottom-up
// @brief
//

#include <cstddef>
#include <lll/algebra/structures.hpp>
#include <lll/core/concepts/storage.hpp>
#include <utility>

using i64 = long long;

namespace lll::data_structures
{
template <lll::algebra::Monoid M, typename Container>
  requires lll::concepts::MutableStorage<Container, typename M::value_type>
class SegmentTreeBoUp
{

public:
  using monoid_type = M;
  using value_type = typename M::value_type;
  using T = value_type;

  const size_t tree_size;
  const size_t original_size;
  Container tree;
  SegmentTreeBoUp(const size_t sz, Container array)
      : tree_size(sz), original_size(sz / 2), tree(std::move(array))
  {

    // 'create' the tree
    for (auto i{original_size - 1}; i > 0; i--)
    {
      tree[i] = M::operation(tree[i << 1], tree[(i << 1) + 1]);
    }

  }


  // Expects 1-based index of original array
  // [L, R)
  T query(size_t const L, const size_t R) const
  {
    T right_res = M::identity();
    T left_res = M::identity();

    size_t l = L + original_size - 1;
    size_t r = R + original_size - 1;
    while (l < r)
    {
      if (l & 1)
      {
        left_res = M::operation(left_res, tree[l]);
        l++;
      }
      if (!(r & 1))
      {
        r--;
        right_res = M::operation(tree[r], right_res);
      }
      l >>= 1;
      r >>= 1;
    }

    return M::operation(left_res, right_res);
  }


  void update(size_t idx, T val)
  {
    size_t i = idx + original_size - 1;

    tree[i] = val;

    for (i >>= 1; i > 0; i >>= 1)
    {
      tree[i] = M::operation(tree[i << 1], tree[i << 1 | 1]);
    }
  }


}; // namespace lll:data_structurestemplate<typenameT,typenameContainer,typenameOP>class
} // namespace lll::data_structures
