#include<iostream>
using namespace std;
class LinkNode {
public:
	int data = 0;
	LinkNode* link;
	LinkNode(LinkNode* ptr = NULL)
	{
		link = ptr;
	}
	LinkNode(const int& item, LinkNode* ptr = NULL)
	{
		data = item;
		link = ptr;
	}
};
class List {
public:
	List()
	{
		first = new LinkNode;
		if (first == NULL)
		{
			cout << "�����ڴ�ʧ��" << endl;
			exit(-1);
		}
	}
	~List()
	{
		LinkNode* q;
		while (first->link != NULL)
		{
			q = first->link;
			first->link = q->link;
			delete q;
		}
	}
	
	LinkNode* getHead()const		//ȡ��ͷ���
	{
		return first;
	}
	void makeEmpty();
	void Input();
private:
	LinkNode* first;
};

//�������
void List::makeEmpty()
{
	LinkNode* q;
	while (first->link != NULL)
	{
		q = first->link;
		first->link = q->link;
		delete q;
	}
}

//����ǽ�����������
void List::Input()
{
	LinkNode* newNode, * last;
	int value = 0;
	last = first;
	while (value != -1)
	{
		cin >> value;
		if (!cin.good())
		{
			cout << "�����������������" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
			makeEmpty();
			last=first;
			continue;
		}
		if (value == -1)
			break;
		newNode = new LinkNode(value);
		if (newNode == NULL)
		{
			cout << "�����ڴ�ռ�ʧ��" << endl;
			exit(-1);
		}
		last->link = newNode;
		last = newNode;
	}
	last->link = NULL;
}

//�󽻼�
void merge(LinkNode *s1,LinkNode *s2,LinkNode *s3)
{
	s1 = s1->link;
	s2 = s2->link;
	s3->link = NULL;
	LinkNode* last = s3;
	while ((s1 != NULL) && (s2 != NULL))
	{
		if ((s1->data) < (s2->data))
		{
			s1 = s1->link;
		}
		else if ((s1->data) > (s2->data))
		{
			s2 = s2->link;
		}
		else if ((s1->data) == (s2->data))
		{
			LinkNode* newNode = new LinkNode;
			if (newNode == NULL)
			{
				cout << "�����ڴ�ռ�ʧ��" << endl;
				exit(-1);
			}
			newNode->data = s1->data;
			last->link = newNode;
			last = newNode;
			s1 = s1->link;
			s2 = s2->link;
		}
	}
	last->link = NULL;
}
int main()
{
	List S1, S2, S3;
	cout << "������ǽ�������S1����-1������-1�����룩" << endl;
	S1.Input();
	cout << "������ǽ�������S2����-1������-1�����룩" << endl;
	S2.Input();
	merge(S1.getHead(), S2.getHead(), S3.getHead());
	if (S3.getHead()->link == NULL)
	{
		cout << "NULL" << endl;
	}
	else
	{
		LinkNode* current = S3.getHead()->link;
		while (current != NULL)
		{
			cout << current->data << " ";
			current = current->link;
		}
		cout << endl;
	}
	return 0;
}
