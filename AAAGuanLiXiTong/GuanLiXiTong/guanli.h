#pragma once
typedef struct student
{
	char name[20];                //����
	char number[12];              //ѧ��
	char book[50];				  //Ҫ�������
	int year;					  //�������
	int month;					  //�����·�
	int day;					  //��������
	int hour;					  //����ʱ
	int minute;					  //�����
	int duration;
}St;//ѧ����Ϣ


//ѧ���ڵ�
typedef struct _Node
{
	St stu;            //ѧ���ڵ�
	struct _Node* next;//��һ�ڵ�
}Node;

void menu();
void inputStudent(Node* head);//¼��
void printStudent(Node* head);//��ӡ��Ϣ
void countStudent(Node* head);//ͳ��
void findStudent(Node* head);//����
void saveStudent(Node* head);//����
void loadStudent(Node* head);//��ȡ��Ϣ
void modifyStudent(Node* head);//�޸�
void deleteStudent(Node* head);//ɾ��
void sortStudent(Node* head);//����
void loginin();