#include <iostream>
#include <cstdio>
#include <cstring>

#define MAX_N 1000
using namespace std;

int data[MAX_N * 2 - 1];
int N, n;

void init() {
  n = 1;
  while(n < N)
    n *= 2;
  for(int i = 0; i < 2 * n - 1; i++)
    data[i] = 1e9;
}

void update(int k, int a) {
  k += n - 1;
  data[k] = a;

  while(k > 0) {
     k = (k - 1) >> 1;
     data[k] = min(data[2 * k + 1], data[2 * k + 2]);
  }
}

int query(int a, int b, int k, int l, int r) {
  if(r <= a || l >= b) return 1e9;
  
  if(a <= l && r <= b) 
    return data[k];
  else {
    int vl = query(a, b, 2 * k + 1, l, (l + r) >> 1);
    int vr = query(a, b, 2 * k + 2, (l + r) >> 1, r);
    return min(vl, vr);
  }
}

struct Suffix {
  int index;
  int rank[3];
};

int cmp(struct Suffix a, struct Suffix b) {
  if(a.rank[0] == b.rank[0])
    return a.rank[1] < b.rank[1];
  
  return a.rank[0] < b.rank[0];
}
int* manberMyers(string txt, int n) {
  
  struct Suffix s[n];
  for(int i = 0; i < n; i++) {
    s[i].index = i;
    s[i].rank[0] = txt[i] - 'a';
    if(i == n - 1) s[i].rank[1] = -1;
    else s[i].rank[1] = txt[i + 1] - 'a';
  }
  // After this, all suffixes are sorted according to first 2 characters.
  sort(s, s + n, cmp);

  int ind[n];// This array is needed to get the index in suffixes[] 
             // from original index.  This mapping is needed to get 
             // next suffix. 

  
  //Let us sort suffixes according to first 4 
  // characters, then first 8 and so on   
  for(int k = 4; k < 2 * n; k <<= 1) {
    int rank_new = 0;
    s[0].rank[2] = rank_new;
    ind[s[0].index] = 0;

    for(int i = 1; i < n; i++) {
      if(s[i].rank[0] == s[i - 1].rank[0] && 
         s[i].rank[1] == s[i - 1].rank[1])
        s[i].rank[2] = rank_new;
      else
        s[i].rank[2] = ++rank_new;

      ind[s[i].index] = i;
    }

    // copy the value
    for(int i = 0; i < n; i++)
      s[i].rank[0] = s[i].rank[2];

    int shift = (k / 2);
    for(int i = 0; i < n; i++) {
      int next = s[i].index + shift;
      if(next < n)
        s[i].rank[1] = s[ ind[next] ].rank[0];
      else
        s[i].rank[1] = -1;
    }

    sort(s, s + n, cmp);
  }

  int *sa = new int [n];
  for(int i = 0; i < n; i++)
    sa[i] = s[i].index;
  return sa;
}
int* kasai(string S, int* sa, int* inv_sa, int n) {
  int* lcp = new int [n];
  memset(lcp, 0, n * sizeof(int));

  int k = 0;
  for(int i = 0; i < n; i++) {
    if(inv_sa[i] == n - 1) {
      k = 0;
      continue;
    }
    int j =  sa[inv_sa[i] + 1];
    while(i + k < n && j + k < n && S[i + k] == S[j + k])
      k++;
    lcp[inv_sa[i]] = k;
    if(k > 0) k--;
  }

  // for(int i = 0; i < n; i++)
  //   cout << i << ", " << lcp[i] << endl;

  return lcp;
}


void solveLCP(string S) {
  string T = S;
  reverse(T.begin(), T.end());
  string txt = S;// + '$' + T;

  N = txt.length();

  int *sa = manberMyers(txt, N);
  int *inv_sa = new int[N];
  for(int i = 0; i < N; i++)
    inv_sa[ sa[i] ] = i;

  int *lcp = kasai(txt, sa, inv_sa, N);
  // int *lcp = new int[N + 1];
  // for(int i = 1; i <= N; i++)
  //   lcp[i] = lcp2[i - 1];
  // lcp[0] = 0;

  cout << "i  : ";
  for(int i = 0; i < N; i++)
    cout << i << " ";
  cout << endl;
  cout << "sa : ";
  for(int i = 0; i < N; i++)
    cout << sa[i] << " ";
  cout << endl;
  cout << "isa: ";
  for(int i = 0; i < N; i++)
    cout << inv_sa[i] << " ";
  cout << endl;
  cout << "lcp: ";
  for(int i = 0; i < N; i++)
    cout << lcp[i] << " ";
  cout << endl;

  init();
  for(int i = 0; i < N; i++)
    update(i, lcp[i]);

  // for(int i = 0; i < 2 * n - 1; i++)
  //   cout << data[i] << " ";
  // cout << endl;

  int ans = 0;
  for(int i = 0; i < N; i++) {
    int j = 2 * N - i;
    int lb = min(inv_sa[i], inv_sa[j]);
    int ub = max(inv_sa[i], inv_sa[j]);
    int l = query(lb, ub, 0, 0, n);
    if(l != 1e9) ans = max(ans, 2 * l - 1);
  }  

  for(int i = 1; i < N; i++) {
    int j = 2 * N - i + 1;
    int lb = min(inv_sa[i], inv_sa[j]);
    int ub = max(inv_sa[i], inv_sa[j]);
    int l = query(lb, ub, 0, 0, n);
    if(l != 1e9) ans = max(ans, 2 * l);
  }
  cout << ans << endl;
}


bool dp[MAX_N][MAX_N];
void solveDP(string str) {
  int n = str.length();
  // dp[i][j] will be false if substring str[i..j] 
  // is not palindrome. 
  memset(dp, 0, sizeof(dp));
  int s = 0;

  int res = 1;
  for(int i = 0; i < n; i++) {
    dp[i][i] = 1;
    if(i < n - 1 && str[i] == str[i + 1]){
      dp[i][i + 1] = 1;
      s = i;
      res = 2;
    }
  }
  // 不必把 odd, even 的狀況分開
  for(int len = 3; len <= n; len++) {
    for(int l = 0; l + len <= n; l++) { // <= n 是因為右界是 open bound
      int r = l + len - 1;
      // 照理說 (長度 - 2) 的 subproblem 已經有解，所以可用dp[l + 1][r - 1] 
      if(dp[l + 1][r - 1]) {
        if(str[l] == str[r]) {
          dp[l][r] = 1;
          res = max(res, len);
          s = l;
        }
      }
    }
  }
  cout << "len: " << res << endl;
  cout << str.substr(s, res) << endl;
}

int main() {
  string str = "abracadabra";
  // string str = "forgeeksskeegfor";
  // string str = "mississippi";
  // solveDP(str);
  solveLCP(str);
}
