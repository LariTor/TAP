#include <algorithm>
#include <array>
#include <iostream>
#include <limits>

using namespace std;

typedef array<array<char, 50>, 50> Game;

typedef struct Restrictions_t {
  int x;
  int y;

  Restrictions_t add(Restrictions_t o) {
    return {
        .x = this->x + o.x,
        .y = this->y + o.y,
    };
  }
} Restrictions;

int lmin(int a, int b) { return min(a, b); }

int lmax(int a, int b) { return max(a, b); }

array<Restrictions, 4> res;
int n, m;

int minimax(Game game, int alpha, int beta, bool maximize,
            Restrictions restrictions) {
  int ret;
  ret = numeric_limits<int>::max();
  auto comp = lmin;
  if (maximize) {
    ret = numeric_limits<int>::min();
    comp = lmax;
  }
  bool moved = false;

  for (Restrictions r : res) {
    Restrictions celda = restrictions.add(r);
    if (celda.x >= 0 && celda.x < n && celda.y >= 0 && celda.y < m &&
        game[celda.x][celda.y] == '.') {
      moved = true;
      game[celda.x][celda.y] = '#';
      int eval = minimax(game, alpha, beta, !maximize, celda);
      game[celda.x][celda.y] = '.';
      ret = comp(ret, eval);
      if (maximize) {
        alpha = max(alpha, eval);
      } else {
        beta = min(beta, eval);
      }
      if (beta <= alpha) {
        break;
      }
    }
  }
  return moved ? ret : !maximize;
}

int main(int argc, char *argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  Game game;

  cin >> n >> m;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> game[i][j];
    }
  }

  res[0] = {.x = -1, .y = 0};
  res[1] = {.x = 1, .y = 0};
  res[2] = {.x = 0, .y = -1};
  res[3] = {.x = 0, .y = 1};

  int winner = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) {
      if (game[i][j] == '.') {
        game[i][j] = '#';
        winner += minimax(game, numeric_limits<int>::min(),
                          numeric_limits<int>::max(), false, {.x = i, .y = j});
        game[i][j] = '.';
      }
    }

  cout << winner << '\n';
  return 0;
}
