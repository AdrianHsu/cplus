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
P path[(MAX_H + 1) * (MAX_W + 1)]; // acted as a stack

P s;
P t;

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

int search(P p, int cur_g, int bound, int depth) {
  
  int cur_f = cur_g + h(p.first, p.second);
  path[depth] = p;
  if(cur_f > bound) 
    return cur_f;
  if(p.first == t.first && p.second == t.second) {
    return -1;
  }
  
  int min_f = 1e9;
  map[p.first][p.second] = '0';
  //printMap();
  for(int k = 0; k < 8; k++) {
    int dy = p.first + direct[k][0];
    int dx = p.second + direct[k][1];
    if(dy < 0 || dy >= H || dx < 0 || dx >= W) continue;
    if(map[dy][dx] == '#') continue;
    if(k == 4 && (map[dy][dx + 1] == '#' || map[dy + 1][dx] == '#')) continue;
    if(k == 5 && (map[dy][dx - 1] == '#' || map[dy + 1][dx] == '#')) continue;
    if(k == 6 && (map[dy][dx - 1] == '#' || map[dy - 1][dx] == '#')) continue;
    if(k == 7 && (map[dy][dx + 1] == '#' || map[dy - 1][dx] == '#')) continue;
    
    bool inClosed = false;
    for(int i = 0; i < depth; i++) {
      if(path[i].first == dy && path[i].second == dx) {
        inClosed = true;
        break;
      }
    }
    if(inClosed) continue;
    
    int next;
    if(k < 4)
      next = search(P(dy, dx), cur_g + 10, bound, depth + 1);
    else
      next = search(P(dy, dx), cur_g + 14, bound, depth + 1);
    map[p.first][p.second] = 'o';
    if(next == -1) {
      return -1;
    } else if(next < min_f) {
      min_f = next;
    } else {
      // do nothing
    }
  }
  return min_f;
}

int idastar(int y, int x) {
  
  int bound = h(y, x);
  while(1) {
    int tmp = search(P(y, x), 0, bound, 0);
    if(tmp == -1)
      return bound; // found
    else if(tmp == 1e9) {
      cout << "NO ROUTE" <<endl;
      return -1; // no route
    } else {
      bound = tmp;
    }
  }
}
void walk() {
  
  int i = 0;
  while(1) {
    if(path[i].first == t.first && path[i].second == t.second)
      break;
    int y = path[i].first;
    int x = path[i].second;
    map[y][x] = '@';
    printMap();
    i++;
  }
}
void solve() {
  //g[s.first][s.second] = 0;
  //f[s.first][s.second] = h(s.first, s.second);

  int res = idastar(s.first, s.second);
  cout << "----------" << endl;
  walk();
  cout << "min distance: " << res << endl;
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
        path[i * MAX_W + j] = P(-1, -1);
        // g[i][j] = 1e8;
        // f[i][j] = 1e8;
        // parent[i][j] = P(-1, -1);
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
  }
  return 0;
}
