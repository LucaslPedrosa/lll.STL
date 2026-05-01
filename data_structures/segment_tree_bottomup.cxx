
// interactive segment tree implementation, 1-based indexing, bottom-up
// construction
class segment_tree1 {
public:
  int n;
  int tree_size;
  int *tree;
  char op = 'M'; // M for max, S for sum
  inline int bit_mod(int v) {
    int const mask = v >> (sizeof(int) * 8 - 1);
    return (v + mask) ^ mask;
  }

  inline int bit_max(int a, int b) { return (a + b + bit_mod(a - b)) / 2; }

  int operate(int a, int b) {
    switch (op) {
    case 'M':
      return bit_max(a, b);
      break;
    case 'S':
      return a + b;
      break;
    }
    return -1;
  }

  void create(int sz, int *arr) {
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

  segment_tree1(int sz, int *arr) { create(sz, arr); }

  int query(int L, int R) {
    int r = R + n;
    int l = L + n;
    int toReturn = (op == 'M') ? -2147483648 : 0;

    while (l <= r) {
      if (l & 1) {
        toReturn = operate(toReturn, tree[l]);
        l++;
      }
      if (!(r & 1)) {
        toReturn = operate(toReturn, tree[l]);
        r--;
      }
      l /= 2;
      r /= 2;
    }

    return toReturn;
  }

  void update(int idx, int val) {
    int i = idx + n;

    tree[i] = operate(tree[i], val);
  }
};
