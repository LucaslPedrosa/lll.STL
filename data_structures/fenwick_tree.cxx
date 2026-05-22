
class fenwick_tree {
public:
  int *original_array;
  int *fenwick_array;
  int size;

  fenwick_tree(int *arr, int sz) {
    original_array = new int[sz + 1];
    fenwick_array = new int[sz + 1];
    size = sz + 1;

    for (int i = 1; i < size; i++) {
      original_array[i] = arr[i - 1];
      fenwick_array[i] = 0;
    }

    fenwick_array[0] = 0;
    original_array[0] = 0;

    int bit;
    int sum;

    for (int i = 1; i < size; i++) {

      fenwick_array[i] += original_array[i];
      int parent = i + (i & -i);
      if (parent < size)
        fenwick_array[parent] += fenwick_array[i];
    }
  }

  ~fenwick_tree() {
    delete[] original_array;
    delete[] fenwick_array;
  }

  int sum(int i) {
    int sum = 0;
    while (i > 0) {
      sum += fenwick_array[i];
      i -= i & -i;
    }
    return sum;
  }

  int fenIndex(int i) { return fenwick_array[i]; }
  int ogIndex(int i) { return original_array[i]; }

  void static_change(int i, int k) {
    int toAdd = k - original_array[i];
    original_array[i] = k;
    add(i, toAdd);
  }

  void dynamic_change(int i, int k) {
    original_array[i] += k;
    add(i, k);
  }

  void add(int i, int k) {
    while (i < size) {
      fenwick_array[i] += k;
      i += i & -i;
    }
  }
};
