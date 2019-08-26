#include <iostream>
#include <cstdio>
#include <cstring>
#define MAX_N 26
//https://www.hackerearth.com/zh/practice/data-structures/advanced-data-structures/trie-keyword-tree/tutorial/
using namespace std;
struct Node {
  Node* child[MAX_N];
  int count; // 一個標誌，用來標記該結點處是否構成一個單詞（關鍵字）
  // count > 0 代表他確實是一個關鍵字
};

Node* root;
void insert(string str) {
  Node *now = root; 
  for(int i = 0; i < str.length(); i++) {
    char c = str[i];
    if(now->child[c - 'a'] == NULL) {
      Node* _next = new Node();
      _next->count = 0;
      memset(_next->child, 0, sizeof(_next->child));
      now->child[c - 'a'] = _next;
    }
    now = now->child[c - 'a'];
  }
  now->count++;
}
int search(string str) {
  Node *now = root;
  int cnt = 0;
  for(int i = 0; i < str.length(); i++) {
    char c = str[i];
    if(now->child[c - 'a'] != NULL) {
      now = now->child[c - 'a'];
    } else {
      return 0;
    }
  }
  return now->count;
}
void solve() {
  root = new Node();
  root->count = 0;
  memset(root->child, 0, sizeof(root->child));
  
  insert("abcde");
  insert("acde");
  insert("abce");
  insert("bce");
  insert("bce");
  insert("ce");
  cout << search("bce") << endl;
  cout << search("abce") << endl;
  cout << search("abcde") << endl;
  cout << search("abcdefbce") << endl;
}
int main() {
  
  solve(); 
  return 0;
}
