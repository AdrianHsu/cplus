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
     // scanf("%c", &room[i][j]); // weird...

   }
}
```



**原則：**

1. **遇到 char, string 要讀入，就用 cin**。因為 scanf 吃 char 要小心不要吃到換行符號，很麻煩
2. **遇到 int 就用 scanf**
3. **全部都用 printf**

