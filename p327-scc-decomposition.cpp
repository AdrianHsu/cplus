#include <cstdio>
#include <iostream>
#include <vector>

#define MAX_V 15

using namespace std;

int V;
vector<int> G[MAX_V]; // adjacency list
vector<int> rG[MAX_V];
vector<int> vs;
bool used[MAX_V];
int cmp[MAX_V];

void add_edge(int from, int to) {
  G[from].push_back(to);
  rG[to].push_back(from);
}

void dfs(int v) {
  used[v] = true;
  for(int i = 0; i < G[v].size(); i++) {
    if(!used[G[v][i]])
      dfs(G[v][i]);
  }
  vs.push_back(v);
}

void printScc() {
  for(int v = 0; v < V; v++) {
    cout << "vertex " << v + 1 << ": belongs to SCC " << cmp[v] << endl;
  }
}

void rdfs(int v, int k) {
  used[v] = true;
  cmp[v] = k;
  for(int i = 0; i < rG[v].size(); i++) {
    if(!used[rG[v][i]])
      rdfs(rG[v][i], k);
  }
}

int scc() {
  memset(used, 0, sizeof(used));
  vs.clear();
  for(int v = 0; v < V; v++)
    if(!used[v]) dfs(v);
  memset(used, 0, sizeof(used));
  int k = 0;
  for(int i = vs.size() - 1; i >= 0; i--)
    if(!used[vs[i]]) rdfs(vs[i], k++);
  return k;
}


int main() {
  V = 12; 
  int E = 16;
  // 編號方式會隨著 traverse 順序而改變
  int from_in [] = {12, 11, 11,  8, 9, 10, 9, 7, 6, 5, 6, 6, 4, 3, 2, 4};
  int to_in [] =   {11,  8, 10, 10, 8,  9, 7, 6, 5, 7, 3, 4, 3, 2, 3, 1};
  for(int i = 0; i < E; i++)
    add_edge(from_in[i], to_in[i]);

  cout << "\nnum of scc sets: " << scc() << endl;
  printScc();
  return 0;
}
