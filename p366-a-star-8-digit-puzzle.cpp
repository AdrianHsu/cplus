#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>

#define MAX_N 5

using namespace std;
typedef pair<int, int> P;

int N;
int ans[MAX_N + 1][MAX_N + 1];

struct State {
  int a[MAX_N + 1][MAX_N + 1];
  int f;
  P blank;
  State *parent;
};

State root;

bool operator<(const State &s1, const State &s2) {
    return s1.f < s2.f;
}

vector<State> open;
vector<State> closed;

const int direct[4][2] = {
  {-1, 0}, // up
  {0, 1}, // right
  {1, 0}, // down
  {0, -1} // left
};

int cal_h(State s) {
  int h = 0;
  for(int i = 0; i < N; i++) 
    for(int j = 0; j < N; j++)  {
      // manhattan distance
      int pos = s.a[i][j] - 1; // e.g. = 4, then pos = 3
      if(pos == -1) pos = 8; // blank put in [8]
      int i_ = pos / N;
      int j_ = pos % N;
      h += abs(i_ - i) + abs(j_ - j);
    }
  return h;
}


State genInit(int *a[MAX_N + 1], int g) {

  State res;
  for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++) {
      res.a[i][j] = a[i][j];
      if(a[i][j] == 0) {
        res.blank.first = i;
        res.blank.second = j;
      }
    }
  res.f = g + cal_h(res);
  res.parent = &root;
  return res;
}

int inClosedList(State s) {
  for(int i = 0; i < closed.size(); i++) {
    State ss = closed[i];
    bool flag = true;
    for(int j = 0; j < N; j++) {
      if(flag == false) break;
      for(int k = 0; k < N; k++) {
        if(ss.a[j][k] != s.a[j][k]) {
          flag = false;
          break;
        }
      }
    }
    if(flag) return i;// same
  }
  return -1;
}
int inOpenList(State s) {
  for(int i = 0; i < open.size(); i++) {
    State ss = open[i];
    bool flag = true;
    for(int j = 0; j < N; j++) {
      if(flag == false) break;
      for(int k = 0; k < N; k++) {
        if(ss.a[j][k] != s.a[j][k]) {
          flag = false;
          break;
        }
      }
    }
    if(flag) return i;// same
  }
  return -1;
}

State genNew(State s, int dy, int dx, int g) {
  State res;
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      res.a[i][j] = s.a[i][j];
    }
  }
  int tmp = res.a[dy][dx];
  res.a[dy][dx] = 0;
  res.a[s.blank.first][s.blank.second] = tmp;
  
  res.blank.first = dy;
  res.blank.second = dx;
  res.f = g + cal_h(res);
  res.parent = &s;
  return res;
}

void printState(State s) {
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      cout << s.a[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

void astar(int dep) {

  State s = open[0];
  //printState(s);
  if(cal_h(s) == 0) { // done
    cout << "dep:" << dep << endl;
    root.parent = &s;
    return;
  }
  open.erase(open.begin());
  for(int i = 0; i < 4; i++) {
    int dy = s.blank.first + direct[i][0];
    int dx = s.blank.second + direct[i][1];
    if(dy < 0 || dy >= N || dx < 0 || dx >= N) continue;
    State m = genNew(s, dy, dx, dep); 
    if(inClosedList(m) != -1) continue; // == -1 means, 沒有一樣的在裡面
    int o = inOpenList(m);
    if(o == -1)
      open.push_back(m);
    else {
      int h = cal_h(open[o]);
      if(dep + h < open[o].f) { 
        open[o].f = dep + h;
        open[o].parent = &s;
      }
    }
  }
  closed.push_back(s);
  if(open.size() == 0) {
    cout << "NO ROUTE" << endl;
  }
  sort(open.begin(), open.end());
  astar(dep + 1);
}

void reversePrint() {
  State s = root;
  while(&*s.parent != &root) {
    printState(s);
    s = *s.parent;
  }
}

void solve(int *a[MAX_N + 1]) {
  State start = genInit(a, 0);
  open.push_back(start);
  astar(0);
  reversePrint();
}

int main() {
  N = 3;
  int fin[] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
  int val[] = {1, 2, 3, 4, 6, 0, 7, 5, 8};// {2, 3, 0, 7, 6, 8, 1, 5, 4};
  int *a[MAX_N + 1];
  for(int i = 0; i < N; i++) {
    a[i] = new int [MAX_N + 1];
    for(int j = 0; j < N; j++) {
      ans[i][j] = fin[i * N + j];
      a[i][j] = val[i * N + j];
    }
  }
  solve(a);
  return 0;
}
