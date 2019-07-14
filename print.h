#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

typedef struct snack
{
    /* snack����ṹ�� */
    int x;              //x����
    int y;              //y����
    struct snack *next; //ָ����һ��snack�ṹ
} snack;
snack *head; //ȫ����ͷָ��
snack *food; //ȫ��ʳ��ָ��

void gotoxy(int x, int y)
{
    /* ��궨λ */
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_ERROR_HANDLE), c);
}

int color(int c)
{
    /* �趨��ɫ */
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
    return 0;
}

void createMap()
{
    /* ������ͼ */
    int i, j;
    for (i = 0; i < 58; i += 2) //��ͼ���±߽�
    {
        color(5);
        gotoxy(i, 0);
        printf("��");
        gotoxy(i, 26);
        printf("��");
    }
    for (i = 1; i < 26; i++) //��ͼ���ұ߽�
    {
        gotoxy(0, i);
        printf("��");
        gotoxy(56, i);
        printf("��");
    }
    for (i = 2; i < 56; i += 2) //��ͼ�ڲ�
    {
        for (j = 1; j < 26; j++)
        {
            color(3);
            gotoxy(i, j);
            printf("��");
        }
    }
}

void print_snack(snack *ss) //������ͷָ��
{
    /* ��ӡ������ */
    while (ss != NULL) //��������
    {
        gotoxy(ss->x, ss->y);
        color(14);
        printf("��");
        ss = ss->next;
    }
}

void initsnack()
{
    /* ��ʼ���� */
    snack *tail;
    int i;
    tail = (snack *)malloc(sizeof(snack)); //�����ڴ�
    tail->x = 20;                          //������
    tail->y = 15;
    tail->next = NULL;
    for (i = 1; i < 4; i++) //ͷ�巨�ӳ�����
    {
        head = (snack *)malloc(sizeof(snack));
        head->next = tail;
        head->x = 20 + 2 * i;
        head->y = 15;
        tail = head;
    }
    print_snack(tail); //��ӡ����
}

void createfood()
{
    /* ���ɲ���ӡʳ�� */
    snack *tem_food, *ss;
    tem_food = (snack *)malloc(sizeof(snack));
    tem_food->x = rand() % 52 + 2; //ʳ������ȡ�����
    while ((tem_food->x % 2) != 0) //��֤xΪ����ʹʳ������ͼ����
    {
        tem_food->x = rand() % 52 + 2;
    }
    tem_food->y = rand() % 24 + 1;
    ss = head;
    while (ss != NULL) //�ж�ʳ���Ƿ��������غ�
    {
        if (ss->x == tem_food->x && ss->y == tem_food->y)
        {
            free(tem_food);
            createfood(); //�غϵĻ��ͷ��ڴ沢��������ʳ��
        }
        ss = ss->next;
    }
    gotoxy(tem_food->x, tem_food->y);
    food = tem_food;
    color(12);
    printf("��"); //��ӡʳ��
}