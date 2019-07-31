#include <iostream>

#define MAX_M 15

using namespace std;
typedef long long ll;

int a[MAX_M];
int n, m;

int gcd(int a, int b) {
  if(b == 0)
    return a;

  return gcd(b, a % b);
}

void solve() {
  
  ll res = 0;
  for(int i = 1; i < (1 << m); i++) {
    
    int num = 0;
    for(int j = i; j != 0; j >>= 1)
      num += j & 1;

    ll lcm = 1;
    for(int k = 0; k < m; k++) {
      if(i >> k & 1) {
        lcm = lcm / gcd(lcm, a[k]) * a[k];

        if(lcm > n) break;
      }
    }
    if(num % 2 == 0)
      res -= (n / lcm);
    else
      res += (n / lcm);
  }
  cout << res << endl;
}

int main() {
  a[0] = 2;
  a[1] = 3;
  a[2] = 7;

  n = 100; m = 3;

  solve();
  return 0;
}
