#include "print.h"
#define U 1 //�����������ҵ��ƶ�
#define D 2
#define L 3
#define R 4

int score = 0;  //�÷�
int status = R; //���ƶ��ķ��򣬳�ʼΪ��

void isfood()
{
    /* �ж����Ƿ�Ե�ʳ�� */
    snack *tail = head;
    if (head->x == food->x && head->y == food->y) //��ͷ��ʳ�������غϼ��Ե�ʳ��
    {
        print_snack(head); //��ӡ����
        free(food);        //�ͷ��ڴ�
        score += 1;
        gotoxy(60, 1);
        color(2);
        printf("�÷֣�%d", score); //��ӡ�÷�+1
        createfood();              //���´���ʳ��
        gotoxy(58, 26);            //�������
    }
    else
    {
        while (tail->next->next != NULL)
        {
            tail = tail->next;
        }
        gotoxy(tail->next->x, tail->next->y);
        color(3);
        printf("��");       //����ʳ��Ļ�����β�����ϵ�ͼ
        free(tail->next);  //�ͷ���β
        tail->next = NULL; //��һ�ڳ�Ϊ��β
        print_snack(head); //���´�ӡ����
        gotoxy(58, 26);
    }
}

int kill()
{
    /* �ж��Ƿ����� */
    int flag = 0;
    snack *s;
    s = head->next;
    if (head->x == 0 || head->x == 56 || head->y == 0 || head->y == 26) //ײǽ�ж�
    {
        flag = 1;
    }
    while (s->next != NULL)
    {
        if (head->x == s->x && head->y == s->y) //ײ���Լ������ж�
        {
            flag = 1;
        }
        s = s->next;
    }
    return flag;
}

void snack_move()
{
    /* �ߵ��ƶ� */
    snack *next_head; //��ͷ����һ��λ��
    next_head = (snack *)malloc(sizeof(snack));
    if (status == U) //�����ƶ�
    {
        next_head->x = head->x;
        next_head->y = head->y - 1;
        next_head->next = head;
        head = next_head;
        isfood();
    }
    if (status == D) //�����ƶ�
    {
        next_head->x = head->x;
        next_head->y = head->y + 1;
        next_head->next = head;
        head = next_head;
        isfood();
    }
    if (status == L) //�����ƶ�
    {
        next_head->x = head->x - 2;
        next_head->y = head->y;
        next_head->next = head;
        head = next_head;
        isfood();
    }
    if (status == R) //�����ƶ�
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
    /* �жϼ��̰��� */
    status = R;          //��ʼ�����ƶ�
    int sleeptime = 200; //���ʱ��
    gotoxy(60, 1);
    color(2);
    printf("�÷֣�%d", score); //��ӡ��ʼ��
    while (1)                  //��ȡ����ָ��
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
        if (kill()) //ʧ������ѭ��
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