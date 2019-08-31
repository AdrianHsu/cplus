#include <cstdio>
#include <iostream>
#include <algorithm>

#define MAX_N 100
using namespace std;
int data[MAX_N * 2];
int N;

void build(int arr[]) {
  for(int i = 0; i < 2 * N; i++)
    data[i] = 1e9;

  for(int i = 0; i < N; i++)
    data[i + N] = arr[i];
  for(int i = N - 1; i >= 1; i--) {
    data[i] = min(data[2 * i], data[2 * i + 1]);
  }
  
  for(int i = 0; i < 2 * N; i++)
    cout << data[i] << " ";
  cout << endl;
}
void update(int idx, int val) {
  idx += N;
  data[idx] = val;
  while(idx > 1) {
    idx >>= 1;
    data[idx] = min(data[2 * idx], data[2 * idx + 1]);
  }
}

void query(int l, int r) {
  int res = 1e9;
  l += N; r += N;
  while(l < r) {
    if(l & 1)
      res = min(res, data[l++]);
    if(r & 1)
      res = min(res, data[--r]);
    l >>= 1;
    r >>= 1;
  }
  cout << res << endl;
}
int main() {
  //int arr[] = {1, 5, 3, 7, 3, 2, 5, 7};
  //N = 8;
  
  // N 不是 2 的次方怎麼辦？ 
  int arr[] = {4, 3, 9, 1, 6, 7}; // https://blog.csdn.net/Yaokai_AssultMaster/article/details/79599809#t5
  N = 6;
  int queryArr[][2] = {{0, 4}, {1, 3}, {3, 6}}; // [l, r), where r is open, l is closed
  build(arr);
  query(queryArr[0][0], queryArr[0][1]);
  query(queryArr[1][0], queryArr[1][1]);
  query(queryArr[2][0], queryArr[2][1]);
  return 0;
}
