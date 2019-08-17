#include <cstdio>
#include <iostream>
#include <string>

using namespace std;
const int c[10]= {6, 7, 8, 11, 12, 15, 16, 17};
int a[24] ,maxH = 1;
char p[100001]; //result string, e.g. AC or DDHH or ...

int rot[8][7] = {                
    {0,2,6,11,15,20,22},         //A
    {1,3,8,12,17,21,23},         //B
    {10,9,8,7,6,5,4},            //C
    {19,18,17,16,15,14,13},     //D
    {23,21,17,12,8,3,1},        //E
    {22,20,15,11,6,2,0},         //F
    {13,14,15,16,17,18,19},     //G
    {4,5,6,7,8,9,10}             //H 
};

bool check() {
  for(int i = 0; i < 8; i++)
    if(a[c[0]] != a[c[i]]) return false;
  return true;
}



void move(int x) {
  int head = a[rot[x][0]];
  for(int i = 0; i < 6; i++) {
    // 1 move to 0, 2 move to 1, 3 move to 2... 6 move to 5
    a[rot[x][i]] = a[rot[x][i + 1]];
  }
  a[rot[x][6]] = head; // head: move to tail (i.e., 0 move to 6)
}

bool dfs(int dep) {
  if(dep > maxH) return false;
  if(check()) {
    p[dep] = '\0'; // end of string
    return true;
  }
  //if(dep + cnt() > maxH) return false;
  for(int i = 0; i < 8; i++) {
    p[dep] = 'A' + i; // A, B, C, D, ..., H
    move(i);
    
    if(dfs(dep + 1))
      return true;
    // move is done, and do backtracking... return to original place
    if(i % 2 == 0) // i = 0, 2, 4, 6
      move((i + 5) % 8); // e.g. move(2) -> move(2 + 5 % 8)
    else // i = 1, 3, 5, 7
      move((i + 3) % 8);
  }
  
  return false;
}


void solve() {
  if(check()) {
    printf("No moves needed\n%d\n", a[c[0]]);
    return;
  }
  while(!dfs(0))
    maxH++;
  printf("%s\n", p);
  printf("%d\n", a[c[0]]);
}

int main() {
  while(scanf("%d", &a[0]) && a[0]) {
    maxH = 1;
    for(int i = 1; i < 24; i++)
      scanf("%d", &a[i]);
    
    solve();
  }
  return 0;
}
