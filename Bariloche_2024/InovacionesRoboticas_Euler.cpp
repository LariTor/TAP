#include <array>
#include <iostream>
#include <set>
#include <stack>
#include <string>
#include <vector>

using namespace std;

typedef vector<string> FilaS;
typedef vector<FilaS> Tablero;

typedef struct {
  int x;
  int y;
} Edge;

typedef struct {
  bool fila;
  int cord;
  set<Edge> edges;
} Vertex;

typedef array<Vertex, 1010> Fila;

bool operator<(const Edge &e0, const Edge &e1) {
  return (e0.x == e1.x) ? e0.y < e1.y : e0.x < e1.x;
}

int main(int argc, char *argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  Tablero tablero;
  Fila secas_filas = {};
  Fila secas_colum = {};

  int secas = 0;
  for (int i = 0; i < n; ++i) {
    FilaS fila;
    for (int j = 0; j < m; ++j) {
      char c;
      cin >> c;
      fila.push_back(string(1, c));
      if (c == '.') {
        Edge edge = {.x = i, .y = j};
        secas_filas[i].edges.insert(edge);
        secas_colum[j].edges.insert(edge);
        secas++;
      }
    }
    tablero.push_back(fila);
  }
  int impares = 0;
  int impf = -1;
  int impc = -1;
  for (int i = 0; i < n; ++i) {
    secas_filas[i].cord = i;
    secas_filas[i].fila = true;
    bool b = secas_filas[i].edges.size() % 2;
    impares += b;
    if (b) {
      impf = i;
    }
  }
  for (int i = 0; i < m; ++i) {
    secas_colum[i].cord = i;
    secas_colum[i].fila = false;
    bool b = secas_colum[i].edges.size() % 2;
    impares += b;
    if (b) {
      impc = i;
    }
  }
  if (impares != 0 && impares != 2) {
    cout << "*\n";
    return 0;
  }
  Vertex *current = nullptr;
  if (impf != -1) {
    current = &secas_filas[impf];
  }
  if (impc != -1) {
    current = &secas_colum[impc];
  }
  if (!current) {
    for (int i = 0; i < n; ++i) {
      if (!secas_filas[i].edges.empty()) {
        current = &secas_filas[i];
        break;
      }
    }
  }

  stack<Vertex *> pila = {};
  vector<Vertex *> circuit = {};

  while (!pila.empty() || !current->edges.empty()) {
    if (current->edges.empty()) {
      circuit.push_back(current);
      current = pila.top();
      pila.pop();
    } else {
      pila.push(current);
      Edge e = current->edges.extract(current->edges.begin()).value();
      current = current->fila ? &secas_colum[e.y] : &secas_filas[e.x];
      current->edges.erase(e);
    }
  }
  circuit.push_back(current);

  int visitadas = 0;
  for (int i = 1; i < circuit.size(); ++i) {
    Vertex *o = circuit[i - 1];
    Vertex *d = circuit[i];
    int x = o->fila ? o->cord : d->cord;
    int y = d->fila ? o->cord : d->cord;
    visitadas++;
    tablero[x][y] = to_string(visitadas);
  }

  if (visitadas != secas) {
    cout << "*\n";
    return 0;
  }
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cout << tablero[i][j] << ' ';
    }
    cout << '\n';
  }

  return 0;
}
