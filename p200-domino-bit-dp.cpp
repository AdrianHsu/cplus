#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

#define MAX_N 11
#define MAX_M 11

int dp [MAX_N * MAX_M][1 << MAX_M];
int n = 0, m = 0;

void solve() {
  memset(dp, -1, sizeof(dp));
  int iter = 0;
  dp[iter][0] = 1;
  for(int i = n - 1; i >= 0; i--){ 
    for(int j = m - 1; j >= 0; j--){
      for(int u = 0; u < (1 << m); u++) {
        if( (u >> j) & 1 )
          dp[iter + 1][u] = dp[iter][u & ~(1 << j)];
        else {
          int res = 0;
          if(j + 1 < m && !( (u >> (j + 1)) & 1 ))
            res += dp[iter][u | 1 << (j + 1)];
          
          if(i + 1 < n)
            res += dp[iter][u | (1 << j)];
          
          dp[iter + 1][u] = res;
        }
      }
      iter ++;
    }
  }
  printf("%d\n", dp[iter][0]);
}

int main() {
  while(scanf("%d%d", &n, &m) != EOF) {
    if(n == 0 && m == 0) break;

    solve();
  }
  return 0;
}
