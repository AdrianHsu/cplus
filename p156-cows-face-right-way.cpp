#include <cstdio>
#include <iostream>
#include <algorithm>

#define MAX_N 5001
using namespace std;

int N;
int dir[MAX_N]; // 0: F, 1: B
int f[MAX_N]; // [i, i - K + 1] flip times

int calc(int K) {
  memset(f, 0, sizeof(f));
  int res = 0;
  int sum = 0; // sum of f
  for(int i = 0; i + K <= N; i++) {
    if((sum + dir[i]) % 2 == 1) { // need flip
      f[i] = 1;
      res ++;
    }
    sum += f[i];
    if(i - K + 1 >= 0)
      sum -= f[i - K + 1];
  }
  for(int i = N - K + 1; i < N; i++) {
    if((sum + dir[i]) % 2 == 1) {
      return -1;
    }
    if(i - K + 1 >= 0)
      sum -= f[i - K + 1];
  }
  return res;
}

void solve() {
  int K = 1;
  int M = N; // M : num of flip times
  for(int k = 1; k <= N; k++){
    int m = calc(k);
    if(m != -1 && m < M) { // m is better than M
      M = m;
      K = k; // k changes automatically
    }
  }
  printf("%d %d\n", K, M);
}

int main() {
  scanf("%d", &N);
  char c;
  int i = 0;
  while(cin >> c) {
    if(c == 'F')
      dir[i] = 0;
    else if(c == 'B')
      dir[i] = 1;
    i++;    
  }
  solve();
  return 0;
}
