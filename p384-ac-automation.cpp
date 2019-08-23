#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>

#define MAX_N 26

using namespace std;
struct Node {
  Node* child[MAX_N];
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
    if(now->child[c - 'a'] == NULL) {
      Node* _next = new Node();
      now->child[c - 'a'] = _next;
    }
    now = now->child[c - 'a'];
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
    for(int i = 0; i < MAX_N; i++) {
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
    index = s[i] - 'a';
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
  
 // insert("say");
 // insert("she");
 // insert("shr");
 // insert("he");
 // insert("her");
 
  insert("a");
  insert("ab");
  insert("bab");
  insert("bc");
  insert("bca");
  insert("c");
  insert("caa");

  acAutomation(); // after this, you cannot insert later on
  //string target = "yasherhs";
  string target = "abccab";
  cout << query(target) << endl;
}
int main() {
  
  solve(); 
  return 0;
}
