#include <iostream>
#include <stdlib.h>
#include <cstring>
#include <iomanip>
using namespace std;
class LinkNode {
public:
	string studentID; //��ʾѧ������
	string studentName;//��ʾѧ������
	string student_sex;//��ʾѧ���Ա�
	string student_age;//��ʾѧ������
	string student_category;//��ʾѧ����������
	LinkNode* link;//�������ָ����
	LinkNode(string sID = "", string sName = "", string sex = "", string age = "", string category = "", LinkNode* ptr = NULL) :
		studentID(sID),
		studentName(sName),
		student_sex(sex),
		student_age(age),
		student_category(category),
		link(ptr)
	{}
};
class List {
public:
	List();							 //���캯��
	List(string sID, string sName, string sex, string age, string category, LinkNode* ptr);				 //���ι��캯��
	List(List& L);					 //�������ƹ��캯��
	~List();						//��������
	void makeEmpty();				//���������
	LinkNode* getHead()const;		//ȡ��ͷ���
	LinkNode* Search();		//���ҿ���ΪID�Ŀ����ĵ�ַ������
	bool findData();		//���ҿ���ΪID�Ŀ���
	bool setData();			//�޸Ŀ���ΪID�Ŀ�������
	bool Insert();		//����
	bool Remove();			//ɾ������ΪID�Ŀ���
	bool check(string ID, LinkNode* temp);					//����
	void Input(int studentNumber);	//ͨ����巨��������
	void display();					//���
protected:
	LinkNode* first;
	int Length = 0;
};



