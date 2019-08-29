#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>

#define MAX_N 200010

using namespace std;
int N;

struct Suffix {
  int index;
  int rank[3];
};

int cmp(struct Suffix a, struct Suffix b) {
  if(a.rank[0] == b.rank[0])
    return a.rank[1] < b.rank[1];
  
  return a.rank[0] < b.rank[0];
}
int* manberMyers(int* A, int n) {
  
  struct Suffix s[n];
  for(int i = 0; i < n; i++) {
    s[i].index = i;
    s[i].rank[0] = A[i];
    if(i == n - 1) s[i].rank[1] = -1;
    else s[i].rank[1] = A[i + 1];
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


int main() {
  scanf("%d", &N);
  vector<int> ans;

  int *arr = new int[MAX_N];
  for(int i = 0; i < N; i++)
    cin >> arr[i];
  reverse(arr, arr + N);
  int *sa = manberMyers(arr, N);
  for(int i = sa[0]; i < N; i++)
    ans.push_back(arr[i]);
  //cout << sa[0] << endl; 
  N = sa[0];
  int *doubleArr = new int[2 * MAX_N];
  for(int i = 0; i < 2 * N; i++) {
    doubleArr[i] = arr[i % N];
  }
  sa = manberMyers(doubleArr, 2 * N);
  int k;
  for(k = 0; k < 2 * N; k++) {
    if(sa[k] > 0 && sa[k] < N) {
      break;
    }
  }
  for(int i = sa[k]; i < N; i++)
    ans.push_back(doubleArr[i]);
  for(int i = 0; i < sa[k]; i++)
    ans.push_back(doubleArr[i]);

  for(int i = 0; i < ans.size(); i++)
    cout << ans[i] << endl; 
}
