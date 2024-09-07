#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

struct Nodo {
  int valor;
  Nodo *siguiente = nullptr;
  Nodo *anterior = nullptr;
};

struct Lista {
  void push(int);
  void swap(Nodo *);
  void swapleft(Nodo *);

  Nodo *inicio = nullptr;
  Nodo *fin = nullptr;
  size_t len = 0;
};

void Lista::push(int val) {
  Nodo *nuevo = new Nodo;
  nuevo->valor = val;
  if (len == 0) {
    inicio = nuevo;
    fin = nuevo;
    len = 1;
    return;
  }
  fin->siguiente = nuevo;
  nuevo->anterior = fin;
  fin = nuevo;
  len++;
}

void Lista::swap(Nodo *ref) {
  Nodo *sig = ref->siguiente;
  ref->siguiente = fin;
  fin->siguiente = sig;
  Nodo *pre = fin->anterior;
  fin->anterior = ref;
  fin = pre;
  fin->siguiente = nullptr;
}

void Lista::swapleft(Nodo *ref) {
  Nodo *sig = ref->siguiente;
  ref->siguiente = inicio;
  Nodo *post = inicio->siguiente;
  inicio->siguiente = sig;
  inicio->anterior = ref;
  inicio = post;
  inicio->anterior = nullptr;
}

int main(int argc, char *argv[]) {
  int n, x;
  std::cin >> n >> x;
  std::vector<int> vec;
  for (int i = 0; i < n; ++i) {
    int aux;
    std::cin >> aux;
    vec.push_back(aux);
  }
  std::sort(vec.begin(), vec.end());
  Lista b;
  for (int v : vec) {
    b.push(v);
  }

  bool fail = false;

  for (Nodo *ptr = b.inicio; ptr != b.fin; ptr = ptr->siguiente) {
    if (ptr->valor + ptr->siguiente->valor == x) {
      if (ptr->siguiente->valor != b.fin->valor) {
        b.swap(ptr);
      } else if (ptr->valor != b.inicio->valor) {
        b.swapleft(ptr);
      } else {
        std::cout << "*\n";
        fail = true;
        break;
      }
    }
  }

  if (!fail) {
    for (Nodo *ptr = b.inicio; ptr != nullptr; ptr = ptr->siguiente) {
      std::cout << ptr->valor << ' ';
    }
    std::cout << std::endl;
  }

  return 0;
}
