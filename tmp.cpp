#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <algorithm>
#include <stack>
#include <cctype>
#include <cmath>
#include <vector>
#include <sstream>
#include <bitset>
#include <deque>
#include <iomanip>
using namespace std;
#define pr(x) cout << #x << " = " << x << endl;
#define bug cout << "bugbug" << endl;
#define ppr(x, y) printf("(%d, %d)\n", x, y);
#define MST(a,b) memset(a,b,sizeof(a))
#define CLR(a) MST(a,0)
#define SQR(a) ((a)*(a))
#define PCUT puts("\n---------------")

typedef long long ll;
typedef double DBL;
typedef pair<int, int> P;
typedef unsigned int uint;
const int MOD = 1e9 + 7;
const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int maxn = 4e5 + 4;
const int maxm = 1e3 + 4;
const double pi = acos(-1.0);

int a[maxn], b[maxn];
vector<int> v;
int Getid(int num){
    return lower_bound(v.begin(), v.end(), num) - v.begin(); 
}
struct SuffixArray{
    int n, t[maxn << 1], t2[maxn << 1], c[maxn], sa[maxn], Rank[maxn], Height[maxn];
    int s[maxn];
    void build_sa(int m){
        memset(t, 0, sizeof t);
        memset(t2, 0, sizeof t2);
        int i, *x = t, *y = t2;
        for (i = 0; i < m; ++i) c[i] = 0;
        for (i = 0; i < n; ++i) c[x[i] = s[i]]++;
        for (i = 1; i < m; ++i) c[i] += c[i-1];
        for (i = n-1; i >= 0; --i) sa[--c[x[i]]] = i;
        for (int k = 1; k < n; k *= 2){
            int p = 0;
            for (i = n - k; i < n; ++i) y[p++] = i;
            for (i = 0; i < n; ++i)
                if (sa[i] >= k) y[p++] = sa[i] - k;
            for (i = 0; i < m; ++i) c[i] = 0;
            for (i = 0; i < n; ++i) c[x[y[i]]]++;
            for (i = 1; i < m; ++i) c[i] += c[i-1];
            for (i = n-1; i >= 0; --i) sa[--c[x[y[i]]]] = y[i];
            swap(x, y);
            p = 1; x[sa[0]] = 0;
            for (i = 1; i < n; ++i)
                x[sa[i]] = y[sa[i]] == y[sa[i-1]] && y[sa[i-1] + k] == y[sa[i] + k] ? p-1 : p++;
            if (p >= n) break;
            m = p; 
        }
        return;
    }
    void RankAndHeight(){
        for (int i = 0; i < n; ++i) Rank[sa[i]] = i;
        int k = 0;
        Height[sa[0]] = 0;
        for (int i = 1; i < n; ++i){
            if (k) k--;
            if (Rank[i] == 0) continue;
            int *p = s + i, *q = s + sa[Rank[i]-1];
            while(p[k] == q[k]) k++;
            Height[i] = k;
        }
        return;
    }
}SA; 

int main(){
//必須編譯過才能交
    int ik, i, j, k, kase;
    int n;
    scanf("%d", &n);
    for (i = 0; i < n; ++i) scanf("%d", a+i), v.push_back(a[i]);
    sort(v.begin(), v.end());
    unique(v.begin(), v.end());
    for (i = 0; i < n; ++i) a[i] = Getid(a[i]);
    reverse(a, a+n-2);
    memcpy(SA.s, a, sizeof a);
    SA.n = n - 2;
    SA.build_sa(n);
    reverse(a, a+n-2);
    // 0 1 2 3 4 5 6   -> 6 5 4 3 2 1 0  sa[0] 對應的是 n-2 n = 9 n - 3 - sa[0]
    int Cut = n - 3 - SA.sa[0];
    reverse(a, a+Cut+1);
    
    
    memcpy(b, a, n*4);
    reverse(a+Cut+1, a+n-1);
    memcpy(SA.s, a+Cut+1, (n-2-Cut)*4);
    memcpy(a, b, n*4);
    reverse(a+Cut+1, a+n);
    memcpy(SA.s+n-2-Cut, a+Cut+1, n-Cut-1);
    SA.n = n - 2 - Cut + n - Cut - 1;
    SA.build_sa(n);
    int Cut2;
    for (i = 0; i < SA.n; ++i)
        if (SA.sa[i] < n - 2 - Cut){
            Cut2 = n - 3 - Cut - SA.sa[i] + Cut + 1 ;
            break;
        }
    memcpy(a, b, n*4);
    reverse(a+Cut+1, a+Cut2+1);
    reverse(a+Cut2+1, a+n); 
    
    
    
    
    for (i = 0; i < n; ++i) printf("%d\n", v[a[i]]);
    return 0;
}