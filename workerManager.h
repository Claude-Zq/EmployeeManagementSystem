/*管理类的文件*/
#pragma once          //防止头文件重复包含

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

	/*展示菜单*/
	void showMenu();

	/*显示员工*/
	void showEmp();

	/*判断员工是否存在:若存在，返回所在位置的下标，不存在：返回-1*/
	int IsExist(int id);

	/*删除职工*/
	void deleteEmp();

	/*记录职工总人数*/
	int m_Empnum;

	/*职工数组指针*/
	Worker** m_EmpArray;

	/*保存文件*/
	void save();

	/*添加职工*/
	void addEmp();

	/*修改职工*/
	void modEmp();

	/*判断文件是否为空的标志*/
	bool m_FileIsEmpty;

	/*统计文件中的人数*/
	int getEmpNum();

	/*查找指定员工的信息*/
	void searchEmp();

	/*按职工编号排序*/
	void sortEmp();

	/*清空文件*/
	void cleanFile();

	/*初始化员工数组*/
	void initEmp();
	
	/*退出程序*/
	void exitSystem();

	/*destructor*/
	~workerManager();



};
