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
  P blank;
};
State path[100001];
State root;
bool finished;


const int direct[4][2] = {
  {-1, 0}, // up
  {0, 1}, // right
  {1, 0}, // down
  {0, -1} // left
};

int cal_h(State s) {
  int h = 0;
  for(int i = 0; i < N; i++) { 
    for(int j = 0; j < N; j++)  {
      // manhattan distance
      int pos = s.a[i][j] - 1; // e.g. = 4, then pos = 3
      if(pos == -1) pos = 8; // blank put in [8]
      int i_ = pos / N;
      int j_ = pos % N;
      h += abs(i_ - i) + abs(j_ - j);
    }
  }
  return h;
}

State genInit(int *input[MAX_N + 1]) {

  State res;
  for(int i = 0; i < N; i++)
    for(int j = 0; j < N; j++) {
      res.a[i][j] = input[i][j];
      if(res.a[i][j] == 0) {
        res.blank.first = i;
        res.blank.second = j;
      }
    }
  return res;
}

bool theSame(State ss, State s) {
  if(ss.blank.first != s.blank.first || 
     ss.blank.second != s.blank.second) return false;
 
  for(int j = 0; j < N; j++)  
    for(int k = 0; k < N; k++) 
      if(ss.a[j][k] != s.a[j][k])
        return false;
      
  return true;
}

State genNew(State s, int dy, int dx) {
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

int search(State s, int cur_g, int bound) {

  int cur_f = cur_g + cal_h(s);
  path[cur_g] = s; // cur_g = depth
  if(cur_f > bound) 
    return cur_f;
  if(cal_h(s) == 0) { // reach the end
    finished = true;
    return bound;
  }
  int min_f = 1e9;
  for(int i = 0; i < 4; i++) {
    int dy = s.blank.first + direct[i][0];
    int dx = s.blank.second + direct[i][1];
    if(dy < 0 || dy >= N || dx < 0 || dx >= N) continue;
    State m = genNew(s, dy, dx); 
    int h = cal_h(m);
    bool inPath = false;
    for(int i = 0; i < cur_g; i++) {
      if(theSame(m, s)) {
        inPath = true;
        break;
      }
    }
    if(inPath) continue;
    int next = search(m, cur_g + 1, bound);
    
    if(finished)
      return min_f;
    
    if(next < min_f) {
      min_f = next;
    } else {
      // do nothing
    }
  }
  return min_f;
}
int idastar(State s) {

  int bound = cal_h(s);
  while(1) {
    int tmp = search(s, 0, bound);
    if(finished) {
      return bound; // found
    } else if(tmp == 1e9) {
      cout << "NO ROUTE" <<endl;
      return -1; // no route
    } else {
      bound = tmp;
    }
  }
}

int traverse() {
  int i = 0;
  while(1) {
    State s = path[i];
    cout << "Step " << i + 1 << ":" << endl;
    printState(s);
    if(cal_h(s) == 0) break;
    i++;
  }
  return i;
}

void solve(int *a[MAX_N + 1]) {
  State start = genInit(a);
  cout << "input: " << endl;
  printState(start);
  finished = false;
  int bound = idastar(start);
  cout << "---------------" << endl;
  int dep = traverse();
  cout << "bound: " << bound << endl; 
  cout << "min depth: " << dep + 1 << endl;
  // TODO: traverse
}

int main() {
  N = 3;
  int fin[] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
  //int val[] = {1, 2, 3, 4, 6, 0, 7, 5, 8};// {2, 3, 0, 7, 6, 8, 1, 5, 4};
  int val[] = {1, 6, 4, 8, 7, 0, 3, 2, 5}; // 21 steps in minimum!
  // int val[] = {2, 3, 0, 1, 6, 8, 7, 5, 4};
  // int val[] = {6, 0, 2, 8, 4, 5, 7, 3, 1};

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
