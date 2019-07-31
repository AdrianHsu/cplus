#include <iostream>
#include <cstdio>
using namespace std;

int extgcd(int a, int b, int &x, int &y) {
  
  int d = a; 
  if(b != 0) {
    d = extgcd(b, a % b, x, y);
    int x_prime = x;
    x = y;
    y = x_prime - (a / b) * y;
  } else {
    x = 1; y = 0;
  }

  return d;
}

int main() {
  int x, y;
  cout << extgcd(12, 28, x, y) << endl;
  cout << x << "," << y << endl;
  return 0;
}
