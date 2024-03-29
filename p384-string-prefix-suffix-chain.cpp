// hdu 5318 
#include <iostream>
#include <cstdio>
#include <set>
#define MAX_N 55
const int MOD = 1000000007;
typedef long long int ll;

using namespace std;
set<string> S;
int N, M;

struct Matrix {
  ll mat[MAX_N][MAX_N];
};

string s[MAX_N];

bool judge(int x, int y) {
  string s1 = s[x];
  string s2 = s[y];
  int len1 = s1.length();
  int len2 = s2.length();
  
  if(len1 == 1 || len2 == 1) return false;
  
  for(int k = len1 - 2; k >= 0; k--) {
    int i = k;
    int j = 0;
    while(i < len1 && j < len2) {
      if(s1[i] == s2[j]) {
        i++; j++;
      } else break;
    }
    if(i == len1) return true;
  }
  return false;
}

void printMat(Matrix &A) {
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      cout << A.mat[i][j] << " ";
    }
    cout << endl;
  }
}
Matrix matmul(Matrix &A, Matrix &B) {
  Matrix R;
  memset(R.mat, 0, sizeof(R.mat));
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      ll tmp = 0;
      for(int k = 0; k < N; k++) {
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
  for(int i = 0; i < N; i++) 
    ans.mat[i][i] = 1;

  M--;
  while(M > 0) {
    if(M & 1)
      ans = matmul(ans, A);
    A = matmul(A, A);
    M >>= 1;
  }
  return ans;
}

int main() {
  int T;
  scanf("%d", &T);
  while(T > 0) {
    scanf("%d%d", &N, &M);
    
    int pos = 0;
    for(int i = 0; i < N; i++) {
      string tmp;
      cin >> tmp;
      int si = S.size();
      S.insert(tmp);
      if(si != S.size()) {
        s[pos++] = tmp;
      }
    }
    N = pos;
    Matrix A;
    memset(A.mat, 0, sizeof(A.mat));
    for(int i = 0; i < N; i++) {
      for(int j = 0; j < N; j++)  {
        if(judge(i, j)) 
          A.mat[i][j] = 1;
        else
          A.mat[i][j] = 0;
      }
    }
    //printMat(A);
    Matrix ans = mod_pow(A);
    ll res = 0;
    for(int i = 0 ; i < N; i++)
      for(int j = 0; j < N; j++)
        res = (res + ans.mat[i][j]) % MOD;
    cout << res << endl;
    T--;
  }
  return 0;
}
