#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

typedef struct {
  long double x;
  long long m, b;
} Seg;

typedef struct hull_t {
  vector<Seg> hull;

  void insert(long long m, long long b) {
    while (hull.size()) {
      Seg s = hull.back();
      if (s.b + s.m * s.x < b + m * s.x) {
        if (s.m != m) {
          hull.push_back({(b - s.b) / (long double)(s.m - m), m, b});
        }
        return;
      }
      hull.pop_back();
    }
    hull = {{LLONG_MIN, m, b}};
  }

  long long query(long long x) {
    Seg s = *--upper_bound(hull.begin(), hull.end(), x,
                           [](long long a, Seg b) { return a < b.x; });
    return s.b + s.m * x;
  }

} Hull;

typedef struct {
  long long w, h, a;
} Rect;

int main(int argc, char *argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int N, M, P;
  cin >> N >> M >> P;
  vector<int> X(N);
  vector<int> tpo(M + 1);
  vector<int> prtpo(M + 1);
  for (int i = 1; i < N; ++i) {
    int d;
    cin >> d;
    X[i] = d + X[i - 1];
  }
  for (int i = 0; i < M; ++i) {
    int h, t;
    cin >> h >> t;
    tpo[i] = t - X[h - 1];
  }
  sort(tpo.begin(), tpo.end());
  prtpo[0] = tpo[0];
  for (int i = 1; i <= M; ++i) {
    prtpo[i] = tpo[i] + prtpo[i - 1];
  }

  long long dp[M + 1][P + 1];

  for (int j = 1; j <= P; ++j) {
    Hull h;
    h.insert(0, 0);
    for (int i = 1; i <= M; ++i) {
      dp[i][j] = prtpo[i] + h.query(i);
      h.insert(-tpo[i + 1], dp[i][j - 1] + tpo[i + 1] * (i + 1) - prtpo[i + 1]);
    }
  }
  cout << dp[M][P] << '\n';

  return 0;
}

/*

        dp[i] = min_{j<i}(prtpo[i]-prtpo[j]-tpo[j]*(i-j)+dp[j-1])

        dp[i] = prtpo[i] + min_{j<i](-tpo[j]*i + dp[j-1]+tpo[j]*j-prtpo[j])

*/
