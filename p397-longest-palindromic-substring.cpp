#include <iostream>
#include <cstdio>
#include <cstring>

#define MAX_N 1000
using namespace std;

bool dp[MAX_N][MAX_N];

void solveDP(string str) {
  int n = str.length();
  // dp[i][j] will be false if substring str[i..j] 
  // is not palindrome. 
  memset(dp, 0, sizeof(dp));
  int s = 0;

  int res = 1;
  for(int i = 0; i < n; i++) {
    dp[i][i] = 1;
    if(i < n - 1 && str[i] == str[i + 1]){
      dp[i][i + 1] = 1;
      s = i;
      res = 2;
    }
  }
  // 不必把 odd, even 的狀況分開
  for(int len = 3; len <= n; len++) {
    for(int l = 0; l + len <= n; l++) { // <= n 是因為右界是 open bound
      int r = l + len - 1;
      // 照理說 (長度 - 2) 的 subproblem 已經有解，所以可用dp[l + 1][r - 1] 
      if(dp[l + 1][r - 1]) {
        if(str[l] == str[r]) {
          dp[l][r] = 1;
          res = max(res, len);
          s = l;
        }
      }
    }
  }
  cout << "len: " << res << endl;
  cout << str.substr(s, res) << endl;
}

int main() {
  //string str = "forgeeksskeegfor";
  string str = "mississippi";
  solveDP(str);
}
