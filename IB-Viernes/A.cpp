#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  ios_base::sync_with_stdio(false);
  cin.tie(0);

  long long n, m;
  cin >> n >> m;

  long long A = 0;
  for (int i = 0; i < n; ++i) {
    int a;
    cin >> a;
    A += a;
  }

  long long B = (n + 1) * (n / 2 + (n % 2));

  return 0;
}
