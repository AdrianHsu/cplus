#include <cstdio>
#include <algorithm>
#define MAX_N 100000

using namespace std;

int C; // num of testcases
int N;
int S;
int a[MAX_N];

void solve() {
  int res = N + 1;
  int s = 0, t = 0, sum = 0;
  while(true){
    while(t < N && sum < S)
      sum += a[t++];
    if(sum < S) break;
    res = min(res, t - s);
    sum -= a[s++];
  }
  if(res > N) res = 0;
  printf("%d\n", res);
}

int main() {
  scanf("%d", &C);
  while(scanf("%d%d", &N, &S) != EOF) {
    for(int i = 0; i < N; i++) {
      scanf("%d", &a[i]);
    }
    solve();
  }
  return 0;
}
