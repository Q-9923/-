#define _CRT_SECURE_NO_WARNINGS
#include<windows.h>
#include<stdlib.h>
#include"guanli.h"
#include<stdio.h>
int main()
{
    //loginin();
    char c;
    // 创建头结点
    Node* head = (Node*)malloc(sizeof(Node));
    if (head == NULL)
    {
        printf("头结点创建失败");
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
            // 登陆后才能继续
            break;
        case '2': // 录入
            inputStudent(head);
            break;
        case '3': // 读取数据
            loadStudent(head);
            break;
        case '4': // 4.修改已保存学生借书信息
            modifyStudent(head);
            break;
        case '5': // 删除
            deleteStudent(head);
            break;
        case '6': // 信息查询
            findStudent(head);
            break;
        case '7': // 数据统计
            countStudent(head);
            break;
        case '8': // 按升降排序
            sortStudent(head);
            break;
        case '9': // 打印报表
            printStudent(head);
            break;
        case '0':
            system("cls");
            printf("\n欢迎下次再来\n");
            exit(0);
            break;
        default:
            system("cls");
            menu();
            printf("\n请重新重新输入\n");
            break;
        }
    }

    // 释放头结点
    free(head);
    return 0;
}

// 菜单
void menu()
{
    printf("                                                   \n ");
    printf("              欢迎来到图书馆管理系统1.0            \n ");
    printf("                                                   \n ");
    printf("               请选择以下功能                      \n ");
    printf("               1.管理人员登录界面                  \n ");
    printf("               2.录入学生借书信息系统              \n ");
    printf("               3.读取数据                          \n ");
    printf("               4.修改已保存学生借书信息            \n ");
    printf("               5.数据删除                          \n ");
    printf("               6.预约信息查询                      \n ");
    printf("               7.数据统计                          \n ");
    printf("               8.对数据升降排序                    \n ");
    printf("               9.打印报表                          \n ");
    printf("               0.退出                              \n ");
    printf("\n请做出选择>>");
}

// 录入学生信息
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
        printf("节点创建失败");
        return;
    }

    printf("请输入学生的名字：");
    scanf("%s", new->stu.name);
    while (getchar() != '\n');

    printf("请输入学生的学号：");
    scanf("%s", new->stu.number);
    while (getchar() != '\n');

    printf("请输入学生要借的书名：");
    scanf("%s", new->stu.book);
    while (getchar() != '\n');

    printf("请输入学生借书时间：年-月-日 时:分:\n");
    scanf("%d%d%d%d%d", &new->stu.year, &new->stu.month, &new->stu.day, &new->stu.hour, &new->stu.minute);
    while (getchar() != '\n');

    printf("请输入学生借书时长：\n");
    scanf("%d", &new->stu.duration);
    new->next = NULL;
    cur->next = new;
    saveStudent(head);
    system("cls");
    printf("--------录入成功-------\n");
}

// 保存数据
// 信息写入文件
void saveStudent(Node* head)
{
    FILE* fp = fopen("student.txt", "w");
    if (fp == NULL)
    {
        perror("文件打开失败\n");
        return;
    }
    Node* cur = head->next;
    while (cur != NULL)
    {
        if (fwrite(&cur->stu, sizeof(St), 1, fp) != 1)
        {
            perror("写入失败\n");
            fclose(fp);
            return;
        }
        cur = cur->next;
    }
    fclose(fp);
    printf("\n------------------保存成功---------------\n");
}

// 读取数据
void loadStudent(Node* head)
{
    FILE* fp = fopen("student.txt", "r");
    if (fp == NULL)
    {
        fp = fopen("student.txt", "w");
        printf("\n新文件创建成功\n");
        fclose(fp);
        return;
    }
    // 清空链表
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
            printf("连接节点创建失败");
            fclose(fp);
            return;
        }
        new->stu = temp;
        new->next = NULL;
        cur->next = new;
        cur = new;
    }
    fclose(fp);
    printf("-------------------读取成功------------------\n");
}

// 打印信息
void printStudent(Node* head)
{
    Node* cur = head;
    if (cur->next == NULL)
    {
        printf("\n没有数据\n");
        return;
    }
    cur = cur->next;
    while (cur != NULL)
    {
        printf("\n名字：%s\n", cur->stu.name);
        printf("学号：%s\n", cur->stu.number);
        printf("书名：%s\n", cur->stu.book);
        printf("借书时间:%d-%d-%d %d:%d\n", cur->stu.year, cur->stu.month, cur->stu.day, cur->stu.hour, cur->stu.minute);
        printf("借书时长:%d\n", cur->stu.duration);
        cur = cur->next;
    }
    printf("\n");
}

