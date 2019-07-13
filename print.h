#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

typedef struct snack
{
    /* snack */
    int x;
    int y;
    struct snack *next;
} snack;
snack *q;
snack *head;
snack *food;
int status,sleeptime=200;

void gotoxy(int x, int y)
{
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_ERROR_HANDLE), c);
}

int color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
    return 0;
}

void createMap()
{
    int i, j;
    for (i = 0; i < 58; i += 2)
    {
        color(5);
        gotoxy(i, 0);
        printf("¡õ");
        gotoxy(i, 26);
        printf("¡õ");
    }
    for (i = 1; i < 26; i++)
    {
        gotoxy(0, i);
        printf("¡õ");
        gotoxy(56, i);
        printf("¡õ");
    }
    for (i = 2; i < 56; i += 2)
    {
        for (j = 1; j < 26; j++)
        {
            color(3);
            gotoxy(i, j);
            printf("¡ö");
        }
    }
}

void print_snack(snack *qs)
{
    while(qs->next->next!=NULL)
    {
    gotoxy(qs->x,qs->y);
    color(14);
    printf("¡ô");
    qs=qs->next;
    }
}

void initsnack()
{
    snack *tail;
    int i;
    tail = (snack *)malloc(sizeof(snack));
    tail->x = 24;
    tail->y = 5;
    tail->next = NULL;
    for (i = 1; i <= 3; i++)
    {
        head = (snack *)malloc(sizeof(snack));
        head->next = tail;
        head->x = 24 + 2 * i;
        head->y = 5;
        tail = head;
    }
    print_snack(head);
}

void createfood()
{
    snack *food_1;
    srand((unsigned)time(NULL));
    food_1 = (snack *)malloc(sizeof(snack));
    while ((food_1->x % 2) != 0)
    {
        food_1->x = rand() % 52 + 2;
    }
    food_1->y = rand() % 24 + 1;
    q = head;
    while (q->next == NULL)
    {
        if (q->x == food_1->x && q->y == food_1->y)
        {
            free(food_1);
            createfood();
        }
        q = q->next;
    }
    gotoxy(food_1->x, food_1->y);
    food = food_1;
    color(12);
    printf("55");
}
