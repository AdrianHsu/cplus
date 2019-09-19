#include <iostream>
#include <vector>
using namespace std;

void backtracking(string str, int i, int n, vector<string>&res) {
  if(i < 0) return;
  
  if(str.length() == 2 * n) {
    if(i == 0) res.push_back(str);
    return;
  }
  backtracking(str + ")", i - 1, n, res);
  backtracking(str + "(", i + 1, n, res);
}
vector<string> generateParenthesis(int n) {
  vector<string> res;
  backtracking("", 0, n, res);
  return res;
}
int main() {
  generateParenthesis(3);
}
