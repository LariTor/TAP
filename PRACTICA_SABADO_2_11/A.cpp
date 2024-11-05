#include <algorithm>
#include <bits/stdc++.h>
#include <climits>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
typedef long double ld;

typedef struct {
  ld x;
  ll m, b;
} Seg;

typedef struct min_hull_t {
  vector<Seg> hull;

  void insert(ll m, ll b) {
    while (hull.size()) {
      Seg s = hull.back();
      if (s.b + s.m * s.x < b + m * s.x) {
        if (s.m != m) {
          hull.push_back({(b - s.b) / (ld)(s.m - m), m, b});
        }
        return;
      }
      hull.pop_back();
    }
    hull = {{LLONG_MIN, m, b}};
  }

  ld query(ld x) {
    Seg s = *--upper_bound(hull.begin(), hull.end(), x,
                           [](ld a, Seg b) { return a < b.x; });
    return (ld)s.b + (ld)s.m * x;
  }

} MinHull;

typedef struct max_hull_t {
  vector<Seg> hull;

  void insert(ll m, ll b) {
    while (hull.size()) {
      Seg s = hull.back();
      if (s.b + s.m * s.x > b + m * s.x) {
        if (s.m != m) {
          hull.push_back({(b - s.b) / (ld)(s.m - m), m, b});
        }
        return;
      }
      hull.pop_back();
    }
    hull = {{LLONG_MIN, m, b}};
  }

  ld query(ld x) {
    Seg s = *--upper_bound(hull.begin(), hull.end(), x,
                           [](ld a, Seg b) { return a < b.x; });
    return (ld)s.b + (ld)s.m * x;
  }

} MaxHull;

template <class ForwardIterator>
pair<ForwardIterator *, ForwardIterator *>
min_it_endable(pair<ForwardIterator *, ForwardIterator *> a,
               pair<ForwardIterator *, ForwardIterator *> b) {
  if (*a.first == *a.second)
    return b;
  if (*b.first == *b.second)
    return a;
  return !((**b.first).x < (**a.first).x) ? a : b;
}

template <class ForwardIterator>
ForwardIterator *min_4_it(ForwardIterator *a, ForwardIterator *ae,
                          ForwardIterator *b, ForwardIterator *be,
                          ForwardIterator *c, ForwardIterator *ce,
                          ForwardIterator *d, ForwardIterator *de) {
  return min_it_endable(
             min_it_endable(pair<ForwardIterator *, ForwardIterator *>{a, ae},
                            pair<ForwardIterator *, ForwardIterator *>{b, be}),
             min_it_endable(pair<ForwardIterator *, ForwardIterator *>{c, ce},
                            pair<ForwardIterator *, ForwardIterator *>{d, de}))
      .first;
}

ld area(MinHull &min_x, MinHull &min_y, MaxHull &max_x, MaxHull &max_y, ld t) {
  return (max_x.query(t) - min_x.query(t)) * (max_y.query(t) - min_y.query(t));
}

int main(int argc, char *argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  size_t N;
  cin >> N;
  vector<Seg> X(N);
  vector<Seg> Y(N);
  for (size_t i = 0; i < N; ++i) {
    ll x, y, vx, vy;
    cin >> x >> y >> vx >> vy;
    X[i] = {.x = 0., .m = vx, .b = x};
    Y[i] = {.x = 0., .m = vy, .b = y};
  }

  auto ascendente = [](const Seg &a, const Seg &b) { return a.m < b.m; };
  auto descendente = [](const Seg &a, const Seg &b) { return a.m > b.m; };

  MinHull min_x;
  MinHull min_y;
  MaxHull max_x;
  MaxHull max_y;

  sort(X.begin(), X.end(), descendente);
  sort(Y.begin(), Y.end(), descendente);
  for (size_t i = 0; i < N; ++i) {
    min_x.insert(X[i].m, X[i].b);
    min_y.insert(Y[i].m, Y[i].b);
  }

  sort(X.begin(), X.end(), ascendente);
  sort(Y.begin(), Y.end(), ascendente);
  for (size_t i = 0; i < N; ++i) {
    max_x.insert(X[i].m, X[i].b);
    max_y.insert(Y[i].m, Y[i].b);
  }

  auto a = min_x.hull.begin();
  auto b = max_x.hull.begin();
  auto c = min_y.hull.begin();
  auto d = max_y.hull.begin();
  auto ae = min_x.hull.end();
  auto be = max_x.hull.end();
  auto ce = min_y.hull.end();
  auto de = max_y.hull.end();

  ld min_area = area(min_x, min_y, max_x, max_y, 0.);

  while (a != ae || b != be || c != ce || d != de) {
    auto minit = min_4_it(&a, &ae, &b, &be, &c, &ce, &d, &de);
    ld x = (**minit).x;
    if (x > 0.)
      min_area = min(min_area, area(min_x, min_y, max_x, max_y, x));
    (*minit)++;
  }

  cout << fixed << setprecision(15) << min_area << '\n';

  return 0;
}
