#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <queue>

typedef long long ll;

#define MAX_M 15
// #define MAX_N 2000000005 // matrix mul: for large testcase
#define MAX_N 100 // DP is only for small testcase

int M; // num of patterns
int n; // last pos id
ll N; // length of combine string (can be very long...)

#define MOD 100000
#define MAXC 4
#define MAXS 105 // num of state, at most 10 * 10 (which is LEN_MAX * 10 pieces of patterns)

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
//          while(go[fail][i] == -1) 
//            fail = f[ fail ];
          fail = go[fail][i];
          f[child] = fail;
          val[child] |= val[fail];
          Q.push(child);
        }
      }
    }
  }
} ac;
struct Matrix {
  ll mat[MAXS][MAXS];
};


void initMat(Matrix &A) {

  int id;
  memset(A.mat, 0, sizeof(A.mat));
  for(int i = 0; i < n; i++) {
    if(ac.val[i] == false) {
      for(int k = 0; k < MAXC; k++) {
        id = ac.go[i][k];
        if(ac.val[id] == false)
          A.mat[i][id]++;
      }
    }
  }
}

Matrix matmul(Matrix &A, Matrix &B) {
  Matrix R;
  memset(R.mat, 0, sizeof(R.mat));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      ll tmp = 0;
      for(int k = 0; k < n; k++) {
        tmp = (tmp + A.mat[i][k] * B.mat[k][j]) % MOD;
      }
      R.mat[i][j] = tmp % MOD;
    }
  }
  return R;
}
Matrix mod_pow(Matrix &A) {
  Matrix ans;
  memset(ans.mat, 0, sizeof(ans.mat)); 
  for(int i = 0; i < n; i++) 
    ans.mat[i][i] = 1;

  while(N > 0) {
    if(N & 1)
      ans = matmul(ans, A);
    A = matmul(A, A);
    N >>= 1;
  }
  return ans;
}
void printMat(Matrix A) {
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      cout << A.mat[i][j] << " ";
    }
    cout << endl;
  }
}

int dp[MAX_N][MAXS];

void solveDP() {
  for(int i = 0; i <= N; i++)
    for(int j = 0; j < n; j++)
      dp[i][j] = 0;

  dp[0][0] = 1;
  for(int i = 1; i <= N; i++) {
    for(int j = 0; j < n; j++) {

      for(int k = 0; k < MAXC; k++) {
        int child = ac.go[j][k];
        if(ac.val[child] == false) {
          dp[i][child] += dp[i - 1][j];
        }
      }
    }
  }
  
  int total = 0;
  for(int i = 0; i < n; i++)
    total += dp[N][i];

  cout << total << endl;
}

void solve(){
  Matrix A;
  initMat(A);
  // printMat(A);
  
  Matrix ans = mod_pow(A);
  ll total = 0;
  for(int i = 0; i < n; i++)
    total = (total + ans.mat[0][i]) % MOD;
  cout << total << endl;
}

int main() {
  scanf("%d%lld", &M, &N);
  ac.clear();
  for(int i = 0; i < M; i++) {
    string s;
    cin >> s;
    ac.insert(s);
  }
  ac.build();
  n = ac.pos;

  // solveDP();
  solve();
  return 0;
}
