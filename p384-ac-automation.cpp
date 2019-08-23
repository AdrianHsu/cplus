#include <iostream>
#include <cstdio>
#include <cstring>
#define MAX_N 26

using namespace std;
struct Node {
  Node* child[MAX_N];
  int cnt;
};

Node* root;
void insert(string str) {
  Node *now = root; 
  for(int i = 0; i < str.length(); i++) {
    char c = str[i];
    if(now->child[c - 'a'] == NULL) {
      Node* _next = new Node();
      _next->cnt = 0;
      memset(_next->child, 0, sizeof(_next->child));
      now->child[c - 'a'] = _next;
    }
    now = now->child[c - 'a'];
  }
  now->cnt++;
}
bool search(string str) {
  Node *now = root;
  for(int i = 0; i < str.length(); i++) {
    char c = str[i];
    if(now->child[c - 'a'] != NULL) {
      now = now->child[c - 'a'];
    } else {
      return false;
    }
  }
  return now->cnt;
}
void solve() {
  root = new Node();
  memset(root->child, 0, sizeof(root->child));
  
  insert("abcde");
  insert("acde");
  insert("bce");
  cout << search("bce") << endl;
  cout << search("abce") << endl;
  cout << search("abcde") << endl;
  cout << search("abcdef") << endl;
}
int main() {
  
  solve(); 
  return 0;
}
