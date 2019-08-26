#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <queue>

#define MAX_M 15
#define MAX_N 2000000005
typedef long long ll;

#define MM 4
const int NN = 10 * 10 + 5; // 10 個pattern, 每個 pattern 長度 10，所以 Trie 最大就 100
int M;
ll N;


using namespace std;
typedef long long ll;

struct acAutomata {
  int ch[NN][MM];
  int val[NN];
  int f[NN];
  int pos;

  void clear() {
    pos = 1;
    memset(ch[0], 0, sizeof(ch[0]));
  }
  int idx(char c) {
    if(c == 'A') return 0;
    else if(c == 'C') return 1;
    else if(c == 'T') return 2;
    else return 3;
  }
  
  void insert(string s) {
    int dep = 0;
    for(int i = 0; i < s.length(); i++) {
      int c = idx(s[i]);
      if(ch[dep][c] == 0) {
        memset(ch[pos], 0, sizeof(ch[pos]));
        val[pos] = 0;
        ch[dep][c] = pos++;
      }
      dep = ch[dep][c];
    }
    val[dep] = 1;
  }
  
  void build() {
    queue<int> Q;
    f[0] = 0; // root
    // for depth = 1
    for(int i = 0; i < MM; i++) {
      int child = ch[0][i];
      if(child != 0) {
        f[child] = 0;
        Q.push(child);
      }
    }
    // for depth > 1
    while(!Q.empty()) {
      int r = Q.front(); Q.pop();
      for(int i = 0; i < MM; i++) { // ATCG 都各自建立 
        int child = ch[r][i];
        if(child == 0) {
          ch[r][i] = ch[ f[r] ][i];
          val[r] |= (val[ f[r] ]);
          continue;
        }
        Q.push(child);
        f[child] = ch[ f[r] ][i];
      }
    }
  }
} ac;

#define MOD 100000
#define MAT 200
struct Matrix {
  ll mat[MAT][MAT];
};

int n;
void initMat(Matrix &A) {
  n = ac.pos;
  int child_id;
  memset(A.mat, 0, sizeof(A.mat));
  for(int i = 0; i < n; i++) {
    if(ac.val[i] == 0) {
      for(int k = 0; k < MM; k++) {
        child_id = ac.ch[i][k];
        if(ac.val[child_id] == 0)
          A.mat[i][child_id]++;
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

int main() {
  scanf("%d%lld", &M, &N);
  ac.clear();
  for(int i = 0; i < M; i++) {
    string s;
    cin >> s;
    ac.insert(s);
  }
  ac.build();
  Matrix A;
  initMat(A);
  //printMat(A);
  
  Matrix ans = mod_pow(A);
  ll total = 0;
  for(int i = 0; i < n; i++)
    total = (total + ans.mat[0][i]) % MOD;
  cout << total << endl;

  return 0;
}
