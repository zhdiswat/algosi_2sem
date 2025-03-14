#include <cmath>
#include <iostream>
#include <string>
#include <vector>
const int cMag = 2147483647;
int main() {
  int n;
  std::cin >> n;
  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    std::cin >> a[i];
  }
  std::vector<int> d(n + 1, cMag);
  std::vector<int> pos(n + 1, -1);
  std::vector<int> prev(n, -1);
  d[0] = -cMag;
  int length = 0;
  for (int i = 0; i < n; i++) {
    int left = 0;
    int right = length + 1;
    while (right - left > 1) {
      int mid = (left + right) / 2;
      if (d[mid] >= a[i]) {
        left = mid;
      } else {
        right = mid;
      }
    }
    if (d[right] > a[i]) {
      d[right] = a[i];
      pos[right] = i;
      prev[i] = pos[right - 1];
      length = std::max(length, right);
    }
  }
  std::cout << length << '\n';
  std::vector<int> ans;
  int p = pos[length];
  while (p != -1) {
    ans.push_back(p + 1);
    p = prev[p];
  }
  for (int i = ans.size(); i > 0; i--) {
    std::cout << ans[i - 1] << " ";
  }
}