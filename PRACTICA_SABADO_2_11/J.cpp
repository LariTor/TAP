#include <bits/stdc++.h>
using namespace std;

typedef struct {
  double A, B, U, W;
  double u, w;
  double index;
} Recurso;

int main(int argc, char *argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  int N;
  cin >> N;

  double Ta = 0.;
  double Ca = 0.;
  double Tb = 0.;
  double Cb = 0.;

  Recurso recursos[100000];
  for (int i = 0; i < N; ++i) {
    double a, b, u, w;
    cin >> a >> u >> b >> w;
    double u_ = u + w;
    double in = b - a;
    recursos[i] = {
        .A = a, .B = b, .U = u, .W = w, .u = u_, .w = 0., .index = in};
    Ta += a * u_;
    Ca += a * u;
    Cb += b * w;
  }

  sort(recursos, recursos + N,
       [](Recurso &a, Recurso &b) { return a.index < b.index; });

  size_t i = 0;
  while (Ta > Ca) {
    Recurso rec = recursos[i];
    double saco = min((Ta - Ca) / rec.A, rec.u);
    rec.u -= saco;
    rec.w += saco;
    Ta -= rec.A * saco;
    Tb += rec.B * saco;
    recursos[i] = rec;
    i++;
  }
  i = N - 1;
  while (Tb > Cb) {
    Recurso rec = recursos[i];
    double saco = min((Tb - Cb) / rec.B, rec.w);
    rec.u += saco;
    rec.w -= saco;
    Ta += rec.A * saco;
    Tb -= rec.B * saco;
    recursos[i] = rec;
    i--;
  }

  cout << fixed;
  cout << setprecision(15);
  cout << Ta + Tb << '\n';

  return 0;
}
