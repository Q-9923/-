#define _CRT_SECURE_NO_WARNINGS
#include<windows.h>
#include<stdlib.h>
#include"guanli.h"
#include<stdio.h>
int main()
{
    //loginin();
    char c;
    // ����ͷ���
    Node* head = (Node*)malloc(sizeof(Node));
    if (head == NULL)
    {
        printf("ͷ��㴴��ʧ��");
        return 1;
    }
    head->next = NULL;

    loadStudent(head);
    while (1)
    {
        menu();
        c = _getch();
        switch (c)
        {
        case '1':
            // ��½����ܼ���
            break;
        case '2': // ¼��
            inputStudent(head);
            break;
        case '3': // ��ȡ����
            loadStudent(head);
            break;
        case '4': // 4.�޸��ѱ���ѧ��������Ϣ
            modifyStudent(head);
            break;
        case '5': // ɾ��
            deleteStudent(head);
            break;
        case '6': // ��Ϣ��ѯ
            findStudent(head);
            break;
        case '7': // ����ͳ��
            countStudent(head);
            break;
        case '8': // ����������
            sortStudent(head);
            break;
        case '9': // ��ӡ����
            printStudent(head);
            break;
        case '0':
            system("cls");
            printf("\n��ӭ�´�����\n");
            exit(0);
            break;
        default:
            system("cls");
            menu();
            printf("\n��������������\n");
            break;
        }
    }

    // �ͷ�ͷ���
    free(head);
    return 0;
}

// �˵�
void menu()
{
    printf("                                                   \n ");
    printf("              ��ӭ����ͼ��ݹ���ϵͳ1.0            \n ");
    printf("                                                   \n ");
    printf("               ��ѡ�����¹���                      \n ");
    printf("               1.������Ա��¼����                  \n ");
    printf("               2.¼��ѧ��������Ϣϵͳ              \n ");
    printf("               3.��ȡ����                          \n ");
    printf("               4.�޸��ѱ���ѧ��������Ϣ            \n ");
    printf("               5.����ɾ��                          \n ");
    printf("               6.ԤԼ��Ϣ��ѯ                      \n ");
    printf("               7.����ͳ��                          \n ");
    printf("               8.��������������                    \n ");
    printf("               9.��ӡ����                          \n ");
    printf("               0.�˳�                              \n ");
    printf("\n������ѡ��>>");
}

// ¼��ѧ����Ϣ
void inputStudent(Node* head)
{
    Node* cur = head;
    while (cur->next != NULL)
    {
        cur = cur->next;
    }
    Node* new = (Node*)malloc(sizeof(Node));
    if (new == NULL)
    {
        printf("�ڵ㴴��ʧ��");
        return;
    }

    printf("������ѧ�������֣�");
    scanf("%s", new->stu.name);
    while (getchar() != '\n');

    printf("������ѧ����ѧ�ţ�");
    scanf("%s", new->stu.number);
    while (getchar() != '\n');

    printf("������ѧ��Ҫ���������");
    scanf("%s", new->stu.book);
    while (getchar() != '\n');

    printf("������ѧ������ʱ�䣺��-��-�� ʱ:��:\n");
    scanf("%d%d%d%d%d", &new->stu.year, &new->stu.month, &new->stu.day, &new->stu.hour, &new->stu.minute);
    while (getchar() != '\n');

    printf("������ѧ������ʱ����\n");
    scanf("%d", &new->stu.duration);
    new->next = NULL;
    cur->next = new;
    saveStudent(head);
    system("cls");
    printf("--------¼��ɹ�-------\n");
}

// ��������
// ��Ϣд���ļ�
void saveStudent(Node* head)
{
    FILE* fp = fopen("student.txt", "w");
    if (fp == NULL)
    {
        perror("�ļ���ʧ��\n");
        return;
    }
    Node* cur = head->next;
    while (cur != NULL)
    {
        if (fwrite(&cur->stu, sizeof(St), 1, fp) != 1)
        {
            perror("д��ʧ��\n");
            fclose(fp);
            return;
        }
        cur = cur->next;
    }
    fclose(fp);
    printf("\n------------------����ɹ�---------------\n");
}

