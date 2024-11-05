#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

bool ntS(vector<int> &clientes, size_t &i);
bool ntA(vector<int> &clientes, size_t &i);
bool ntB(vector<int> &clientes, size_t &i);
bool ntC(vector<int> &clientes, size_t &i, int);
bool ntD(vector<int> &clientes, size_t &i);
bool ntE(vector<int> &clientes, size_t &i, int);

vector<int> sobran = {};
string res = "";

bool ntS(vector<int> &clientes, size_t &i) {
  if (i >= clientes.size() || clientes[i] < 0)
    return false;
  int cliente = clientes[i];
  res.push_back('G');
  bool ret = ntA(clientes, ++i);
  if (i >= clientes.size() || cliente != -clientes[i])
    return false;
  return ret && ntB(clientes, ++i);
}

bool ntA(vector<int> &clientes, size_t &i) {
  if (i >= clientes.size())
    return false;
  int cliente = clientes[i];
  if (cliente < 0)
    return true;
  return ntC(clientes, ++i, cliente);
}

bool ntC(vector<int> &clientes, size_t &i, int cliente_previo) {
  if (i >= clientes.size())
    return true;
  int cliente = clientes[i];
  if (cliente < 0) {
    if (-cliente == cliente_previo) {
      ++i;
      res.push_back('G');
    } else {
      sobran.push_back(cliente_previo);
      res.push_back('S');
    }
    return true;
  }
  return ntC(clientes, ++i, cliente);
}

bool ntB(vector<int> &clientes, size_t &i) {
  if (i >= clientes.size())
    return true;
  int cliente = clientes[i];
  if (cliente < 0) {
    sobran.push_back(cliente);
    return ntB(clientes, ++i);
  }
  return ntD(clientes, i);
}

bool ntD(vector<int> &clientes, size_t &i) {
  if (i >= clientes.size() || clientes[i] < 0)
    return false;
  res.push_back('G');
  int cliente = clientes[i];
  bool ret = ntE(clientes, ++i, cliente);
  return ret && ntB(clientes, i);
}

bool ntE(vector<int> &clientes, size_t &i, int cliente_previo) {
  if (i >= clientes.size())
    return false;
  int cliente = clientes[i];
  if (cliente < 0) {
    if (-cliente == cliente_previo) {
      ++i;
      return true;
    } else {
      sobran.push_back(cliente);
      return ntE(clientes, ++i, cliente_previo);
    }
  }
  bool ret = ntC(clientes, ++i, cliente);
  return ret && ntE(clientes, i, cliente_previo);
}

bool ntZ(vector<int> &clientes, size_t &i) {
  if (i >= clientes.size() || clientes[i] < 0)
    return true;
  int cliente = clientes[i];
  bool ret = ntZ(clientes, ++i);
  if (i >= clientes.size() || cliente != -clientes[i])
    return false;
  return ret && ntZ(clientes, ++i);
}

int main(int argc, char *argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  int N;
  cin >> N;

  vector<int> clientes(2 * N);
  for (int i = 0; i < 2 * N; ++i)
    cin >> clientes[i];

  size_t i = 0;
  bool s = ntS(clientes, i);
  i = 0;
  bool z = ntZ(sobran, i);
  /*cout << s << ' ' << z << '\n';
  for (int s : sobran) {
    cout << s << '\n';
  }*/
  string out = s && z ? res : "*";
  cout << out << '\n';

  return 0;
}
