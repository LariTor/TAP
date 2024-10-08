#include <bits/stdc++.h>

using namespace std;

int solve(int i, int k, vector<vector<int>> &dp, vector<int> &V, vector<int> &C,
          vector<int> &P) {
  if (i >= dp.size() || k <= 0)
    return 0;
  if (dp[i][k - 1] == -1) {
    int G = P[i] * max(0, k - C[i]);
    for (int j = 0; j <= k; ++j) {
      int R = V[i] * j;
      int next = solve(i + 1, k - j, dp, V, C, P);
      dp[i][k - 1] = max(dp[i][k - 1], R - G + next);
    }
  }
  return dp[i][k - 1];
}

int main(int argc, char *argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int N, K;
  cin >> N >> K;

  vector<int> V(N);
  vector<int> C(N);
  vector<int> P(N);

  for (int i = 0; i < N; ++i)
    cin >> V[i];
  for (int i = 0; i < N; ++i)
    cin >> C[i];
  for (int i = 0; i < N; ++i)
    cin >> P[i];

  vector<vector<int>> dp(N, vector<int>(K, -1));

  cout << solve(0, K, dp, V, C, P) << '\n';

  return 0;
}
