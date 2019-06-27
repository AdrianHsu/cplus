#include <cstdio>
#include <cstring>
#include <queue>
#include <iostream>

#define MAX_H 20
#define MAX_W 20

using namespace std;
char room[MAX_H][MAX_W];

int res;
int W;
int H;
// up, down, left, right
const int direct[4][2] = { 
  {-1, 0}, // dy, dx
  {1, 0},
  {0, -1},
  {0, 1}
};

void printRoom() {
  for(int i = 0; i < H; i ++) {
    printf("%s\n", room[i]);    
  }
  printf("\n");
}


void DFS(int pos_y, int pos_x) {
  room[pos_y][pos_x] = '#';
  res += 1;

  for(int i = 0; i < 4; i++) {  
    int py = pos_y + direct[i][0];
    int px = pos_x + direct[i][1];

    if(py < 0 || py >= H || px < 0 || px >= W || room[py][px] == '#') // red block
      continue;
    DFS(py, px);
  }
}

typedef pair<int, int> P;

void BFS(int pos_y, int pos_x) {
  queue<P> que;
  que.push(P(pos_y, pos_x));
  room[pos_y][pos_x] = '#';

  while(!que.empty()){
    P p = que.front(); que.pop();
    res += 1; 
    for(int i = 0; i < 4; i ++) {
      int py = p.first + direct[i][0];
      int px = p.second + direct[i][1];
      if(py < 0 || py >= H || px < 0 || px >= W || room[py][px] == '#') // red block
        continue;
      que.push(P(py, px)); 
      room[py][px] = '#';
    }
  }
}

void solve(int pos_y, int pos_x) {
  DFS(pos_y, pos_x);
  //BFS(pos_y, pos_x);
}

int main() {

  int pos_x = 0, pos_y = 0;
  while(scanf("%d%d", &W, &H) != EOF){ 
    if(W == 0 || H == 0) break;
    memset(room, 0, sizeof(room));
    res = 0;

    for(int i = 0; i < H; i++) {  
      for(int j = 0; j < W; j++) {
        cin >> room[i][j]; // AC
        // scanf("%c", &room[i][j]); // read \0
      }
    }
    // printRoom();
    for(int i = 0; i < H; i++) {  
      // scanf("%s", room[i]); // it will read \0 
      for(int j = 0; j < W; j++) {
        if(room[i][j] == '@'){
          pos_y = i;
          pos_x = j;
        }
      }
    }
    solve(pos_y, pos_x);
    printf("%d\n", res);
  }
  return 0;
}
