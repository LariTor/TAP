#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

typedef struct {
  int a;
  int b;
  int c;
} Arma;

int p_nuevo(Arma a, int p) { return std::floor((float)(p - a.b) / a.a); }

int minimax(std::vector<Arma> armas, int alpha, int p, int hp) {
  if (armas.size() == 0 || p < 0) {
    return hp;
  }
  auto comp = [p](const Arma &a, const Arma &b) {
    int pa = p_nuevo(a, p);
    int pb = p_nuevo(b, p);
    if (pa == pb) {
      return a.c > b.c;
    }
    return pa > pb;
  };
  std::sort(armas.begin(), armas.end(), comp);
  int ret = hp;
  int p_prev = p + 1;
  int c_prev = -1;
  //std::cout << "armas\n";
  //for (Arma &arma : armas) {
    //std::cout << arma.a << ", " << arma.b << ", " << arma.c << "\n";
  //}
  //std::cout << "for\n";
  for (int i = 0; i < armas.size(); ++i) {
    int p_n = p_nuevo(armas[i], p);
    if (p_prev == p_n && armas[i].c < c_prev) {
      //std::cout << p_n << ' ' << p_prev << ' ' << armas[i].c << ' ' << c_prev
                //<< " continue\n";
      continue;
    }
    //std::cout << armas[i].a << ", " << armas[i].b << ", " << armas[i].c << "; "
              //<< alpha << "\n";
    p_prev = p_n;
    c_prev = armas[i].c;
    std::vector<Arma> move;
    int c_res = armas[i].c;
    for (int j = 0; j < i; ++j) {
      if (armas[j].b <= p_n) {
        move.push_back(armas[j]);
        c_res += armas[j].c;
      }
    }
    for (int j = i + 1; j < armas.size(); ++j) {
      if (armas[j].b <= p_n) {
        move.push_back(armas[j]);
        c_res += armas[j].c;
      }
    }
    if (alpha >= c_res + hp) {
      //std::cout << p_n << ' ' << p_prev << ' ' << armas[i].c << ' ' << c_prev
                //<< ' ' << alpha << ' ' << c_res << " break\n";
      break;
    }
    int danno = p_n < 0 ? 0 : armas[i].c;
    int eval = minimax(move, alpha, p_n, hp + danno);
    ret = std::max(ret, eval);
    alpha = std::max(alpha, ret);
  }
  return ret;
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

  res = minimax(armas, 0, p, 0);

  std::cout << res << std::endl;

  return 0;
}
