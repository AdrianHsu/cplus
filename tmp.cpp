#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>
#include <queue>
using namespace std;
typedef long long ll;
 
struct AC_Automata {
    #define Nn 102
    #define M 4
    int ch[Nn][M], val[Nn], f[Nn], last[Nn], sz;
    void clear() { sz = 1; memset(ch[0], 0, sizeof(ch[0])); }
    int idx(char c) {
        if (c == 'A') return 0;
        if (c == 'C') return 1;
        if (c == 'T') return 2;
        return 3;
    }
 
    void insert(char s[], int v) {
        int u = 0;
        for (int i=0; s[i]; i++) {
            int c = idx(s[i]);
            if (!ch[u][c]) {
                memset(ch[sz], 0, sizeof(ch[sz]));
                val[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        val[u] = 1;  ///標記當前節點是病毒串
    }
    void build() {
        queue<int> q;
        f[0] = 0;
        for (int c=0; c<M; c++) {
            int u = ch[0][c];
            if (u) { f[u] = last[u] = 0; q.push(u); }
        }
        while (!q.empty()) {
            int r = q.front(); q.pop();
            for (int c=0; c<M; c++) {
                int u = ch[r][c];
                if (!u) {
                    ch[r][c] = ch[f[r]][c];
                    val[r] = val[r] || val[f[r]];  ///如果失配邊指向的結點是病毒，那麼當前串的後綴也是病毒串
                    continue;
                }
                q.push(u);
                f[u] = ch[f[r]][c];
                last[u] = val[f[u]] ? f[u] : last[f[u]];
            }
        }
    }
} ac;
#define Mod 100000ll
#define N 200
ll a[N][N];
int n;
//c = a*b
void Multi(ll a[][N], ll b[][N], ll c[][N]) {
    for (int i=0; i<n; i++)
        for (int j=0; j<n; j++) {
            c[i][j] = 0;
            for (int k=0; k<n; k++)
                c[i][j] = (c[i][j] + a[i][k]*b[k][j]) % Mod;
        }
}
//d = s
void copy(ll d[][N], ll s[][N]) {
    for (int i=0; i<n; i++) for (int j=0; j<n; j++)
        d[i][j] = s[i][j];
}
//a = a^b % Mod
void PowerMod(ll a[][N], ll b) {
    ll t[N][N], ret[N][N];
    for (int i=0; i<n; i++) ret[i][i] = 1;
    while (b) {
        if (b & 1) { Multi(ret, a, t); copy(ret, t); }
        Multi(a, a, t); copy(a, t);
        b >>= 1;
    }
    copy(a, ret);
}
void init() {
    n = ac.sz;
    int u;
    memset(a, 0, sizeof(a));
    for (int i=0; i<n; i++) if (!ac.val[i]) {
        for (int j=0; j<4; j++) {
            u = ac.ch[i][j];
            if (!ac.val[u]) a[i][u]++;
        }
    }
}
int main() {
    char s[12];
    int m;
    ll b;
    while (scanf("%d %lld", &m, &b) == 2) {
        ac.clear();
        for (int i=1; i<=m; i++) {
            scanf(" %s", s); ac.insert(s, i);
        }
        ac.build();
        init();
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
              cout << a[i][j] << " ";
            }
            cout << endl;
          }
        PowerMod(a, b);
 
        ll sum = 0;
        for (int i=0; i<n; i++) sum = (sum + a[0][i]) % Mod;
        cout << sum << endl;
    }
 
    return 0;
}
