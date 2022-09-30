//*Info��*
Info::Info()//���캯��
{
	//��ʼ��
	memset(name, 0, sizeof(name));
	memset(gender, 0, sizeof(gender));
	memset(phone, 0, sizeof(phone));
	memset(qq, 0, sizeof(qq));
	memset(email, 0, sizeof(email));
	index = 0;
	next = NULL;
}
#ifdef  _VC2010_VER_
ofstream& operator << (ofstream& ofs, const Info& c)//����� << ����
{
	ofs << c.name << " " << c.gender << " " << c.phone << " " << c.qq << " " << c.email << " ";
	return ofs;
}

ifstream& operator >> (ifstream& ifs, Info& c)//����� >> ����
{
	ifs >> c.name >> c.gender >> c.phone >> c.qq >> c.email;
	return ifs;
}
#endif

//*AddressBook��*
AddressBook::AddressBook() //���캯��
{
	head = NULL;
}

AddressBook::~AddressBook() //��������
{
	Info* temp = head;
	while (head != NULL)
	{
		temp = head;
		head = head->next;
		delete temp;
	}
}

void AddressBook::Load() //*��ȡ�ļ��е�����*
{
	//�ļ�Ŀ¼��ǰĿ¼�µ�data.txt
	ifstream ifile(".\\data.txt");
	//���û���ļ��򣬴�ӡ��"���ļ�ʧ��"
	if (!ifile)
	{
		cout << "���ļ�ʧ��" << endl;
		return;
	}
	//�ļ����ڶ�ȡ����
	while (!ifile.eof())
	{
		Info* temp = new Info;

#ifdef  _VC2010_VER_
		ifile >> *temp;
#else
		ifile >> temp->name >> temp->gender >> temp->phone >> temp->qq >> temp->email;
#endif
		//���뵽������
		if (ifile)
		{
			AddBase(temp);
		}
	}
	//�ر���
	ifile.close();
}

void AddressBook::Save() //*�����ݱ��浽�ļ�*
{
	//���ļ����浽
	ofstream ofile(".\\data.txt", ios::trunc);
	if (!ofile)
	{
		cout << "����ʧ��" << endl;
		return;
	}
	Info* temp = head;
	//д��
	while (temp != NULL)
	{

#ifdef  _VC2010_VER_
		ofile << *temp << endl;
#else
		ofile << temp->name << " " << temp->gender << " " << temp->phone << " " << temp->qq << " " << temp->email << " " << endl;
#endif
		temp = temp->next;
	}
	ofile.close();
}

void AddressBook::Add() //*�������*
{
	cout << "��������ϵ����Ϣ: " << endl;
	Info* temp = new Info;
	// ʵ�ʿ���������Ҫ�����쳣:�ڴ�����ʧ��
	cout << "����( 1 ~ " << sizeof(temp->name) - 1 << " �ַ�): " << ends;
	cin >> temp->name;

	cout << "�Ա�(  ��   Ů ): " << ends;
	cin >> temp->gender;

	cout << "�绰( 1 ~ " << sizeof(temp->phone) - 1 << " �ַ�): " << ends;
	cin >> temp->phone;

	cout << "QQ( 1 ~ " << sizeof(temp->qq) - 1 << " �ַ�): " << ends;
	cin >> temp->qq;

	cout << "email( 0 ~ " << sizeof(temp->email) - 1 << " �ַ�): " << ends;
	cin >> temp->email;

	AddBase(temp);
}

void AddressBook::Query() //*��ѯ��ϵ�ˣ���������绰�ţ�*
{
	cout << "   ��ѡ���ѯ��ʽ    " << endl;
	cout << "   0. ������         " << endl;
	cout << "   1. �绰           " << endl;

	int choose = 0;
	cin >> choose;
	//������ҷ�ʽ
	char str[50] = { 0 };
	switch (choose)
	{
	case 0:
		cout << "����������: " << ends;
		cin >> str;
		break;
	case 1:
		cout << "������绰: " << ends;
		cin >> str;
		break;
	default:
		cout << "û�и�ѡ��" << endl;
		return;
	}
	Info* result = head;
	//�����ͷ��Ϣ
	ShowInfoTitle();
	int index = 0;
	do
	{
		//����
		result = QueryBase(result, choose, str);
		// ��ʾ��ѯ������
		if (result != NULL)
		{
			result->index = index;
			ShowInfo(result);
			index++;
			result = result->next;
		}
	} while (result != NULL);
}

