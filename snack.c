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
        printf("����0������Ϸ��Ϸ������1���¿�ʼ��");
        scanf("%d", &ctrl);
        system("cls");
    }
    return 0;
}
