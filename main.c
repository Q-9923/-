//#define  _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"StudentManage.h"


int main(int argc,char*argv[])
{
	List list;
	//创建链表 几种初始化的方式    要初始化指针和size不然为野指针和随机数
	//方式1
	/*
	list.front = NULL;
	list.size = 0;*/

	//方式2
	//List list = { 0 };

	//方式3  调用内存设置函数memset(void*list,int 数字,size)
	memset(&list, 0, sizeof(list));
	while (1)
	{
		switch (menu())
		{
		case Quit:
			printf("退出\n");
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
		
		
		system("pause");//程序暂停看到以下helloworld的信息

		system("cls");//清除冗余的菜单信息避免繁琐
	}
	

	return 0;
}