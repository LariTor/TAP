#include <algorithm>
#include <array>
#include <iostream>
#include <limits>

typedef std::array<std::array<char, 3>, 3> Game;

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

typedef struct {
  int eval;
  Game game;
} MiniMaxedGame;

MiniMaxedGame min(MiniMaxedGame a, MiniMaxedGame b) {
  return a.eval < b.eval ? a : b;
}

MiniMaxedGame max(MiniMaxedGame a, MiniMaxedGame b) {
  return a.eval < b.eval ? b : a;
}

MiniMaxedGame minimax(Game game, int alpha, int beta, bool maximize) {
  MiniMaxedGame ret = {.game = game};
  if (game_over(game, &ret.eval)) {
    return ret;
  }
  ret.eval = std::numeric_limits<int>::max();
  char player = 'O';
  auto comp = min;
  if (maximize) {
    ret.eval = std::numeric_limits<int>::min();
    player = 'X';
    comp = max;
  }
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (game[i][j] == '.') {
        Game move = game;
        move[i][j] = player;
        MiniMaxedGame eval = minimax(move, alpha, beta, !maximize);
        eval.game = move;
        ret = comp(ret, eval);
        if (maximize) {
          alpha = std::max(alpha, eval.eval);
        } else {
          beta = std::min(beta, eval.eval);
        }
        if (beta <= alpha) {
          break;
        }
      }
    }
  }
  return ret;
}

void print(Game &game) {
  for (auto row : game) {
    for (char cell : row) {
      std::cout << cell << "|";
    }
    std::cout << "\n-+-+-\n";
  }
}

int main(int argc, char *argv[]) {
  Game game;
  for (int i = 0; i < 3; ++i) {
    for (int j = 0; j < 3; ++j) {
      game[i][j] = '.';
    }
  }
  int winner;
  bool pc = true;
  while (!game_over(game, &winner)) {
    if (pc) {
      MiniMaxedGame pc_move = minimax(game, std::numeric_limits<int>::min(),
                                      std::numeric_limits<int>::max(), true);
      game = pc_move.game;
      print(game);
    } else {
      int x = -1, y = -1;
      while (x < 0 && y < 0) {
        std::cin >> x >> y;
        x = x >= 0 && x < 3 ? x : -1;
        y = y >= 0 && y < 3 ? y : -1;
        if (x != -1 && y != -1 && game[x][y] != '.') {
          x = -1;
          y = -1;
        }
      }
      game[x][y] = 'O';
    }
    pc ^= true;
  }

  char winnerC = 'E';
  winnerC = winner > 0 ? 'X' : winnerC;
  winnerC = winner < 0 ? 'O' : winnerC;

  std::cout << "Winner: " << winnerC << '\n';
  return 0;
}
