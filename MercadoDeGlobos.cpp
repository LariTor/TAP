#include <cmath>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef long long ll;

const ll N = 8;
const ll L = 4;

struct LzSegTree {
  typedef ll T;
  typedef ll U;

  T idT = 0, t[2 * N];
  U idU = 0, u[N];
  ll x = (fill_n(u, N, idU), 0);

  T f(T a, T b) { return max(a, b); }
  T g(T a, U b) { return a - b; }
  U h(U a, U b) { return a + b; }

  void apply(ll p, U v) {
    t[p] = g(t[p], v);
    if (p < N)
      u[p] = h(u[p], v);
  }

  void push(ll p) {
    for (ll s = L - 1; s > 0; --s) {
      ll i = p >> s;
      apply(2 * i, u[i]);
      apply(2 * i + 1, u[i]);
      u[i] = idU;
    }
  }

  void modifyP(ll p, T v) {
    if (p < N) {
      push(p += N);
      t[p] = v;
    }
    while (p /= 2)
      t[p] = g(f(t[2 * p], t[2 * p + 1]), u[p]);
  }

  void modifyR(ll l, ll r, U v) {
    ll l0 = (l += N), r0 = (r += N);
    for (; l < r; l /= 2, r /= 2) {
      if (l & 1)
        apply(l++, v);
      if (r & 1)
        apply(--r, v);
    }
    modifyP(l0, idT), modifyP(r0 - 1, idT);
  }

  T querry(ll l, ll r) {
    l += N, r += N;
    push(l), push(r - 1);
    T resl = idT, resr = idT;
    for (; l < r; l /= 2, r /= 2) {
      if (l & 1)
        resl = f(resl, t[l++]);
      if (r & 1)
        resr = f(t[--r], resr);
    }
    return f(resl, resr);
  }
};

int main(int argc, char *argv[]) {
  LzSegTree seg;

  int n = 5;
  int k = 6;

  vector<ll> V = {5, 7, 8, 8, 10};
  vector<ll> C = {2, 0, 3, 0, 2};
  vector<ll> P = {2, 2, 2, 1, 2};

  for (int i = 0; i < n; ++i)
    seg.modifyP(i, V[i]);

  map<int, vector<pair<int, int>>> imp;
  imp[0] = {};
  for (int i = 0; i < n; ++i)
    imp[C[i]].push_back({i, P[i]});

  int i = 0;
  int f = 0;
  int res = 0;

  for (auto e : imp) {
    // Sacable
    cout << seg.querry(0, n) << '\n';
    for (int i = 0; i < n; ++i) {
      cout << seg.querry(i, i + 1) << ' ';
    }

    f = e.first;
    int max = seg.querry(0, n);
    res += max * (f - i);
    i = f;
    for (auto trib : e.second) {
      seg.modifyR(trib.first, n, trib.second);
    }

    // Sacable
    cout << '\n' << res << "\n\n";
  }
  f = k;
  int max = seg.querry(0, n);
  res += max * (f - i);

  // Sacable
  cout << seg.querry(0, n) << '\n';
  for (int i = 0; i < n; ++i) {
    cout << seg.querry(i, i + 1) << ' ';
  }
  cout << "\n\n";

  cout << res << '\n';

  return 0;
}
