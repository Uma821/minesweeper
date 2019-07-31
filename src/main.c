//マインスイーパー0.5
//爆弾多い
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
int main(void){ 

    /* map の配列要素は、 
　　　　-2　: 爆弾が入っている。
　　　　-1　: 爆弾は入っていない。開けられてもいない。
        0  : 開けられた。この周りには爆弾が無い。
        1　: 開けられた。この周りには爆弾が 1 つある。
        2　: 開けられた。この周りには爆弾が 2 つある。
        このような感じ
    */

    int x, y, high, wide, ranx, rany, count = 0, xs, ys, bomb;
    printf("盤面の高さを入力＝＞　");
    scanf("%d", &high);
    printf("盤面の幅を入力＝＞　");
    scanf("%d", &wide);

    int map[wide+2][high+2]; 

    //配列初期化
    for(x = 0; x < high+2; x++) { 
        for(y = 0; y < wide+2; y++) { 
            map[x][y] = -1; 
        } 
    } 

    //爆弾セット
    srand( time(0) );
    for(x = 0; x < high; x++) { 
        for(y = 0; y < wide+2; y++) { 
            ranx = rand() % high + 1;
            rany = rand() % wide + 1;
            map[ranx][rany] = -2; 
        }
    } 

    
    //ゲーム開始 
    while (1) { 
         //現在の結果を画面に表示 
        printf("  ");
        for(x = 1; x <= wide; x++){
            printf(" %d",x % 10);
        }
        printf("\n +"); 
        for(x = 1; x <= wide; x++){
            printf("--");
        }
        puts("-+"); 
        for (y = 1; y <= high; y++) { 
            printf("%d| ", y % 10);

            for (x = 1; x <= wide; x++) { 
                if (map[x][y] >= 0) { 
                    printf("%d ",map[x][y]); 
                } else { 
                    printf("  "); 
                } 
            } 
            puts("|"); 
        } 
        
        printf(" +"); 
        for(x = 1; x <= wide; x++){
            printf("--");
        }
        puts("-+"); 

         //プレーヤーが場所を入力  
        count++; 
        printf("場所を入力してください (x y) [%d 回目]:", count); 
        scanf("%d %d",&xs ,&ys);

         //爆弾を引いた
        if (map[xs][ys] == -2) 
            break; 

         //プレーヤーが指定した場所のまわりの爆弾を数える  
        bomb = 0; 
        if (map[ys - 1][xs] == -2) 
            bomb ++; 
        if (map[ys + 1][xs] == -2) 
            bomb ++; 
        if (map[ys][xs - 1] == -2) 
            bomb ++; 
        if (map[ys][xs + 1] == -2) 
            bomb ++; 
        if (map[ys - 1][xs - 1] == -2) 
            bomb ++; 
        if (map[ys + 1][xs + 1] == -2) 
            bomb ++; 
        if (map[ys + 1][xs - 1] == -2) 
            bomb ++; 
        if (map[ys - 1][xs + 1] == -2) 
            bomb ++; 

        map[xs][ys] = bomb; 
    } 
     //ゲーム終了
    printf("爆弾 !\n"); 
    
    for (y = 1; y <= high; y++) { 
        for (x = 1; x <= wide; x++){
            printf("%d ",map[x][y]);
        }
        puts("");
    } 
}