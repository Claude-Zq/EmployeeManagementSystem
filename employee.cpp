/*普通员工源文件*/
#include "employee.h"


/*构造函数*/
Employee::Employee(string name,int id,int did)
{
	this->m_Name = name;
	this->m_Id = id;
	this->m_DeptId = did;
}

/*展示个人信息*/
void Employee::showInfo()
{
	cout << "员工姓名：" << m_Name << "\t"
		<< "员工编号：" << m_Id << "\t"
		<< "岗位：" << getPost() << "\t"
		<< "职责：" << "完成经理交给的任务" << endl;

}

/*获取岗位名称*/
string Employee::getPost()
{
	return (string)"普通员工";
}

/*析构函数*/
Employee::~Employee()
{

}

