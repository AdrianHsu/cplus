# 精華總結 {{
"""
http://www.1point3acres.com/bbs/thread-436925-1-1.html
http://joshuablog.herokuapp.com/Leetcode-%E6%80%BB%E7%BB%93.html
1. 分解問題的角度: fix 某一維度，嘗試另一維度上的所有可能
   a. 可能是array的(i, j)pointers, b. 可能是矩形的長與寬, c. 可能是tree的每一個subtree, d. 可能是情景題的每一對pair...
2. 求所有解的, 暴力上backtracking吧
3. 如果問最短/最少的, 先想BFS、DP這對好基友
4. 如果環相關/重複訪問, DFS + visited state雄起
5. 如果問連通性, 靜態靠DFS/BFS, 動態靠Union-Find
6. 如果有依賴性, 想想Topologic order 和indegree
7. DAG的萬能套路 DFS+memo, 再到DP
8. 建圖的時候想想vertex, edges/neighbors, cost分別是什麼。如果出現cycle, 別忘了給vertex增加狀態
9. 樹相關, 永遠有backtracking 和 pure recursion兩條路
10. 遇到字符串/字典/char board相關的, Trie tree總是可以試試的
11. Range裡求最大/最小/sum等特徵值, Segment tree會是不錯的選擇
12. Matrix和Array通常都是1. Two Pointers, 2. Sliding Window(fixed & not fixed), 3. DP
13. DP題型往往是: a. 問你可不可以啊, 數量有多少啊, b. 兩個string上match來match去的, c. 1D/2D array 相關, d. 博弈遊戲
14. 破解DAG cycle想想哪個維度是具有單調性的: 常見的steps, directions, paths
15. Reversed idea非常重要, 可能會幫助你破題: 最長可能是某種最短的反面, 
    最多可能是某種最少的反面, obstacle的反面是reachable, subarray的反面是array中的剩下元素, left的反面是right。
16. Look up別忘了HashMap/HashSet, HashMap + DLL是常見hybrid數據結構。
17. 找規律試試那些旁門左道: 單調Stack/雙端Deque
18. 排序大法總是可以試試的
19. 時空複雜度: a. backtracking相關, 想想branching factor和height
                         b. DFS+memo/DP相關, 想想state數量, 以及每個state的cost
                         c. tree相關, 總是要考慮balanced 和 single linked list的 
                         d. array/矩陣相關, 先數數你有多少個for loops 
                         e. binary search application相關, 別忘了check function開銷
                         f. stack/queue/deque相關, 常說的吃進去一次又吐出來一次
                         g. Java的string是朵奇葩, string concatenation不是免費的
                         h. 沒人知道n是什麼, 先告訴別人m，n，k，V，E是什麼
20. 比較不同sol的trade offs: a. Time/Space complexity異同
                                             b. online/offline算法
                                             c. pre-computation cost
                                             d. 不同APIs的call frequency差異會導致不同的時間要求
                                             e. extension: 是否適用於generic parameters/stream input
                                             f. 線程安全/large scale
簡而言之 DP有六部曲 個人建議面試時寫在白板上 清楚明了 一步都不能少 基本上你寫出這些 implement起來也非常簡單了 
1. definition: dp 或者 dp[j] 表示什麼含義，比如largest subarray sum ending at arr, and must include arr. 
   注意語言描述, 包括還是不包括arr/matrix[j]
2. induction rule: dp 的 dependency 是怎麼樣的，依賴於dp[i-1] 還是 dp[i+1] 還是 dp[k] for all k < i or all k > i 等等，試著過幾個小例子推導一下
3. base case:  往往是dp[0]，二維往往是第一行， 第一列，也就是dp[0], dp[0][j]
4. result: 往往的dp[n], max(dp) 等等, 從definition 出發
5. filling order: 也就是你填dp表格的順序，從induction rule 的 dependency出發 判斷的從左到右 還是 從左上到右下
6. optimized: 分為時間和空間兩方面。時間的比較難，因為往往需要你重新define dp state 和 induction rule。
   空間比較簡單，可以根據induction rule看出來，比如斐波那契數列: dp = dp[i - 1] + dp[i - 2], 那麼dp 只依賴於前兩個元素，就不需要create 整個 dp array，兩個variable即可，空間可以從O(n)優化到O(1)。
最後, 多總題多總結多積累小tips，熟能生巧後dp其實是非常簡單，也非常有套路的，一些induction rule 的常見pattern 你一眼就能看出來了。
"""
# }}
