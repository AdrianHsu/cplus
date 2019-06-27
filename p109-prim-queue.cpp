#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <utility> // pair
#include <queue>

#define MAX_V 15
#define INF 0xfffffff

using namespace std;

struct edge { int to, cost; };
typedef pair<int, int> P; // first: mincost, second: idx

//int V;
vector<edge> G[MAX_V]; // un-directed graph
int mincost[MAX_V];
int pre[MAX_V]; // prev

void prim(int s) {
  priority_queue<P, vector<P>, greater<P> > que;
  fill(mincost, mincost + MAX_V, INF);
  fill(pre, pre + MAX_V, -1);
  mincost[s] = 0;
  que.push(P(0, s));
  
  vector<bool> inMST(MAX_V, false);
  int res = 0;

  while(!que.empty()){
    P p = que.top(); que.pop();
    int v = p.second;
    inMST[v] = true; 
    if(mincost[v] < p.first) continue;
    for (int i = 0; i < G[v].size(); i ++) {
      edge e = G[v][i];
      if(!inMST[e.to] && mincost[e.to] > e.cost) {
        mincost[e.to] = e.cost;
        que.push(P(mincost[e.to], e.to));
        pre[e.to] = v;
      }
    }
    res += mincost[v];
  }
  printf("Total Min Cost: %d\n", res);
}
void printMinCost(){
  printf("MINCOST...\n");
  for(int i = 0; i < MAX_V; i++)
    printf("%d: %d\n", i, mincost[i]);
}
void printPre(){
  printf("PREV VERTEX...\n");
  for(int i = 0; i < MAX_V; i++)
    printf("%d: %d\n", i, pre[i]);
}

int main() {
  // ./run.sh p109-prim-queue.cpp < in/prim-sample.in  
  int s;
  edge e;
  int eof = 1;
  while(true){
    eof = scanf("%d%d%d", &s, &e.to, &e.cost);
    if(eof == EOF) break;

    printf("%d,%d,%d\n", s, e.to, e.cost);
    G[s].push_back(e);
  }
  printf("------\n");
  prim(1);
  printMinCost();
  printf("-----\n");
  printPre();
  return 0;
}
