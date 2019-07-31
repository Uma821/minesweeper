//マインスイーパー1.1
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
void opensel(int ,int);
int map[9999][9999][3], wide, high;
int main(void){ 

    int x, y, ranx, rany, count = 0, xs, ys, bomb, bombs, n, fin=0;
    printf("盤面の高さを入力＝＞　");
    scanf("%d", &high);
    printf("盤面の幅を入力＝＞　");
    scanf("%d", &wide);


    //配列初期化
     for(y = 0; y <= high + 1; y++) { 
        for(x = 0; x <= wide + 1; x++) { 
            map[x][y][0] = map[x][y][1] = -1; 
        } 
    } 

    printf("爆弾の数(%d個以内)を入力＝＞　",high*wide);
    scanf("%d", &bombs);

    //爆弾セット
    srand( time(0) );
    for(x = 0; x < bombs;) { 
        ranx = rand() % wide + 1;
        rany = rand() % high + 1;
        if(map[ranx][rany][0] != -2) {
            map[ranx][rany][0] = -2; 
            x++;
        }
    }
    
    /* for (y = 1; y <= high; y++) { 
        for (x = 1; x <= wide; x++){
            printf("%d ",map[x][y][0]);
        }
        puts("");
    } puts("\n"); */


    //場所のまわりの爆弾を数える
    for (ys = 1; ys <= high; ys++){
        for(xs = 1; xs <= wide ; xs++){
            if(map[xs][ys][0] == -2){
                map[xs][ys][2] = -2; 
                continue;
            }
            bomb = 0; 

            if (map[xs - 1][ys - 1][0] == -2) 
                bomb ++; 
            if (map[xs - 1][ys][0] == -2) 
                bomb ++; 
            if (map[xs - 1][ys + 1][0] == -2) 
                bomb ++; 
            if (map[xs][ys - 1][0] == -2) 
                bomb ++; 
            if (map[xs][ys + 1][0] == -2) 
                bomb ++; 
            if (map[xs + 1][ys - 1][0] == -2) 
                bomb ++; 
            if (map[xs + 1][ys][0] == -2) 
                bomb ++; 
            if (map[xs + 1][ys + 1][0] == -2) 
                bomb ++; 

            map[xs][ys][2] = bomb; 
        }
    }

    /* for (y = 1; y <= high; y++) { 
        for (x = 1; x <= wide; x++){
            printf("%2d ",map[x][y][2]);
        }
        puts("");
    } puts("\n"); */


    //ゲーム開始 
    while (1) { 
        n = -1;
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
                if (map[x][y][1] == 1) { 
                    printf("%d ",map[x][y][2]); 
                } else { 
                    printf("  "); 
                    n++;
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
        if (map[xs][ys][0] == -2) 
            break; 
        
        opensel(xs, ys);

        if(bombs == n){
            fin = 1;
            break;
        }
    } 
     //ゲーム終了
    if(fin == 0){
        printf("爆弾 !\n"); 
    
        for (y = 1; y <= high; y++) { 
            for (x = 1; x <= wide; x++){
                printf("%2d ",map[x][y][0]);
            }
            puts("");
        } 
    }

    if(fin == 1){
        puts("congratulation!");
    } 
    return 0;
}

void opensel(int x,int y){
    //爆弾がないときその周囲を開ける
    if(x < 1 || x > wide || y < 1 || y > high)
        return;
    if(map[x][y][1] == 1)
        return;
    map[x][y][1] = 1;
    if (map[x][y][2] == 0){
        opensel(x - 1, y - 1);
        opensel(x - 1, y);
        opensel(x - 1, y + 1);
        opensel(x, y + 1);
        opensel(x, y - 1);
        opensel(x + 1, y - 1);
        opensel(x + 1, y);
        opensel(x + 1, y + 1);
    }
}