#pragma once
//��ӡ�˵��빦��
int menu();
enum MenuOptions
{
	Quit,      //0.�˳�
	Entry,	   //1.¼��
	Print,	   //2.��ӡ
	Save,	   //3.����
	Stastics,  //4.ͳ��
	Find,	   //5.����
	Read,	   //6.��ȡ
	Delete,	   //7.ɾ��
	Modified,  //8.�޸�

};//ö�ٹ���//
//ѧ������
typedef struct student
{
	char name[20];                //����
	unsigned long long number;    //ѧ��
	float score_c;         //�����ѧ�Ƴɼ�
	float score_English;          //Ӣ��ѧ�Ƴɼ�
	float score_Chinese;          //����ѧ�Ƴɼ�
	float score_Math;             //����ѧ�Ƴɼ�


}St;//ѧ����Ϣ
typedef struct Node
{
	St stu;           //ѧ��
	struct Node* next;//��һ�ڵ�
}Node;

typedef struct List
{
	Node* front;//ָ���һ���ڵ�
	int size;   //�ڵ����
}List;
void entry(List* list);//����ָ��
void prin(List* list);