/*�������ܣ�չʾ�˵�*/
#include "workerManager.h"

workerManager::workerManager()
{
	
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//1.�ļ�������
	if (!ifs.is_open())
	{
		/*��ʼ����¼����*/
		this->m_Empnum = 0;
		/*��ʼ���ļ��Ƿ�Ϊ��*/
		this->m_FileIsEmpty = true;
		/*��ʼ��ָ������*/
		this->m_EmpArray = nullptr;
		/*�ر��ļ�*/
		ifs.close();
		return;
	}
	
	//2.�ļ����ڣ���û�м�¼
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		/*��ʼ����¼����*/
		this->m_Empnum = 0;
		/*��ʼ���ļ��Ƿ�Ϊ��*/
		this->m_FileIsEmpty = true;
		/*��ʼ��ָ������*/
		this->m_EmpArray = nullptr;
		/*�ر��ļ�*/
		ifs.close();
		return;
	}

	//3.�ļ����ڣ����м�¼
	int num = this->getEmpNum();
	/*��ʼ����¼����*/
	this->m_Empnum = num;
	/*��ʼ���ļ��Ƿ�Ϊ��*/
	this->m_FileIsEmpty = false;

	this->m_EmpArray = new Worker * [this->m_Empnum];
	/*��ʼ��ָ������*/
	initEmp();
	/*�ر��ļ�*/
	ifs.close();

	return;


}


/*չʾ�˵�*/
void  workerManager::showMenu()
{
	cout << "*********************************************************" << endl;
	cout << "*********************************************************" << endl;
	cout << "**************** ��ӭʹ��ְ������ϵͳ *******************" << endl;
	cout << "*****************   0.�˳��������   ********************" << endl;
	cout << "*****************   1.����Ա����Ϣ   ********************" << endl;
	cout << "*****************   2.��ʾְ����Ϣ   ********************" << endl;
	cout << "*****************   3.ɾ����ְԱ��   ********************" << endl;
	cout << "*****************   4.�޸�ְ����Ϣ   ********************" << endl;
	cout << "*****************   5.����ְ����Ϣ   ********************" << endl;
	cout << "*****************   6.���ձ������   ********************" << endl;
	cout << "*****************   7.��������ĵ�   ********************" << endl;
	cout << "*********************************************************" << endl;
	cout << "*********************************************************" << endl;
	cout << endl;
	

	return;
}

/*��ʾԱ��*/
void workerManager::showEmp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "��ǰ��¼Ϊ�գ�" << endl;
	}
	else
	{
		for (int i = 0; i < this->m_Empnum; i++)
		{
			//���ö�̬���ýӿ�
			this->m_EmpArray[i]->showInfo();
		}
	}

	/*�������������*/
	system("pause");
	system("cls");

}

/*�ж�Ա���Ƿ����:�����ڣ���������λ�õ��±�,�����ڣ�����-1*/
int workerManager::IsExist(int id)
{
	int flag = 0; /*�Ƿ���ڵı�־����*/
	int index = 0; /*��¼�±�*/
	for (; index < this->m_Empnum; index++)
	{
		if (this->m_EmpArray[index]->m_Id == id)
		{
			flag = 1;/*��־�ҵ�*/
			break;
		}
	}

	return (flag ? index : -1);


}

/*ɾ��ְ��*/
void workerManager::deleteEmp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "��¼Ϊ�գ�" << endl;
	}
	else
	{
		int index; /*���ڼ�¼Ա��������λ�õ��±�*/
		int id;
		
		/*����ְ�����*/
		while (true)
		{
			cout << "��������ְԱ���ı�ţ�" << endl;
			if (cin >> id) break;   /*����Ϸ���������ѭ��*/
			cout << "�����������������룡" << endl;
			/*������뻺����*/
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}
		index = IsExist(id);

		if (index == -1) /*ְ��������*/
		{
			cout << "���޴��ˣ�" << endl;
		}
		else
		{
			/*�ͷŸ�Ա����Ϣ�ڶ����Ŀռ�*/
			delete this->m_EmpArray[index];
			for (; index < this->m_Empnum; index++)
			{
				/*�ӱ�ɾԱ����ʼ�������ָ�븲��ǰ���ָ��*/
				m_EmpArray[index] = m_EmpArray[index + 1];
			}
			/*�ͷ��������Ŀռ�*/
			//delete &m_EmpArray[m_Empnum - 1];  /*����bug,����ֻɾ���������һ��*/

			/*��������*/
			this->m_Empnum--;
			/*ͬ�����µ��ļ���*/
			this->save();

			/*��ʾ*/
			cout << "ɾ���ɹ���" << endl;
		}
	}

	/*�������������*/
	system("pause");
	system("cls");
}

