#include <array>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

enum class Direccion { Arriba, Abajo, Izquierda, Derecha };

typedef std::array<int, 1000> Fila;
typedef std::vector<std::string> FilaS;
typedef std::vector<FilaS> Tablero;

#define SECO "."

void tablero_p(Tablero &t) {
  std::cout << "\n";
  for (auto &f : t) {
    for (std::string &c : f) {
      std::cout << c << ' ';
    }
    std::cout << "\n";
  }
}

int resolver(Tablero &tablero, int i, int j, Direccion d, Fila &secas_filas,
             Fila &secas_colum, int n, int m) {
  tablero[i][j] = "X";
  if (d == Direccion::Abajo || d == Direccion::Arriba) {
    for (int k = m-1; k >= 0; --k) {
      if (tablero[i][k] == SECO) {
        Direccion nd = k < j ? Direccion::Izquierda : Direccion::Derecha;
        int ret =
            1 + resolver(tablero, i, k, nd, secas_filas, secas_colum, n, m);
        tablero[i][j] = std::to_string(ret);
        return ret;
      }
    }
    if (secas_filas[i] % 2 == 1) {
      int k = 0;
      int lim = i;
      if (d == Direccion::Abajo) {
        k = i + 1;
        lim = n;
      }
      for (; k < lim; ++k) {
        if (tablero[k][j] == SECO) {
          tablero[i][j] = SECO;
          return resolver(tablero, k, j, d, secas_filas, secas_colum, n, m);
        }
      }
    }
  } else {
    for (int k = 0; k < n; ++k) {
      if (tablero[k][j] == SECO) {
        Direccion nd = k < i ? Direccion::Arriba : Direccion::Abajo;
        int ret =
            1 + resolver(tablero, k, j, nd, secas_filas, secas_colum, n, m);
        tablero[i][j] = std::to_string(ret);
        return ret;
      }
    }
    if (secas_filas[i] % 2 == 1) {
      int k = 0;
      int lim = j;
      if (d == Direccion::Izquierda) {
        k = j + 1;
        lim = m;
      }
      for (; k < lim; ++k) {
        if (tablero[i][k] == SECO) {
          tablero[i][j] = SECO;
          return resolver(tablero, k, j, d, secas_filas, secas_colum, n, m);
        }
      }
    }
  }
  tablero[i][j] = "1";
  return 1;
}

int main(int argc, char *argv[]) {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);
  int n, m;
  std::cin >> n >> m;
  Tablero tablero;
  Fila secas_filas = {};
  Fila secas_colum = {};
  int secas = 0;
  int x, y;
  for (int i = 0; i < n; ++i) {
    FilaS fila;
    for (int j = 0; j < m; ++j) {
      char c;
      std::cin >> c;
      fila.push_back(std::string(1, c));
      int seco = c == '.';
      secas_colum[j] += seco;
      secas_filas[i] += seco;
      secas += seco;
      if (seco) {
        x = i;
        y = j;
      }
    }
    tablero.push_back(fila);
  }
  int impares = 0;
  int impf = -1;
  int impc = -1;
  for (int i = 0; i < n; ++i) {
    bool b = secas_filas[i] % 2;
    impares += b;
    if (b) {
      impf = i;
    }
  }
  for (int i = 0; i < m; ++i) {
    bool b = secas_colum[i] % 2;
    impares += b;
    if (b) {
      impc = i;
    }
  }
  if (impares != 0 && impares != 2) {
    std::cout << "*\n";
    return 0;
  }
  Direccion d = Direccion::Izquierda;
  if (impf != -1) {
    for (int i = 0; i < m; ++i) {
      if (tablero[impf][i] == SECO) {
        x = impf;
        y = i;
        break;
      }
    }
  } else if (impc != -1) {
    for (int i = 0; i < n; ++i) {
      if (tablero[i][impc] == SECO) {
        x = i;
        y = impc;
        d = Direccion::Abajo;
        break;
      }
    }
  }

  int visitadas = resolver(tablero, x, y, d, secas_filas, secas_colum, n, m);

  if (visitadas != secas) {
    std::cout << "*\n";
    return 0;
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      std::cout << std::setw(2) << tablero[i][j] << ' ';
    }
    std::cout << '\n';
  }

  return 0;
}
