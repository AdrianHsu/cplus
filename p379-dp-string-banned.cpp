#include <cstdio>  
#include <cstring>  
#include <string>  
#include <algorithm>  
#include <iostream>  
using namespace std;  
int n,k;  
string S;  

const char *agct = "AGCT";  

const int maxn = 10010;  
int dp[maxn][110];  
int _next[maxn][4];  
const int MOD = 10009;  

void init(){  
    memset(dp,0,sizeof(dp));  
    dp[0][0] = 1;  
}  

void solve(){  
  
  for(int i = 0; i < k; i++) {
    for(int j = 0; j < 4; j++) {
     
      string s = S.substr(0, i) + agct[j];
      while(S.substr(0, s.length()) != s) {
        s = s.substr(1);
      }
      _next[i][j] = s.length();
    }
  }

  for(int i = 0; i < n; i++) {
    for(int x = 0; x < k; x++) {
      for(int j = 0; j < 4; j++) {
        int t = _next[x][j];
        if(t == k) continue;
        dp[i + 1][t] += dp[i][x] % MOD;
      }
    }
  }
  int ans = 0;
  for(int i = 0; i < k; i++)
    ans += dp[n][i] % MOD;
  
  cout << ans << endl;
}  

int main(){  
    while(cin>>n>>k>>S){  
        init();  
        solve();  
    }  
}  
