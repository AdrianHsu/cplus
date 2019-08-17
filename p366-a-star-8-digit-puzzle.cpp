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
  int f, g;
  P blank;
  int parent;
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
  res.g = 0;
  res.f = res.g + cal_h(res);
  res.parent = -1;
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

int inClosedList(State s) {
  for(int i = closed.size() - 1; i >= 0; i--) {
    State ss = closed[i];
    if(theSame(ss, s)) return i;// same
  }
  return -1;
}
int inOpenList(State s) {
  for(int i = 0; i < open.size(); i++) {
    State ss = open[i];
    if(theSame(ss, s)) return i;
  }
  return -1;
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
  res.g = s.g + 1;
  res.f = res.g + cal_h(res);
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
  //cout << "h: " << cal_h(s) << "\n" << endl;
}

int astar() {
  while(open.size() != 0) {
    State s = open[0];
    //printState(s);
    if(cal_h(s) == 0) { // done
      return s.g;
    }
    open.erase(open.begin());
    closed.push_back(s);
    int pid = closed.size() - 1;

    for(int i = 0; i < 4; i++) {
      int dy = s.blank.first + direct[i][0];
      int dx = s.blank.second + direct[i][1];
      if(dy < 0 || dy >= N || dx < 0 || dx >= N) continue;
      State m = genNew(s, dy, dx); 
      m.parent = pid;
      int in = inClosedList(m);  // == -1 means, 沒有一樣的在裡面
      int op = inOpenList(m);
      if(op != -1) {
        int h = cal_h(open[op]);
        if(m.g + h < open[op].f) {
          open[op].g = m.g;
          open[op].f = m.g + h;
          open[op].parent = pid;
        }
      } else if(in != -1) {
        int h = cal_h(closed[in]);
        if(m.g + h < closed[in].f) {
          open.push_back(m);
          //closed.erase(closed.begin() + in); // no way! the index will be effected..
        }
      } else {
        open.push_back(m);
      }
    }
    sort(open.begin(), open.end());
  }
  cout << "NO ANSWER" << endl;
  return -1;
}

void reversePrint(int result) {
  State s = open[0];
  int i = 1;
  while(true) {

    cout << "Step " << result - i + 1 << ":" << endl;
    printState(s);
    if(s.parent == -1) break;
    s = closed[s.parent];
    i++;
  }
}

void solve(int *a[MAX_N + 1]) {
  State start = genInit(a);
  cout << "input: " << endl;
  printState(start);
  cout << "---------------" << endl;
  open.push_back(start);
  int dep = astar();
  cout << "min depth: " << dep + 1 << endl;
  cout << "---------------" << endl;
  reversePrint(dep + 1);
}

int main() {
  N = 3;
  int fin[] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
  //int val[] = {1, 2, 3, 4, 6, 0, 7, 5, 8};// {2, 3, 0, 7, 6, 8, 1, 5, 4};
  int val[] = {1, 6, 4, 8, 7, 0, 3, 2, 5}; // 21 steps in minimum!
  //int val[] = {2, 3, 0, 1, 6, 8, 7, 5, 4};
  //int val[] = {6, 0, 2, 8, 4, 5, 7, 3, 1};

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
