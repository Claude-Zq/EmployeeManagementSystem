/*ְ����������ļ�*/
#pragma once
#include <iostream>
using namespace std;


class Worker
{
public:

	/*չʾ������Ϣ*/
	virtual void showInfo() = 0;

	/*��ȡ��λ����*/
	virtual string getPost() = 0;

	/*ְ������*/
	string m_Name;
	
	/*ְ�����*/
	int m_Id;

	/*���ű��*/
	/*1.��ְͨ�� 2.���� 3.�ϰ�*/
	int m_DeptId;


};


