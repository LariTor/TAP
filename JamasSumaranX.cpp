#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

struct Nodo {
  int valor;
  Nodo *siguiente;
  Nodo *anterior;
};

struct Lista {
  void push(int);
  void swap(Nodo *);
  void swapleft(Nodo *);

  Nodo *inicio;
  Nodo *fin;
  size_t len;
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
  Nodo *pre = ref->anterior;
  ref->siguiente = nullptr;
  ref->anterior = fin->anterior;
  fin->siguiente = sig;
  fin->anterior = pre;
  if (fin->anterior != nullptr) {
    fin->anterior->siguiente = fin;
  }
  if (fin->siguiente != nullptr) {
    fin->siguiente->anterior = fin;
  }
  fin = ref;
}

void Lista::swapleft(Nodo *ref) {
  Nodo *sig = ref->siguiente;
  Nodo *pre = ref->anterior;
  ref->siguiente = inicio->siguiente;
  ref->anterior = nullptr;
  inicio->siguiente = sig;
  inicio->anterior = pre;
  if (inicio->anterior != nullptr) {
    inicio->anterior->siguiente = inicio;
  }
  if (inicio->siguiente != nullptr) {
    inicio->siguiente->anterior = inicio;
  }
  inicio = ref;
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
  std::cout << "insertado\n";

  bool fail = false;

  for (Nodo *ptr = b.inicio; ptr != b.fin->anterior; ptr = ptr->siguiente) {
    if (ptr->valor + ptr->siguiente->valor == x) {
      if (ptr->valor != b.fin->valor) {
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
    for (Nodo *ptr = b.inicio; ptr != b.fin; ptr = ptr->siguiente) {
      std::cout << ptr->valor << ' ';
    }
    std::cout << std::endl;
  }

  return 0;
}
