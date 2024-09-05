#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

typedef struct {
  int a;
  int b;
  int c;
} Arma;

int pierdo(Arma a, int p) { return std::floor((float)(p - a.b) / a.a); }

int calc(std::vector<Arma> armas, int p, size_t i) {
  if (armas.size() == 0 || i >= armas.size()) {
    return 0;
  }
  Arma arma = armas[i];
  int p_nuevo = pierdo(arma, p);
  int take = 0;
  std::vector<Arma> armas_restantes;
  std::vector<Arma> *armas_salteadas = &armas;
  if (p_nuevo >= 0) {
    for (int j = 0; j < i; j++) {
      armas_restantes.push_back(armas[j]);
    }
    for (int j = i + 1; j < armas.size(); j++) {
      armas_restantes.push_back(armas[j]);
    }
    take = arma.c + calc(armas_restantes, p_nuevo, 0);
  } else {
    armas_salteadas = &armas_restantes;
  }
  int skip = calc(*armas_salteadas, p, i + 1);
  return std::max(take, skip);
}

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

  res = calc(armas, p, 0);

  std::cout << res << std::endl;

  return 0;
}
