#include <iostream>
using namespace std;
#include "workerManager.h"

/*
�����ܣ�����ְ������Ϣ
���ߣ�����
ʱ�䣺2021/12/22-202/12/27
*/

int main()
{

	
	workerManager wm;

	while (true)
	{
		wm.showMenu();
		cout << "����������ѡ��:" << endl;
		int choice;

		while (!(cin >> choice)) //������벻�Ϸ�����������
		{
			cout << "���벻�Ϸ�,���������룡" << endl;
			/*������뻺����*/
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}
		

		switch (choice)
		{
		/* �˳�������� */
		case 0:
			wm.exitSystem();
			break;
		/*����Ա����Ϣ*/
		case 1:
			wm.addEmp();
			break;
		/*��ʾְ����Ϣ*/
		case 2:
			wm.showEmp();
			break;
		/*ɾ����ְԱ��*/
		case 3:
			wm.deleteEmp();
			break;
		/*�޸�ְ����Ϣ*/
		case 4:
			wm.modEmp();
			break;
		/*����Ա��*/
		case 5:
			wm.searchEmp();
			break;
		/*���ձ������*/
		case 6:
			wm.sortEmp();
			break;
		/*��������ĵ�*/
		case 7:
			wm.cleanFile();
			break;
		default:
			cout << "�޸�ѡ�" << endl;
			system("pause");
			system("cls");
		}
	}
	
	return 0;
	system("pause");

}