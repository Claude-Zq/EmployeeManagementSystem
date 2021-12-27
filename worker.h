/*职工抽象类的文件*/
#pragma once
#include <iostream>
using namespace std;


class Worker
{
public:

	/*展示个人信息*/
	virtual void showInfo() = 0;

	/*获取岗位名称*/
	virtual string getPost() = 0;

	/*职工姓名*/
	string m_Name;
	
	/*职工编号*/
	int m_Id;

	/*部门编号*/
	/*1.普通职工 2.经理 3.老板*/
	int m_DeptId;


};