// ��ȡ����
void loadStudent(Node* head)
{
    FILE* fp = fopen("student.txt", "r");
    if (fp == NULL)
    {
        fp = fopen("student.txt", "w");
        printf("\n���ļ������ɹ�\n");
        fclose(fp);
        return;
    }
    // �������
    Node* cur = head->next;
    Node* next;
    while (cur != NULL)
    {
        next = cur->next;
        free(cur);
        cur = next;
    }
    head->next = NULL;

    cur = head;
    St temp;
    while (fread(&temp, sizeof(St), 1, fp) == 1)
    {
        Node* new = (Node*)malloc(sizeof(Node));
        if (new == NULL)
        {
            printf("���ӽڵ㴴��ʧ��");
            fclose(fp);
            return;
        }
        new->stu = temp;
        new->next = NULL;
        cur->next = new;
        cur = new;
    }
    fclose(fp);
    printf("-------------------��ȡ�ɹ�------------------\n");
}

// ��ӡ��Ϣ
void printStudent(Node* head)
{
    Node* cur = head;
    if (cur->next == NULL)
    {
        printf("\nû������\n");
        return;
    }
    cur = cur->next;
    while (cur != NULL)
    {
        printf("\n���֣�%s\n", cur->stu.name);
        printf("ѧ�ţ�%s\n", cur->stu.number);
        printf("������%s\n", cur->stu.book);
        printf("����ʱ��:%d-%d-%d %d:%d\n", cur->stu.year, cur->stu.month, cur->stu.day, cur->stu.hour, cur->stu.minute);
        printf("����ʱ��:%d\n", cur->stu.duration);
        cur = cur->next;
    }
    printf("\n");
}

// ͳ������
int count_book(Node* head, char* name)
{
    Node* cur = head->next;
    int count = 0;
    while (cur)
    {
        if (strcmp(cur->stu.book, name) == 0)
        {
            count++;
        }
        cur = cur->next;
    }
    return count;
}

void countStudent(Node* head) // ����ͳ��
{
    Node* cur = head;
    int count = 0;
    int all_day = 0;
    if (cur->next == NULL)
    {
        printf("��ǰ������\n");
        return;
    }
    cur = cur->next;
    while (cur != NULL)
    {
        int all_book = 0;
        all_book += count_book(head, cur->stu.book);
        printf("\n   ����: %s     ���ѽ�����: %d��\n", cur->stu.book, all_book);
        all_day += cur->stu.day;
        count++;
        cur = cur->next;
    }
    printf("\nѧ����Ϣ�ѱ���������%d\n", count);
    if (count > 0)
    {
        printf("����ѧ��ƽ������ʱ��%d\n", all_day / count);
    }
}

// ɾ��
void deleteStudent(Node* head)
{
    char del_number[20];
    printf("\n������Ҫɾ����ѧ��ѧ�ţ�");
    scanf("%s", del_number);
    Node* cur = head;
    if (cur->next == NULL)
    {
        printf("û������ �޷�ɾ��\n");
        return;
    }
    Node* del = cur->next;
    while (del)
    {
        if (strcmp(del->stu.number, del_number) == 0)
        {
            cur->next = del->next;
            free(del);
            break;
        }
        cur = cur->next;
        del = del->next;
    }
    if (del == NULL)
    {
        printf("δ�ҵ���ѧ��\n");
    }
    saveStudent(head);
    system("cls");
    printf("ɾ���ɹ�\n");
}

