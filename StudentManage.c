#define  _CRT_SECURE_NO_WARNINGS
//#include"StudentManage.h"
#include<stdio.h>
#include "StudentManage.h"
int menu()
{
	printf("                                                   \n");
	printf("              ��ӭ����ѧ������ϵͳ1.0              \n");
	printf("                                                   \n ");
	printf("               ��ѡ�����¹���                      \n ");
	printf("               1.¼��ѧ����Ϣ                      \n ");
	printf("               2.��ӡѧ����Ϣ                      \n ");
	printf("               3.����ѧ����Ϣ                      \n ");
	printf("               4.ͳ��ѧ����Ϣ                      \n ");
	printf("               5.����ѧ����Ϣ                      \n ");
	printf("               6.��ȡѧ����Ϣ                      \n ");
	printf("               7.ɾ��ѧ����Ϣ                      \n ");
	printf("               8.�޸�ѧ����Ϣ                      \n ");
	printf("               0.�˳�                      \n ");
	printf("������ѡ��>");
	int select = -1;
	scanf("%d", &select);
	return select;
}

void entry(List* list)
{
	Node* node = (Node*)malloc(sizeof(Node));
	if (node == NULL)
	{
		printf("�ڵ㶯̬����ʧ��\n");
		return;
	}
	node->next = NULL;
	
	
	printf("����������:");
	
	/*scanf("%s", node->stu.name);*/
	gets(node->stu.name);
	
	printf("����ѧ��:");
	scanf("%ld", &node->stu.number);
	
	printf("������c�ɼ�:");
	scanf("%f", &node->stu.score_c);
	
	printf("������Ӣ��ɼ�:");
	scanf("%f", &node->stu.score_English);
	
	printf("���������ĳɼ�:");
	scanf("%f", &node->stu.score_Chinese);
	
	printf("����������ɼ�:");
	scanf("%f", &node->stu.score_Math);
	
	//���뵽����
	node->next = list->front;
	list->front = node;
	list->size++;
}
