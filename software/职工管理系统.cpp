#include <iostream>
using namespace std;
#include "workerManager.h"

/*
程序功能：管理职工的信息
作者：周青
时间：2021/12/22-202/12/27
*/

int main()
{

	
	workerManager wm;

	while (true)
	{
		wm.showMenu();
		cout << "请输入您的选择:" << endl;
		int choice;

		while (!(cin >> choice)) //如果输入不合法，重新输入
		{
			cout << "输入不合法,请重新输入！" << endl;
			/*清空输入缓冲区*/
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}
		

		switch (choice)
		{
		/* 退出管理程序 */
		case 0:
			wm.exitSystem();
			break;
		/*增加员工信息*/
		case 1:
			wm.addEmp();
			break;
		/*显示职工信息*/
		case 2:
			wm.showEmp();
			break;
		/*删除离职员工*/
		case 3:
			wm.deleteEmp();
			break;
		/*修改职工信息*/
		case 4:
			wm.modEmp();
			break;
		/*查找员工*/
		case 5:
			wm.searchEmp();
			break;
		/*按照编号排序*/
		case 6:
			wm.sortEmp();
			break;
		/*清空所有文档*/
		case 7:
			wm.cleanFile();
			break;
		default:
			cout << "无该选项！" << endl;
			system("pause");
			system("cls");
		}
	}
	
	return 0;
	system("pause");

}