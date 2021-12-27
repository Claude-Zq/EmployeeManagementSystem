/*老板源文件*/
#include "boss.h"


/*构造函数*/
Boss::Boss(string name, int id, int did)
{
	this->m_Name = name;
	this->m_Id = id;
	this->m_DeptId = did;
}

/*展示个人信息*/
void Boss::showInfo()
{
	cout << "员工姓名：" << m_Name << "\t"
		<< "员工编号：" << m_Id << "\t"
		<< "岗位：" << getPost() << "\t"
		<< "职责：" << "将任务分配给经理" << endl;

}

/*获取岗位名称*/
string Boss::getPost()
{
	return (string)"老板";
}

/*析构函数*/
Boss::~Boss()
{

}

