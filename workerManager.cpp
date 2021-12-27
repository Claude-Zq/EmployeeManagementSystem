/*函数功能：展示菜单*/
#include "workerManager.h"

workerManager::workerManager()
{
	
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//1.文件不存在
	if (!ifs.is_open())
	{
		/*初始化记录人数*/
		this->m_Empnum = 0;
		/*初始化文件是否为空*/
		this->m_FileIsEmpty = true;
		/*初始化指针数组*/
		this->m_EmpArray = nullptr;
		/*关闭文件*/
		ifs.close();
		return;
	}
	
	//2.文件存在，但没有记录
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		/*初始化记录人数*/
		this->m_Empnum = 0;
		/*初始化文件是否为空*/
		this->m_FileIsEmpty = true;
		/*初始化指针数组*/
		this->m_EmpArray = nullptr;
		/*关闭文件*/
		ifs.close();
		return;
	}

	//3.文件存在，且有记录
	int num = this->getEmpNum();
	/*初始化记录人数*/
	this->m_Empnum = num;
	/*初始化文件是否为空*/
	this->m_FileIsEmpty = false;

	this->m_EmpArray = new Worker * [this->m_Empnum];
	/*初始化指针数组*/
	initEmp();
	/*关闭文件*/
	ifs.close();

	return;


}


/*展示菜单*/
void  workerManager::showMenu()
{
	cout << "*********************************************************" << endl;
	cout << "*********************************************************" << endl;
	cout << "**************** 欢迎使用职工管理系统 *******************" << endl;
	cout << "*****************   0.退出管理程序   ********************" << endl;
	cout << "*****************   1.增加员工信息   ********************" << endl;
	cout << "*****************   2.显示职工信息   ********************" << endl;
	cout << "*****************   3.删除离职员工   ********************" << endl;
	cout << "*****************   4.修改职工信息   ********************" << endl;
	cout << "*****************   5.查找职工信息   ********************" << endl;
	cout << "*****************   6.按照编号排序   ********************" << endl;
	cout << "*****************   7.清空所有文档   ********************" << endl;
	cout << "*********************************************************" << endl;
	cout << "*********************************************************" << endl;
	cout << endl;
	

	return;
}

/*显示员工*/
void workerManager::showEmp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "当前记录为空！" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Empnum; i++)
		{
			//利用多态调用接口
			this->m_EmpArray[i]->showInfo();
		}
	}

	/*按任意键后请屏*/
	system("pause");
	system("cls");

}

/*判断员工是否存在:若存在，返回所在位置的下标,不存在：返回-1*/
int workerManager::IsExist(int id)
{
	int flag = 0; /*是否存在的标志变量*/
	int index = 0; /*记录下标*/
	for (; index < this->m_Empnum; index++)
	{
		if (this->m_EmpArray[index]->m_Id == id)
		{
			flag = 1;/*标志找到*/
			break;
		}
	}

	return (flag ? index : -1);


}

/*删除职工*/
void workerManager::deleteEmp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "记录为空！" << endl;
	}
	else
	{
		int index; /*用于记录员工在数组位置的下标*/
		int id;
		
		/*输入职工编号*/
		while (true)
		{
			cout << "请输入离职员工的编号：" << endl;
			if (cin >> id) break;   /*输入合法才能跳出循环*/
			cout << "输入有误，请重新输入！" << endl;
			/*清空输入缓冲区*/
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}
		index = IsExist(id);

		if (index == -1) /*职工不存在*/
		{
			cout << "查无此人！" << endl;
		}
		else
		{
			/*释放该员工信息在堆区的空间*/
			delete this->m_EmpArray[index];
			for (; index < this->m_Empnum; index++)
			{
				/*从被删员工开始，后面的指针覆盖前面的指针*/
				m_EmpArray[index] = m_EmpArray[index + 1];
			}
			/*释放数组最后的空间*/
			//delete &m_EmpArray[m_Empnum - 1];  /*遇到bug,不能只删除数组最后一节*/

			/*更新人数*/
			this->m_Empnum--;
			/*同部更新到文件中*/
			this->save();

			/*提示*/
			cout << "删除成功！" << endl;
		}
	}

	/*按任意键后清屏*/
	system("pause");
	system("cls");
}

