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
    memset(child, NULL, sizeof(child));
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
}

void solve() {
  root = new Node();
  memset(root->child, 0, sizeof(root->child));
  
  insert("say");
  insert("she");
  insert("shr");
  insert("he");
  insert("her");
  
  acAutomation(); // after this, you cannot insert later on

}
int main() {
  
  solve(); 
  return 0;
}
