#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define MAX_V 10

using namespace std;

struct edge {
  int from, to, cap, rev;
};

vector<edge> G[MAX_V];
bool used[MAX_V];

void addEdge(int from, int to, int cap) {

  edge a = (edge){from, to, cap, G[to].size()};
  edge b = (edge){to, from, 0, G[from].size()};

  G[from].push_back(a); G[to].push_back(b);
}

int dfsFord(int v, int t, int f) {
  if(v == t) return f;
  used[v] = true;
  for(int i = 0; i < G[v].size(); i++) {
    edge &e = G[v][i];
    if(!used[e.to] && e.cap > 0) {
      //printf("%d, %d, %d\n", v, e.to, used[e.to]);
      int d = dfsFord(e.to, t, min(f, e.cap));
      if(d > 0) {
        e.cap -= d;
        G[e.to][e.rev].cap += d;
        return d;
      }
    }
  }
  return 0;
}

int maxFlowFord(int s, int t) {
  int flow = 0;
  while(true) {
    memset(used, 0, sizeof(used));
    int f = dfsFord(s, t, 1e9);
    if(f == 0)
      return flow;
    flow += f;
  }
}

void bfsKarp(int s, vector<edge*> &pred) {
  
  queue<int> que;
  que.push(s);
  while(!que.empty()) {
    int v = que.front(); que.pop();
    for(int i = 0; i < G[v].size(); i++){
      edge &e = G[v][i];
      if(pred[e.to] == 0 && e.cap > 0) {
        que.push(e.to);
        pred[e.to] = &e;
      }
    }
  }
}

int maxFlowKarp(int s, int t) {
  int flow = 0;
  while(true) {
    vector<edge*> pred(MAX_V, (edge*) NULL);
    bfsKarp(s, pred);
    if(pred[t] == 0) return flow;
   
    int f = 1e9;
    for(int v = t; v != s; v = pred[v]->from) {
      edge *e = pred[v];
      f = min(f, e->cap);
    }
    for(int v = t; v != s; v = pred[v]->from) {
      edge *e = pred[v];
      e->cap -= f;
      G[e->to][e->rev].cap += f;
    }
    flow += f;
  }
}

int level[MAX_V];
int iter[MAX_V];

void bfsDinic(int s) {
  memset(level, -1, sizeof(level));
  queue<int> que;
  level[s] = 0;
  que.push(s);
  while(!que.empty()) {
    int v = que.front(); que.pop();
    for(int i = 0; i < G[v].size(); i++) {
      edge &e = G[v][i];
      if(e.cap > 0 && level[e.to] < 0) {//unvisited
        level[e.to] = level[v] + 1;
        que.push(e.to);
      }
    }
  }
}

int dfsDinic(int v, int t, int f) {
  if(v == t) return f;
  for(int &i = iter[v]; i < G[v].size(); i++) {
    edge &e = G[v][i];
    if(e.cap > 0 && level[v] + 1 == level[e.to]) {
      int d = dfsDinic(e.to, t, min(f, e.cap));
      if(d > 0) {
        e.cap -= d;
        G[e.to][e.rev].cap += d;
        return d;
      }
    }
  }
  return 0;
}

int maxFlowDinic(int s, int t) {
  int flow = 0, f;
  while(true) {
    bfsDinic(s);
    if(level[t] < 0) return flow;
    memset(iter, 0, sizeof(iter));
    int f = dfsDinic(s, t, 1e9);
    if(f > 0){
      flow += f;
    }
  }
  // no need to return 
}

int main(){
  int from, to, c;
  while(scanf("%d%d%d", &from, &to, &c) != EOF) {
    addEdge(from, to, c);
  }
  // choose only one of them
//  printf("result: %d\n", maxFlowFord(0, 4));
  printf("result: %d\n", maxFlowKarp(0, 4));
//  printf("result: %d\n", maxFlowDinic(0, 4));
  
  return 0;
}