/*保存职工信息*/
void workerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::trunc); /*打开方式：如果文件存在，先删除，在创建*/
	for (int i = 0; i < this->m_Empnum; i++)
	{
		/*每行记录一个职工的信息，信息间用空格隔开*/
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " " 
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	/*关闭文件夹*/
	ofs.close();

}

/*统计文件中的人数*/
int workerManager::getEmpNum()
{
	int num = 0;/*统计人数*/
	ifstream ifs;
	ifs.open(FILENAME, ios::in); /*打开文件，读文件方式*/

	int id;
	string name;
	int dId;

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		/*人数加1*/
		num++;
	}
	return num;
}

/*初始化员工数组*/
void workerManager::initEmp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);/*打开文件，打开方式：读文件*/

	int id; 
	string name;
	int dId;

	Worker* pworker = nullptr;
	int index = 0;/*数组下标*/
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		/*普通员工*/
		if (dId == 1)
		{
			pworker = new Employee(name, id, dId);
		}
		/*经理*/
		if (dId == 2)
		{
			pworker = new Manager(name, id, dId);
		}
		/*老板*/
		if (dId == 3)
		{
			pworker = new Boss(name, id, dId);
		}

		/*将指针放入输入中*/
		this->m_EmpArray[index] = pworker;
		index++; //数组下标右移
	}

	/*关闭文件夹*/
	ifs.close();
}

