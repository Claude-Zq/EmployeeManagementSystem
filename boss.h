/*�ϰ����ͷ�ļ�*/
#pragma once
#include "worker.h"

class Boss : public  Worker
{
public:

	/*���캯��*/
	Boss(string name, int id, int did);
	/*չʾ������Ϣ*/
	void showInfo();
	/*��ȡ��λ����*/
	string getPost();
	/*��������*/
	~Boss();

};