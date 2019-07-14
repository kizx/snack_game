#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

typedef struct snack
{
    /* snack链表结构体 */
    int x;              //x坐标
    int y;              //y坐标
    struct snack *next; //指向下一个snack结构
} snack;
snack *head; //全局蛇头指针
snack *food; //全局食物指针

void gotoxy(int x, int y)
{
    /* 光标定位 */
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_ERROR_HANDLE), c);
}

int color(int c)
{
    /* 设定颜色 */
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
    return 0;
}

void createMap()
{
    /* 创建地图 */
    int i, j;
    for (i = 0; i < 58; i += 2) //地图上下边界
    {
        color(5);
        gotoxy(i, 0);
        printf("□");
        gotoxy(i, 26);
        printf("□");
    }
    for (i = 1; i < 26; i++) //地图左右边界
    {
        gotoxy(0, i);
        printf("□");
        gotoxy(56, i);
        printf("□");
    }
    for (i = 2; i < 56; i += 2) //地图内部
    {
        for (j = 1; j < 26; j++)
        {
            color(3);
            gotoxy(i, j);
            printf("■");
        }
    }
}

void print_snack(snack *ss) //传入蛇头指针
{
    /* 打印蛇身体 */
    while (ss != NULL) //遍历蛇体
    {
        gotoxy(ss->x, ss->y);
        color(14);
        printf("◆");
        ss = ss->next;
    }
}

void initsnack()
{
    /* 初始化蛇 */
    snack *tail;
    int i;
    tail = (snack *)malloc(sizeof(snack)); //分配内存
    tail->x = 20;                          //出生点
    tail->y = 15;
    tail->next = NULL;
    for (i = 1; i < 4; i++) //头插法加长蛇身
    {
        head = (snack *)malloc(sizeof(snack));
        head->next = tail;
        head->x = 20 + 2 * i;
        head->y = 15;
        tail = head;
    }
    print_snack(tail); //打印蛇体
}

void createfood()
{
    /* 生成并打印食物 */
    snack *tem_food, *ss;
    tem_food = (snack *)malloc(sizeof(snack));
    tem_food->x = rand() % 52 + 2; //食物坐标取随机数
    while ((tem_food->x % 2) != 0) //保证x为奇数使食物对齐地图网格
    {
        tem_food->x = rand() % 52 + 2;
    }
    tem_food->y = rand() % 24 + 1;
    ss = head;
    while (ss != NULL) //判断食物是否与蛇体重合
    {
        if (ss->x == tem_food->x && ss->y == tem_food->y)
        {
            free(tem_food);
            createfood(); //重合的话释放内存并重新生成食物
        }
        ss = ss->next;
    }
    gotoxy(tem_food->x, tem_food->y);
    food = tem_food;
    color(12);
    printf("★"); //打印食物
}