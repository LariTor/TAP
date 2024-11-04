#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(int argc, char *argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  ll R, C, K;
  cin >> R >> C >> K;

  for (ll i = 0; i < R; ++i) {
    bool A = true;
    for (ll j = 0; j < C; ++j) {
      char c;
      cin >> c;
      A &= c == '*';
    }
    bool B = false;
    for (ll j = 0; j < K; ++j) {
      char c;
      cin >> c;
      B |= c == '*';
    }
    if ((!A) && B) {
      cout << "N\n";
      return 0;
    }
  }

  cout << "Y\n";

  return 0;
}
