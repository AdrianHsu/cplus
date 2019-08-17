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

int cnt(){
    int num = 1e9;
    for(int i = 1; i <= 3; i++){ // try: symbols 1 or 2 or 3
        int tmp = 0;
        // 檢查目前中央那 8 格之中，共有幾個 = i。越多越好，假如 2 有 7 個、
        // 1 有 3 個，那當然是選把 2 湊齊，因為比較容易
        for(int j = 0; j < 8; j++)
            if(a[ c[j] ] != i) tmp++;
        
        num = min(num, tmp);
    }
    return num;
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
  // pruning, e.g. 放棄組出 8 個 1 或 8 個 3，只嘗試組 8 個 2
  // 因為每次加深一層，最多就是多一個 2（i.e. 擠掉一個 3 ）
  // 除此之外並不影響其他格。假如目前 5 個 2，代表還需要最少移動 3 次湊齊 8 個 2
  // 也就是最少要加深 3 層。所以 dep + cnt() > maxH 代表永遠達不到，直接放棄
  if(dep + cnt() > maxH) return false;
  
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
