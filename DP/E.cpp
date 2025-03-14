#include <cmath>
#include <iostream>
#include <string>
#include <vector>
std::vector<unsigned long> ans;
void FindAns(unsigned long k, unsigned long s,
             std::vector<std::vector<unsigned long>>& dp,
             std::vector<unsigned long>& w) {
  if (dp[k][s] == 0) {
  } else if (dp[k - 1][s] == dp[k][s]) {
    FindAns(k - 1, s, dp, w);
  } else {
    FindAns(k - 1, s - w[k - 1], dp, w);
    ans.push_back(k);
  }
}
int main() {
  unsigned long n;
  unsigned long m;
  std::cin >> n >> m;
  std::vector<unsigned long> w(n);
  std::vector<unsigned long> c(n);
  for (unsigned long i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  for (unsigned long i = 0; i < n; i++) {
    std::cin >> c[i];
  }
  std::vector<std::vector<unsigned long>> dp(n + 1,
                                             std::vector<unsigned long>(m + 1));
  for (unsigned long i = 1; i <= n; ++i) {
    for (unsigned long j = 0; j <= m; ++j) {
      dp[i][j] = dp[i - 1][j];
      if (j >= w[i - 1]) {
        dp[i][j] = std::max(dp[i][j], dp[i - 1][j - w[i - 1]] + c[i - 1]);
      }
    }
  }
  FindAns(n, m, dp, w);
  for (unsigned long i = 0; i < ans.size(); i++) {
    std::cout << ans[i] << '\n';
  }
}