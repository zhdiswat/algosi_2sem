#include <algorithm>
#include <iostream>
#include <map>
#include <utility>
#include <vector>
class ConnectivityAnalyzer {
 private:
  const int cKMaxVisitTime = 1000000;
  int vertex_total_;
  int edge_total_;
  int clock_counter_;
  std::vector<std::map<int, int>> neighbor_map_;
  std::vector<bool> marked_;
  std::vector<int> entry_time_;
  std::vector<int> min_reachable_;
  std::vector<int> critical_edges_;
  std::map<std::pair<int, int>, int> edge_counter_;
  std::map<std::pair<int, int>, int> edge_index_lookup_;

 public:
  ConnectivityAnalyzer(int vertices, int edges) {
    vertex_total_ = vertices;
    edge_total_ = edges;
    clock_counter_ = 0;
    neighbor_map_.resize(vertices + 1);
    marked_.resize(vertices + 1, false);
    entry_time_.resize(vertices + 1, cKMaxVisitTime);
    min_reachable_.resize(vertices + 1, cKMaxVisitTime);
  }
  void RegisterConnection(int start_point, int end_point, int position) {
    std::pair<int, int> forward_edge;
    std::pair<int, int> backward_edge;
    if (start_point < end_point) {
      forward_edge = {start_point, end_point};
      backward_edge = {end_point, start_point};
    } else {
      forward_edge = {end_point, start_point};
      backward_edge = {start_point, end_point};
    }
    edge_counter_[forward_edge]++;

    neighbor_map_[start_point][end_point] = position + 1;
    neighbor_map_[end_point][start_point] = position + 1;
    edge_index_lookup_[forward_edge] = position + 1;
    edge_index_lookup_[backward_edge] = position + 1;
  }

  void TraverseGraph(int current_vertex, int parent_vertex = -1) {
    marked_[current_vertex] = true;
    entry_time_[current_vertex] = clock_counter_;
    min_reachable_[current_vertex] = clock_counter_;
    clock_counter_++;

    for (const auto& edge_data : neighbor_map_[current_vertex]) {
      int adjacent_vertex = edge_data.first;
      if (adjacent_vertex == parent_vertex) {
        continue;
      }
      if (marked_[adjacent_vertex]) {
        min_reachable_[current_vertex] = std::min(
            min_reachable_[current_vertex], entry_time_[adjacent_vertex]);
      } else {
        TraverseGraph(adjacent_vertex, current_vertex);
        min_reachable_[current_vertex] = std::min(
            min_reachable_[current_vertex], min_reachable_[adjacent_vertex]);
        if (entry_time_[current_vertex] < min_reachable_[adjacent_vertex]) {
          std::pair<int, int> edge_pair;
          if (current_vertex < adjacent_vertex) {
            edge_pair = {current_vertex, adjacent_vertex};
          } else {
            edge_pair = {adjacent_vertex, current_vertex};
          }
          if (edge_counter_[edge_pair] == 1) {
            critical_edges_.push_back(
                edge_index_lookup_[{current_vertex, adjacent_vertex}]);
          }
        }
      }
    }
  }

  bool WasVisited(int vertex) const { return marked_[vertex]; }

  std::vector<int> GetBridgeList() {
    std::sort(critical_edges_.begin(), critical_edges_.end());
    return critical_edges_;
  }
};

int main() {
  int n;
  int m;
  std::cin >> n >> m;
  ConnectivityAnalyzer analyzer(n, m);
  for (int i = 0; i < m; ++i) {
    int source;
    int target;
    std::cin >> source >> target;
    analyzer.RegisterConnection(source, target, i);
  }
  for (int v = 1; v <= n; ++v) {
    if (!analyzer.WasVisited(v)) {
      analyzer.TraverseGraph(v);
    }
  }
  std::vector<int> results = analyzer.GetBridgeList();
  std::cout << results.size() << "\n";
  for (int id : results) {
    std::cout << id << " ";
  }
  return 0;
}