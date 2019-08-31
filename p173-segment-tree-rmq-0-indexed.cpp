#include <cstdio>
#include <iostream>
#include <algorithm>

#define MAX_N 100
using namespace std;
int data[MAX_N * 2 - 1];
int N, n;

void init() {
  n = 1;
  while(n < N)
    n *= 2;
  for(int i = 0; i < 2 * n - 1; i++)
    data[i] = 1e9;
}

void update(int k, int a) {
  k += n - 1;
  data[k] = a;

  while(k > 0) {
     k = (k - 1) >> 1;
     data[k] = min(data[2 * k + 1], data[2 * k + 2]);
  }
}

int query(int a, int b, int k, int l, int r) {
  if(r <= a || l >= b) return 1e9;
  
  if(a <= l && r <= b) 
    return data[k];
  else {
    int vl = query(a, b, 2 * k + 1, l, (l + r) >> 1);
    int vr = query(a, b, 2 * k + 2, (l + r) >> 1, r);
    return min(vl, vr);
  }
}

int main() {
  //int arr[] = {1, 5, 3, 7, 3, 2, 5, 7};
  //N = 8;
  
  // N 不是 2 的次方怎麼辦？ 湊到 2 的次方( = n ) 為止
  int arr[] = {4, 3, 9, 1, 6, 7};
  N = 6;
  int queryArr[][2] = {{0, 4}, {1, 3}, {3, 6}}; // [l, r), where r is open, l is closed
  init();
  for(int i = 0; i < N; i++)
    update(i, arr[i]);

  for(int i = 0; i < 2 * n - 1; i++)
    cout << data[i] << " ";
  cout << endl;

  int v1 = query(queryArr[1][0], queryArr[1][1], 0, 0, n);
  cout << v1 << endl;
  int v2 = query(queryArr[2][0], queryArr[2][1], 0, 0, n);
  cout << v2 << endl;
  return 0;
}
