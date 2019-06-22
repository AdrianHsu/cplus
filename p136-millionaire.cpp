#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm> // math
using namespace std; // memset

#define MAX_M 5

int M, X;
double P;
double dp[MAX_M][(1<<MAX_M) + 1];

void printDP(int m, int n){
  for(int i = 0; i < m; i ++) {
    for(int j = 0; j < n; j ++) {
      if(j == n - 1)
        printf("%.1f", dp[i][j]);
      else
        printf("%.1f, ", dp[i][j]);
    }
    printf("\n");
  }
}

void solve() {
  int n = 1 << M;
  memset(dp, 0, sizeof(double) * n * n);
  dp[0][n] = 1.0;
  for(int r = 0; r < M; r ++) {
    for(int i = 0; i <= n; i ++) {
      int jub = min(i, n - i); // prevent i + j > n
      double t = 0.0;
      for(int j = 0; j <= jub; j ++) {
        t = max(t, P * dp[r][i + j] + (1 - P) * dp[r][i - j]);
      }
      dp[r + 1][i] = t;
    }
  }
  //printDP(MAX_M, n + 1);
  int res = (long long)X * n / 1000000;
  //printf("%d\n", res);
  printf("%.6f\n", dp[M][res]);
}


int main() {
  M = 3;
  P = 0.75;
  X = 600000;
  //M = 3;
  //P = 0.75;
  //X = 600000;
  scanf("%d%lf%d", &M, &P, &X); 

  solve();
  return 0;
}
