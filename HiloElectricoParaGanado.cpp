#include <algorithm>
#include <iomanip>
#include <iostream>
#include <limits>
#include <set>
#include <vector>
using namespace std;

class Punto;
class Cerco;
class Cierre;
class Evento;
struct PuntoCmp;

class Punto {
public:
  Punto(Punto &&) = default;
  Punto(const Punto &) = default;
  Punto &operator=(Punto &&) = default;
  Punto &operator=(const Punto &) = default;
  virtual ~Punto() = default;

  Punto(int x, int y) : x_m(x), y_m(y) {}

  int get_x() const { return x_m; }
  int get_y() const { return y_m; }

  virtual void evento(set<Evento *, PuntoCmp> &abiertos) = 0;

private:
  int x_m, y_m;
};

struct PuntoCmp {
  bool operator()(const Punto *lhs, const Punto *rhs) const {
    return lhs->get_y() < rhs->get_y();
  }
};

void evento_punto(set<Evento *, PuntoCmp> &, Punto *);
void evento_cerco(set<Evento *, PuntoCmp> &, Cerco *);
void evento_cierre(set<Evento *, PuntoCmp> &, Cierre *);

class Aterrizaje : public Punto {
public:
  Aterrizaje(Aterrizaje &&) = default;
  Aterrizaje(const Aterrizaje &) = default;
  Aterrizaje &operator=(Aterrizaje &&) = default;
  Aterrizaje &operator=(const Aterrizaje &) = default;
  ~Aterrizaje() = default;

  virtual void evento(set<Evento *, PuntoCmp> &abiertos) {
    evento_punto(abiertos, this);
  }

  Aterrizaje(int x, int y) : Punto(x, y) {}

private:
};

class Cerco : public Punto {
public:
  Cerco(Cerco &&) = default;
  Cerco(const Cerco &) = default;
  Cerco &operator=(Cerco &&) = default;
  Cerco &operator=(const Cerco &) = default;
  ~Cerco() = default;

  Cerco() : Punto(0, 0), x1_m(0), y1_m(0), nid(-1) {}
  Cerco(int x0, int y0, int x1, int y1)
      : Punto(x0, y0), x1_m(x1), y1_m(y1), nid(ids++) {}

  int get_x1() const { return this->x1_m; }
  int get_y1() const { return this->y1_m; }

  Cerco *get_padre() const { return this->padre; }

  void insertar_cerco(Cerco *c) {
    c->padre = this;
    this->hijos.push_back(c);
  }

  void insertar_punto() { this->M++; }
  int get_M() { return this->M; }
  double get_E() { return this->E; }

  void resolver() {
    if (this->hijos.size() == 0) {
      this->A += 1;
      return;
    }
    // for (Cerco *h : this->hijos) {
    // h->resolver();
    //}
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

  virtual void evento(set<Evento *, PuntoCmp> &abiertos) override {
    evento_cerco(abiertos, this);
  }

  int id() { return nid; }
  std::vector<Cerco *> &get_hijos() { return hijos; }

private:
  static int ids;
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

  int x1_m;
  int y1_m;
  int nid;
  double E = 0.0;
  double A = 0.0;
  int M = 0;
  vector<Cerco *> hijos = {};
  Cerco *padre = nullptr;
};

class Cierre : public Punto {
public:
  Cierre(Cierre &&) = default;
  Cierre(const Cierre &) = default;
  Cierre &operator=(Cierre &&) = default;
  Cierre &operator=(const Cierre &) = default;
  ~Cierre() = default;

  Cierre(Cerco *cerco)
      : Punto(cerco->get_x1(), cerco->get_y1()), cerco_m(cerco) {}

  Cerco *get_cerco() { return cerco_m; }

  virtual void evento(set<Evento *, PuntoCmp> &abiertos) override {
    evento_cierre(abiertos, this);
  }

private:
  Cerco *cerco_m;
};

class Evento : public Punto {
public:
  Evento(Evento &&) = default;
  Evento(const Evento &) = default;
  Evento &operator=(Evento &&) = default;
  Evento &operator=(const Evento &) = default;
  ~Evento() = default;

  Evento(Cerco *cerco, bool abre)
      : Punto(cerco->get_x(), abre ? cerco->get_y() : cerco->get_y1()),
        cerco_m(cerco), abre_m(abre) {}

