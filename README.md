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

