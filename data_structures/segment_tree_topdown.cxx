
class segment_tree {
public:
  int og_size;
  int seg_size;
  int *seg_tree;

  inline int bit_mod(int v) {
    int const mask = v >> (sizeof(int) * 8 - 1);
    return (v + mask) ^ mask;
  }

  inline int bit_max(int a, int b) { return (a + b + bit_mod(a - b)) / 2; }

  void create(int sz, int *arr) {
    og_size = sz;
    seg_size = sz * 4;
    seg_tree = new int[seg_size];
    for (int i = 0; i < og_size; i++) {
      seg_tree[seg_size - 1 - i] = arr[og_size - 1 - i];
    }
    for (int i = og_size - 1; i > 0; i--) {
      seg_tree[i] = seg_tree[i * 2] + seg_tree[i * 2 + 1];
    }
  }

  segment_tree(int sz, int *arr) { create(sz, arr); }
};
