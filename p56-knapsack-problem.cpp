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
  for(int i = 0; i < N + 1; i++) {
    dp[i][0] = 0;
    for(int j = 1; j <= W; j++)
      dp[i][j] = -1e9;
  }
  
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

void solveFull1() {
  for(int i = 0; i < N; i++) {
    for(int j = 0; j <= W; j++) {
      int upper = j / w[i];
      for(int k = 0; k <= upper; k++) {
        //if(j - k * w[i]  < 0) { // useless, j - k * w[i] must >= 0
        //  dp[i + 1][j] = dp[i][j];
        //} else {
          // in the beginning, dp[i + 1][j] is not yet set (for recursion use)
          dp[i + 1][j] = max(dp[i + 1][j], dp[i][j - k * w[i]] + k * v[i]);
        //}
      }
    }
  }
}

// Binary item size
// more similar to 0/1 knapsack, rather than the solveFull1()
void solveFull2() {
  for(int i = 0; i < N; i++) {
    int num = W / w[i];
    for(int k = 1; num > 0; k <<= 1) {
      int mul = min(k, num);
      for(int j = 0; j <= W; j++) {
        if(j - mul * w[i]  < 0) {
          dp[i + 1][j] = dp[i][j];
        } else {
          dp[i + 1][j] = max(dp[i][j], dp[i][j - mul * w[i]] + mul * v[i]);
        }
      }
      num -= mul;
    }
  }
}

void solveFull3() {
  for(int i = 0; i < N; i++) {
    for(int j = 0; j <= W; j++){
      if(j - w[i] < 0) {
        dp[i + 1][j] = dp[i][j];
      } else {
        dp[i + 1][j] = max(dp[i][j], dp[i + 1][j - w[i]] + v[i]);
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
  //memcpy(w, w2, sizeof(w2));
  //memcpy(v, v2, sizeof(v2));
  //solve01fixW();
  
  N = 3; W = 7;
  int w3[] = {3, 4, 2};
  int v3[] = {4, 5, 3};
  memcpy(w, w3, sizeof(w3));
  memcpy(v, v3, sizeof(v3));
  //solveFull1();
  solveFull2();
  //solveFull3();
  
  printf("answer: %d\n", dp[N][W]);
  return 0;
}