void AddressBook::Modify() //*�޸���ϵ����Ϣ*
{
	cout << "��ѡ��Ҫ�޸ĵ���ϵ��(�������): " << endl;
	//���������Ϣ
	int count = ShowAllInfo();
	int index = 0;
	cin >> index;
	//�ж����������Ƿ����
	if (index < 0 || index >= count)
	{
		cout << "ѡ����Ч, û�и���ŵ���ϵ��" << endl;
		return;
	}
	//ɾ��
	DelBase(index);
	//���
	Add();
	//����޸�
}

void AddressBook::Del()	//*ɾ����ϵ��*
{
	cout << "��ѡ��Ҫɾ������ϵ��(�������): " << endl;
	//������е���Ϣ
	int count = ShowAllInfo();
	int index = 0;
	//�������
	cin >> index;
	//�ж�����Ƿ����
	if (index < 0 || index >= count)
	{
		cout << "ѡ����Ч, û�и���ŵ���ϵ��" << endl;
		return;
	}
	//������ɾ��
	DelBase(index);
}

void AddressBook::ShowAll()//*���������Ϣ*
{
	ShowAllInfo();
}

void AddressBook::AddBase(Info* pInfo)
{
	Info** parent = &head;
	Info* temp = head;

	while (temp)
	{
		// �����ֵ���
		if (strcmp(temp->name, pInfo->name) >= 0)
		{
			break;
		}

		parent = &temp->next;
		temp = temp->next;
	}
	pInfo->next = temp;
	*parent = pInfo;
}

Info* AddressBook::QueryBase(Info* start, int choose, const char* str) //*�����ֻ�绰�Ų���*
{
	while (start != NULL)
	{
		switch (choose)
		{
		case 0: // ������ƥ��
			if (strcmp(start->name, str) == 0)
			{
				return start;
			}
			else {
				start = start->next;
				continue;
			}
			break;
		case 1: // ���绰����ƥ��
			if (strcmp(start->phone, str) == 0)
			{
				return start;
			}
			else {
				start = start->next;
				continue;
			}
			break;
		default:
			break;
		}
		return NULL;
	}
	return start;
}

void AddressBook::DelBase(int index) //*�����ɾ��*
{
	Info* temp = head;
	Info** parent = &head;
	while (temp != NULL)
	{
		if (temp->index == index)
		{
			*parent = temp->next;
			delete temp;
			return;
		}
		parent = &temp->next;
		temp = temp->next;
	}
}

void AddressBook::ShowInfoTitle() //*�����ϵ����Ϣ*
{
	cout << "���          ����          �Ա�          �绰          QQ            email" << endl;
}

void AddressBook::ShowInfo(const Info* pInfo)
{
	cout << setiosflags(ios::left) // ��������
		<< setw(14) << pInfo->index
		<< setw(14) << pInfo->name
		<< setw(14) << pInfo->gender
		<< setw(14) << pInfo->phone
		<< setw(14) << pInfo->qq
		<< setw(14) << pInfo->email << endl;
}

int AddressBook::ShowAllInfo() //*������*
{
	int index = 0;
	Info* temp = head;

	ShowInfoTitle();
	while (temp)
	{
		temp->index = index;
		index++;

		ShowInfo(temp);
		temp = temp->next;
	}
	return index;
}

void exit()//�˳�����
{
	cout << "        ****************************************************************" << endl;
	cout << "        *******************          ллʹ��          *****************" << endl;
	cout << "        ****************************************************************" << endl;
}


int menu()//���˵�����
{
	system("cls");//����
	cout << "        ****************************************************************" << endl;
	cout << "        |                                                              |" << endl;
	cout << "        |                    ��ӭ��¼ͨѶ¼����ϵͳ                    |" << endl;
	cout << "        |                                                              |" << endl;
	cout << "        ****************************************************************" << endl;
	cout << "        |                      ��1 . �����ϵ��                        |" << endl;
	cout << "        |                                                              |" << endl;
	cout << "        |                      ��2 . ��ѯ��ϵ��                        |" << endl;
	cout << "        |                                                              |" << endl;
	cout << "        |                      ��3 . �޸���ϵ��                        |" << endl;
	cout << "        |                                                              |" << endl;
	cout << "        |                      ��4 . ɾ����ϵ��                        |" << endl;
	cout << "        |                                                              |" << endl;
	cout << "        |                      ��5 . ��ʾ������ϵ��                    |" << endl;
	cout << "        |                                                              |" << endl;
	cout << "        |                      ��6 . ���浽�ļ�                        |" << endl;
	cout << "        |                                                              |" << endl;
	cout << "        |                      ��0 . �˳�ϵͳ                          |" << endl;
	cout << "        ****************************************************************" << endl;

	int m = 0;
	do
	{
		cout << "������ѡ��0-8\n";
		cin >> m;
	} while (m < 0 || m > 8);

	return m;
}