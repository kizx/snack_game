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
int status, sleeptime = 400;

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

snack *print_snack(snack *ss)
{
    snack *sstemp;
    while (ss->next != NULL)
    {
        gotoxy(ss->x, ss->y);
        color(14);
        printf("¡ô");
        sstemp = ss;
        ss = ss->next;
    }
    return sstemp;
}

void initsnack()
{
    snack *tail;
    int i;
    tail = (snack *)malloc(sizeof(snack));
    tail->x = 24;
    tail->y = 15;
    tail->next = NULL;
    for (i = 1; i <= 4; i++)
    {
        head = (snack *)malloc(sizeof(snack));
        head->next = tail;
        head->x = 24 + 2 * i;
        head->y = 15;
        tail = head;
    }
    print_snack(tail);
}

void createfood()
{
    snack *food_temp;    
    food_temp = (snack *)malloc(sizeof(snack));
    food_temp->x = rand() % 52 + 2;
    while ((food_temp->x % 2) != 0)
    {
        food_temp->x = rand() % 52 + 2;
    }
    food_temp->y = rand() % 24 + 1;
    q = head;
    while (q->next == NULL)
    {
        if (q->x == food_temp->x && q->y == food_temp->y)
        {
            free(food_temp);
            createfood();
        }
        q = q->next;
    }
    gotoxy(food_temp->x, food_temp->y);
    food = food_temp;
    color(12);
    printf("¡ï");
}
