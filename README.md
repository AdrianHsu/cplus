# 邏輯腦

## 1-* Time Complexity

1. 抽籤 [p.22], O(N^2logN), 建一個 c + d 的所有可能的 array。然後 val - (c + d) 做二分搜
2. Ants [p.17], 彈性碰撞

## 2-1 Recursion（完全搜尋）

1. Fibonacci [p.27], with memory DP
2. 部分和 [p.31] , TC = O(2^N) 因為每個人都可以二擇一：選或不選。答案的那隻分支 return true，在他之前的分支 return false 了所以才輪得到它，在他後面的分支根本不會走到。（p.s. 可以剪枝）
3. Lake Counting [p.32], 將目前位置換成 '.'
4. 迷宮的最短路徑 [p.35], 用 dp 還沒走過的設為 INF，走過的不再走，找最短路
5. BFS 會從 state tree 之中，較近的 state 開始搜尋，因此可求出最短路線 / 最少步驟數。
6. DFS 會重複走同樣的路徑，因此通常找最短路徑時，我們會用 BFS 而不是 DFS。但 DFS 好處是比較不佔記憶體。
7. Next Permutation (數字) 把 array [1, 2, 3,...n] 這 n 個數字的所有排列都印出來。backtracking。

```c++
bool used[MAX_N]; // 也可以用傳進去的，類似 leetcode 作法
int perm[MAX_N]; // 也可以用傳進去的

void permu(int pos, int n) {
  if(pos == n) {
    // print out perm as results
    return;
  }
  for(int i = 0; i < n; i++) {
    if(used[i]) continue;
    used[i] = true;
    perm[pos] = i;
    permu(pos + 1, n);
    used[i] = false;
  }
}
```

8. 位元列舉（3-2 章節）

## 2-2 Greedy

1. 硬幣問題 [p.40], 從大的開始、能取多少就盡量取。並不會發生漏洞情形、因為都可以換錢。
2. 行程規劃 [p.43], 就 leetcode 的 Conference Room 簡單版。用 T 排序，結束的 t 越早，之後能挑的選擇越多。不用管兩者 s 誰先誰後，看 t 就好。
3. 字典順序最小 [p.44] 不能只考慮 front 還有 back 這兩人，還要考慮相同時、如果隨便拔一個、後面的可能順序會錯。所以先用字典順序比較 S 與 S'，然後每次刪完一個後就重新字典順序比較、然後取字典序列小的。也是貪心。
4. Saruman's Army [p.47] 貪心，從最左出發，找一個能包住 A[0] 但是離他最遠的點，然後選這個點。選好後，把 i+1 當成 A[0]，然後一樣找一個能包住此 A[0] 但是離他最遠的點，依此類推。
5. Fence Repair [p.48] 貪心，成本合計 = 各葉子節點他們的長度 * 他們所在的深度。貪心把最短的放最深，然後第二短的放他兄弟，合起來之後的人，再拿去跟其他人比，然後一樣找最短跟第二短的。
6. Huffman Encoding [p.51] 資料量 = sum of (出現頻率 * 節點深度)。例如：我 (5 times)，想要 (12 times) 這幾個縣頻率低的，就放在深的節點（長序列）也是貪心。可算壓縮率。

## 2-3 DP

1. 0/1 背包 [p.56], 其中 `dp[i][j]`  他的大小是 `dp[N + 1][W + 1]` 也就是說，我們 `dp[i][j]` 狀態轉移式，定義為 在考慮到目前第 i 個東西時，選擇出重量總和 <= j 的物品組合中所造出的價值總和最大值（1-indexed，當 i = 0 時代表一個東西都還沒考慮， i = N 則是考慮完所有的人） 
2. `dp[3[3] = max(dp[2][3], dp[2][3 - w[2]] + v[2])` 其中 `dp[2][3 - w[2]] + v[2] = dp[2][3 - 3] + v[2] = dp[2][0] + v[2] = 0 + 4 = 4` 他的意思是，當你有 i=1,2,3 這個東西可選擇時、然後你容量 =3 ，則你要馬是不選 3 這個人，結果 = `dp[2][3]` 。要馬是選了 3 之後， 1,2 去填剩下的空間（但這個 case 他剩下 0 空間就是了）

```c++
memset(dp, 0, sizeof(dp));
// p.s. dp[0][j] for every j，他的值必然都是 = 0
for(int i = 0; i < n; i++) {
  for(int j = 0; j <= W; j++) {
    if(j < w[i])
      dp[i + 1][j] = dp[i][j];
    else
      dp[i + 1][j] = max(dp[i][j], dp[i][j - w[i] + v[i]]);
  }
}
return dp[N][W];
```

3. LCS 最長共同子序列 [p.58]，令 `dp[i][j]` 等於在 $s_1s_2s_3...s_i$ 還有 $t_1t_2...t_j$ 這兩個字串中的 LCS。我們要求的是 `dp[N1][N2]` 也就是 $s_1s_2s_3...s_{N1}$ 還有 $t_1t_2....t_{N2}$ 的LCS (e.g., abce, abcce: $s_1s_2s_3s_4$ & $t_1t_2t_3t_4t_5$ 的 LCS = abce)

```c++
for(int i = 0; i < N1; i++) {
  for(int j = 0; j < N2; j++) {
    if(s[i] == t[j]) {
      dp[i + 1][j + 1] = dp[i][j] + 1;
    } else {
      dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
    }
  }
}
```

4. 完全背包 [p.60]。`dp[i + 1][j] = max(dp[i][j], dp[i + 1][j - w[i]] + v[i]);`
5. 0/1 背包，但 W 超大 [p.63]
6. 有個數限制的部分和 [p.64] 
7. LIS [p.66]
8. 分割數 [p.68]
9. 重複組合 [p.70]