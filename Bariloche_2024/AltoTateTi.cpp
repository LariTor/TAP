#include <algorithm>
#include <array>
#include <iostream>
#include <limits>
#include <set>

typedef std::array<std::array<char, 3>, 3> Game;
typedef std::array<std::set<int>, 9> Restrictions;

bool game_over(Game game, int *ret) {
  if (game[0][0] != '.' && game[0][0] == game[1][1] &&
      game[1][1] == game[2][2]) {
    *ret = game[0][0] == 'O' ? -1 : 1;
    return true;
  }
  if (game[2][0] != '.' && game[2][0] == game[1][1] &&
      game[1][1] == game[0][2]) {
    *ret = game[2][0] == 'O' ? -1 : 1;
    return true;
  }
  for (int i = 0; i < 3; ++i) {
    if (game[0][i] != '.' && game[0][i] == game[1][i] &&
        game[1][i] == game[2][i]) {
      *ret = game[0][i] == 'O' ? -1 : 1;
      return true;
    }
    if (game[i][0] != '.' && game[i][0] == game[i][1] &&
        game[i][1] == game[i][2]) {
      *ret = game[i][0] == 'O' ? -1 : 1;
      return true;
    }
  }
  *ret = 0;
  bool over = true;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      over &= game[i][j] != '.';
    }
  }
  return over;
}

int min(int a, int b) { return std::min(a, b); }

int max(int a, int b) { return std::max(a, b); }

int minimax(Game game, int alpha, int beta, bool maximize,
            Restrictions restrictions) {
  int ret;
  if (game_over(game, &ret)) {
    return ret;
  }
  ret = std::numeric_limits<int>::max();
  char player = 'O';
  auto comp = min;
  if (maximize) {
    ret = std::numeric_limits<int>::min();
    player = 'X';
    comp = max;
  }
  bool moved = false;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (game[i][j] == '.' && restrictions[i * 3 + j].empty()) {
        moved = true;
        Game move = game;
        Restrictions new_res = restrictions;
        move[i][j] = player;
        for (int k = 0; k < 9; ++k) {
          new_res[k].erase(i * 3 + j);
        }
        int eval = minimax(move, alpha, beta, !maximize, new_res);
        ret = comp(ret, eval);
        if (maximize) {
          alpha = std::max(alpha, eval);
        } else {
          beta = std::min(beta, eval);
        }
        if (beta <= alpha) {
          break;
        }
      }
    }
  }
  return moved ? ret : 0;
}

int main(int argc, char *argv[]) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  Game game;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      game[i][j] = '.';
    }
  }

  Restrictions restrictions = {};

  int n;
  std::cin >> n;
  for (int i = 0; i < n; ++i) {
    int a, b;
    std::cin >> a >> b;
    restrictions[b - 1].insert(a - 1);
  }

  int winner = minimax(game, std::numeric_limits<int>::min(),
                       std::numeric_limits<int>::max(), true, restrictions);

  char winnerC = 'E';
  winnerC = winner > 0 ? 'X' : winnerC;
  winnerC = winner < 0 ? 'O' : winnerC;

  std::cout << winnerC << '\n';
  return 0;
}
