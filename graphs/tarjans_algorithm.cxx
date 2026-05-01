#include <stack>
#include <vector>

class tarjans_algorithm {

  static constexpr int UNVISITED = 0;
  static constexpr int VISITED = 1;

public:
  std::vector<std::vector<int>> graph;
  std::vector<std::vector<int>> sccs;
  std::stack<int> stack;
  std::vector<int> ids;
  std::vector<int> low;
  std::vector<int> onStack;
  int id = 1;
  int sccsCount = 0;
  int size;

  tarjans_algorithm(std::vector<std::vector<int>> graph)
      : graph(std::move(graph)) {
    size = this->graph.size();
    ids.assign(size, UNVISITED);
    low.assign(size, 0);
    onStack.assign(size, 0);
  }

  ~tarjans_algorithm() {}

  void dfs(int idx) {

    ids[idx] = id++;
    low[idx] = ids[idx];

    onStack[idx] = 1;
    stack.push(idx);

    for (auto const &x : graph[idx]) {
      if (ids[x] == UNVISITED)
        dfs(x);
      if (onStack[x]) {
        low[idx] = std::min(low[idx], low[x]);
      }
    }
    if (ids[idx] == low[idx]) {
      std::vector<int> scc;
      for (auto node = stack.top();; node = stack.top()) {
        stack.pop();
        scc.push_back(node);
        onStack[node] = 0;
        low[node] = ids[idx];
        if (node == idx) {
          break;
        }
      }
      sccs.push_back(scc);
      sccsCount++;
    }
  }

  void findSccs() {
    for (int i = 1; i < size; i++) {
      if (ids[i] == UNVISITED) {
        dfs(i);
      }
    }
  }
};
