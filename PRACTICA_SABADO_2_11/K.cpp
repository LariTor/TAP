#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(int argc, char *argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  set vocales = {'A', 'E', 'I', 'O', 'U', 'Y'};

  ll N;
  cin >> N;

  vector<string> palabras(N);

  for (ll i = 0; i < N; ++i) {
    cin >> palabras[i];
  }

  ll cont = N;
  string *prev;
  string *pprev;

  int con_consec = 0;
  bool exito = true;
  for (string &palabra : palabras) {
    con_consec++;
    if (vocales.count(palabra[0])) {
      con_consec = 0;
    }
    if (con_consec == 3) {
      if (prev->length() > 1 && vocales.count((*prev)[1])) {
        cont++;
        con_consec = 1;
      } else if (pprev->length() > 1 && vocales.count((*pprev)[1])) {
        cont++;
        con_consec = 2;
      } else if (pprev->length() > 2 && vocales.count((*pprev)[2])) {
        cont += 2;
        con_consec = 2;
      } else {
        cout << '*' << '\n';
        return 0;
      }
    }
    pprev = prev;
    prev = &palabra;
  }

  cout << cont << '\n';

  return 0;
}
