#include"move.h"

int main()
{
    createMap();
    initsnack();
    srand((unsigned)time(NULL));
    createfood();
    key();
    

    gotoxy(60,26);
    //system("pause");
    getch();
    return 0;
}
