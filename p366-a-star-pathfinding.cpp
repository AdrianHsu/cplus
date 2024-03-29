#include <cstdio>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>
#include <cmath>
#include <set>

#define MAX_W 15
#define MAX_H 15

using namespace std;
typedef pair<int, int> P;
typedef pair<int, P> Q;

const int direct[8][2] = {
  {-1, 0}, // += 10
  {1, 0},
  {0, -1},
  {0, 1},

  {-1, -1}, // += 14
  {-1, 1},
  {1, 1},
  {1, -1}
};

int W, H;
char map[MAX_H + 1][MAX_W + 1];
int f[MAX_H + 1][MAX_W + 1];
int g[MAX_H + 1][MAX_W + 1];
P parent[MAX_H + 1][MAX_W + 1];

P s;
P t;
priority_queue<Q, vector<Q>, greater<Q> > open;
set<P> closed;

void printMap() {
  for(int i = 0; i < H; i++) {
    for(int j = 0; j < W; j++) {
      if(i == s.first && j == s.second) cout << "S";
      else if(i == t.first && j == t.second) cout << "T";
      //else if(map[i][j] == '0') cout << '.';
      else cout << map[i][j];
    }
    cout << endl;
  }
  cout << endl;
}
int h(int y, int x) { // heuristic function
  return 10 * (abs(y - t.first) + abs(x - t.second));  
}
void astar() {
  
  while(open.size() != 0){
    Q q = open.top();
    open.pop();
    int y = q.second.first;
    int x = q.second.second;
    closed.insert(q.second);
  
    map[y][x] = '0'; // closed
    if(y == t.first && x == t.second) {
      //cout << "REACH END" << endl;
      return;
    }
    for(int k = 0; k < 8; k++) {
      int dy = y + direct[k][0];
      int dx = x + direct[k][1];
      if(dy < 0 || dy >= H || dx < 0 || dx >= W) continue;
      if(map[dy][dx] == '#') continue;
      //set<P>::iterator it = closed.find(P(dy, dx));
      //if(it != closed.end()) continue;
      if(map[dy][dx] == '0') continue;

      if(k == 4 && (map[dy][dx + 1] == '#' || map[dy + 1][dx] == '#')) continue;
      if(k == 5 && (map[dy][dx - 1] == '#' || map[dy + 1][dx] == '#')) continue;
      if(k == 6 && (map[dy][dx - 1] == '#' || map[dy - 1][dx] == '#')) continue;
      if(k == 7 && (map[dy][dx + 1] == '#' || map[dy - 1][dx] == '#')) continue;
      if(k < 4)
        g[dy][dx] = min(g[dy][dx], g[y][x] + 10);
      else
        g[dy][dx] = min(g[dy][dx], g[y][x] + 14);
      
      if(f[dy][dx] > g[dy][dx] + h(dy, dx)) {
        f[dy][dx] = g[dy][dx] + h(dy, dx);
        parent[dy][dx] = P(y, x);
      }
      
      if(map[dy][dx] == '.')  {
        open.push(Q(f[dy][dx], P(dy, dx))); 
        map[dy][dx] = 'o';
      }
    }
    printMap();
    if(open.size() == 0) {
      cout << "NO ROUTE" << endl; 
      return;
    }
  }
}
void walkBack() {
  P p;

  p.first = t.first;
  p.second = t.second;
  if(parent[t.first][t.second].first == -1 && parent[t.first][t.second].second == -1) return;
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
  g[s.first][s.second] = 0;
  f[s.first][s.second] = h(s.first, s.second);

  while(!open.empty())
    open.pop();
  open.push(Q(f[s.first][s.second], s));
  astar();
  cout << "----------" << endl;
  walkBack();
  cout << "min distance: " << f[t.first][t.second] << endl;
}

int main() {
//.......
//...#...
//.s.#.t.
//...#...
//.......
  while(scanf("%d%d", &H, &W) != EOF) {
    if(H == 0 && W == 0) break;
    for(int i = 0; i < MAX_H; i++){ 
      for(int j = 0; j < MAX_W; j++) {
        map[i][j] = 0;
        g[i][j] = 1e8;
        f[i][j] = 1e8;
        parent[i][j] = P(-1, -1);
      }
    }
    
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
