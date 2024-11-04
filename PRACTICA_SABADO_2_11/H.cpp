#include <bits/stdc++.h>
#include <string>

using namespace std;

typedef long long ll;

void I(bool &i, ll &R) { i ^= true; }
void L(bool &i, ll &R, ll n) {
  if (i) {
    R += n;
  } else {
    R -= n;
  }
}
void R(bool &i, ll &R, ll n) {
  if (i) {
    R -= n;
  } else {
    R += n;
  }
}

inline ll mod(ll a, ll b) {
  ll ret = a % b;
  return ret >= 0 ? ret : ret + b;
}

ll eq(bool inverted, ll r_shift, ll periodo, ll offset) {
  if (inverted) {
    if (offset < 0) {
      return -1LL - mod(r_shift, periodo);
    }
    r_shift -= offset;
  }
  return mod(r_shift, periodo);
}

ll comb(ll n, ll k) {
  if (k > n)
    return 0;
  if (k * 2 > n)
    k = n - k;
  if (k == 0)
    return 1;

  ll result = n;
  for (ll i = 2; i <= k; ++i) {
    result *= (n - i + 1);
    result /= i;
  }
  return result;
}

int main(int argc, char *argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  string S;
  cin >> S;

  ll K;
  cin >> K;

  ll r = 0LL;
  bool In = false;
  string SS = S + S;
  ll p = SS.find(S, 1);
  reverse(S.begin(), S.end());
  ll offset = SS.find(S);

  if (offset == string::npos) {
    offset = -1LL;
  }

  map<ll, ll> valores;
  valores[eq(In, r, p, offset)]++;

  for (ll i = 0LL; i < K; ++i) {
    char op;
    ll num;
    cin >> op;
    if (op != 'I')
      cin >> num;
    switch (op) {
    case 'I':
      I(In, r);
      break;
    case 'L':
      L(In, r, num);
      break;
    case 'R':
      R(In, r, num);
      break;
    }
    valores[eq(In, r, p, offset)]++;
  }

  ll cont = 0LL;

  for (auto v : valores) {
    cont += comb(v.second, 2LL);
  }

  cout << cont << '\n';

  return 0;
}
