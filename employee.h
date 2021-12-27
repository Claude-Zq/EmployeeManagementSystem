/*普通员工头文件*/
#pragma once
#include "worker.h"

class Employee : public  Worker
{
public:

	/*构造函数*/
	Employee(string name, int id, int did);
	/*展示个人信息*/
	void showInfo();
	/*获取岗位名称*/
	string getPost();
	/*析构函数*/
	~Employee();

};