/*����Դ�ļ�*/
#include "manager.h"


/*���캯��*/
Manager::Manager(string name,int id,int did)
{
	this->m_Name = name;
	this->m_Id = id;
	this->m_DeptId = did;
}

/*չʾ������Ϣ*/
void Manager::showInfo()
{
	cout << "Ա��������" << m_Name << "\t"
		<< "Ա����ţ�" << m_Id << "\t"
		<< "��λ��" << getPost() << "\t"
		<< "ְ��" << "����ϰ彻�������񣬲��·���Ա��" << endl;

}

/*��ȡ��λ����*/
string Manager::getPost()
{
	return (string)"����";
}

/*��������*/
Manager::~Manager()
{

}

