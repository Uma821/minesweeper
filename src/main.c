//マインスイーパー2.2.4
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int neta(int);
void op(void);
void opensel(int ,int);
int map[9999][9999][4], wide, high;
int main(void){
    int x, y, ranx, rany, count = 0, xs, ys, bomb, bombs, n, fin = 0;
    wide = high = bombs = -1;

    do {
        printf("盤面の高さを入力＝＞　");
        fflush(stdout);
        scanf("%d", &high);
        while(getchar() != '\n');
    }while(high < 0 || high > 9999);
    do {
        printf("盤面の幅を入力＝＞　");
        fflush(stdout);
        scanf("%d", &wide);
        while(getchar() != '\n');
    }while(wide < 0 || wide > 9999);

    //配列初期化
     for(y = 0; y <= high + 1; y++) {
        for(x = 0; x <= wide + 1; x++)
            map[x][y][0] = map[x][y][1] = map[x][y][3] = -1;
    }

    do{
        printf("爆弾の数(%d個以内)を入力＝＞　",high * wide);
        fflush(stdout);
        scanf("%d", &bombs);
        while(getchar() != '\n');
    }while(bombs > high*wide || bombs < 0);

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

    //neta(-1);puts("");

    //ゲーム開始
    while (1) {
        //現在の結果を画面に表示
        n = neta(fin);

        if(bombs == n){
            fin = 1;
            break;
        }

         //プレーヤーが場所を入力
        do {
            xs = ys = -1;
            count++;
            printf("場所を入力してください (x y) [%d 回目]:", count);
            fflush(stdout);
            scanf("%d %d",&xs ,&ys);
            while(getchar() != '\n');
        }while(xs < 0 || xs > wide || ys < 0 || ys > high);

        if(xs == 0 && ys == 0)
            op();

         //爆弾を引いた
        if (map[xs][ys][0] == -2){
            fin = -1;
            break;
        }

        opensel(xs, ys);
    }
     //ゲーム終了
    if(fin == -1){
        printf("爆弾 !\n");
        neta(fin);
    }

    if(fin == 1){
        puts("congratulation!");
        fflush(stdout);
    }
    return 0;
}

void op(void){
    int x, y, a;
    do {
        x = y = 0;
        printf("Flagの場所を入力してください (x y) :");
        fflush(stdout);
        scanf("%d %d",&x ,&y);
        while(getchar() != '\n');
    }while(x < 1 || x > wide || y < 1 || y > high);
    do {
        printf("0？1？　");
        fflush(stdout);
        scanf("%d",&a);
        while(getchar() != '\n');
    }while(a <  0 || a > 1);
    if(a == 1)
        map[x][y][3] = 0;
    else
        map[x][y][3] = 1;
}

int neta(int s){
    int n = 0, x, y;
    printf("  ");
    for(x = 1; x <= wide; x++)
        printf(" %d",x % 10);
    printf("\n +");
    for(x = 1; x <= wide; x++)
        printf("--");
    puts("-+");
    for (y = 1; y <= high; y++) {
        printf("%d| ", y % 10);

        for (x = 1; x <= wide; x++) {
        	if(s == -1){
        		if(map[x][y][0] == -2)
        		    printf("B ");
        		else
        		    printf("%d ",map[x][y][2]);
            } else {
                if (map[x][y][1] == 1) {
                    if(map[x][y][2] == 1)
                        printf("\033[038;2;100;100;255m");
                    else if(map[x][y][2] == 2)
                        printf("\033[038;2;100;255;100m");
                    else if(map[x][y][2] == 3)
                        printf("\033[038;2;255;100;100m");
                    else if(map[x][y][2] == 4)
                        printf("\033[038;2;255;100;255m");
                    else if(map[x][y][2] == 5)
                        printf("\033[038;2;165;42;42m");
                    else if(map[x][y][2] == 6)
                        printf("\033[038;2;0;206;100m");
                    else if(map[x][y][2] == 7)
                        printf("\033[038;2;10;10;10m");
                    else if(map[x][y][2] == 8)
                        printf("\033[038;2;127;127;127m");
                    printf("%d \033[m",map[x][y][2]);
                } else if (map[x][y][3] != 0) {
                    printf("  ");
                    n++;
                } else if (map[x][y][3] == 0){
                    printf("\033[31mF \033[m");
                    n++;
                }
            }
        }
        puts("|");
    }

    printf(" +");
    for(x = 1; x <= wide; x++){
        printf("--");
    }
    puts("-+");
    fflush(stdout);
    return n;
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