#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <vector>
using namespace std;

struct Cerco {
  int x0;
  int y0;
  int x1;
  int y1;
  vector<Cerco *> hijos;
  Cerco *padre;
  int M;
  double A;
  double E;

  inline void insertar_cerco(Cerco *c) {
    c->padre = this;
    this->hijos.push_back(c);
  }

  inline void insertar_punto() { this->M++; }

  void resolver() {
    if (this->hijos.size() == 0) {
      this->A += 1;
      return;
    }
    Cerco *hijo = this->mergeFus(0, this->hijos.size() - 1);
    int lM = hijo->M + this->M;
    double lA;
    double lE;
    if (lM == 0) {
      lA = 0.0;
      lE = 0.0;
    } else {
      double Ph = (double)hijo->M / lM;
      double Pp = (double)this->M / lM;
      double Phh = Ph * Ph;
      double Php = Ph * Pp;
      lA = hijo->A * Ph + this->A * Pp + 1;
      lE = hijo->E * Phh + 2 * hijo->A * Php;
    }
    this->M = lM;
    this->A = lA;
    this->E = lE;
  }

  void fusionarCerco(Cerco *otro) {
    int lM = this->M + otro->M;
    double lA;
    double lE;
    if (lM == 0) {
      lA = 0.0;
      lE = 0.0;
    } else {
      double P0 = (double)otro->M / lM;
      double P1 = (double)this->M / lM;
      double P00 = P0 * P0;
      double P01 = P0 * P1;
      double P11 = P1 * P1;
      lA = otro->A * P01 + otro->M * P1;
      lE = otro->E * P00 + this->E * P11 + 2 * (otro->A + this->A) * P01;
    }
    this->M = lM;
    this->A = lA;
    this->E = lE;
  }

  Cerco *mergeFus(size_t L, size_t R) const {
    if (L == R) {
      return this->hijos[L];
    }
    size_t mid = (R - L) / 2;
    Cerco *ret = this->mergeFus(L, mid);
    Cerco *otro = this->mergeFus(mid + 1, R);
    ret->fusionarCerco(otro);
    delete otro;
    return ret;
  }
};

enum class TipoDeEvento { AbroCerco, PuntoAterrizaje, CierroCerco };

union Sujeto {
  int y;
  Cerco *cerco;
};

struct Evento {
  int x;
  TipoDeEvento tipo;
  Sujeto sujeto;
};

struct Abierto {
  bool abierto_y;
  Cerco *cerco_m;
};

inline void evento_punto(map<int, Abierto> &abiertos, int y) {
  auto arr = abiertos.lower_bound(y);
  if (!(*arr).second.abierto_y) {
    (*arr).second.cerco_m->insertar_punto();
  } else {
    auto pre_arr = prev(arr);
    if ((*pre_arr).second.abierto_y) {
      (*pre_arr).second.cerco_m->insertar_punto();
    } else {
      (*pre_arr).second.cerco_m->padre->insertar_punto();
    }
  }
}

inline void evento_cerco(map<int, Abierto> &abiertos, Cerco *cerco) {
  auto arr = abiertos.lower_bound(cerco->y0);
  if (!(*arr).second.abierto_y) {
    (*arr).second.cerco_m->insertar_cerco(cerco);
  } else {
    auto pre_arr = prev(arr);
    if ((*pre_arr).second.abierto_y) {
      (*pre_arr).second.cerco_m->insertar_cerco(cerco);
    } else {
      (*pre_arr).second.cerco_m->padre->insertar_cerco(cerco);
    }
  }
  abiertos[cerco->y0] = {.abierto_y = true, .cerco_m = cerco};
  abiertos[cerco->y1] = {.abierto_y = false, .cerco_m = cerco};
}

inline void evento_cierre(map<int, Abierto> &abiertos, Cerco *cerco) {
  abiertos.erase(cerco->y0);
  abiertos.erase(cerco->y1);
  cerco->resolver();
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout << fixed;
  cout << setprecision(10);

  int n, m;
  cin >> n >> m;

  vector<Evento> eventos;
  for (int i = 0; i < n; ++i) {
    int x0, y0, x1, y1;
    cin >> x0 >> y0 >> x1 >> y1;
    Cerco *cer = new Cerco;
    *cer = {
        .x0 = x0,
        .y0 = y0,
        .x1 = x1,
        .y1 = y1,
        .hijos = {},
        .padre = nullptr,
        .M = 0,
        .A = 0.0,
        .E = 0.0,
    };
    eventos.push_back(
        {.x = x0, .tipo = TipoDeEvento::AbroCerco, .sujeto = Sujeto{.cerco = cer}});
    eventos.push_back(
        {.x = x1, .tipo = TipoDeEvento::CierroCerco, .sujeto = Sujeto{.cerco = cer}});
  }
  for (int i = 0; i < m; ++i) {
    int x, y;
    cin >> x >> y;
    eventos.push_back(
        {.x = x, .tipo = TipoDeEvento::PuntoAterrizaje, .sujeto = {.y = y}});
  }
  auto comp = [](const Evento &a, const Evento &b) { return a.x < b.x; };
  sort(eventos.begin(), eventos.end(), comp);
  Cerco raiz = {
      .x0 = numeric_limits<int>::min(),
      .y0 = numeric_limits<int>::min(),
      .x1 = numeric_limits<int>::max(),
      .y1 = numeric_limits<int>::max(),
      .hijos = {},
      .padre = nullptr,
      .M = 0,
      .A = 0.0,
      .E = 0.0,
  };
  eventos.push_back({.x = raiz.x1,
                     .tipo = TipoDeEvento::CierroCerco,
                     .sujeto = Sujeto{.cerco = &raiz}});
  map<int, Abierto> abiertos = {};
  abiertos[raiz.y0] = {.abierto_y = true, .cerco_m = &raiz};
  abiertos[raiz.y1] = {.abierto_y = false, .cerco_m = &raiz};

  for (Evento &e : eventos) {
    switch (e.tipo) {
    case TipoDeEvento::AbroCerco:
      evento_cerco(abiertos, e.sujeto.cerco);
      break;
    case TipoDeEvento::PuntoAterrizaje:
      evento_punto(abiertos, e.sujeto.y);
      break;
    case TipoDeEvento::CierroCerco:
      evento_cierre(abiertos, e.sujeto.cerco);
      break;
    }
  }

  cout << raiz.E << '\n';

  return 0;
}
