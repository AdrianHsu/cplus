#include <cstdio>
#include <iostream>
#include <utility>

#define MAX_N 100
#define MAX_M 1000
#define MAX_LOG_N 10
using namespace std;

int N, M;
int s[MAX_N * 2], t[MAX_N * 2];

pair<int, int> ps[MAX_N * 4];
int _next[MAX_N * 2];
int __next[MAX_LOG_N][MAX_N * 2];

void solve() {
  int res = 0;

  for(int i = 0; i < N; i++) {
    if(t[i] < s[i]) t[i] += M;
    s[N + i] = s[i] + M;
    t[N + i] = t[i] + M;
  }

  for(int i = 0; i < 2 * N; i++) {
    ps[i] = make_pair(t[i], i);
    ps[2 * N + i] = make_pair(s[i], 2 * N + i);
  }
   
  sort(ps, ps + 4 * N);
   
  int last = -1;
  for(int i = 4 * N - 1; i >= 0; i --) {
    int id = ps[i].second;
    if(id < 2 * N) {
      _next[id] = last;
      cout << id << "," << _next[id] << endl;
    } else {
      id -= 2 * N;
      if(last < 0 || t[last] > t[id]) 
        last = id;
    }
  }
  
  for(int i = 0; i < N; i++) {
    int tmp = 0;
    for(int j = i; t[j] < s[i] + M; j = _next[j]) 
      tmp++;
    res = max(res, tmp);
  }
  printf("ans: %d\n", res);
}

void printNext() {
  for(int i = 0; i < MAX_LOG_N; i++) {
    for(int j = 0; j < 2 * N; j++)
      cout << __next[i][j] << " ";
    cout << endl;
  }
}

void solve2() {
  int res = 0;

  for(int i = 0; i < N; i++) {
    if(t[i] < s[i]) t[i] += M;
    s[N + i] = s[i] + M;
    t[N + i] = t[i] + M;
  }

  for(int i = 0; i < 2 * N; i++) {
    ps[i] = make_pair(t[i], i);
    ps[2 * N + i] = make_pair(s[i], 2 * N + i);
  }
   
  sort(ps, ps + 4 * N);
   
  int last = -1;
  for(int i = 4 * N - 1; i >= 0; i --) {
    int id = ps[i].second;
    if(id < 2 * N) {
      __next[0][id] = last;
      //cout << id << "," << __next[0][id] << endl;
    } else {
      id -= 2 * N;
      if(last < 0 || t[last] > t[id]) 
        last = id;
    }
  }
  
  for(int k = 0; k + 1 < MAX_LOG_N; k++) {
    for(int i = 0; i < 2 * N; i++) {
      if(__next[k][i] == -1)
        __next[k + 1][i] = -1;
      else
        __next[k + 1][i] = __next[k][__next[k][i]];
    }
  }
  printNext();
  for(int i = 0; i < N; i++) {
    int tmp = 0, j = i;
     
    for(int k = MAX_LOG_N - 1; k >= 0; k--) {
      int j2 = __next[k][j];
      if(j2 >= 0 && t[j2] <= s[i] + M) {
        j = j2;
        tmp |= (1 << k);
        cout << i << "," << k << "," << tmp << endl;
      }
    }
    res = max(res, tmp + 1);
  }
  printf("ans: %d\n", res);
}

int main() {
  N = 6; M = 10;
  //int s1[] = {0, 4, 6};
  //int t1[] = {5, 6, 3};
  int s1[] = {0, 2, 4, 6, 8, 9};
  int t1[] = {1, 3, 5, 8, 9, 2};

  memcpy(s, s1, sizeof(s1));
  memcpy(t, t1, sizeof(t1));
//  solve();
  solve2();

  return 0;
}





