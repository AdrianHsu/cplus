#include <iostream>
#include <cstdio>
#include <vector>

#define MAX_V 10

using namespace std;

int V_right;
int V_left;
vector<int> G[MAX_V];
int match[MAX_V];
bool used[MAX_V];

void add_edge(int u, int v) {
  G[u].push_back(v);
  G[v].push_back(u);
}

bool dfs(int v) {
  for(int i = 0; i < G[v].size(); i++) {
    int u = G[v][i], w = match[u];
    if(!used[u]) {
      used[u] = true;
      if(w < 0 || dfs(w)) {
        match[v] = u;
        match[u] = v;
        return true;
      }
    }
  }
  return false;
}

int hungarian() { // bipartite matching
  int res = 0;
  memset(match, -1, sizeof(match));
  for(int v = 0; v < V_left + V_right; v++) {
    if(match[v] < 0) {
      memset(used, 0, sizeof(used));
      if(dfs(v)) res++;
    }
  }
  return res;
}

int main() {
  V_right = 4;
  V_left = 4;
  add_edge(1, 5);
  add_edge(1, 7);
  add_edge(2, 5);
  add_edge(3, 5);
  add_edge(3, 6);
  add_edge(4, 7);
  add_edge(4, 8);
  printf("result: %d\n", hungarian());
  return 0;
}
