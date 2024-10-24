#include <cmath>
#include <iostream>

using namespace std;

typedef long long ll;

const ll N = 8;
const ll L = 4;

struct LzSegTree {
  typedef ll T;
  typedef ll D;

  T idT = 0, t[2 * N];
  T idD = 0, d[N];
  ll x = (fill_n(d, N, idD), 0);

  T f(T a, T b) { return a + b; }
  T g(T a, D b) { return a + b; }
  D h(D a, D b) { return a + b; }

  void apply(ll p, D v) {
    t[p] = g(t[p], v);
    if (p < N)
      d[p] = h(d[p], v);
  }

  void push(ll p) {
    for (ll s = L - 1; s > 0; --s) {
      ll i = p >> s;
      apply(2 * i, d[i]);
      apply(2 * i + 1, d[i]);
      d[i] = idD;
    }
  }

  void modifyP(ll p, T v) {
    if (p < N) {
      push(p += N);
      t[p] = v;
    }
    while (p /= 2)
      t[p] = g(f(t[2 * p], t[2 * p + 1]), d[p]);
  }

  void modifyR(ll l, ll r, D v) {
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

  seg.modifyP(0, 2);
  seg.modifyP(1, 3);
  seg.modifyP(2, 5);
  seg.modifyP(3, 7);
  seg.modifyP(4, 9);
  seg.modifyP(5, 1);
  seg.modifyP(6, 3);
  seg.modifyP(7, 6);

  cout << seg.querry(0, 8) << '\n';
  for (int i = 0; i < 8; ++i) {
    cout << seg.querry(i, i + 1) << ' ';
  }
  cout << "\n\n";

  seg.modifyR(0, 5, 7);

  cout << seg.querry(0, 8) << '\n';
  for (int i = 0; i < 8; ++i) {
    cout << seg.querry(i, i + 1) << ' ';
  }
  cout << '\n';

  return 0;
}
