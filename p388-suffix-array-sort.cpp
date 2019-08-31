#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

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
int* kasai(string S, int* sa, int n) {
  int* lcp = new int [n];
  int inv_sa[n];
  for(int i = 0; i < n; i++)
    inv_sa[ sa[i] ] = i;
  for(int i = 0; i < n; i++)
    cout << i << ", " << inv_sa[i] << endl;

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
  return lcp;
}


int main() {
  string txt = "adacadb$bdacada";
  //  string txt = "abracadabra";
  int n = txt.length();
  int *sa = manberMyers(txt, n);
  for(int i = 0; i < n; i++)
    cout << i << ", " << sa[i] << endl;
  
  int *lcp = kasai(txt, sa, n);
  for(int i = 0; i < n; i++)
    cout << i << ", " << lcp[i] << endl;

}