// ����
void findStudent(Node* head) // ����
{
    Node* cur = head;
    if (cur->next == NULL)
    {
        printf("û������\n");
        return;
    }
    char find_data[20];
    printf("��ѡ����ҷ�ʽ:\n");
    printf("1.��ѧ�Ų���   ");
    printf("2.�����ֲ���   ");
    printf("3.����������   \n");
    while (1)
    {
        char c = _getch();
        int flag = 0;
        cur = head->next; // ��������ָ��
        switch (c)
        {
        case '1':
            printf("\n������Ҫ��ѯ��ѧ��:>>");
            scanf("%s", find_data);
            while (cur)
            {
                if (strcmp(cur->stu.number, find_data) == 0)
                {
                    flag = 1;
                    printf("���֣�%s\t", cur->stu.name);
                    printf("������%s\t", cur->stu.book);
                    printf("����ʱ�䣺%d-%d-%d %d:%d\t", cur->stu.year, cur->stu.month, cur->stu.day, cur->stu.hour, cur->stu.minute);
                    printf("����������%d\t", cur->stu.duration);
                    break;
                }
                cur = cur->next;
            }
            if (flag == 0)
            {
                printf("δ�ҵ���ѧ��\n");
            }
            break;
        case '2':
            printf("������Ҫ��ѯ������:>>");
            scanf("%s", find_data);
            while (cur)
            {
                if (strcmp(cur->stu.name, find_data) == 0)
                {
                    flag = 1;
                    printf("ѧ�ţ�%s\t", cur->stu.number);
                    printf("������%s\t", cur->stu.book);
                    printf("����ʱ�䣺%d-%d-%d %d:%d\t", cur->stu.year, cur->stu.month, cur->stu.day, cur->stu.hour, cur->stu.minute);
                    printf("����������%d\t", cur->stu.duration);
                    break;
                }
                cur = cur->next;
            }
            if (flag == 0)
            {
                printf("δ�ҵ���ѧ��\n");
            }
            break;
        case '3':
            printf("������Ҫ��ѯ������:>>");
            scanf("%s", find_data);
            while (cur)
            {
                if (strcmp(cur->stu.book, find_data) == 0)
                {
                    flag = 1;
                    printf("���֣�%s\t", cur->stu.name);
                    printf("ѧ�ţ�%s\t", cur->stu.number);
                    printf("����ʱ�䣺%d-%d-%d %d:%d\t", cur->stu.year, cur->stu.month, cur->stu.day, cur->stu.hour, cur->stu.minute);
                    printf("����������%d\t", cur->stu.duration);
                    break;
                }
                cur = cur->next;
            }
            if (flag == 0)
            {
                printf("δ�ҵ���ѧ��\n");
            }
            break;
        case '0':
            exit(0);
        default:
            printf("\n����������\n");
            break;
        }
        break;
    }
}

// �޸�
void modifyStudent(Node* head) // �޸�
{
    Node* cur = head;
    if (cur->next == NULL)
    {
        printf("û������ �޷��޸�\n");
        return;
    }
    cur = cur->next; // ָ���һ���ڵ�
    char modify_data[20];
    printf("��ѡ���޸ķ�ʽ:\n");
    printf("1.��ѧ���޸�   ");
    printf("2.�������޸�   ");
    printf("3.�������޸�   \n");
    int flag = 0;
    while (1)
    {
        char c = _getch();
        cur = head->next; // ��������ָ��
        switch (c)
        {
        case '1':
            printf("�������޸Ķ���ѧ��:>>");
            scanf("%s", modify_data);
            while (cur)
            {
                if (strcmp(cur->stu.number, modify_data) == 0)
                {
                    flag = 1;
                    printf("�������µ����֣�");
                    scanf("%s", cur->stu.name);
                    while (getchar() != '\n');

                    printf("�������µ�ѧ�ţ�");
                    scanf("%s", cur->stu.number);
                    while (getchar() != '\n');

                    printf("�������µ�������");
                    scanf("%s", cur->stu.book);
                    while (getchar() != '\n');

                    printf("�������µĽ���ʱ�䣺");
                    scanf("%d%d%d%d%d", &cur->stu.year, &cur->stu.month, &cur->stu.day, &cur->stu.hour, &cur->stu.minute);
                    while (getchar() != '\n');

                    printf("�������µĽ���������");
                    scanf("%d", &cur->stu.duration);
                    while (getchar() != '\n');

                    break;
                }
                cur = cur->next;
            }
            if (flag == 0)
            {
                printf("δ�ҵ���ѧ��\n");
            }
            break;
        case '2':
            printf("�������޸Ķ�������:>>");
            scanf("%s", modify_data);
            while (getchar() != '\n');
            while (cur)
            {
                if (strcmp(cur->stu.name, modify_data) == 0)
                {
                    flag = 1;
                    printf("�������µ�ѧ�ţ�");
                    scanf("%s", cur->stu.number);
                    while (getchar() != '\n');

                    printf("�������µ�������");
                    scanf("%s", cur->stu.book);
                    while (getchar() != '\n');

                    printf("�������µĽ���ʱ�䣺");
                    scanf("%d%d%d%d%d", &cur->stu.year, &cur->stu.month, &cur->stu.day, &cur->stu.hour, &cur->stu.minute);
                    while (getchar() != '\n');

                    printf("�������µĽ���������");
                    scanf("%d", &cur->stu.duration);
                    while (getchar() != '\n');

                    break;
                }
                cur = cur->next;
            }
            if (flag == 0)
            {
                printf("δ�ҵ���ѧ��\n");
            }
            break;
        case '3':
            printf("�������޸Ķ�������:>>");
            scanf("%s", modify_data);
            while (getchar() != '\n');
            while (cur)
            {
                if (strcmp(cur->stu.book, modify_data) == 0)
                {
                    flag = 1;
                    printf("�������µ����֣�");
                    scanf("%s", cur->stu.name);
                    while (getchar() != '\n');

                    printf("�������µ�ѧ�ţ�");
                    scanf("%s", cur->stu.number);
                    while (getchar() != '\n');

                    printf("�������µĽ���ʱ�䣺");
                    scanf("%d%d%d%d%d", &cur->stu.year, &cur->stu.month, &cur->stu.day, &cur->stu.hour, &cur->stu.minute);
                    while (getchar() != '\n');

                    printf("�������µĽ���������");
                    scanf("%d", &cur->stu.duration);
                    while (getchar() != '\n');
                    break;
                }
                cur = cur->next;
            }
            if (flag == 0)
            {
                printf("δ�ҵ���ѧ��\n");
            }
            break;
        case '0':
            exit(0);
        default:
            printf("\n����������\n");
            break;
        }
        break;
    }
    saveStudent(head); // һ��Ҫ�ǵñ����޸ģ���������
    system("cls");
}

