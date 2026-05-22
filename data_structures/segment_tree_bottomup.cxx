
// interactive segment tree implementation, 1-based indexing, bottom-up

#include <algorithm>
#include <limits>
using i64 = long long;

class segment_tree_bottomup {
public:
  int n;
  int tree_size;
  int *tree;
  char op = 'M'; // M for max, S for sum

  int operate(int a, int b) {
    switch (op) {
    case 'M':
      return std::max(a, b);
    case 'S':
      return a + b;
    default:
      return 0;
    }
  }

  void create(const int sz, const int *arr) {
    n = sz;
    tree_size = sz << 1;
    tree = new int[tree_size];
    for (int i = 0; i < n; i++) {
      tree[n + i] = arr[i];
    }
    for (int i = n - 1; i > 0; i--) {
      tree[i] = operate(tree[i << 1], tree[i << 1 | 1]);
    }
  }

  segment_tree_bottomup(const int sz, const int *arr) { create(sz, arr); }
  ~segment_tree_bottomup() { delete[] tree; }
  segment_tree_bottomup(const segment_tree_bottomup &) = delete;
  segment_tree_bottomup &operator=(const segment_tree_bottomup &) = delete;

  int query(int L, int R) {
    int r = R + n - 1;
    int l = L + n - 1;
    i64 toReturn = (op == 'M') ? std::numeric_limits<i64>::min() : 0;
    while (l <= r) {
      if (l & 1) {
        toReturn = operate(toReturn, tree[l]);
        l++;
      }
      if (!(r & 1)) {
        toReturn = operate(toReturn, tree[r]);
        r--;
      }
      l >>= 1;
      r >>= 1;
    }

    return toReturn;
  }

  void update(int idx, int val) {
    int i = idx + n - 1;

    // tree[i] = operate(tree[i], val);
    tree[i] = val;

    for (i >>= 1; i > 0; i >>= 1) {
      tree[i] = operate(tree[i << 1], tree[i << 1 | 1]);
    }
  }
};
