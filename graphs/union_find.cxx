class union_find {

public:
  int *parent;
  int *group_size;
  int array_size;

  void create(int size, const union_find *other = nullptr) {
    this->array_size = size;
    parent = new int[size];
    group_size = new int[size];

    for (int i = 0; i < size; i++) {
      parent[i] = other ? other->parent[i] : i;
      group_size[i] = other ? other->group_size[i] : 1;
    }
  }

  union_find(int size) { create(size); };

  union_find(const union_find &other) { create(other.array_size, &other); }

  union_find &operator=(const union_find &other) {

    if (this == &other)
      return *this;

    array_size = other.array_size;
    delete[] this->parent;
    delete[] this->group_size;
    create(array_size, &other);
    return *this;
  }

  // Returns the group representative
  int find(int x) {
    if (parent[x] == x)
      return x;

    parent[x] = find(parent[x]); // Path compression
    return parent[x];
  }

  int unite(int x, int y) {

    int p1 = find(y);
    int p2 = find(x);

    if (p1 == p2)
      return -1;

    if (group_size[p1] > group_size[p2]) {
      p1 ^= p2;
      p2 ^= p1;
      p1 ^= p2;
    }

    parent[p1] = p2;
    group_size[p2] += group_size[p1];
    return parent[y];
  }

  ~union_find() {
    delete[] parent;
    delete[] group_size;
  }
};
