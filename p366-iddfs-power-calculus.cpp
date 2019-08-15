#include <cstdio>
#include <cstring>
using namespace std;

const int MAX_N = 1010;
int num[MAX_N], N, maxH;

bool iddfs(int n, int curH)
{ 
  if(n << (maxH - curH) < N) return 0;
  if(curH > maxH) return 0;
  if(n == N) return 1;
  num[curH] = n;
  for(int i = 0; i <= curH; i++){
    if(iddfs(n + num[i], curH + 1)) return 1;
    if(iddfs(n - num[i], curH + 1)) return 1; 
  }
  return 0;
}
void solve() {
  while(!iddfs(1, 0)){
    memset(num, 0, sizeof(num));
    maxH++;
  }
  printf("%d\n",maxH);
}
int main() {
  while(scanf("%d",&N) && N){
    maxH = 0, memset(num, 0, sizeof(num));
    solve();
  }
  return 0;
}
