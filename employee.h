/*��ͨԱ��ͷ�ļ�*/
#pragma once
#include "worker.h"

class Employee : public  Worker
{
public:

	/*���캯��*/
	Employee(string name, int id, int did);
	/*չʾ������Ϣ*/
	void showInfo();
	/*��ȡ��λ����*/
	string getPost();
	/*��������*/
	~Employee();

};