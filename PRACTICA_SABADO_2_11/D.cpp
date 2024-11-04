#include <cmath>
#include <iostream>
#include <map>
using namespace std;

// factorizo N y retorno un mapa con factores primos y sus potencias
map<long long, int> factorizar(long long N) {
  map<long long, int> factores;
  for (long long d = 2; d * d <= N; ++d) {
    while (N % d == 0) {
      factores[d]++;
      N /= d;
    }
  }
  if (N > 1) {
    factores[N]++;
  }
  return factores;
}

bool tieneEstrategiaGanadora(long long N) {
  map<long long, int> factores = factorizar(N);

  if (factores.size() == 1) {
    // Caso 1: N = p^α
    int alpha = factores.begin()->second;
    return (alpha % 2 == 1); // si alfa es impar
  } else if (factores.size() == 2) {
    // Caso 2: N = p^α * q^β
    auto it = factores.begin();
    int alpha = it->second;
    ++it;
    int beta = it->second;

    // If α = β = 1, N es producto de 2 primos
    return (alpha == 1 && beta == 1);
  } else {
    // tercer caso :.N tiene al menos 3 diferentes divisores primos
    return false;
  }
}

int main() {
  long long N;
  cin >> N;
  cout << (tieneEstrategiaGanadora(N) ? 'Y' : 'N') << '\n';
  return 0;
}
