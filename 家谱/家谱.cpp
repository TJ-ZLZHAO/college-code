#include <iostream>
#include <cstring>
using namespace std;

template <class T>
struct TreeNode {
	T data;
	TreeNode<T>* firstChild, * nextBrother;
	TreeNode(T value = 0, TreeNode<T>* fc = NULL, TreeNode<T>* nb = NULL) :data(value), firstChild(fc), nextBrother(nb) {}
};

template <class T>
class Tree {
private:
	TreeNode<T>* root, * current;
	void destroy(TreeNode<T>* p);						//ɾ����pΪ��������
public:
	Tree()
	{
		root = current = NULL;
	}
	Tree(T value)
	{
		root = new TreeNode<T>(value);
		if (root == NULL)
		{
			cout << "����ռ�ʧ��" << endl;
			exit(-1);
		}
		current = root;
	}
	~Tree()
	{
		destroy(root);
	}
	bool Root();										//Ѱ�Ҹ���ʹ���Ϊ��ǰ�ڵ�
	bool IsEmpty()										//�п�
	{
		return root == NULL;
	}
	T getData()
	{
		return current->data;
	}
	bool FirstChild();									//Ѱ��current�ĵ�һ����Ů����ʹ���Ϊ��ǰ�ڵ�
	bool NextBrother();									//Ѱ��current����һ���ֵܣ���ʹ���Ϊ��ǰ�ڵ�
	bool Parent();										//Ѱ��current�ĸ��ڵ㣬��ʹ���Ϊ��ǰ�ڵ�
	bool Find(TreeNode<T>* p, T value);					//����pΪ����������value����ʹ���Ϊ��ǰ�ڵ�
	bool FindParent(TreeNode<T>* t, TreeNode<T>* p);	//�ڸ�Ϊ*t��������*p�ĸ��ڵ㣬��ʹ���Ϊ��ǰ�ڵ�
	void InsertFamilyMember();							//��Ӽ�ͥ��Ա
	void RemovesubTree();								//��ɢ��ͥ
	void CompleteFamilyTree();							//���Ƽ���
	void changeName();									//���ļ�ͥ��Ա����
	void MemberMessage();								//��������
	void printfirstChildren();							//��ӡ��һ����Ů

};

template <class T>
bool Tree<T>::Root()									//Ѱ�Ҹ���ʹ���Ϊ��ǰ�ڵ�
{
	if (root == NULL)
	{
		current = NULL;
		return false;
	}
	else
	{
		current = root;
		return true;
	}
}

template <class T>
bool Tree<T>::Parent()									//Ѱ��current�ĸ��ڵ㣬��ʹ���Ϊ��ǰ�ڵ�
{
	TreeNode<T>* p = current;
	if (current == NULL || current == root)
	{
		current = NULL;
		return false;
	}
	return FindParent(root, p);
}

template <class T>
bool Tree<T>::FindParent(TreeNode<T>* t, TreeNode<T>* p)//�ڸ�Ϊ*t��������*p�ĸ��ڵ㣬��ʹ���Ϊ��ǰ�ڵ�
{
	TreeNode<T>* q = t->firstChild;
	bool succ;
	while (q != NULL && q != p)
	{
		if ((succ = FindParent(q, p)) == true)
			return succ;
		q = q->nextBrother;
	}
	if (q != NULL && q == p)
	{
		current = t;
		return true;
	}
	else
	{
		current = NULL;
		return false;
	}
}

template <class T>
bool Tree<T>::FirstChild()								//Ѱ��current�ĵ�һ����Ů����ʹ���Ϊ��ǰ�ڵ�
{
	if (current != NULL && current->firstChild != NULL)
	{
		current = current->firstChild;
		return true;
	}
	current = NULL;
	return false;
}

template <class T>
bool Tree<T>::NextBrother()								//Ѱ��current����һ���ֵܣ���ʹ���Ϊ��ǰ�ڵ�
{
	if (current != NULL && current->nextBrother != NULL)
	{
		current = current->nextBrother;
		return true;
	}
	current = NULL;
	return false;
}

