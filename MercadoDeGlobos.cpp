#include <cmath>
#include <iostream>

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

  seg.modifyP(0, 5);
  seg.modifyP(1, 7);
  seg.modifyP(2, 8);
  seg.modifyP(3, 8);
  seg.modifyP(4, 10);

  cout << seg.querry(0, n) << '\n';
  for (int i = 0; i < n; ++i) {
    cout << seg.querry(i, i + 1) << ' ';
  }
  cout << "\n\n";

  seg.modifyR(1, 5, 2);
  seg.modifyR(3, 5, 1);

  cout << seg.querry(0, n) << '\n';
  for (int i = 0; i < n; ++i) {
    cout << seg.querry(i, i + 1) << ' ';
  }
  cout << "\n\n";

  seg.modifyR(0, 5, 2);
  seg.modifyR(4, 5, 2);

  cout << seg.querry(0, n) << '\n';
  for (int i = 0; i < n; ++i) {
    cout << seg.querry(i, i + 1) << ' ';
  }
  cout << "\n\n";

  seg.modifyR(2, 5, 2);

  cout << seg.querry(0, n) << '\n';
  for (int i = 0; i < n; ++i) {
    cout << seg.querry(i, i + 1) << ' ';
  }
  cout << "\n\n";

  return 0;
}
