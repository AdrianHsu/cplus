#include <iostream>
#include <cstdio>

#define MAX_W 10
#define MAX_H 10

using namespace std;
int W, H;
int p[MAX_H + 1][MAX_W + 1];
int t[MAX_H + 1][MAX_W + 1];
int k[MAX_H + 1][MAX_W + 1];

void printCarpet() {
  for(int i = 0; i < H; i++) {
    for(int j = 0; j < W; j++)
      cout << p[i][j] << " ";
    cout << endl;
  }
}

void preprocess() {

}

void solve() {
  preprocess();
}

int main() {
  while(scanf("%d%d", &W, &H) != EOF) {
    if(W == 0 && H == 0) break;

    for(int i = 0; i < H; i++)
      for(int j = 0; j < W; j++)
        scanf("%d", &p[i][j]);
    solve();
  }
  return 0;
}
