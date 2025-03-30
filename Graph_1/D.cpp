#include <algorithm>
#include <iostream>
#include <vector>
const int cMax = 2e4 + 5;

std::vector<std::vector<int>> g(cMax);
std::vector<std::vector<int>> t(cMax);
std::vector<bool> used(cMax);
std::vector<int> order;
std::vector<int> component(cMax);
int cnt_components = 0;

void DFS1(int v) {
  used[v] = true;
  for (int u : g[v]) {
    if (!used[u]) {
      DFS1(u);
    }
  }
  order.push_back(v);
}

void DFS2(int v, int comp) {
  component[v] = comp;
  for (int u : t[v]) {
    if (component[u] == 0) {
      DFS2(u, comp);
    }
  }
}

int main() {
  int n;
  int m;
  std::cin >> n >> m;
  for (int i = 0; i < m; i++) {
    int u;
    int v;
    std::cin >> u >> v;
    u--;
    v--;
    g[u].push_back(v);
    t[v].push_back(u);
  }

  for (int i = 0; i < n; i++) {
    if (!used[i]) {
      DFS1(i);
    }
  }
  fill(used.begin(), used.end(), false);

  reverse(order.begin(), order.end());
  for (int v : order) {
    if (component[v] == 0) {
      cnt_components++;
      DFS2(v, cnt_components);
    }
  }

  std::cout << cnt_components << '\n';
  for (int i = 0; i < n; i++) {
    std::cout << component[i] << " ";
  }
  std::cout << '\n';

  return 0;
}