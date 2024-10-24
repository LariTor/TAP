typedef long long ll;

const ll N = 10;

struct SegTree {
  typedef ll T;
  T id = 0, t[2 * N];

  T f(T a, T b) { return a + b; }

  void modify(ll p, T v) {
    for (t[p += N] = v; p /= 2;)
      t[p] = f(t[2 * p], t[2 * p + 1]);
  }

  T querry(ll l, ll r) {
    T resl = id, resr = id;
    for (l += N, r += N; l < r; l /= 2, r /= 2) {
      if (l & 1)
        resl = f(resl, t[l++]);
      if (r & 1)
        resr = f(t[--r], resr);
    }
    return f(resl, resr);
  }
};
