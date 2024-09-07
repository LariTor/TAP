#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

typedef struct {
  int a;
  int b;
  int c;
} Arma;

int pierdo(Arma a, int p) { return p - std::floor((float)(p - a.b) / a.a); }

int dif(Arma a, int p) { return a.c - pierdo(a, p); }

int main(int argc, char *argv[]) {
  int n, p;
  std::cin >> n >> p;
  std::vector<Arma> armas;
  for (int i = 0; i < n; ++i) {
    int a, b, c;
    std::cin >> a >> b >> c;
    armas.push_back({.a = a, .b = b, .c = c});
  }
  int res = 0;

  while (armas.size() > 0) {
    auto comp = [p](const Arma &a, const Arma &b) {
      return dif(a, p) < dif(b, p);
    };
    std::sort(armas.begin(), armas.end(), comp);
    Arma mejor;
    int pierdo_v;
    do {
      mejor = armas.back();
      armas.pop_back();
      pierdo_v = pierdo(mejor, p);
    } while (pierdo_v > p && armas.size() > 0);
    if (pierdo_v > p) {
      break;
    }
    p -= pierdo_v;
    res += mejor.c;
  }

  std::cout << res << std::endl;

  return 0;
}