/*����ְ����Ϣ*/
void workerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::trunc); /*�򿪷�ʽ������ļ����ڣ���ɾ�����ڴ���*/
	for (int i = 0; i < this->m_Empnum; i++)
	{
		/*ÿ�м�¼һ��ְ������Ϣ����Ϣ���ÿո����*/
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " " 
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	/*�ر��ļ���*/
	ofs.close();

}

/*ͳ���ļ��е�����*/
int workerManager::getEmpNum()
{
	int num = 0;/*ͳ������*/
	ifstream ifs;
	ifs.open(FILENAME, ios::in); /*���ļ������ļ���ʽ*/

	int id;
	string name;
	int dId;

	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		/*������1*/
		num++;
	}
	return num;
}

/*��ʼ��Ա������*/
void workerManager::initEmp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);/*���ļ����򿪷�ʽ�����ļ�*/

	int id; 
	string name;
	int dId;

	Worker* pworker = nullptr;
	int index = 0;/*�����±�*/
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		/*��ͨԱ��*/
		if (dId == 1)
		{
			pworker = new Employee(name, id, dId);
		}
		/*����*/
		if (dId == 2)
		{
			pworker = new Manager(name, id, dId);
		}
		/*�ϰ�*/
		if (dId == 3)
		{
			pworker = new Boss(name, id, dId);
		}

		/*��ָ�����������*/
		this->m_EmpArray[index] = pworker;
		index++; //�����±�����
	}

	/*�ر��ļ���*/
	ifs.close();
}

