#include "data_structures/segment_tree_bottomup.cxx"

int main()
{

  Monoid<i64> mono = {[](i64 a, i64 b) { return std::max(a, b); },
                      std::numeric_limits<i64>::lowest()};
  std::array<i64, 8> arr = {0, 0, 0, 0, 1, 2, 3, 4};

  SegmentTreeBoUp<i64, std::array<i64, 8>> seg(arr.size(), arr, mono);

  std::cout << seg.tree[1] << '\n';
  seg.update(3, 10);
  std::cout << seg.tree[1] << '\n';
}
