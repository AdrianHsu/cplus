#include <iostream>

using namespace std;

int main() {
  int a = 0, b = 1;
  if(a != 0 && b++ == 2) 
    cout << "?" << endl;
  cout << b << endl;
}
