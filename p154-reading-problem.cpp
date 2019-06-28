#include <cstdio>
#include <set>
#include <map>
#include <algorithm>

#define MAX_P 1000000

using namespace std;

int a[MAX_P];
int P;
int n;

void solve() {
  int s = 0, t = 0, num = 0;
  int res = P;
  map<int, int> count;
  while(true) {
    while(t < P && num < n) {
      int ci = a[t++];
      if(count[ci] == 0)
        num ++;
      count[ci]++;
    }
    if(num < n) break;
    res = min(res, t - s);
    //printf("%d,%d\n", s, t);
    int ci = a[s++];
    if(--count[ci] == 0)
      num--;
  }
  printf("%d\n", res);
}

int main() {

  scanf("%d", &P);
  int i = 0;
  set<int> all;
  while(scanf("%d", &a[i]) != EOF){
    all.insert(a[i++]);
  }
  n = all.size();
  solve();
  return 0;
}
