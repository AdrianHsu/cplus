#include <cstdio>
#include <vector>
#include <algorithm>
#define MAX_V 10

using namespace std;

struct edge {
  int to, cap, rev;
};

vector<edge> G[MAX_V];
bool used[MAX_V];

void addEdge(int from, int to, int cap) {

  G[from].push_back((edge){to, cap, G[to].size()});
  G[to].push_back((edge){from, 0, G[from].size() - 1});
}

int dfs(int v, int t, int f) {
  if(v == t) return f;
  used[v] = true;
  for(int i = 0; i < G[v].size(); i++) {
    edge &e = G[v][i];
    if(!used[e.to] && e.cap > 0) {
      //printf("%d, %d, %d\n", v, e.to, used[e.to]);
      int d = dfs(e.to, t, min(f, e.cap));
      if(d > 0) {
        e.cap -= d;
        G[e.to][e.rev].cap += d;
        return d;
      }
    }
  }
  return 0;
}

int maximumFlow(int s, int t) {
  int flow = 0;
  while(true) {
    memset(used, 0, sizeof(used));
    int f = dfs(s, t, 1e9);
    if(f == 0)
      return flow;
    flow += f;
  }
}

int main(){
  int from, to, c;
  while(scanf("%d%d%d", &from, &to, &c) != EOF) {
    addEdge(from, to, c);
  }
  printf("result: %d\n", maximumFlow(0, 4));
  
  return 0;
}
