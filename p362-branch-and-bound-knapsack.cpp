#include <cstdio>
#include <iostream>
#include <vector>
#include <utility>
#include <queue>

#define MAX_N 15
using namespace std;
typedef pair<int, double> Item;

bool cmp(Item a, Item b) 
{ 
    double r1 = ((double)a.first) / a.second;
    double r2 = ((double)b.first) / b.second; 
    return r1 > r2; 
} 

int N;
double W;
vector<Item> items;

struct Node {
  int level;
  int profit;
  int bound;
  double weight;
};

int bound(Node u) {
  if (u.weight >= W)
    return 0;

  int profit_bound = u.profit;
  int j = u.level + 1;
  double totweight = u.weight;
  
  while(j < N && totweight + items[j].second <= W) {

    totweight += items[j].second;
    profit_bound += items[j].first;
    j++;
  }

  if (j < N)
    profit_bound += (W - totweight) * items[j].first / items[j].second;
  return profit_bound;
}

void solve() {
  sort(items.begin(), items.end(), cmp);

  queue<Node> Q;
  Node u, v;

  // dummy node u
  u.level = -1; u.profit = 0; u.weight = 0;
  Q.push(u);

  int maxProfit = 0;
  while(!Q.empty()) {
    u = Q.front();
    Q.pop();
    
    if(u.level == N - 1) continue;      
    v.level = u.level + 1;
    // case 1
    v.weight = u.weight + items[v.level].second;
    v.profit = u.profit + items[v.level].first;

    if (v.weight <= W && v.profit > maxProfit) 
      maxProfit = v.profit; 
    
    v.bound = bound(v);
    if (v.bound > maxProfit) 
      Q.push(v);
    
    // case 2
    v.weight = u.weight; 
    v.profit = u.profit; 
    v.bound = bound(v); 
    if (v.bound > maxProfit) 
      Q.push(v);
   }
  cout << maxProfit << endl;
}

int main() {
  N = 5;
  W = 10.0;
  int c1 [] = {40, 50, 100, 95, 30};
  double w1[] = {2, 3.14, 1.98, 5, 3};

  for(int i = 0; i < N; i++) {
    items.push_back(Item(c1[i], w1[i])); 
  }
  
  solve();
  return 0;
}