template <class T>
bool Tree<T>::Find(TreeNode<T>* p, T value)				//����pΪ����������value����ʹ���Ϊ��ǰ�ڵ�
{
	bool result = false;
	if (p->data == value)
	{
		result = true;
		current = p;
	}
	else
	{
		TreeNode<T>* q = p->firstChild;
		while (q != NULL && !(result = Find(q, value)))
			q = q->nextBrother;
	}
	return result;
}

template <class T>
void Tree<T>::destroy(TreeNode<T>* p)					//ɾ����pΪ��������
{
	if (p != NULL)
	{
		destroy(p->firstChild);
		destroy(p->nextBrother);
		delete p;
	}
}

template <class T>
void Tree<T>::InsertFamilyMember()						//��Ӽ�ͥ��Ա
{
	T name;
	cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�������";
	while (1)
	{
		cin >> name;
		if (!cin.good())
		{
			cout << "�����������������" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
			continue;
		}
		break;
	}
	if (Find(root, name) == false)
		cout << "���޴���" << endl;
	else
	{
		cout << "������" << current->data << "����ӵĶ��ӣ���Ů������������";
		string s;
		while (1)
		{
			cin >> s;
			if (!cin.good())
			{
				cout << "�����������������" << endl;
				cin.clear();
				cin.ignore(65535, '\n');
				continue;
			}
			break;
		}
		TreeNode<T>* newNode = new TreeNode<T>(s);
		if (newNode == NULL)
		{
			cout << "����ռ�ʧ��" << endl;
			exit(-1);
		}
		if (current->firstChild == NULL)
			current->firstChild = newNode;
		else
		{
			TreeNode<T>* temp = current->firstChild;
			while (temp->nextBrother)
				temp = temp->nextBrother;
			temp->nextBrother = newNode;
		}
		printfirstChildren();
	}
}

template <class T>
void Tree<T>::RemovesubTree()							//ɾ����pΪ��������,�������ڵ�
{
	T name;
	cout << "������Ҫ��ɢ��ͥ���˵�������";
	while (1)
	{
		cin >> name;
		if (!cin.good())
		{
			cout << "�����������������" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
			continue;
		}
		break;
	}
	if (Find(root, name) == false)
		cout << "���޴���" << endl;
	else
	{
		cout << "Ҫ��ɢ��ͥ�����ǣ�" << current->data << endl;
		printfirstChildren();
		destroy(current->firstChild);
		current->firstChild = NULL;
	}
}

template <class T>
void Tree<T>::CompleteFamilyTree()						//���Ƽ���
{
	T name;
	cout << "������Ҫ������ͥ���˵�����:";
	while (1)
	{
		cin >> name;
		if (!cin.good())
		{
			cout << "�����������������" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
			continue;
		}
		break;
	}
	if (Find(root, name) == false)
		cout << "���޴���" << endl;
	else
	{
		if (current->firstChild)
			cout << "�ѽ�����ͥ���޷��ٽ���" << endl;
		else
		{
			cout << "������" << current->data << "�Ķ�Ů������";
			int n;
			while (1)
			{
				cin >> n;
				if (!cin.good() || n < 0)
				{
					cout << "�����������������" << endl;
					cin.clear();
					cin.ignore(65535, '\n');
					continue;
				}
				break;
			}
			if (n != 0)
			{
				cout << "����������" << current->data << "�Ķ�Ů��������";
				string s;
				while (1)
				{
					cin >> s;
					if (!cin.good())
					{
						cout << "�����������������" << endl;
						cin.clear();
						cin.ignore(65535, '\n');
						continue;
					}
					break;
				}
				TreeNode<T>* newNode = new TreeNode<T>(s);
				if (newNode == NULL)
				{
					cout << "����ռ�ʧ��" << endl;
					exit(-1);
				}
				current->firstChild = newNode;
				TreeNode<T>* temp = current->firstChild;
				for (int i = 1; i < n; i++)
				{
					string s;
					while (1)
					{
						cin >> s;
						if (!cin.good())
						{
							cout << "�����������������" << endl;
							cin.clear();
							cin.ignore(65535, '\n');
							continue;
						}
						break;
					}
					TreeNode<T>* newNode = new TreeNode<T>(s);
					if (newNode == NULL)
					{
						cout << "����ռ�ʧ��" << endl;
						exit(-1);
					}
					while (temp->nextBrother)
						temp = temp->nextBrother;
					temp->nextBrother = newNode;
				}
				printfirstChildren();
			}
		}
	}
}