// 统计数据
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

void countStudent(Node* head) // 数据统计
{
    Node* cur = head;
    int count = 0;
    int all_day = 0;
    if (cur->next == NULL)
    {
        printf("当前无数据\n");
        return;
    }
    cur = cur->next;
    while (cur != NULL)
    {
        int all_book = 0;
        all_book += count_book(head, cur->stu.book);
        printf("\n   书名: %s     该已借数量: %d本\n", cur->stu.book, all_book);
        all_day += cur->stu.day;
        count++;
        cur = cur->next;
    }
    printf("\n学生信息已保存总数：%d\n", count);
    if (count > 0)
    {
        printf("所有学生平均借书时长%d\n", all_day / count);
    }
}

// 删除
void deleteStudent(Node* head)
{
    char del_number[20];
    printf("\n请输入要删除的学生学号：");
    scanf("%s", del_number);
    Node* cur = head;
    if (cur->next == NULL)
    {
        printf("没有数据 无法删除\n");
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
        printf("未找到该学生\n");
    }
    saveStudent(head);
    system("cls");
    printf("删除成功\n");
}

// 查找
void findStudent(Node* head) // 查找
{
    Node* cur = head;
    if (cur->next == NULL)
    {
        printf("没有数据\n");
        return;
    }
    char find_data[20];
    printf("请选择查找方式:\n");
    printf("1.按学号查找   ");
    printf("2.按名字查找   ");
    printf("3.按书名查找   \n");
    while (1)
    {
        char c = _getch();
        int flag = 0;
        cur = head->next; // 重置链表指针
        switch (c)
        {
        case '1':
            printf("\n请输入要查询的学号:>>");
            scanf("%s", find_data);
            while (cur)
            {
                if (strcmp(cur->stu.number, find_data) == 0)
                {
                    flag = 1;
                    printf("名字：%s\t", cur->stu.name);
                    printf("书名：%s\t", cur->stu.book);
                    printf("借书时间：%d-%d-%d %d:%d\t", cur->stu.year, cur->stu.month, cur->stu.day, cur->stu.hour, cur->stu.minute);
                    printf("借书天数：%d\t", cur->stu.duration);
                    break;
                }
                cur = cur->next;
            }
            if (flag == 0)
            {
                printf("未找到该学生\n");
            }
            break;
        case '2':
            printf("请输入要查询的名字:>>");
            scanf("%s", find_data);
            while (cur)
            {
                if (strcmp(cur->stu.name, find_data) == 0)
                {
                    flag = 1;
                    printf("学号：%s\t", cur->stu.number);
                    printf("书名：%s\t", cur->stu.book);
                    printf("借书时间：%d-%d-%d %d:%d\t", cur->stu.year, cur->stu.month, cur->stu.day, cur->stu.hour, cur->stu.minute);
                    printf("借书天数：%d\t", cur->stu.duration);
                    break;
                }
                cur = cur->next;
            }
            if (flag == 0)
            {
                printf("未找到该学生\n");
            }
            break;
        case '3':
            printf("请输入要查询的书名:>>");
            scanf("%s", find_data);
            while (cur)
            {
                if (strcmp(cur->stu.book, find_data) == 0)
                {
                    flag = 1;
                    printf("名字：%s\t", cur->stu.name);
                    printf("学号：%s\t", cur->stu.number);
                    printf("借书时间：%d-%d-%d %d:%d\t", cur->stu.year, cur->stu.month, cur->stu.day, cur->stu.hour, cur->stu.minute);
                    printf("借书天数：%d\t", cur->stu.duration);
                    break;
                }
                cur = cur->next;
            }
            if (flag == 0)
            {
                printf("未找到该学生\n");
            }
            break;
        case '0':
            exit(0);
        default:
            printf("\n请重新输入\n");
            break;
        }
        break;
    }
}