/*���ְ��*/
void workerManager::addEmp()
{
	
	int addNum = 0;
	/*����������������Ϸ���*/
	while (true)
	{
		cout << "��������ӵ�Ա��������" << endl;
		
		if ((cin >> addNum) && addNum>0 ) break;
		else
		{
			cout << "������������������" << endl;
			/*������뻺����*/
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}
	}

	int  newSize = this->m_Empnum + addNum; /*�¿ռ����� = ԭ������ + ��������*/

	//�����¿ռ�
	Worker** newArray = new Worker * [newSize];

	/*��ԭ�����������ָ�뿽����������*/
	if (this->m_Empnum > 0)												/*��ԭ�治ͬ*/
	{
		for (int i = 0; i < m_Empnum; i++)
		{
			newArray[i] = m_EmpArray[i];
		}
	}

	/*���������Ա��*/
	for (int i = 0; i < addNum; i++)
	{
		int id; //ְ�����
		string name;//ְ������
		int dSelelect; //����ѡ��

		while (true)
		{
			cout << "�������" << i + 1 << "����ְ�����" << endl;
			if (cin >> id) //����Ϸ�
			{
				if (this->IsExist(id) == -1) break;
				cout << "�ñ����ʹ�ã����������룡" << endl;
			}
			else cout << "���벻�Ϸ������������룡" << endl;
			/*������뻺����*/
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			
		}

		cout << "�������" << i + 1 << "����ְ��������(�����ո�)��" << endl;
		cin >> name;
		/*������뻺����*/
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		
		/*���벿��*/
		/*����Ϸ��Լ��*/
		while (true)
		{
			cout << "��ѡ���ְ���ĸ�λ" << endl
				<< "1.��ͨԱ��" << endl
				<< "2.����" << endl
				<< "3.�ϰ�" << endl;
			cin >> dSelelect;
			if (dSelelect == 1 || dSelelect == 2 || dSelelect == 3) break;
			cout << "�޸�ѡ�����������" << endl;
			/*������뻺����*/
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
		//�������õ�ְ����ָ�룬���������鵱��
		newArray[this->m_Empnum + i] = pworker;
	}

	/*�ͷ�ԭ��������*/
	delete[] this->m_EmpArray;
	
	//�����µĿռ��ָ��
	this->m_EmpArray = newArray;

	/*����ְ��������*/
	this->m_Empnum = newSize;

	/*��ʾ��ӳɹ�*/
	cout << "�ɹ����" << addNum << "����ְ��" << endl;
	
	/*ͣ�ٺ�����*/
	system("pause");
	system("cls");

	/*����ְ����Ϣ*/
	save();
	/*�����ļ��Ƿ�Ϊ��*/
	this->m_FileIsEmpty = false;

}

/*�޸�ְ��*/
void workerManager::modEmp()
{
	/*����ļ�Ϊ��*/
	if (this->m_FileIsEmpty)
	{
		cout << "��ǰ��¼Ϊ��" << endl;
	}
	else
	{
		int id;
		cout << "�������޸�Ա���ı��" << endl;
		while (!(cin >> id))
		{
			cout << "����������������룡" << endl;
			/*������뻺����*/
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}

		/*�ҵ���Ա�����±�*/
		int index = this->IsExist(id);

		/*�������ֵΪ-1*/
		if (index == -1)
		{
			cout << "���޴���" << endl;
		}
		else
		{
			int newId;
			string name;
			int dId;
			
			/*����Ա�����*/
			while (true)
			{
				cout << "�鵽��" << id << "��Ա������������ְ���ţ�" << endl;
				if (cin >> newId) break; //�������Ϸ�������ѭ��
				cout << "������������������" << endl;
				/*������뻺����*/
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			}
			
			/*����ְ������*/
			cout << "�������Ա����ǰ������(�����ո�)��";
			cin >> name;

			/*����Ա��ְλ*/
			while (true)
			{
				cout << "�������Ա����ǰ�ĸ�λ��" << endl
					<< "1.��ְͨ��" << endl
					<< "2.����" << endl
					<< "3.�ϰ�" << endl;

				if (cin >> dId && (dId == 1 || dId ==2 || dId == 3 )) break; //�������Ϸ�������ѭ��
				cout << "������������������" << endl;
				/*������뻺����*/
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			}

			/*ְλû��*/
			if (this->m_EmpArray[index]->m_DeptId == dId)
			{
				/*��������*/
				this->m_EmpArray[index]->m_Name = name;
				/*����ְ�����*/
				this->m_EmpArray[index]->m_Id = newId;

			}
			/*ְλ����*/
			else
			{
				Worker* pNew = nullptr;

				/*�ڶ������¿��ٿռ�*/
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

				/*�ͷ�ԭ���Ŀռ�*/
				delete this->m_EmpArray[index];
				/*����ָ��ָ��*/
				this->m_EmpArray[index] = pNew;
			}

			/*���浽�ļ���*/
			this->save();

			/*������ʾ*/
			cout << "�޸ĳɹ�!" << endl;
			
		}

	}
	/*�������������*/
	system("pause");
	system("cls");

}

/*����ָ��Ա������Ϣ*/
void workerManager::searchEmp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "��ǰ��¼Ϊ��" << endl;
	}
	else
	{
		int selection;
		cout << "��ѡ��" << endl
			<< "1.����������" << endl
			<< "2.����Ų���" << endl;

		while (!(cin >> selection) || (selection != 1 && selection != 2)) //������벻�Ϸ�����������
		{
			cout << "���벻�Ϸ������������룡" << endl;
			/*������뻺����*/
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
		}
		
		/*�û�ѡ����������*/
		if (selection == 1)
		{
			string name;

			cout << "���������Ա��������(�����ո�):" << endl;
			cin >> name;
			/*������뻺����*/
			cin.clear();
			cin.ignore(numeric_limits<std::streamsize>::max(), '\n');

			bool flag = false; //�Ƿ��ҵ�ְ���ı�ʾ������δ�ҵ�
			for (int i = 0; i < this->m_Empnum; i++)
			{
				if (this->m_EmpArray[i]->m_Name == name)
				{
					if (!flag)
					{
						cout << "��������Ӧ��Ϣ���£�" << endl;
						flag = true; //���±�ʾ����,���ҵ�
					}
					this->m_EmpArray[i]->showInfo();
				}
			}

			/*δ�鵽ְ��*/
			if (!flag)
			{
				cout << "���޴��ˣ�" << endl;
			}

			
		}
		/*�û�ѡ������Ա�����*/
		else
		{
			int index;  //��¼ְ����Ϣ�������е��±�
			int id;
			cout << "���������Ա���ı��:" << endl;
			while (!(cin >> id)) //������벻�Ϸ�����������
			{
				cout << "���벻�Ϸ������������룡" << endl;
				cout << "���������Ա���ı��:" << endl;
				/*������뻺����*/
				cin.clear();
				cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
			}

			/*����Ա��������λ�õ��±�*/
			index = this->IsExist(id);
	
		if (index == -1) /*δ�ҵ�ָ��Ա��*/
		{
			cout << "���޴���" << endl;
		}
		else
		{
			cout << "���ҵ���Ա��" << endl;
			/*չʾԱ����Ϣ*/
			this->m_EmpArray[index]->showInfo();
		}
		}

	}
	
	/*�������������*/
	system("pause");
	system("cls");
}

