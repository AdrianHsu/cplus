#include <cstdio>
#include <iostream>
#include <algorithm>

#define DAT_SIZE  (1 << 18) - 1
#define MAX_N 100000
#define MAX_Q 100000

using namespace std;

typedef long long ll;

int N, Q;
ll A[MAX_N];
char T[MAX_Q];
int L[MAX_Q], R[MAX_Q], X[MAX_Q];

ll data[DAT_SIZE];
ll datb[DAT_SIZE];

void add(int a, int b, int x, int k, int l, int r) {
  if(a <= l && r <= b) {
    data[k] += x;
  } else if(l < b && a < r) {
    datb[k] += (min(b, r) - max(a, l)) * x;
    add(a, b, x, k * 2 + 1, l, (l + r) / 2);
    add(a, b, x, k * 2 + 2, (l + r) / 2, r);
  }
}

ll sum(int a, int b, int k, int l, int r) {
  if(b <= l || r <= a) return 0;
  else if(a <= l && r <= b){ 
    return data[k] * (r - l) + datb[k];
  } else {
    ll res = (min(b, r) - max(a, l)) * data[k];
    res += sum(a, b, k * 2 + 1, l, (l + r) / 2);
    res += sum(a, b, k * 2 + 2, (l + r) / 2, r);
    return res;
  }
}

void printData() {
  for(int i = 0; i < 2 * N; i++) {
    printf("%lld, ", data[i]);
  }
  printf("\n");
  for(int i = 0; i < 2 * N; i++) {
    printf("%lld, ", datb[i]);
  }
  printf("\n");
}

void solve() {
  // init
  for(int i = 0; i < N; i ++) {
    add(i, i + 1, A[i], 0, 0, N);
  }
//  printData();
  for(int i = 0; i < Q; i++) {
    if(T[i] == 'C') // the problem is one-indexed: so -1 here
      add(L[i] - 1, R[i] - 1 + 1, X[i], 0, 0, N);
    else 
      printf("%lld\n", sum(L[i] - 1, R[i] - 1 + 1, 0, 0, N));
  }
}

int main() {

  scanf("%d%d", &N, &Q);
  for(int i = 0; i < N; i ++) {
    scanf("%lld", &A[i]);
  }
  for(int i = 0; i < Q; i++) {
    cin >> T[i];
    if(T[i] == 'Q') {
      scanf("%d%d", &L[i], &R[i]);
    } else {
      scanf("%d%d%d", &L[i], &R[i], &X[i]);
    }
  }
  solve();
  return 0;
}
