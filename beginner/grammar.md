# Grammar

* scanf() : It returns total number of Inputs Scanned successfully, or EOF if input failure occurs before the first receiving argument was assigned.

```
char room[MAX_H][MAX_W];

for(int i = 0; i < H; i++) {
      cin >> room[i]; // WA
      scanf("%s", room[i]); // WA
      // 會爛掉不意外，room[i] 這根本不是 String
}
```

```
for(int i = 0; i < H; i++) {  
   for(int j = 0; j < W; j++) {
     cin >> room[i][j]; // AC
     //用scanf("%c",&room[i][j]);的話會WA,原因未知
	 //找到錯誤原因了，在前面加getchar()清理緩存區
     
     // scanf("%c", &room[i][j]); // weird..
   }
}
```

````
for(int i = 0; i < H; i++) {  
   getchar();
   for(int j = 0; j < W; j++) {
     // cin >> room[i][j]; // AC
     scanf("%c", &room[i][j]); // AC!!!
   }
}
````

***getchar*()取得使用者輸入的字元**

輸入時，用scanf（）讀入之前 一定getchar（）一下，前面**加 getchar()清理緩存區**，把Enter吃掉，否則有一行將讀不進來。

gets() 不安全，不要用!



**原則：**

1. **遇到 char, string 要讀入，就用 cin**。因為 scanf 吃 char 要小心不要吃到換行符號，很麻煩
2. **遇到 int 就用 scanf**
3. **全部都用 printf**



## Vector

```
vector<string> v1;         // 创建空容器，其对象类型为string类
vector<string> v2(10);     // 创建有10个具有初始值（即空串）的string类对象的容器
vector<string> v3(5, "hello"); // 创建有5个值为“hello”的string类对象的容器
```

