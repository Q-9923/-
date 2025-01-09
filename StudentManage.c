#define  _CRT_SECURE_NO_WARNINGS
//#include"StudentManage.h"
#include<stdio.h>
#include "StudentManage.h"
int menu()
{
	printf("                                                   \n");
	printf("              欢迎来到学生管理系统1.0              \n");
	printf("                                                   \n ");
	printf("               请选择以下功能                      \n ");
	printf("               1.录入学生信息                      \n ");
	printf("               2.打印学生信息                      \n ");
	printf("               3.保存学生信息                      \n ");
	printf("               4.统计学生信息                      \n ");
	printf("               5.查找学生信息                      \n ");
	printf("               6.读取学生信息                      \n ");
	printf("               7.删除学生信息                      \n ");
	printf("               8.修改学生信息                      \n ");
	printf("               0.退出                      \n ");
	printf("请做出选择>");
	int select = -1;
	scanf("%d", &select);
	return select;
}

void entry(List* list)
{
	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL)
	{
		printf("节点动态开辟失败\n");
		return;
	}
	node->next = NULL;
	
	
	printf("请输入名字:");
	
	/*scanf("%s", node->stu.name);*/
	gets(node->stu.name);
	
	printf("请输学号:");
	scanf("%ld", &node->stu.number);
	
	printf("请输入c成绩:");
	scanf("%f", &node->stu.score_c);
	
	printf("请输入英语成绩:");
	scanf("%f", &node->stu.score_English);
	
	printf("请输入语文成绩:");
	scanf("%f", &node->stu.score_Chinese);
	
	printf("请输入高数成绩:");
	scanf("%f", &node->stu.score_Math);
	
	//插入到链表
	node->next = list->front;
	list->front = node;
	list->size++;
}
