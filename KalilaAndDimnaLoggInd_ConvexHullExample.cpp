#include <algorithm>
#include <bits/stdc++.h>
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
                           [](int a, Seg b) { return a < b.x; });
    return s.b + s.m * x;
  }

} Hull;

int main(int argc, char *argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int N;
  cin >> N;
  vector<int> A(N);
  vector<int> B(N);
  for (int i = 0; i < N; ++i)
    cin >> A[i];
  for (int i = 0; i < N; ++i)
    cin >> B[i];

  Hull h;

  h.insert(B[0], 0);
  for (int i = 1; i < N - 1; ++i) {
    h.insert(B[i], h.query(A[i]));
  }
  cout << h.query(A[N - 1]) << '\n';

  return 0;
}

/*

	dp[i] = min_{j<i}(A[i]*B[j]+dp[j])

*/

