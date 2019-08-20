#include <cstdio>
#include <iostream>
#include <string>

typedef unsigned long long ull;
const ull B = 100000007;

using namespace std;

int naive(string a, string b) {
  int cnt = 0;
  int al = a.length(), bl = b.length();
  if(al > bl) return 0;
  
  for(int i = 0; i <= bl - al; i++) {
    int j;
    for(j = 0; j < al; j++)
      if(b[i + j] != a[j]) break;
    if(j == al) cnt++;
  }
  
  return cnt;
}

int rabinKarp(string a, string b) {
  
  int al = a.length(), bl = b.length();
  if(al > bl) return 0;
  
  ull t = 1;
  for(int i = 0; i < al; i++) 
    t *= B;

  ull ah = 0, bh = 0;
  for(int i = 0; i < al; i++) ah = ah * B + a[i];
  for(int i = 0; i < al; i++) bh = bh * B + b[i];
  
  int cnt = 0, i = 0;
  while(i + al <= bl) {
    if(ah == bh) cnt ++;
    if(i + al != bl)
      bh = bh * B - b[i] * t + b[i + al];
    i++;
  }
  return cnt;
}

int main() {

  string a = "geek";
  string b = "geeksforgeek";
  cout << naive(a, b) << endl;
  cout << rabinKarp(a, b) << endl;

  return 0;
}
