/*������ͷ�ļ�*/
#pragma once
#include "worker.h"

class Manager : public  Worker
{
public:

	/*���캯��*/
	Manager(string name, int id, int did);
	/*չʾ������Ϣ*/
	void showInfo();
	/*��ȡ��λ����*/
	string getPost();
	/*��������*/
	~Manager();

};