#include <cstdio>
#include <iostream>

#define MAX_N 15

using namespace std;
int N;
int x[MAX_N];
int num;

void printResult() {
  for(int i = 1; i <= N; i++) {
    for(int j = 1; j <= N; j++) {
      if(x[i] == j) cout << "Q";
      else cout << ".";
    }
    cout << endl;
  }
  cout << endl;
}
bool canPlace(int i, int k) {
  for(int j = 1; j < k; j++) {
    if(x[j] == i) {// same col
      return false;
    } else if(x[k - j] == i - j) { // same diag (left)
      return false;
    } else if(i + j <= N && x[k - j] == i + j) { // same diag (right)
      return false;
    }
  }
  return true;
}

void backtracking(int k) {
  if(k == N + 1) {
    printResult();
    num ++;
    return;
  }
  for(int i = 1; i <= N; i++) { // where to put Qk
    if(canPlace(i, k)) { // we can place Qk at index i
      x[k] = i;
      backtracking(k + 1);
      x[k] = 0;
    }
  }
}

void solve() {
  num = 0;
  memset(x, 0, sizeof(x));
  backtracking(1);
}

int main() {
  while(scanf("%d", &N) != EOF) {
    solve();
    cout << "num of solutions: " << num << endl;
  }
  return 0;
}
