#pragma once
typedef struct student
{
	char name[20];                //名字
	char number[12];              //学号
	char book[50];				  //要借的书名
	int year;					  //借书年份
	int month;					  //借书月份
	int day;					  //借书日期
	int hour;					  //借书时
	int minute;					  //借书分
	int duration;
}St;//学生信息


//学生节点
typedef struct _Node
{
	St stu;            //学生节点
	struct _Node* next;//下一节点
}Node;

void menu();
void inputStudent(Node* head);//录入
void printStudent(Node* head);//打印信息
void countStudent(Node* head);//统计
void findStudent(Node* head);//查找
void saveStudent(Node* head);//保存
void loadStudent(Node* head);//读取信息
void modifyStudent(Node* head);//修改
void deleteStudent(Node* head);//删除
void sortStudent(Node* head);//排序
void loginin();