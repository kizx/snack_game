#include"print.h"
#define U 1
#define D 2
#define L 3
#define R 4


void snack_move()
{
    snack *next_head;
    next_head=(snack*)malloc(sizeof(snack));
    if(status==U)
    {
        next_head->x=head->x;
        next_head->y=head->y-1;
        next_head->next=head;
        if(next_head->x==food->x && next_head->y==food->y)
        {
            while(q!=NULL)
            {
                gotoxy(q->x,q->y);
                color(14);
                printf("◆");
                q=q->next;
            }
            createfood();
        }        
        else
        {
            print_snack(q);
            
        }
    }
    if(status==2)
    {
        next_head->x=head->x;
        next_head->y=head->y+1;
        next_head->next=head;
    }
}

void key()
{
    status=R;
    while(1)
    {
        if(GetAsyncKeyState(VK_UP)&& status!=D)
        {
            status=U;
        }
        else if(GetAsyncKeyState(VK_DOWN)&& status!=U)
        {
            status=D;
        }
        else if(GetAsyncKeyState(VK_LEFT)&& status!=R)
        {
            status=L;
        }
        else if(GetAsyncKeyState(VK_RIGHT)&& status!=L)
        {
            status=R;
        }
        Sleep(sleeptime);
        snack_move();
    }
}