  bool abierto() { return this->abre_m; }
  Cerco *get_cerco() { return cerco_m; }
  virtual void evento(set<Evento *, PuntoCmp> &) override {}

private:
  Cerco *cerco_m;
  bool abre_m;
};

int Cerco::ids = 0;

void evento_punto(set<Evento *, PuntoCmp> &abiertos, Punto *punto) {
  auto arr = abiertos.lower_bound((Evento *)punto);
  if (!(*arr)->abierto()) {
    (*arr)->get_cerco()->insertar_punto();
  } else {
    auto pre_arr = prev(arr);
    if ((*pre_arr)->abierto()) {
      (*pre_arr)->get_cerco()->insertar_punto();
    } else {
      (*pre_arr)->get_cerco()->get_padre()->insertar_punto();
    }
  }
}

void evento_cerco(set<Evento *, PuntoCmp> &abiertos, Cerco *cerco) {
  auto arr = abiertos.lower_bound((Evento *)cerco);
  if (!(*arr)->abierto()) {
    (*arr)->get_cerco()->insertar_cerco(cerco);
  } else {
    auto pre_arr = prev(arr);
    if ((*pre_arr)->abierto()) {
      (*pre_arr)->get_cerco()->insertar_cerco(cerco);
    } else {
      (*pre_arr)->get_cerco()->get_padre()->insertar_cerco(cerco);
    }
  }
  abiertos.insert(new Evento(cerco, true));
  abiertos.insert(new Evento(cerco, false));
}

void evento_cierre(set<Evento *, PuntoCmp> &abiertos, Cierre *cierre) {
  Evento *a = new Evento(cierre->get_cerco(), true);
  Evento *b = new Evento(cierre->get_cerco(), false);
  auto c = abiertos.extract(a);
  auto d = abiertos.extract(b);
  cierre->get_cerco()->resolver();
  delete a;
  delete b;
  delete c.value();
  delete d.value();
}

template <typename T, typename C>
std::ostream &operator<<(std::ostream &out, const std::set<T, C> &set) {
  if (set.empty())
    return out << "{}";
  out << "{ " << *set.begin();
  std::for_each(std::next(set.begin()), set.end(),
                [&out](const T &element) { out << ", " << element; });
  return out << " }";
}

std::ostream &operator<<(std::ostream &out, Evento *evento) {
  Cerco *cerco = evento->get_cerco();
  int y = evento->abierto() ? cerco->get_y() : cerco->get_y1();
  char abierto = evento->abierto() ? 'A' : 'C';
  out << '<' << y << ", " << abierto << ", C" << cerco->id() << '>';
  return out;
}

std::ostream &operator<<(std::ostream &out, Cerco *cerco) {
  out << "<(" << cerco->get_x() << ',' << cerco->get_y() << ")("
      << cerco->get_x1() << ',' << cerco->get_y1() << ") M=" << cerco->get_M()
      << " [";
  for (Cerco *h : cerco->get_hijos()) {
    out << h << ", ";
  }
  out << "]>";
  return out;
}

int main() {
  try {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout << fixed;
    cout << setprecision(10);

    int n, m;
    cin >> n >> m;

    vector<Punto *> eventos;
    for (int i = 0; i < n; ++i) {
      int x0, y0, x1, y1;
      cin >> x0 >> y0 >> x1 >> y1;
      Cerco *cer = new Cerco(x0, y0, x1, y1);
      eventos.push_back(cer);
      eventos.push_back(new Cierre(cer));
    }
    for (int i = 0; i < m; ++i) {
      int x, y;
      cin >> x >> y;
      eventos.push_back(new Aterrizaje(x, y));
    }
    auto comp = [](const Punto *a, const Punto *b) {
      return a->get_x() < b->get_x();
    };
    sort(eventos.begin(), eventos.end(), comp);
    set<Evento *, PuntoCmp> abiertos = {};
    Cerco *raiz =
        new Cerco(numeric_limits<int>::min(), numeric_limits<int>::min(),
                  numeric_limits<int>::max(), numeric_limits<int>::max());
    abiertos.insert(new Evento(raiz, true));
    abiertos.insert(new Evento(raiz, false));
    eventos.push_back(new Cierre(raiz));

    // cout << "------------------------------\n";
    for (Punto *p : eventos) {
      p->evento(abiertos);
      // cout << abiertos << '\n';
    }
    // cout << "------------------------------\n";

    // cout << raiz << '\n';

    // cout << "------------------------------\n";
    cout << raiz->get_E() << '\n';
  } catch (...) {
    cout << "HOLA\n";
  }

  return 0;
}
