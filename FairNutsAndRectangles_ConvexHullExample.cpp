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
      if (s.b + s.m * s.x > b + m * s.x) {
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

  int N;
  cin >> N;
  vector<Rect> R(N);
  for (int i = 0; i < N; ++i) {
    long long x, y, a;
    cin >> x >> y >> a;
    R[i] = {x, y, a};
  }
  sort(R.begin(), R.end(),
       [](const Rect &a, const Rect &b) { return a.w < b.w; });

  Hull h;

  long long res = 0;
  h.insert(0, 0);
  for (int i = 0; i < N; ++i) {
    Rect r = R[i];
    long long dpi = r.w * r.h - r.a + h.query(-r.h);
    res = max(res, dpi);
    h.insert(r.w, dpi);
  }
  cout << res << '\n';

  return 0;
}

/*

	dp[i] = max_{j<i}(h[i]*(w[i]-w[j])-a[i]+dp[j])

	dp[i] = h[i]*w[i]-a[i]+max_{j<i}(w[j]*(-h[i])+dp[j])

*/
