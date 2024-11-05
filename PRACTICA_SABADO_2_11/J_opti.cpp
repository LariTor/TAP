#include <bits/stdc++.h>
using namespace std;

typedef struct {
  float A, B;
  float u;
} Recurso;

int main(int argc, char *argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);

  int N;
  cin >> N;

  float Ta = 0.;
  float Ca = 0.;
  float Tb = 0.;

  Recurso recursos[100000];
  for (int i = 0; i < N; ++i) {
    float a, b, u, w;
    cin >> a >> u >> b >> w;
    float u_ = u + w;
    recursos[i] = {.A = a, .B = b, .u = u_};
    Ta += a * w;
    Ca += a * u;
  }

  sort(recursos, recursos + N, [](const Recurso &a, const Recurso &b) {
    return (a.B - a.A) < (b.B - b.A);
  });

  for (size_t i = 0; Ta > 0.; ++i) {
    const Recurso &rec = recursos[i];
    float saco = min(Ta / rec.A, rec.u);
    Ta -= rec.A * saco;
    Tb += rec.B * saco;
  }

  cout << fixed << setprecision(15) << Ta + Tb + Ca << '\n';

  return 0;
}
