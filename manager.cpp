/*经理源文件*/
#include "manager.h"


/*构造函数*/
Manager::Manager(string name,int id,int did)
{
	this->m_Name = name;
	this->m_Id = id;
	this->m_DeptId = did;
}

/*展示个人信息*/
void Manager::showInfo()
{
	cout << "员工姓名：" << m_Name << "\t"
		<< "员工编号：" << m_Id << "\t"
		<< "岗位：" << getPost() << "\t"
		<< "职责：" << "完成老板交给的任务，并下发给员工" << endl;

}

/*获取岗位名称*/
string Manager::getPost()
{
	return (string)"经理";
}

/*析构函数*/
Manager::~Manager()
{

}