/*添加职工*/
void workerManager::addEmp()
{
	
	int addNum = 0;
	/*输入添加人数并检查合法性*/
	while (true)
	{
		cout << "请输入添加的员工数量：" << endl;
		
		if ((cin >> addNum) && addNum>0 ) break;
		else
		{
			cout << "输入有误请重新输入" << endl;
			/*清空输入缓冲区*/
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	int  newSize = this->m_Empnum + addNum; /*新空间人数 = 原来人数 + 新增人数*/

	//开辟新空间
	Worker** newArray = new Worker * [newSize];

	/*将原来的数组里的指针拷贝到新数组*/
	if (this->m_Empnum > 0)												/*和原版不同*/
	{
		for (int i = 0; i < m_Empnum; i++)
		{
			newArray[i] = m_EmpArray[i];
		}
	}

	/*批量添加新员工*/
	for (int i = 0; i < addNum; i++)
	{
		int id; //职工编号
		string name;//职工姓名
		int dSelelect; //部门选择

		while (true)
		{
			cout << "请输入第" << i + 1 << "个新职工编号" << endl;
			if (cin >> id) //输入合法
			{
				if (this->IsExist(id) == -1) break;
				cout << "该编号已使用，请重新输入！" << endl;
			}
			else cout << "输入不合法，请重新输入！" << endl;
			/*清空输入缓冲区*/
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			
		}

		cout << "请输入第" << i + 1 << "个新职工的姓名(不含空格)：" << endl;
		cin >> name;
		/*清空输入缓冲区*/
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		
		/*输入部门*/
		/*输入合法性检查*/
		while (true)
		{
			cout << "请选择该职工的岗位" << endl
				<< "1.普通员工" << endl
				<< "2.经理" << endl
				<< "3.老板" << endl;
			cin >> dSelelect;
			if (dSelelect == 1 || dSelelect == 2 || dSelelect == 3) break;
			cout << "无该选项，请重新输入" << endl;
			/*清空输入缓冲区*/
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}
		
		Worker* pworker= nullptr;
		switch (dSelelect)
		{
			case 1:
				pworker = new Employee(name,id,1);
				break;
			case 2:
				pworker = new Manager(name, id, 2);
				break;
			case 3:
				pworker = new Boss(name, id, 3);
				break;
		}
		//将创建好的职工的指针，保存在数组当中
		newArray[this->m_Empnum + i] = pworker;
	}

	/*释放原来的数组*/
	delete[] this->m_EmpArray;
	
	//更改新的空间的指向
	this->m_EmpArray = newArray;

	/*更新职工总人数*/
	this->m_Empnum = newSize;

	/*提示添加成功*/
	cout << "成功添加" << addNum << "名新职工" << endl;
	
	/*停顿后清屏*/
	system("pause");
	system("cls");

	/*保存职工信息*/
	save();
	/*更新文件是否为空*/
	this->m_FileIsEmpty = false;

}

/*修改职工*/
void workerManager::modEmp()
{
	/*如果文件为空*/
	if (this->m_FileIsEmpty)
	{
		cout << "当前记录为空" << endl;
	}
	else
	{
		int id;
		cout << "请输入修改员工的编号" << endl;
		while (!(cin >> id))
		{
			cout << "输入错误，请重新输入！" << endl;
			/*清空输入缓冲区*/
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}

		/*找到该员工的下标*/
		int index = this->IsExist(id);

		/*如果返回值为-1*/
		if (index == -1)
		{
			cout << "查无此人" << endl;
		}
		else
		{
			int newId;
			string name;
			int dId;
			
			/*输入员工编号*/
			while (true)
			{
				cout << "查到：" << id << "号员工，请输入新职工号：" << endl;
				if (cin >> newId) break; //如果输入合法，跳出循环
				cout << "输入有误请重新输入" << endl;
				/*清空输入缓冲区*/
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			}
			
			/*输入职工姓名*/
			cout << "请输入该员工当前的姓名(不含空格)：";
			cin >> name;

			/*输入员工职位*/
			while (true)
			{
				cout << "请输入该员工当前的岗位：" << endl
					<< "1.普通职工" << endl
					<< "2.经理" << endl
					<< "3.老板" << endl;

				if (cin >> dId && (dId == 1 || dId ==2 || dId == 3 )) break; //如果输入合法，跳出循环
				cout << "输入有误请重新输入" << endl;
				/*清空输入缓冲区*/
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			}

			/*职位没变*/
			if (this->m_EmpArray[index]->m_DeptId == dId)
			{
				/*更新名字*/
				this->m_EmpArray[index]->m_Name = name;
				/*更新职工编号*/
				this->m_EmpArray[index]->m_Id = newId;

			}
			/*职位变了*/
			else
			{
				Worker* pNew = nullptr;

				/*在堆区重新开辟空间*/
				switch (dId)
				{
				case 1:
					pNew = new Employee(name,newId, dId);
					break;
				case 2:
					pNew = new Manager(name, newId, dId);
					break;
				case 3:
					pNew = new Boss(name, newId, dId);
					break;
				}

				/*释放原来的空间*/
				delete this->m_EmpArray[index];
				/*更新指针指向*/
				this->m_EmpArray[index] = pNew;
			}

			/*保存到文件中*/
			this->save();

			/*输入提示*/
			cout << "修改成功!" << endl;
			
		}

	}
	/*按任意键后清屏*/
	system("pause");
	system("cls");

}

/*查找指定员工的信息*/
void workerManager::searchEmp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "当前记录为空" << endl;
	}
	else
	{
		int selection;
		cout << "请选择：" << endl
			<< "1.按姓名查找" << endl
			<< "2.按编号查找" << endl;

		while (!(cin >> selection) || (selection != 1 && selection != 2)) //如果输入不合法，重新输入
		{
			cout << "输入不合法，请重新输入！" << endl;
			/*清空输入缓冲区*/
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}
		
		/*用户选择输入姓名*/
		if (selection == 1)
		{
			string name;

			cout << "请输入查找员工的姓名(不含空格):" << endl;
			cin >> name;
			/*清空输入缓冲区*/
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

			bool flag = false; //是否找到职工的表示变量，未找到
			for (int i = 0; i < this->m_Empnum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					if (!flag)
					{
						cout << "该姓名对应信息如下：" << endl;
						flag = true; //更新表示变量,已找到
					}
					this->m_EmpArray[i]->showInfo();
				}
			}

			/*未查到职工*/
			if (!flag)
			{
				cout << "查无此人！" << endl;
			}

			
		}
		/*用户选择输入员工编号*/
		else
		{
			int index;  //记录职工信息在数组中的下标
			int id;
			cout << "请输入查找员工的编号:" << endl;
			while (!(cin >> id)) //如果输入不合法，重新输入
			{
				cout << "输入不合法，请重新输入！" << endl;
				cout << "请输入查找员工的编号:" << endl;
				/*清空输入缓冲区*/
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			}

			/*接收员工在数组位置的下标*/
			index = this->IsExist(id);
	
		if (index == -1) /*未找到指定员工*/
		{
			cout << "查无此人" << endl;
		}
		else
		{
			cout << "查找到该员工" << endl;
			/*展示员工信息*/
			this->m_EmpArray[index]->showInfo();
		}
		}

	}
	
	/*按任意键后清屏*/
	system("pause");
	system("cls");
}

