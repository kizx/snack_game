#include "print.h"
#define U 1 //定义上下左右的移动
#define D 2
#define L 3
#define R 4

int score = 0;  //得分
int status = R; //蛇移动的方向，初始为右

void isfood()
{
    /* 判断蛇是否吃到食物 */
    snack *tail = head;
    if (head->x == food->x && head->y == food->y) //蛇头与食物坐标重合即吃到食物
    {
        print_snack(head); //打印蛇体
        free(food);        //释放内存
        score += 1;
        gotoxy(60, 1);
        color(2);
        printf("得分：%d", score); //打印得分+1
        createfood();              //重新创建食物
        gotoxy(58, 26);            //光标移走
    }
    else
    {
        while (tail->next->next != NULL)
        {
            tail = tail->next;
        }
        gotoxy(tail->next->x, tail->next->y);
        color(3);
        printf("■");       //不是食物的话在蛇尾处补上地图
        free(tail->next);  //释放蛇尾
        tail->next = NULL; //上一节成为蛇尾
        print_snack(head); //重新打印蛇体
        gotoxy(58, 26);
    }
}

int kill()
{
    /* 判断是否死亡 */
    int flag = 0;
    snack *s;
    s = head->next;
    if (head->x == 0 || head->x == 56 || head->y == 0 || head->y == 26) //撞墙判断
    {
        flag = 1;
    }
    while (s->next != NULL)
    {
        if (head->x == s->x && head->y == s->y) //撞到自己身体判断
        {
            flag = 1;
        }
        s = s->next;
    }
    return flag;
}

void snack_move()
{
    /* 蛇的移动 */
    snack *next_head; //蛇头的下一个位置
    next_head = (snack *)malloc(sizeof(snack));
    if (status == U) //向上移动
    {
        next_head->x = head->x;
        next_head->y = head->y - 1;
        next_head->next = head;
        head = next_head;
        isfood();
    }
    if (status == D) //向下移动
    {
        next_head->x = head->x;
        next_head->y = head->y + 1;
        next_head->next = head;
        head = next_head;
        isfood();
    }
    if (status == L) //向左移动
    {
        next_head->x = head->x - 2;
        next_head->y = head->y;
        next_head->next = head;
        head = next_head;
        isfood();
    }
    if (status == R) //向右移动
    {
        next_head->x = head->x + 2;
        next_head->y = head->y;
        next_head->next = head;
        head = next_head;
        isfood();
    }
}

void key()
{
    /* 判断键盘按键 */
    status = R;          //初始向右移动
    int sleeptime = 200; //间隔时间
    gotoxy(60, 1);
    color(2);
    printf("得分：%d", score); //打印初始分
    while (1)                  //获取按键指令
    {
        if (GetAsyncKeyState(VK_UP) && status != D)
        {
            status = U;
        }
        else if (GetAsyncKeyState(VK_DOWN) && status != U)
        {
            status = D;
        }
        else if (GetAsyncKeyState(VK_LEFT) && status != R)
        {
            status = L;
        }
        else if (GetAsyncKeyState(VK_RIGHT) && status != L)
        {
            status = R;
        }
        if (kill()) //失败跳出循环
        {
            gotoxy(60, 5);
            color(12);
            printf("You are dead!");
            break;
        }
        Sleep(sleeptime);
        snack_move();
    }
}