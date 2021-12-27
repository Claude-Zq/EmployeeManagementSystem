/*��������ļ�*/
#pragma once          //��ֹͷ�ļ��ظ�����

#define FILENAME "empf.txt"
#include <iostream>
#include <fstream>
#include "worker.h"
#include "boss.h"
#include"employee.h"
#include "manager.h"
//using namespace std;

class workerManager
{
public:
	/*constructor*/
	workerManager();

	/*չʾ�˵�*/
	void showMenu();

	/*��ʾԱ��*/
	void showEmp();

	/*�ж�Ա���Ƿ����:�����ڣ���������λ�õ��±꣬�����ڣ�����-1*/
	int IsExist(int id);

	/*ɾ��ְ��*/
	void deleteEmp();

	/*��¼ְ��������*/
	int m_Empnum;

	/*ְ������ָ��*/
	Worker** m_EmpArray;

	/*�����ļ�*/
	void save();

	/*���ְ��*/
	void addEmp();

	/*�޸�ְ��*/
	void modEmp();

	/*�ж��ļ��Ƿ�Ϊ�յı�־*/
	bool m_FileIsEmpty;

	/*ͳ���ļ��е�����*/
	int getEmpNum();

	/*����ָ��Ա������Ϣ*/
	void searchEmp();

	/*��ְ���������*/
	void sortEmp();

	/*����ļ�*/
	void cleanFile();

	/*��ʼ��Ա������*/
	void initEmp();
	
	/*�˳�����*/
	void exitSystem();

	/*destructor*/
	~workerManager();



};
