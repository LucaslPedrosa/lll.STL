
class fenwick_tree {
public:
  int *ogArr;
  int *fenArr;
  int size;

  fenwick_tree(int *arr, int sz) {
    ogArr = new int[sz + 1];
    fenArr = new int[sz + 1];
    size = sz + 1;

    for (int i = 1; i < size; i++) {
      ogArr[i] = arr[i - 1];
      fenArr[i] = 0;
    }

    fenArr[0] = 0;
    ogArr[0] = 0;

    int bit;
    int sum;

    for (int i = 1; i < size; i++) {

      fenArr[i] += ogArr[i];
      int parent = i + (i & -i);
      if (parent < size)
        fenArr[parent] += fenArr[i];
    }
  }

  ~fenwick_tree() {
    delete[] ogArr;
    delete[] fenArr;
  }

  int sum(int i) {
    int sum = 0;
    while (i > 0) {
      sum += fenArr[i];
      i -= i & -i;
    }
    return sum;
  }

  int fenIndex(int i) { return fenArr[i]; }
  int ogIndex(int i) { return ogArr[i]; }

  void static_change(int i, int k) {
    int toAdd = k - ogArr[i];
    ogArr[i] = k;
    add(i, toAdd);
  }

  void dynamic_change(int i, int k) {
    ogArr[i] += k;
    add(i, k);
  }

  void add(int i, int k) {
    while (i < size) {
      fenArr[i] += k;
      i += i & -i;
    }
  }
};
