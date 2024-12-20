#include <cmath>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef long long ll;

const ll N = 200010;
const ll L = 20;

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
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  ll n, k;
  cin >> n >> k;

  vector<ll> V(n);
  vector<ll> C(n);
  vector<ll> P(n);

  for (ll i = 0; i < n; ++i)
    cin >> V[i];
  for (ll i = 0; i < n; ++i)
    cin >> C[i];
  for (ll i = 0; i < n; ++i)
    cin >> P[i];

  LzSegTree seg;
  for (ll i = 0; i < n; ++i)
    seg.modifyP(i, V[i]);

  map<ll, vector<pair<ll, ll>>> imp;
  for (ll i = 0; i < n; ++i)
    imp[C[i]].push_back({i, P[i]});

  ll i = 0;
  ll res = 0;
  ll maxq, f;

  for (auto e : imp) {
    f = min(k, e.first);
    maxq = max(0LL, seg.querry(0, n));
    res += maxq * (f - i);
    i = f;
    for (auto trib : e.second)
      seg.modifyR(trib.first, n, trib.second);
  }
  f = k;
  maxq = max(0LL, seg.querry(0, n));
  res += maxq * (f - i);

  cout << res << '\n';

  return 0;
}
