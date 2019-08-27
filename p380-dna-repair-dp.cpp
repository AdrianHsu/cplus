#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <queue>

typedef long long ll;

#define MAX_N 55
#define MAX_P_LEN 25
#define MAX_T_LEN 1005
#define INT_INF 1e9

int N;
int M = 1; // num of testcases

#define MOD 100000
#define MAXC 4
const int MAXS = 55 * 4;

using namespace std;
typedef long long ll;

struct acAutomata {
  int go[MAXS][MAXC];
  bool val[MAXS]; // 要嘛是 0（不會掛掉）要嘛是 1（直接掛掉，湊滿此 pattern 了）
  int f[MAXS];
  int pos;

  void clear() {
    pos = 1;
    memset(go, -1, sizeof(go));
    memset(val, false, sizeof(val));
    memset(f, -1, sizeof(f));
  }
  int idx(char c) {
    if(c == 'A') return 0;
    else if(c == 'C') return 1;
    else if(c == 'T') return 2;
    else return 3;
  }
  
  void insert(string s) {
    int state = 0; // start from root

    for(int i = 0; i < s.length(); i++) {
      int c = idx(s[i]);
      if(go[state][c] == -1)
        go[state][c] = pos++;
      state = go[state][c];
    }
    val[state] = true;
  }
  
  void build() {

    for(int i = 0; i < MAXC; i++) {
      if(go[0][i] == -1)
        go[0][i] = 0;
    }

    queue<int> Q;
    // for depth = 1
    for(int i = 0; i < MAXC; i++) {
      int child = go[0][i];
      if(child > 0) {
        f[child] = 0;
        Q.push(child);
      }
    }
    // for depth > 1
    while(!Q.empty()) {
      int r = Q.front(); Q.pop();
      for(int i = 0; i < MAXC; i++) {
        int child = go[r][i];
        int fail = f[r];
        if(child == -1) {
          go[r][i] = go[ fail ][i];
          val[r] |= val[fail];
        } else {
          // while(go[fail][i] == -1) 
          //   fail = f[ fail ];
          fail = go[fail][i];
          f[child] = fail;
          val[child] |= val[fail];
          Q.push(child);
        }
      }
    }
  }
} ac;

int dp[MAX_T_LEN][MAXS];

void solve(string target) {
  int tl = target.length();
  int ans = INT_INF;
  int sN = ac.pos; // number of states

  for(int i = 0; i <= tl; i++)
    for(int j = 0; j < sN; j++)
      dp[i][j] = INT_INF;
  dp[0][0] = 0;

  for(int i = 1; i <= tl; i++) {
    char c = target[i - 1];
    for(int j = 0; j < sN; j++) {
      if(dp[i - 1][j] == INT_INF) continue;

      for(int k = 0; k < MAXC; k++) {
        int child = ac.go[j][k];
        if(child == -1) continue;
        if(ac.val[child] == false) {
          int add = (ac.idx(c) != k); // 0 or 1
          dp[i][child] = min(dp[i][child],
            dp[i - 1][j] + add);
        }
      }
    }
  }

  for(int i = 0; i < sN; i++)
    if(ac.val[i] == false)
      ans = min(ans, dp[tl][i]);
  if(ans == INT_INF) ans = -1;
  printf("Case %d: %d\n", M++, ans);
}

int main() {

  while(scanf("%d", &N) != EOF){
    if(N == 0) return 0;
    ac.clear();
    for(int i = 0; i < N; i++){
      string s;
      cin >> s;
      ac.insert(s);
    }
    ac.build();
    string target;
    cin >> target;
    solve(target);
  }

  return 0;
}