// 修改
void modifyStudent(Node* head) // 修改
{
    Node* cur = head;
    if (cur->next == NULL)
    {
        printf("没有数据 无法修改\n");
        return;
    }
    cur = cur->next; // 指向第一个节点
    char modify_data[20];
    printf("请选择修改方式:\n");
    printf("1.按学号修改   ");
    printf("2.按名字修改   ");
    printf("3.按书名修改   \n");
    int flag = 0;
    while (1)
    {
        char c = _getch();
        cur = head->next; // 重置链表指针
        switch (c)
        {
        case '1':
            printf("请输入修改对象学号:>>");
            scanf("%s", modify_data);
            while (cur)
            {
                if (strcmp(cur->stu.number, modify_data) == 0)
                {
                    flag = 1;
                    printf("请输入新的名字：");
                    scanf("%s", cur->stu.name);
                    while (getchar() != '\n');

                    printf("请输入新的学号：");
                    scanf("%s", cur->stu.number);
                    while (getchar() != '\n');

                    printf("请输入新的书名：");
                    scanf("%s", cur->stu.book);
                    while (getchar() != '\n');

                    printf("请输入新的借书时间：");
                    scanf("%d%d%d%d%d", &cur->stu.year, &cur->stu.month, &cur->stu.day, &cur->stu.hour, &cur->stu.minute);
                    while (getchar() != '\n');

                    printf("请输入新的借书天数：");
                    scanf("%d", &cur->stu.duration);
                    while (getchar() != '\n');

                    break;
                }
                cur = cur->next;
            }
            if (flag == 0)
            {
                printf("未找到该学生\n");
            }
            break;
        case '2':
            printf("请输入修改对象名字:>>");
            scanf("%s", modify_data);
            while (getchar() != '\n');
            while (cur)
            {
                if (strcmp(cur->stu.name, modify_data) == 0)
                {
                    flag = 1;
                    printf("请输入新的学号：");
                    scanf("%s", cur->stu.number);
                    while (getchar() != '\n');

                    printf("请输入新的书名：");
                    scanf("%s", cur->stu.book);
                    while (getchar() != '\n');

                    printf("请输入新的借书时间：");
                    scanf("%d%d%d%d%d", &cur->stu.year, &cur->stu.month, &cur->stu.day, &cur->stu.hour, &cur->stu.minute);
                    while (getchar() != '\n');

                    printf("请输入新的借书天数：");
                    scanf("%d", &cur->stu.duration);
                    while (getchar() != '\n');

                    break;
                }
                cur = cur->next;
            }
            if (flag == 0)
            {
                printf("未找到该学生\n");
            }
            break;
        case '3':
            printf("请输入修改对象书名:>>");
            scanf("%s", modify_data);
            while (getchar() != '\n');
            while (cur)
            {
                if (strcmp(cur->stu.book, modify_data) == 0)
                {
                    flag = 1;
                    printf("请输入新的名字：");
                    scanf("%s", cur->stu.name);
                    while (getchar() != '\n');

                    printf("请输入新的学号：");
                    scanf("%s", cur->stu.number);
                    while (getchar() != '\n');

                    printf("请输入新的借书时间：");
                    scanf("%d%d%d%d%d", &cur->stu.year, &cur->stu.month, &cur->stu.day, &cur->stu.hour, &cur->stu.minute);
                    while (getchar() != '\n');

                    printf("请输入新的借书天数：");
                    scanf("%d", &cur->stu.duration);
                    while (getchar() != '\n');
                    break;
                }
                cur = cur->next;
            }
            if (flag == 0)
            {
                printf("未找到该学生\n");
            }
            break;
        case '0':
            exit(0);
        default:
            printf("\n请重新输入\n");
            break;
        }
        break;
    }
    saveStudent(head); // 一定要记得保存修改！！！！！
    system("cls");
}

// 排序   后期可以改为自选排序方式
void sortStudent(Node* head)
{
    if (head->next == NULL)
    {
        printf("没有数据 无法排序\n");
        return;
    }
    if (head->next->next == NULL)
    {
        printf("只有一个数据 无需排序\n");
        return;
    }
    Node* p, * q;
    St temp;
   char choice=0;
   printf("请选择排序方式:1.按名字排序  2.按学号排序  3.按时间先后排序\n");
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
        printf("\n请重新输入:\n");
        break;
    }
    }
    
}


//登录函数
void loginin()
{
    char user_name[20];
    char password[20];
    while (1)
    {
        printf("\n请输入用户名: \n");
        scanf("%s", user_name);
        while (getchar() != '\n');
        printf("\n请输入密码: \n");
        scanf("%s", password);
        while (getchar() != '\n');
        if (strcmp(user_name, "11111") == 0 && strcmp(password, "11111") == 0)
        {
            printf("\n-----用户名与密码正确请继续操作----\n");
            break;
        }
    }
}