void readData(string& sID, string& sName, string& sex, string& age, string& category)
{
	while (1)
	{
		cin >> sID >> sName >> sex >> age >> category;
		if (!cin.good())
		{
			cout << "�����������������" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}
}
void print(string sID, string sName, string sex, string age, string category)
{
	cout << setw(10) << setfill(' ') << sID;
	cout << setw(10) << setfill(' ') << sName;
	cout << setw(8) << setfill(' ') << sex;
	cout << setw(6) << setfill(' ') << age;
	cout << setw(20) << setfill(' ') << category << endl;
}
void readData(string& sID, string& sName, string& sex, string& age, string& category);
//���캯��
List::List()
{
	first = new LinkNode;
	if (first == NULL)
	{
		cout << "�����ڴ�ʧ��" << endl;
		exit(-1);
	}
}

//���ι��캯��
List::List(string sID, string sName, string sex, string age, string category, LinkNode* ptr)
{
	first = new LinkNode(sID, sName, sex, age, category, ptr);
	if (first == NULL)
	{
		cout << "�����ڴ�ʧ��" << endl;
		exit(-1);
	}
}

//��������
List::~List()
{
	LinkNode* q;
	while (first->link != NULL)
	{
		q = first->link;
		first->link = q->link;
		delete q;
	}
	Length = 0;
}

//�������ƹ��캯��
List::List(List& L)
{
	string sID, sName, sex, age, category;
	LinkNode* srcptr = L.getHead();
	LinkNode* destptr = first = new LinkNode;
	while (srcptr->link != NULL)
	{
		sID = srcptr->link->studentID;
		sName = srcptr->link->studentName;
		sex = srcptr->link->student_sex;
		age = srcptr->link->student_age;
		category = srcptr->link->student_category;
		destptr->link = new LinkNode(sID, sName, sex, age, category);
		if (destptr->link == NULL)
		{
			cout << "�����ڴ�ʧ��" << endl;
			exit(-1);
		}
		destptr = destptr->link;
		srcptr = srcptr->link;
	}
	destptr->link = NULL;
}

//���������
void List::makeEmpty()
{
	LinkNode* q;
	while (first->link != NULL)
	{
		q = first->link;
		first->link = q->link;
		delete q;
	}
	Length = 0;
}

//ȡ��ͷ���
LinkNode* List::getHead()const
{
	return first;
}

//���ҿ���ΪID�Ŀ����Ľ���ַ������
LinkNode* List::Search()
{
	string ID;
	while (1)
	{
		cin >> ID;
		if (!cin.good())
		{
			cout << "����������������룺";
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}
	LinkNode* current = first->link;
	while (current != NULL)
	{
		if (current->studentID == ID)
			break;
		else
			current = current->link;
	}
	return current;
}

//���ҿ���ΪID�Ŀ���
bool List::findData()
{
	LinkNode* current = Search();
	if (current == NULL)
	{
		cout << "��Ҫ���ҵĿ���������" << endl;
		return false;
	}
	else
	{
		cout << setw(10) << setfill(' ') << "����";
		cout << setw(10) << setfill(' ') << "����";
		cout << setw(8) << setfill(' ') << "�Ա�";
		cout << setw(6) << setfill(' ') << "����";
		cout << setw(20) << setfill(' ') << "��������" << endl;
		cout << setw(10) << setfill(' ') << current->studentID;
		cout << setw(10) << setfill(' ') << current->studentName;
		cout << setw(8) << setfill(' ') << current->student_sex;
		cout << setw(6) << setfill(' ') << current->student_age;
		cout << setw(20) << setfill(' ') << current->student_category << endl;
	}
	return true;
}

//�޸Ŀ���ΪID�Ŀ�������
bool List::setData()
{
	string ID, sID, sName, sex, age, category;
	LinkNode* current = Search();
	if (current != NULL)
	{
		while (1)
		{
			cout << "������Ҫ�޸ĵĿ����Ŀ��ţ��������Ա����䣬�������" << endl;
			readData(sID, sName, sex, age, category);
			if (check(sID, current) == true)
				break;
			else
				cout << "�޸Ŀ��������п����ظ�������������" << endl;
		}
		current->studentID = sID;
		current->studentName = sName;
		current->student_sex = sex;
		current->student_age = age;
		current->student_category = category;
		display();
	}
	else
	{
		cout << "��Ҫ�޸ĵĿ���������" << endl;
		return false;
	}
	return true;
}

//����
bool List::Insert()
{
	int studentnumber;
	string sID, sName, sex, age, category;
	LinkNode* current = first;
	while (1)
	{
		cout << "������Ҫ����Ŀ���λ��[1-" << Length + 1 << "]��";
		cin >> studentnumber;
		if (!cin.good() || studentnumber > Length + 1 || studentnumber <= 0)
		{
			cout << "�������λ�ò��Ϸ������������룡" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}
	for (int i = 0; i < studentnumber - 1; i++)
		current = current->link;
	while (1)
	{
		cout << "������Ҫ���뿼���Ŀ��ţ��������Ա����䣬�������" << endl;
		readData(sID, sName, sex, age, category);
		if (check(sID, current) == true)
			break;
		else
			cout << "���뿼�������п����ظ�������������" << endl;
	}
	LinkNode* newNode = new LinkNode(sID, sName, sex, age, category);
	if (newNode == NULL)
	{
		cerr << "����ռ�ʧ��" << endl;
		exit(-1);
	}
	Length++;
	newNode->link = current->link;
	current->link = newNode;
	display();
	return true;
}

//ɾ��
bool List::Remove()
{
	string ID, sID, sName, sex, age, category;
	LinkNode* current = first;
	while (1)
	{
		cin >> ID;
		if (!cin.good())
		{
			cout << "����������������룺";
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}
	while (current->link != NULL)
	{
		if (current->link->studentID == ID)
			break;
		else
			current = current->link;
	}
	if (current == NULL || current->link == NULL)
	{
		cout << "��Ҫɾ����ѧ��������" << endl;
		return false;
	}
	LinkNode* del = current->link;
	current->link = del->link;
	sID = del->studentID;
	sName = del->studentName;
	sex = del->student_sex;
	age = del->student_age;
	category = del->student_category;
	cout << "��ɾ���Ŀ�������Ϣ�ǣ�";
	print(sID, sName, sex, age, category);
	display();
	Length--;
	delete del;
	return true;
}

//���
void List::display()
{
	LinkNode* current = first->link;
	cout << setw(10) << setfill(' ') << "����";
	cout << setw(10) << setfill(' ') << "����";
	cout << setw(8) << setfill(' ') << "�Ա�";
	cout << setw(6) << setfill(' ') << "����";
	cout << setw(20) << setfill(' ') << "��������" << endl;
	while (current != NULL)
	{
		cout << setw(10) << setfill(' ') << current->studentID;
		cout << setw(10) << setfill(' ') << current->studentName;
		cout << setw(8) << setfill(' ') << current->student_sex;
		cout << setw(6) << setfill(' ') << current->student_age;
		cout << setw(20) << setfill(' ') << current->student_category << endl;
		current = current->link;
	}
}

//���ú�巨��������
void List::Input(int studentnumber)
{
	LinkNode* newNode, * last = NULL;
	string sID, sName, sex, age, category;
	makeEmpty();
	cout << "���������뿼���Ŀ��ţ��������Ա����䣬�������" << endl;
	last = first;
	for (int i = 0; i < studentnumber; i++)
	{
		while (1)
		{
			readData(sID, sName, sex, age, category);
			if (check(sID, last) == true)
				break;
			else
				cout << "���뿼�������п����ظ�������������" << endl;
		}
		newNode = new LinkNode(sID, sName, sex, age, category);
		if (newNode == NULL)
		{
			cerr << "����ռ�ʧ��" << endl;
			exit(-1);
		}
		Length++;
		last->link = newNode;
		last = newNode;
	}
	last->link = NULL;
}

//���Ų���
bool List::check(string ID, LinkNode* temp)
{
	LinkNode* current = first->link;
	while (current != NULL)
	{
		if (current->studentID == ID && current != temp)
			return false;
		current = current->link;
	}
	return true;
}

int main()
{
	int studentNumber, flag = -1;
	cout << setiosflags(ios::left);
	cout << "�����뽨��������Ϣϵͳ��" << endl;
	while (1)
	{
		cout << "�����뿼��������";
		cin >> studentNumber;
		if (!cin.good() || studentNumber <= 0)
		{
			cout << "������һ��������" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}
	List stuTest;
	stuTest.Input(studentNumber);
	while (flag != 0)
	{
		cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊ�˳���" << endl;
		while (1)
		{
			cout << "��ѡ����Ҫ���еĲ�����" << endl;
			cin >> flag;
			if (!cin.good() || flag > 5 || flag < 0)
			{
				cout << "��Ǹ������Ҫ�Ĳ��������ڣ����������룡" << endl;
				cin.clear();
				cin.ignore(65535, '\n');
			}
			else
				break;
		}
		switch (flag)
		{
			case 1:
				stuTest.Insert();
				break;
			case 2:
				cout << "��������Ҫɾ���Ŀ����Ŀ��ţ�";
				stuTest.Remove();
				break;
			case 3:
				cout << "��������Ҫ���ҵĿ����Ŀ��ţ�";
				stuTest.findData();
				break;
			case 4:
				cout << "��������Ҫ�޸ĵĿ����Ŀ��ţ�";
				stuTest.setData();
				break;
			case 5:
				stuTest.display();
				break;
			case 0:
				break;
		}
		if (flag == 0)
			break;
	}
	return 0;
}