#include "move.h"

int main()
{
    int ctrl = 1;
    while (ctrl)
    {
        createMap();
        initsnack();
        srand((unsigned)time(NULL));
        createfood();
        key();
        gotoxy(60, 26);
        color(3);
        printf("输入0结束游戏游戏，输入1重新开始：");
        scanf("%d", &ctrl);
        system("cls");
    }
    return 0;
}
