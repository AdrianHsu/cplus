#include <iostream>
using namespace std;

#define MAX_P 3

int fact[MAX_P];

int mod_fact(int n, int p, int &e) {
  e = 0;
  if(n == 0) return 1;

  int res = mod_fact(n / p, p, e);
  e += n / p;
  
  if(n / p % 2 != 0) 
    return res * (p - fact[n % p]) % p;
  else
    return res * fact[n % p] % p;
}

int main() {
  int p = 3, e;
  fact[0] = 1; // 0! mod 3
  fact[1] = 1;
  fact[2] = 2;
  cout << mod_fact(10, 3, e) << endl;
  cout << e << endl;
  return 0;
}
