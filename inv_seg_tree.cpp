typedef long long ll;

const ll N = 10;

struct InvSegTree {
  typedef ll T;
  T id = 0, t[2 * N];

  T f(T a, T b) { return a + b; }

  void modify(ll l, ll r, T v) {
    for (l += N, r += N; l < r; l /= 2, r /= 2) {
      if (l & 1)
        t[l] = f(t[l++], v);
      if (r & 1)
        t[--r] = f(t[r], v);
    }
  }

  T querry(ll p) {
    T res = id;
    for (p += N; p > 0; p /= 2)
      res = f(res, t[p]);
    return res;
  }
};
