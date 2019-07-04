#include <cstdio>
#include <iostream>
#include <algorithm>

#define DAT_SIZE  (1 << 18) - 1
#define MAX_N 100000
#define MAX_Q 100000

using namespace std;
 
typedef long long ll;

bool isBIT = 1;

int N, Q;
ll A[MAX_N + 1];
char T[MAX_Q];
int L[MAX_Q], R[MAX_Q], X[MAX_Q];

ll data[DAT_SIZE], datb[DAT_SIZE];

void add(int a, int b, int x, int k, int l, int r) {
  if(a <= l && r <= b) {
    data[k] += x;
  } else if(l < b && a < r) {
    datb[k] += (min(b, r) - max(a, l)) * x;
    //printf("bound: %d\n", min(b, r) - max(a, l));
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
  printf("datA\n");
  for(int i = 0; i < 2 * N; i++) {
    printf("[%d]:%lld, ", i, data[i]);
  }
  printf("\ndatB\n");
  for(int i = 0; i < 2 * N; i++) {
    printf("[%d]:%lld, ", i, datb[i]);
  }
  printf("\n\n");
}

void solve() {
  // init
  for(int i = 0; i < N; i ++) {
    add(i, i + 1, A[i], 0, 0, N);
    //printData();
  }
  for(int i = 0; i < Q; i++) {
    if(T[i] == 'C') // the problem is one-indexed: so -1 here
      add(L[i] - 1, R[i] - 1 + 1, X[i], 0, 0, N);
    else 
      printf("%lld\n", sum(L[i] - 1, R[i] - 1 + 1, 0, 0, N));
    //printData();
  }
}

//////////////////////////////////

ll bit0[MAX_N + 1], bit1[MAX_N + 1];

ll sumBIT(ll *b, int i) {
  ll s = 0;
  while(i > 0) {
    s += b[i];
    i -= i&-i;
  }
  return s;
}

void addBIT(ll *b, int i, int v) {
  while(i <= N) {
    b[i] += v;
    i += i & -i;
  }
}

void printBIT() {

  printf("bit0\n");
  for(int i = 1; i < N + 1; i++) {
    printf("[%d]:%lld, ", i, bit0[i]);
  }
  printf("\nbit1\n");
  for(int i = 1; i < N + 1; i++) {
    printf("[%d]:%lld, ", i, bit1[i]);
  }
  printf("\n\n");
}

void solveBIT() {
  memset(bit0, 0, sizeof(bit0));
  memset(bit1, 0, sizeof(bit1));

  for(int i = 1; i <= N; i++) {
    addBIT(bit0, i, A[i]);
  }
  for(int i = 0; i < Q; i++) {
    if(T[i] == 'C') {
      addBIT(bit0, L[i], -X[i] * (L[i] - 1));
      addBIT(bit1, L[i], X[i]);
      addBIT(bit0, R[i] + 1, X[i] * R[i]);
      addBIT(bit1, R[i] + 1, -X[i]);
    } else {
      ll res = 0;
      //printBIT();
      //printf("> %lld\n", sumBIT(bit0, R[i]));
      //printf("> %lld,%d\n", sumBIT(bit1, R[i]), R[i]);
      res += sumBIT(bit0, R[i]) + sumBIT(bit1, R[i]) * R[i];
      //printf("< %lld\n", sumBIT(bit0, L[i] - 1));
      //printf("< %lld\n", sumBIT(bit1, L[i] - 1));
      res -= sumBIT(bit0, L[i] - 1) + sumBIT(bit1, L[i] - 1) * (L[i] - 1);
      printf("%lld\n", res);
    }
  }
}

int main() {

  scanf("%d%d", &N, &Q);
  for(int i = 0; i < N; i ++) {

    if(isBIT)
      scanf("%lld", &A[i + 1]); // if using BIT
    else
      scanf("%lld", &A[i]); // if using SegTree
  }
  for(int i = 0; i < Q; i++) {
    cin >> T[i];
    if(T[i] == 'Q') {
      scanf("%d%d", &L[i], &R[i]);
    } else {
      scanf("%d%d%d", &L[i], &R[i], &X[i]);
    }
  }
  if(isBIT)
    solveBIT();
  else
    solve();
  return 0;
}
