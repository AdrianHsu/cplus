#include <cstdio>
#include <iostream>
#include <algorithm>

#define MAX_N 10
#define MAX_W 100

using namespace std;

int dp[MAX_N + 1][MAX_W + 1];
int N, W;
int w[MAX_N];
int v[MAX_N];

void solve01() {
  for(int i = 0; i < N; i++) {
    for(int j = 0; j <= W; j++) {
      if(j - w[i] < 0) {
        dp[i + 1][j] = dp[i][j];
      } else {
        dp[i + 1][j] = max(dp[i][j], dp[i][j - w[i]] + v[i]);
      }
    }
  }
}

void solve01fixW() {
  for(int i = 0; i < N + 1; i++)
    for(int j = 0; j <= W; j++)
      dp[i][j] = -1e9;
  
  dp[0][0] = 0;
  for(int i = 0; i < N; i++) {
    for(int j = 0; j <= W; j++) {
      if(j - w[i] < 0) {
        dp[i + 1][j] = dp[i][j];
      } else {
        dp[i + 1][j] = max(dp[i][j], dp[i][j - w[i]] + v[i]);
      }
    }
  }
}

int main() {
  //N = 4; W = 5;
  //int w1[] = {2, 1, 3, 2};
  //int v1[] = {3, 2, 4, 2};
  //solve01();

  //N = 3; W = 7;
  //int w2[] = {2, 5, 6};
  //int v2[] = {3, 4, 9};
  //solve01fixW();
  
  memcpy(w, w2, sizeof(w2));
  memcpy(v, v2, sizeof(v2));
  printf("answer: %d\n", dp[N][W]);
  return 0;
}
