#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

typedef struct {
  int a;
  int b;
  int c;
} Arma;

int n_p(Arma a, int p) { return std::floor((float)(p - a.b) / a.a); }

int solve(std::vector<Arma> &armas, int i, int p, int *memo) {
  if (p < 0)
    return -armas[i - 1].c;
  if (i == armas.size())
    return 0;
  if (memo[i + 200 * p] != -1)
    return memo[i + 200 * p];
  Arma a = armas[i];
  int ret = std::max(a.c + solve(armas, i + 1, n_p(a, p), memo),
                     solve(armas, i + 1, p, memo));
  memo[i + 200 * p] = ret;
  return ret;
}

int main(int argc, char *argv[]) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int n, p;
  std::cin >> n >> p;
  std::vector<Arma> armas;
  for (int i = 0; i < n; ++i) {
    int a, b, c;
    std::cin >> a >> b >> c;
    armas.push_back({.a = a, .b = b, .c = c});
  }
  auto comp = [](const Arma &a, const Arma &b) {
    int v1 = -a.b - b.b * a.a;
    int v2 = -b.b - a.b * b.a;
    if (v1 == v2)
      return a.c > b.c;
    return v1 > v2;
  };
  std::sort(armas.begin(), armas.end(), comp);
  int *memo = new int[200 * 100001];
  std::fill_n(memo, 200 * 100001, -1);

  int res = solve(armas, 0, p, memo);

  std::cout << res << std::endl;

  return 0;
}