/*按职工编号选择法排序*/
void workerManager::sortEmp()
{
	/*如果记录为空*/
	if (this->m_FileIsEmpty)
	{
		cout << "当前记录为空!" << endl;
		/*按任意键后清屏*/
		system("pause");
		system("cls");
		return;
	}
	int selection;
	
	/*输入选项*/
	while (true)
	{
		cout << "请选择：" << endl
			<< "1.按职工编号升序排列" << endl
			<< "2.按职工编号降序排列" << endl;
		if ((cin >> selection) && (selection == 1 || selection == 2))  break; //输入合法，跳出循环
		cout << "输入有误，请重新输入" << endl;
		/*清空输入缓冲区*/
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
	}

	/*升序排列*/
	if (selection == 1)
	{
		int minIndex; /*记录每轮排序,最小项下标*/
		for (int i = 0; i < this->m_Empnum - 1;i++)
		{
			int minIndex = i;
			for (int j = i + 1; j < this->m_Empnum; j++)
			{
				if (this->m_EmpArray[j]->m_Id < this->m_EmpArray[minIndex]->m_Id) /*找到较小项*/
				{
					minIndex = j; 
				}
			}
			if (minIndex != i)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minIndex];
				this->m_EmpArray[minIndex] = temp;
			}
		}
	}
	/*降序排列*/
	else if (selection == 2)
	{
		int maxIndex; /*记录每轮排序,最大项下标*/
		for (int i = 0; i < this->m_Empnum - 1; i++)
		{
			int maxIndex = i;
			for (int j = i + 1; j < this->m_Empnum; j++)
			{
				if (this->m_EmpArray[j]->m_Id > this->m_EmpArray[maxIndex]->m_Id) /*找到较大项*/
				{
					maxIndex = j;
				}
			}
			if (maxIndex != i)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[maxIndex];
				this->m_EmpArray[maxIndex] = temp;
			}
		}

	}

	cout << "排序成功！，排序结果为：" << endl;
	/*保存修改*/
	save();
	/*展示排序结果*/
	this->showEmp();

}

/*清空文件*/
void workerManager::cleanFile()
{
	int selection;

	/*输入选项*/
	while (true)
	{
		cout << "请确认：" << endl
			<< "1.继续清空！" << endl
			<< "2.取消清空" << endl;
		if (cin >> selection)
		{
			if (selection == 1 || selection == 2) break; /*输入正确，跳出循环*/
			else cout << "无该选项!,请重新输入！" << endl;
		}
		else
		{
			cout << "输入合法，请重新输入！" << endl;
		}
		/*清空输入缓冲区*/
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
	}
	/*继续删除*/
	if (selection == 1)
	{
		ofstream ofs;
		ofs.open(FILENAME,ios::trunc); //删除来文件后打开
		ofs.close(); //不记录，直接关闭

		this->m_Empnum = 0; /*人数更新为零*/
		this->m_FileIsEmpty = true; 
		if (this->m_EmpArray != nullptr) /*清空数组*/
		{
			for (int i = 0; i < this->m_Empnum; i++)
			{
				/*释放在堆区的职工信息*/
				if (this->m_EmpArray[i] != nullptr)
				{
					delete this->m_EmpArray[i];
					this->m_EmpArray[i] = nullptr;
				}
			}
			/*释放指针数组*/
			delete[] this->m_EmpArray;
			this->m_EmpArray = nullptr;
		}

		cout << "记录已清空" << endl;

	}
	/*取消删除*/
	else if (selection == 2)
	{
		cout << "已取消！" << endl;
	}

	/*按任意键后清屏*/
	system("pause");
	system("cls");
}

/*退出程序*/
void workerManager::exitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

workerManager::~workerManager()
{
	if (this->m_EmpArray != nullptr)
	{
		for (int i = 0; i < this->m_Empnum; i++)
		{
			/*释放在堆区的职工信息*/
			if (this->m_EmpArray[i] != nullptr)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = nullptr;
			}
		}
		/*释放指针数组*/
		delete[] this->m_EmpArray;
		this->m_EmpArray = nullptr;
	}

}