/*��ְ�����ѡ������*/
void workerManager::sortEmp()
{
	/*�����¼Ϊ��*/
	if (this->m_FileIsEmpty)
	{
		cout << "��ǰ��¼Ϊ��!" << endl;
		/*�������������*/
		system("pause");
		system("cls");
		return;
	}
	int selection;
	
	/*����ѡ��*/
	while (true)
	{
		cout << "��ѡ��" << endl
			<< "1.��ְ�������������" << endl
			<< "2.��ְ����Ž�������" << endl;
		if ((cin >> selection) && (selection == 1 || selection == 2))  break; //����Ϸ�������ѭ��
		cout << "������������������" << endl;
		/*������뻺����*/
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
	}

	/*��������*/
	if (selection == 1)
	{
		int minIndex; /*��¼ÿ������,��С���±�*/
		for (int i = 0; i < this->m_Empnum - 1;i++)
		{
			int minIndex = i;
			for (int j = i + 1; j < this->m_Empnum; j++)
			{
				if (this->m_EmpArray[j]->m_Id < this->m_EmpArray[minIndex]->m_Id) /*�ҵ���С��*/
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
	/*��������*/
	else if (selection == 2)
	{
		int maxIndex; /*��¼ÿ������,������±�*/
		for (int i = 0; i < this->m_Empnum - 1; i++)
		{
			int maxIndex = i;
			for (int j = i + 1; j < this->m_Empnum; j++)
			{
				if (this->m_EmpArray[j]->m_Id > this->m_EmpArray[maxIndex]->m_Id) /*�ҵ��ϴ���*/
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

	cout << "����ɹ�����������Ϊ��" << endl;
	/*�����޸�*/
	save();
	/*չʾ������*/
	this->showEmp();

}

/*����ļ�*/
void workerManager::cleanFile()
{
	int selection;

	/*����ѡ��*/
	while (true)
	{
		cout << "��ȷ�ϣ�" << endl
			<< "1.������գ�" << endl
			<< "2.ȡ�����" << endl;
		if (cin >> selection)
		{
			if (selection == 1 || selection == 2) break; /*������ȷ������ѭ��*/
			else cout << "�޸�ѡ��!,���������룡" << endl;
		}
		else
		{
			cout << "����Ϸ������������룡" << endl;
		}
		/*������뻺����*/
		cin.clear();
		cin.ignore(numeric_limits<std::streamsize>::max(), '\n');
	}
	/*����ɾ��*/
	if (selection == 1)
	{
		ofstream ofs;
		ofs.open(FILENAME,ios::trunc); //ɾ�����ļ����
		ofs.close(); //����¼��ֱ�ӹر�

		this->m_Empnum = 0; /*��������Ϊ��*/
		this->m_FileIsEmpty = true; 
		if (this->m_EmpArray != nullptr) /*�������*/
		{
			for (int i = 0; i < this->m_Empnum; i++)
			{
				/*�ͷ��ڶ�����ְ����Ϣ*/
				if (this->m_EmpArray[i] != nullptr)
				{
					delete this->m_EmpArray[i];
					this->m_EmpArray[i] = nullptr;
				}
			}
			/*�ͷ�ָ������*/
			delete[] this->m_EmpArray;
			this->m_EmpArray = nullptr;
		}

		cout << "��¼�����" << endl;

	}
	/*ȡ��ɾ��*/
	else if (selection == 2)
	{
		cout << "��ȡ����" << endl;
	}

	/*�������������*/
	system("pause");
	system("cls");
}

/*�˳�����*/
void workerManager::exitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

workerManager::~workerManager()
{
	if (this->m_EmpArray != nullptr)
	{
		for (int i = 0; i < this->m_Empnum; i++)
		{
			/*�ͷ��ڶ�����ְ����Ϣ*/
			if (this->m_EmpArray[i] != nullptr)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = nullptr;
			}
		}
		/*�ͷ�ָ������*/
		delete[] this->m_EmpArray;
		this->m_EmpArray = nullptr;
	}

}