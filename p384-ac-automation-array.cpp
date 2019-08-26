#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <queue>

typedef long long ll;

#define MAXC 26
const int MAXS = 500; // e.g. 10 個 pattern, 每個 pattern 長度 10，所以 Trie 最大就 100
// MAXS is the Max number of states in the matching machine. 
// Should be equal to the sum of the length of all keywords. 

using namespace std;
typedef long long ll;

struct acAutomata {
  int ch[MAXS][MAXC]; //child
  int f[MAXS];
  int out[MAXS];
  int pos;

  void clear() {
    
    pos = 1; // Initially, we just have the 0 state 
    memset(out, 0, sizeof(out));
    memset(ch, -1, sizeof(ch));
    memset(f, -1, sizeof(f));
  }
  int idx(char c) {
    return c - 'a';
  }
  
  void insert(string s, int i) {
    int dep = 0;
    for(int i = 0; i < s.length(); i++) {
      int c = idx(s[i]);
      if(ch[dep][c] == -1) 
        ch[dep][c] = pos++;
      
      dep = ch[dep][c];
    }
    out[dep] |= (1 << i);
  }
  
  void build() {

    for(int i = 0; i < MAXC; i++)
      if(ch[0][i] == -1)
        ch[0][i] = 0;

    // for depth = 1
    queue<int> Q;
    for(int i = 0; i < MAXC; i++) {
      int child = ch[0][i];
      if(child > 0) { 
        f[child] = 0;
        Q.push(child);
      }
    }

    // for depth > 1
    while(!Q.empty()) {
      int r = Q.front(); Q.pop();
      for(int i = 0; i < MAXC; i++) { 
        int child = ch[r][i];
        if(child == -1)
          continue;
        int fail = f[r];
        while(ch[fail][i] == -1) {
          fail = f[ fail ];
        }
        fail = ch[fail][i];
        f[child] = fail;

        out[child] |= out[fail];
        Q.push(child);
      }
    }
  }

  int find(int state, char c) {
    int ans = state;
    int i = idx(c);
    while(ch[ans][i] == -1)
      ans = f[ans];

    return ch[ans][i];
  }

} ac;

void solve() {
  ac.clear();
  int arr_size = 5;
  string arr[] = {"say", "she", "shr", "he", "her"};
  string target = "yasherhs";
  // string arr[] = {"a", "ab", "bab", "bc", "bca", "c", "caa"};
  // string target = "abccab";

  for(int i = 0; i < arr_size; i++) {
    ac.insert(arr[i], i);
  }
  ac.build();
  // cout << ac.f[0] << endl;
  // cout << ac.f[1] << endl;

  int state = 0;
  int cnt = 0;
  for(int i = 0; i < target.length(); i++) {
    state = ac.find(state, target[i]);

    if(ac.out[state] == 0)
      continue;
    for(int j = 0; j < arr_size; j++) {
      if(ac.out[state] & (1 << j))
        cnt++;
      // if(ac.out[state] & (1 << j))
      //   cout << "Word " << arr[j] << " appears from "
      //                << i - arr[j].size() + 1 << " to " << i << endl; 
    }
  }
  cout << cnt << endl;
}

int main() {
  solve();
  return 0;
}
