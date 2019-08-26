#include <iostream>
#include <cstdio>
#include <map>
#include <queue>
#define MAX_M 15
#define MAX_LEN 15 // pattern len

#define MOD 100000
typedef long long ll;
const int MAX_N = 2000000005;
int M, N;

using namespace std;
map<char, int> ACTG;

string pat[MAX_M];

struct Node {
  Node* child[4];
  Node* fail;
  int cnt;

  Node(){
    fail = NULL;
    cnt = 0;
    memset(child, 0, sizeof(child));
  }
};

Node* root;
void insert(string str) {
  Node *now = root; 
  for(int i = 0; i < str.length(); i++) {
    char c = str[i];
    if(now->child[ACTG[c]] == NULL) {
      Node* _next = new Node();
      now->child[ACTG[c]] = _next;
    }
    now = now->child[ACTG[c]];
  }
  now->cnt++;
}
void acAutomation() {

  queue<Node*> Q;
  Node *now;
  Node *f;
  Q.push(root);

  while(!Q.empty()) {
    Node* now = Q.front();
    Q.pop();
    for(int i = 0; i < 4; i++) {
      if(now->child[i] == NULL) continue;

      if(now == root)
        now->child[i]->fail = root;
      else {
        f = now->fail;
        while(f != NULL) {
          if(f->child[i] != NULL) {
            now->child[i]->fail = f->child[i];
            break;
          }
          f = f->fail;
        }
        if(f == NULL)
          now->child[i]->fail = root;
      }
      Q.push(now->child[i]);
    }
  }
}
int query(string s) {
  int index, cnt = 0;
  Node *now = root;
  Node *tmp;

  for(int i = 0; i < s.length(); i++) {
    index = ACTG[s[i]];
    while(now->child[index] == NULL && now->fail != NULL)
      now = now->fail;
    if(now->child[index] != NULL) {
      now = now->child[index];
      tmp = now;
      while(tmp->cnt > 0) {
        cnt += tmp->cnt;
        tmp->cnt = -1; // after this time, it will not be added again becuz -1 < 0
        tmp = tmp->fail;
      }
    }
  }
  return cnt;
}

void solve() {
  root = new Node();
  for(int i = 0; i < M; i++)
    insert(pat[i]);
  
  acAutomation(); // after this, you cannot insert later on
  //cout << query(target) << endl;
}

int main() {
  ACTG['A'] = 0;
  ACTG['C'] = 1;
  ACTG['T'] = 2;
  ACTG['G'] = 3;

  scanf("%d%d", &M, &N);

  int i = 0, m = M;
  while(m > 0) {
    cin >> pat[i++];
    m--;
  }
  solve();
  return 0;
}
