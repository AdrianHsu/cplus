#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cmath>

using namespace std;

#define ST_SIZE (1 << 15) - 1
#define MAX_N 10000
#define MAX_C 10000


int N, C;
int L[MAX_N];
int S[MAX_C];
int A[MAX_N];

double vx[ST_SIZE], vy[ST_SIZE]; // node (x, y)
double ang[ST_SIZE]; // current absolute angle (not degree) for every node

double prv[MAX_N]; // previous degree

void init(int k, int l, int r) {
  ang[k] = 0.0;
  vx[k] = 0.0;
  
  if(r - l == 1) // leaf -> take L original value into it
    vy[k] = L[l];
  else { // not leaf
    int node_l = 2 * k + 1;
    int node_r = 2 * k + 2;
    init(node_l, l, (l + r) / 2);
    init(node_r, (l + r) / 2, r);
    // RSQ: Range Sum Query
    vy[k] = vy[node_l] + vy[node_r];
  }
}

void update(int s, double a, int v, int l, int r) {
  if(s <= l || s >= r) return;

  int chl = 2 * v + 1; // child left
  int chr = 2 * v + 2; // child right
  int m = (l + r) >> 1;
  
  update(s, a, chl, l, m);
  update(s, a, chr, m, r);

  if(s <= m){

    ang[v] += a;
    printf("%d, %f\n", v, ang[v] * (180 / M_PI));
  }
  double _sin = sin(ang[v]);
  double _cos = cos(ang[v]);
  vx[v] = vx[chl] + (_cos * vx[chr] - _sin * vy[chr]);
  vy[v] = vy[chl] + (_sin * vx[chr] + _cos * vy[chr]);
  
}

void solve() {
  init(0, 0, N);
  for(int i = 1; i < N; i++)
    prv[i] = M_PI; // 180 in the beginning
  
  for(int i = 0; i < C; i++) {
    int s = S[i];
    double a = (double) A[i] * (M_PI / 180.0);
    
    update(s, a - prv[s], 0, 0, N);
    prv[s] = a;

    printf("%.2f %.2f\n", vx[0], vy[0]);
  }
}

int main() {

  while(scanf("%d%d", &N, &C) != EOF) {
    for(int i = 0; i < N; i++){
      scanf("%d", &L[i]);
    }
    for(int i = 0; i < C; i++){
      scanf("%d%d", &S[i], &A[i]);
    }
    solve();
    printf("\n");
  }
  return 0;
}
