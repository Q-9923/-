#pragma once
//打印菜单与功能
int menu();
enum MenuOptions
{
	Quit,      //0.退出
	Entry,	   //1.录入
	Print,	   //2.打印
	Save,	   //3.保存
	Stastics,  //4.统计
	Find,	   //5.查找
	Read,	   //6.读取
	Delete,	   //7.删除
	Modified,  //8.修改

};//枚举功能//
//学生数据
typedef struct student
{
	char name[20];                //名字
	unsigned long long number;    //学号
	float score_c;         //计算机学科成绩
	float score_English;          //英语学科成绩
	float score_Chinese;          //语文学科成绩
	float score_Math;             //高数学科成绩


}St;//学生信息
typedef struct Node
{
	St stu;           //学生
	struct Node* next;//下一节点
}Node;

typedef struct List
{
	Node* front;//指向第一个节点
	int size;   //节点个数
}List;
void entry(List* list);//传递指针
void prin(List* list);