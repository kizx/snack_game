#include"print.h"
#define U 1
#define D 2
#define L 3
#define R 4

void isfood()
{
    snack *tail;
    if(head->x==food->x && head->y==food->y)
    {
        gotoxy(head->x,head->y);
        color(14);
        printf("¡ô");
        createfood();
        gotoxy(60,26);
    }        
    else
    {
        tail=print_snack(head);
        gotoxy(tail->x,tail->y);
        color(3);
        printf("¡ö");
        free(tail->next);
        tail->next=NULL;
        gotoxy(60,26);
    }
}


void snack_move()
{    
    snack *next_head;
    next_head=(snack*)malloc(sizeof(snack));
    if(status==U)
    {
        next_head->x=head->x;
        next_head->y=head->y-1;
        next_head->next=head;
        head=next_head;
        isfood();
    }
    if(status==D)
    {
        next_head->x=head->x;
        next_head->y=head->y+1;
        next_head->next=head;
        head=next_head;
        isfood();
    }
    if(status==L)
    {
        next_head->x=head->x-2;
        next_head->y=head->y;
        next_head->next=head;
        head=next_head;
        isfood();
    }
    if(status==R)
    {
        next_head->x=head->x+2;
        next_head->y=head->y;
        next_head->next=head;
        head=next_head;
        isfood();
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