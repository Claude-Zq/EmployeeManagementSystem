/*��ͨԱ��Դ�ļ�*/
#include "employee.h"


/*���캯��*/
Employee::Employee(string name,int id,int did)
{
	this->m_Name = name;
	this->m_Id = id;
	this->m_DeptId = did;
}

/*չʾ������Ϣ*/
void Employee::showInfo()
{
	cout << "Ա��������" << m_Name << "\t"
		<< "Ա����ţ�" << m_Id << "\t"
		<< "��λ��" << getPost() << "\t"
		<< "ְ��" << "��ɾ�����������" << endl;

}

/*��ȡ��λ����*/
string Employee::getPost()
{
	return (string)"��ͨԱ��";
}

/*��������*/
Employee::~Employee()
{

}