template <class T>
void Tree<T>::changeName()								//���ļ�ͥ��Ա����
{
	T name;
	cout << "������Ҫ�����������˵�����:";
	while (1)
	{
		cin >> name;
		if (!cin.good())
		{
			cout << "�����������������" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
			continue;
		}
		break;
	}
	if (Find(root, name) == false)
		cout << "���޴���" << endl;
	else
	{
		cout << "��������ĺ������:";
		while (1)
		{
			cin >> current->data;
			if (!cin.good())
			{
				cout << "�����������������" << endl;
				cin.clear();
				cin.ignore(65535, '\n');
				continue;
			}
			break;
		}
		cout << name << "�Ѹ���Ϊ" << current->data << endl;
	}
}

template <class T>
void Tree<T>::MemberMessage()							//��������
{
	T name;
	cout << "������Ҫ�鿴�˵�����:";
	while (1)
	{
		cin >> name;
		if (!cin.good())
		{
			cout << "�����������������" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
			continue;
		}
		break;
	}
	if (Find(root, name) == false)
		cout << "���޴���" << endl;
	else
	{
		cout << "������" << current->data << endl;
		if (Parent()) 
		{
			cout << "���ף�" << current->data << endl;
			if (current->firstChild->nextBrother != NULL) 
			{
				TreeNode<T>* temp = current->firstChild;
				cout << "�ֵܣ�";
				while(temp)
				{
					if (temp->data != name)
						cout << temp->data << "    ";
					temp = temp->nextBrother;
				}
				cout << endl;
			}
		}
		Find(root, name);
		printfirstChildren();
	}
}

template <class T>
void Tree<T>::printfirstChildren()						//��ӡ��һ����Ů
{
	if (!current->firstChild)
		cout << current->data << "Ŀǰ��δ�к��";
	else
	{
		cout << current->data << "�ĵ�һ��������:";
		TreeNode<T>* temp = current->firstChild;
		while(temp) {
			cout << temp->data << "   ";
			temp = temp->nextBrother;
		}
	}
}

int main() {
	char ch;
	cout << "**                         ���׹���ϵͳ                         **" << endl;
	cout << "==================================================================" << endl;
	cout << "**                     ��ѡ��Ҫִ�еĲ�����                     **" << endl;
	cout << "**                     A --- ���Ƽ�ͥ                           **" << endl;
	cout << "**                     B --- ��Ӽ�ͥ��Ա                       **" << endl;
	cout << "**                     C --- ��ɢ�ֲ���Ա                       **" << endl;
	cout << "**                     D --- ���ļ�ͥ��Ա����                   **" << endl;
	cout << "**                     E --- �鿴������Ϣ                       **" << endl;
	cout << "**                     F --- �˳�ϵͳ                           **" << endl;
	cout << "==================================================================" << endl;
	cout << "���Ƚ���һ�����ף�" << endl;
	cout << "���������ȵ�������";

	string name;
	while (1)
	{
		cin >> name;
		if (!cin.good())
		{
			cout << "�����������������" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
			continue;
		}
		break;
	}
	Tree<string> Family(name);
	cout << "�˼��׵������ǣ�" << Family.getData() << endl << endl;
	cout << "��ѡ��Ҫִ�еĲ���:";
	cin >> ch;
	while (ch != 'F') {
		switch (ch) {
			case 'A':
				Family.CompleteFamilyTree();
				break;
			case 'B':
				Family.InsertFamilyMember();
				break;
			case 'C':
				Family.RemovesubTree();
				break;
			case 'D':
				Family.changeName();
				break;
			case 'E':
				Family.MemberMessage();
				break;
			default:
				cout << "�����������������";
				break;
		}
		cout << endl << endl;
		cout << "��ѡ��Ҫִ�еĲ���:";
		cin>>ch;
	}
	return 0;
}