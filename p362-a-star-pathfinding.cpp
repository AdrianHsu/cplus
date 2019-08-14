#include <cstdio>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>
#include <cmath>

#define MAX_W 15
#define MAX_H 15

using namespace std;
typedef pair<int, int> P;

const int direct[8][2] = {
  {-1, 0}, // += 10
  {1, 0},
  {0, -1},
  {0, 1},

  {-1, 1}, // += 14
  {-1, -1},
  {1, -1},
  {1, 1}
};


int W, H;
char map[MAX_H + 1][MAX_W + 1];
int f[MAX_H + 1][MAX_W + 1];
int g[MAX_H + 1][MAX_W + 1];
P parent[MAX_H + 1][MAX_W + 1];

P s;
P t;
vector<P> open;

void printMap() {
  for(int i = 0; i < H; i++) {
    for(int j = 0; j < W; j++) {
      cout << map[i][j];
    }
    cout << endl;
  }
  cout << endl;
}
int h(int y, int x) { // heuristic function
  return 10 * (abs(y - t.first) + abs(x - t.second));  
}
void astar(int y, int x) {
  map[y][x] = '#';
  for(int i = 0; i < open.size(); i++) {
    if(open[i].first == y && open[i].second == x) {
      open.erase(open.begin() + i);
      break;
    }
  }
  if(y == t.first && x == t.second) {
    return;
  }
  int dy, dx, currentMin = f[y][x];
  P next;
  bool move = false;
  for(int k = 0; k < 8; k++) {
    dy = y + direct[k][0];
    dx = x + direct[k][1];
    if(dy < 0 || dy >= H || dx < 0 || dx >= W) continue;
    if(map[dy][dx] == '#') continue;
    //map[dy][dx] = 'o';
    if(k < 4)
      g[dy][dx] = min(g[dy][dx], g[y][x] + 10);
    else
      g[dy][dx] = min(g[dy][dx], g[y][x] + 14);
    
    if(f[dy][dx] > g[dy][dx] + h(dy, dx)) {
      f[dy][dx] = g[dy][dx] + h(dy, dx);
      parent[dy][dx] = P(y, x);
    }
    
    if(f[dy][dx] < currentMin) {
      move = true;
      //cout << f[dy][dx] << endl;
      currentMin = f[dy][dx];
      next.first = dy;
      next.second = dx;
    }
    bool push = true;
    for(int i = 0; i < open.size(); i++) {
      if(open[i].first == dy && open[i].second == dx) {
        push = false;
        break;
      }
    }
    if(push) open.push_back(P(dy, dx)); 
  }
  printMap();
  
  if(move) {
    astar(next.first, next.second);
  } else {
    int smallest = 1e9;
    for(int i = 0; i < open.size(); i++) {
      if(f[open[i].first][open[i].second] < smallest) {
        next.first = open[i].first;
        next.second = open[i].second;
      }
    }
    astar(next.first, next.second);
  }
}
void walkBack() {
  P p;
  p.first = t.first;
  p.second = t.second;
  while(true) {
    map[p.first][p.second] = '@';
    printMap();
    if(p.first == s.first && p.second == s.second) break;
    P back = parent[p.first][p.second];
    p.first = back.first;
    p.second = back.second;
  }
}
void solve() {
  for(int i = 0; i < H; i++){ 
    for(int j = 0; j < W; j++) {
      g[i][j] = 1e9;
      f[i][j] = 1e9;
    }
  }
  g[s.first][s.second] = 0;
  f[s.first][s.second] = h(s.first, s.second);
  open.push_back(s);
  astar(s.first, s.second);
  walkBack();
}

int main() {
//.......
//...#...
//.s.#.t.
//...#...
//.......
  while(scanf("%d%d", &H, &W) != EOF) {
    if(H == 0 && W == 0) break;
    for(int i = 0; i < H; i++) {
      for(int j = 0; j < W; j++) {
        cin >> map[i][j];
        if(map[i][j] == 's') {
          s.first = i;
          s.second = j;
          map[i][j] = '.';
        } else if(map[i][j] == 't') {
          t.first = i;
          t.second = j;
          map[i][j] = '.';
        }
      }
    }
    solve();
    //printMap();
  }
  return 0;
}
