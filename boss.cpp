/*�ϰ�Դ�ļ�*/
#include "boss.h"


/*���캯��*/
Boss::Boss(string name, int id, int did)
{
	this->m_Name = name;
	this->m_Id = id;
	this->m_DeptId = did;
}

/*չʾ������Ϣ*/
void Boss::showInfo()
{
	cout << "Ա��������" << m_Name << "\t"
		<< "Ա����ţ�" << m_Id << "\t"
		<< "��λ��" << getPost() << "\t"
		<< "ְ��" << "��������������" << endl;

}

/*��ȡ��λ����*/
string Boss::getPost()
{
	return (string)"�ϰ�";
}

/*��������*/
Boss::~Boss()
{

}

