//#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"StudentManage.h"


int main(int argc,char*argv[])
{
	List list;
	//�������� ���ֳ�ʼ���ķ�ʽ    Ҫ��ʼ��ָ���size��ȻΪҰָ��������
	//��ʽ1
	/*
	list.front = NULL;
	list.size = 0;*/

	//��ʽ2
	//List list = { 0 };

	//��ʽ3  �����ڴ����ú���memset(void*list,int ����,size)
	memset(&list, 0, sizeof(list));
	while (1)
	{
		switch (menu())
		{
		case Quit:
			printf("�˳�\n");
			return 0;
			
		case Entry:
			entry(&list);
			break;
		case Print:
			break;
		case Save:
			break;
		case Stastics:
			break;
		case Find:
			break;
		case Read:
			break;
		case Delete:
			break;
		case Modified:
			break;
		default:
			break;
		}
		
		
		system("pause");//������ͣ��������helloworld����Ϣ

		system("cls");//�������Ĳ˵���Ϣ���ⷱ��
	}
	

	return 0;
}