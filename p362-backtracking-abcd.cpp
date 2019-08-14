#include <iostream>
#include <string>
using namespace std;

string str;
string Ans; // 過程中保存答案用
bool choosed[100] = {0};  // choosed[i]==1表示編號i已經出現過

int N;

void backtracking()    // N表示有N個字
{
    if (Ans.size() == N) {         // 終止條件檢查
        cout << Ans << endl;
        return;
    }
    for (int i = 0; i < N; ++i) {
        if (choosed[i] == 0){      // 如果這個編號還沒出現過(可行性檢查)
            Ans.push_back(str[i]); // 則將它放入Ans
            choosed[i] = 1;        // 並且讓choosed[i]變成1,避免下個遞迴選到

            backtracking();       // 進入下一層遞迴

            Ans.pop_back();        // 將編號i這個字從Ans移除
            choosed[i] = 0;        // 並標示成未選過
        }
    }
}

int main()
{
    str = "ABCD";
    N = str.size();
    backtracking();
}
