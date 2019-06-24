#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
#include <utility> // pair
#include <queue>

#define MAX_V 15
#define INF (1 << 30)

using namespace std;

struct edge { int to, cost; };
typedef pair<int, int> P; // first: distance, second: idx

//int V;
vector<edge> G[MAX_V];
int d[MAX_V];

void dijkstra(int s) {
  priority_queue<P, vector<P>, greater<P> > que;
  fill(d, d + MAX_V, INF);
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
      }
    }
  }
}
void printDistance(){
  for(int i = 0; i < MAX_V; i++)
    printf("%d: %d\n", i, d[i]);
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
  return 0;
}
