#include <cstdio>
#include <iostream>

#define MAX_N 1001
using namespace std;

int N;

void iddfs(int s, int &round) {
  if(N == s) {
    return;
  }
  if((N - s) < (1 << round)) {
    int res = N - s;
    while(res != 0) {
      if(res & 1) {
        round ++;
      }
      res >>= 1;
    }
  } else {
    s <<= 1;
    round += 1;
    iddfs(s, round);
  }
}

void solve() {
  int round = 0;
  int s = 1;
  iddfs(s, round);
  cout << round << endl;
}

int main() {

  while(scanf("%d", &N) != EOF) {
    if(N == 0) break;
    solve();
  }
  return 0;
}
