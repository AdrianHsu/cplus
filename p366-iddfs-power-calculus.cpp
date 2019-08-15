#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

const int MAX_N = 1010;
int num[MAX_N], N, depth;

bool iddfs(int n, int h) { 
  if(n << (depth - h) < N) return 0;
  if(h > depth) return 0;
  if(n == N) return 1;
  
  for(int i = 0; i < h; i++)
    cout << "....";
  cout << n << endl;
  
  num[h] = n;
  for(int i = 0; i <= h; i++){
    if(iddfs(n + num[i], h + 1)) return 1;
    if(iddfs(n - num[i], h + 1)) return 1; 
  }
  return 0;
}
void solve() {
  while(!iddfs(1, 0)){
    cout << "depth: " << depth << endl;
    memset(num, 0, sizeof(num));
    depth++;
  }
  printf("ans: %d\n",depth);
}
int main() {
  while(scanf("%d",&N) && N){
    depth = 0;
    memset(num, 0, sizeof(num));
    solve();
  }
  return 0;
}
