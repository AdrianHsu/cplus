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
typedef pair<int, int> P; // first: distance, second: idx

//int V;
vector<edge> G[MAX_V];
int d[MAX_V];
int pre[MAX_V];

void dijkstra(int s) {
  priority_queue<P, vector<P>, greater<P> > que;
  fill(d, d + MAX_V, INF);
  fill(pre, pre + MAX_V, -1);
  d[s] = 0;
  que.push(P(0, s));

  while(!que.empty()){
    P p = que.top(); que.pop();
    int v = p.second;
    if(d[v] < p.first) continue;
    for (int i = 0; i < G[v].size(); i ++) {
      edge e = G[v][i];
      if(d[e.to] > d[v] + e.cost) {
        d[e.to] = d[v] + e.cost;
        que.push(P(d[e.to], e.to));
        pre[e.to] = v;
      }
    }
  }
}
void printDistance(){
  for(int i = 0; i < MAX_V; i++)
    printf("%d: %d\n", i, d[i]);
}
void printPre(){
  printf("PREV VERTEX...\n");
  for(int i = 0; i < MAX_V; i++)
    printf("%d: %d\n", i, pre[i]);
}
int main() {
  // ./run.sh p105-dijkstra-queue.cpp < in/dijkstra-sample.in  
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
  dijkstra(1);
  printDistance();
  printf("------\n");
  printPre();
  return 0;
}
