#include <cstdio>
#include <iostream>

#define MAX_N 15

using namespace std;
int N;
int x[MAX_N + 1];
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

int b[MAX_N]; // e.g. b = {2, 8, 1, 4} that is, {0010, 1000, 0001, 0100}

void printBinary() {
  for(int i = 0; i < N; i++) {
    for(int j = N - 1; j >= 0; j--) {
      if(b[i] >> j == 1) cout << "Q";
      else cout << ".";
    }
    cout << endl;
  }
  cout << endl;
}

bool canPlaceBinary(int i, int k) {
  for(int j = 0; j < k; j++) {
    if(b[j] == i) return false;
    else if(b[k - (j + 1)] == i << (j + 1)) return false;
    else if(b[k - (j + 1)] == i >> (j + 1)) return false;
  }
  return true;
}

void backtrackingBinary(int k) {
  if(k == N) {
    printBinary();
    num++;
    return;
  }
  for(int i = N - 1; i >= 0; i--) {
    int val = 1 << i;
    if(canPlaceBinary(val, k)) {
      b[k] = val;
      backtrackingBinary(k + 1);
      b[k] = 0;
    }
  }
}

void solveBinary() {
  num = 0;
  memset(b, 0, sizeof(b));
  backtrackingBinary(0);
}

int main() {
  while(scanf("%d", &N) != EOF) {
    solveBinary();
    cout << "num of solutions: " << num << endl;
  }
  return 0;
}