// ����   ���ڿ��Ը�Ϊ��ѡ����ʽ
void sortStudent(Node* head)
{
    if (head->next == NULL)
    {
        printf("û������ �޷�����\n");
        return;
    }
    if (head->next->next == NULL)
    {
        printf("ֻ��һ������ ��������\n");
        return;
    }
    Node* p, * q;
    St temp;
   char choice=0;
   printf("��ѡ������ʽ:1.����������  2.��ѧ������  3.��ʱ���Ⱥ�����\n");
   scanf("%c", &choice);
   switch (choice)
    {
    case'1':
    {
        for (p = head->next; p != NULL; p = p->next)
        {
            for (q = p->next; q != NULL; q = q->next)
            {
                if (strcmp(p->stu.name, q->stu.name) > 0)
                {
                    temp = p->stu;
                    p->stu = q->stu;
                    q->stu = temp;
                }
            }
        }
        
    }
    printStudent(head);
    break;
    case'2':
    {
        for (p = head->next; p != NULL; p = p->next)
        {
            for (q = p->next; q != NULL; q = q->next)
            {
                if (strcmp(p->stu.number, q->stu.number) > 0)
                {
                    temp = p->stu;
                    p->stu = q->stu;
                    q->stu = temp;
                }
            }
        }
        printStudent(head);
        break;
    }
    case'3':
    {
        for (p = head->next; p != NULL; p = p->next)
        {
            for (q = p->next; q != NULL; q = q->next)
            {
                if (p->stu.year>q->stu.year)
                {
                    temp = p->stu;
                    p->stu = q->stu;
                    q->stu = temp;
                }
                else if (p->stu.month>q->stu.month)
                {
                    temp = p->stu;
                    p->stu = q->stu;
                    q->stu = temp;
                }
                else if (p->stu.day>q->stu.day)
                {
                    temp = p->stu;
                    p->stu = q->stu;
                    q->stu = temp;
                }
            }
        }
        printStudent(head);
        break;
    }
    default:
    {
        printf("\n����������:\n");
        break;
    }
    }
    
}


//��¼����
void loginin()
{
    char user_name[20];
    char password[20];
    while (1)
    {
        printf("\n�������û���: \n");
        scanf("%s", user_name);
        while (getchar() != '\n');
        printf("\n����������: \n");
        scanf("%s", password);
        while (getchar() != '\n');
        if (strcmp(user_name, "11111") == 0 && strcmp(password, "11111") == 0)
        {
            printf("\n-----�û�����������ȷ���������----\n");
            break;
        }
    }
}