#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

const int DefaultSize = 200;
const int DefaultVertics = 100;

template <class T>
class LinkNode {
public:
	T data;
	LinkNode<T>* link;
	LinkNode(LinkNode<T>* ptr = NULL)
	{
		link = ptr;
	}
	LinkNode(const T& item, LinkNode<T>* ptr = NULL)
	{
		data = item;
		link = ptr;
	}
};

template <class T>
class LinkedQueue {
public:
	LinkedQueue() :rear(NULL), front(NULL) {}	//���캯���������ն���
	~LinkedQueue()								//��������
	{
		makeEmpty();
	}
	bool EnQueue(const T& x);					//��x���뵽������
	bool DeQueue(T& x);							//ɾ����ͷԪ��,x������ֵ
	bool getFront(T& x)const;					//�鿴��ͷԪ�ص�ֵ
	void makeEmpty();							//�ÿն���
	bool IsEmpty()const							//�ж��пշ�
	{
		return(front == NULL) ? true : false;
	}
	int getSize()const;							//�����Ԫ�ظ���
	friend ostream& operator<<(ostream& os, LinkedQueue<T>& Q);//�������
protected:
	LinkNode<T>* front, * rear;
};

template <class T>
void LinkedQueue<T>::makeEmpty()
{
	LinkNode<T>* p;
	while (front != NULL)
	{
		p = front;
		front = front->link;
		delete p;
	}
}

template <class T>
bool LinkedQueue<T>::EnQueue(const T& x)
{
	if (front == NULL)
	{
		front = rear = new LinkNode<T>(x);
		if (front == NULL)
			return false;
	}
	else
	{
		rear->link = new LinkNode<T>(x);
		if (rear->link == NULL)
			return false;
		rear = rear->link;
	}
	return true;
}

template <class T>
bool LinkedQueue<T>::DeQueue(T& x)
{
	if (IsEmpty() == true)
		return false;
	LinkNode<T>* p = front;
	x = front->data;
	front = front->link;
	delete p;
	return true;
}

template <class T>
bool LinkedQueue<T>::getFront(T& x)const
{
	if (IsEmpty() == true)
		return false;
	x = front->data;
	return true;
}

template <class T>
int LinkedQueue<T>::getSize()const
{
	LinkNode<T>* p = front;
	int k = 0;
	while (p != NULL)
	{
		p = p->link;
		k++;
	}
	return k;
}

template <class T>
ostream& operator <<(ostream& os, LinkedQueue<T>& Q)
{
	os << "�����е�Ԫ�ظ���Ϊ" << Q.getSize() << endl;
	LinkNode<T>* p = Q.front;
	int i = 0;
	while (p != NULL)
	{
		os << ++i << ":" << p->data << endl;
		p = p->link;
	}
	return os;
}

template <class T>
class Graphmtx {
	friend istream& operator >>(istream& in, Graphmtx<T>& G);
	friend ostream& operator<<(ostream& out, Graphmtx<T>& G);
public:
	Graphmtx(int sz = DefaultVertics);
	~Graphmtx()
	{
		delete[]VerticesList;
		delete[]Edge;
	}
	T getValue(int i)
	{
		return VerticesList[i];
	}
	int getWeight(int v1, int v2)
	{

		return v1 != -1 && v2 != -1 ? Edge[v1][v2] : 0;
	}
	bool GraphEmpty()const
	{
		if (numEdges == 0)
			return true;
		else
			return false;
	}
	bool GraphFull()const
	{
		if (numVertices == maxVertices || numEdges == maxVertices * (maxVertices - 1))
			return true;
		else
			return false;
	}
	int NumberOfVertices()
	{
		return numVertices;
	}
	int NumberOfEdges()
	{
		return numEdges;
	}
	int getVertexPos(T vertex)
	{
		for (int i = 0; i < numVertices; i++)
			if (VerticesList[i] == vertex)
				return i;
		return -1;
	}
	bool check(T vertex)
	{
		for (int i = 0; i < numVertices; i++)
			if (VerticesList[i] == vertex)
				return true;
		return false;
	}
	int getFirstNeighbor(int v);
	int getNextNeighbor(int v, int w);
	bool insertVertex(const T& vertex);
	bool insertEdge(int v1, int v2);
	bool removeVertex(int v);
	bool removeEdge(int v1, int v2);
private:
	int maxVertices;
	int numEdges;
	int numVertices;
	T* VerticesList;
	int** Edge;
};

template <class T>
Graphmtx<T>::Graphmtx(int sz)
{
	maxVertices = sz;
	numVertices = 0;
	numEdges = 0;
	int i, j;
	VerticesList = new T[maxVertices];
	Edge = (int**)new int * [maxVertices];
	for (i = 0; i < maxVertices; i++)
		Edge[i] = new int[maxVertices];
	for (i = 0; i < maxVertices; i++)
		for (j = 0; j < maxVertices; j++)
			Edge[i][j] = 0;
}
template <class T>
int Graphmtx<T>::getFirstNeighbor(int v)
{
	if (v != -1)
	{
		for (int col = 0; col < numVertices; col++)
			if (Edge[v][col] != 0)
				return col;
	}
	return -1;
}

template<class T>
int Graphmtx<T>::getNextNeighbor(int v, int w)		 //��������v��ĳ�ڽӶ���w����һ���ڽӶ���
{
	if (v != -1 && w != -1)
	{
		for (int col = w + 1; col < numVertices; col++)
			if (Edge[v][col] != 0)
				return col;
	}
	return -1;
}

template <class T>
bool Graphmtx<T>::insertVertex(const T& vertex)	//���˶��� vertex
{

	if (numVertices == maxVertices) 	// �������, ������
		return false;
	VerticesList[numVertices++] = vertex;
	return true;
}
template <class T>
bool Graphmtx<T>::removeVertex(int v)		//ɾȥ����v����������������ı�
{
	if (v < 0 || v >= numVertices)//v����ͼ��, ��ɾ��
		return false;
	if (numVertices == 1)//ֻʣһ������, ��ɾ��
		return false;
	int i, j;
	VerticesList[v] = VerticesList[numVertices - 1];//�������ɾ���ý��
	for (i = 0; i < numVertices; i++)// ��ȥ��v���������
		if (Edge[i][v] != 0)//�����һ�����v��
			numEdges--;
	for (i = 0; i < numVertices; i++)
		Edge[i][v] = Edge[i][numVertices - 1];
	numVertices--;		//��������1
	for (j = 0; j < numVertices; j++)//����������v��
		Edge[v][j] = Edge[numVertices][j];
	return true;
}
template <class T>
bool Graphmtx<T>::insertEdge(int v1, int v2)
{
	if (v1 > -1 && v1< numVertices && v2>-1 && v2 < numVertices && Edge[v1][v2] == 0)
	{
		Edge[v1][v2] = 1;
		numEdges++;
		return true;
	}
	else
		return false;
}

template <class T>
bool Graphmtx<T>::removeEdge(int v1, int v2)	//��ͼ��ɾȥ��(v1,v2)
{
	if (v1 > -1 && v1 < numVertices && v2> -1 && v2 < numVertices && Edge[v1][v2] != 0)
	{
		Edge[v1][v2] = 0;
		numEdges--;
		return true;
	}
	else
		return false;
}

//ͨ��������������in����n��������Ϣ��e������ߵ���Ϣ�������ڽӾ����ʾ��ͼG,�ڽӾ����ʼ���Ĺ����Ѿ��ڹ��캯������ɡ�
template <class T>
istream& operator>> (istream& in, Graphmtx<T>& G)
{
	int i, j, k, n, m;
	T e1, e2;
	in >> n >> m;
	for (i = 0; i < n; i++) //�������������
	{
		in >> e1;
		G.insertVertex(e1);
	}
	i = 0;
	while (i < m)
	{
		in >> e1 >> e2;
		j = G.getVertexPos(e1);
		k = G.getVertexPos(e2);
		if (j == -1 || k == -1)
			cout << "�����˵���Ϣ������������!" << endl;
		else
		{
			G.insertEdge(j, k);
			i++;
		}
	}
	return in;
}

template <class T>
ostream& operator <<(ostream& out, Graphmtx<T>& G)
{
	int i, j, n, m;
	T e1, e2;
	int w;
	n = G.NumberOfVertices();
	m = G.NumberOfEdges();
	out << n << "," << m << endl;
	for (int i = 0; i < n; i++)
		for (j = i + 1; j < n; j++)
		{
			w = G.getWeight(i, j);
			if (w != 0)
			{
				e1 = G.getValue(i);
				e2 = G.getValue(j);
				out << "(" << e1 << "," << e2 << endl;
			}
		}
	return out;
}

class Timetable {
public:
	string courseID;
	string coursename;
	short times;
	short term;
	bool flag = false;
	short pre = 0;
	string Prerequisite[DefaultVertics];
	Timetable(string ID = "", string name = "", short ti = 0, short te = 0) :courseID(ID), coursename(name), times(ti), term(te)
	{
		for (int i = 0; i < DefaultVertics; i++)
			Prerequisite[i] = "";
	}
};

struct table {
	string name;
	short cost = 0;
	bool flag = false;
};

Timetable list[DefaultVertics];
table stu_table[10][5];

void initialize()
{
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 5; j++)
		{
			stu_table[i][j].name = "";
			stu_table[i][j].cost = 1;
			stu_table[i][j].flag = false;
		}
}

void print(const int& term, ofstream& out)
{
	out << "��" << term << "ѧ�ڿα�" << endl;
	out << "            ����һ              ���ڶ�              ������              ������              ������" << endl;
	for (int i = 0; i < 9; i++)
	{
		out << "��" << i + 1 << "��" << "     ";
		for (int j = 0; j < 5; j++)
			out << setw(20) << setiosflags(ios::left) << stu_table[i][j].name;
		out << endl;
	}
	out << "��" << 10 << "��" << "    ";
	for (int j = 0; j < 5; j++)
		out << setw(20) << setiosflags(ios::left) << stu_table[9][j].name;
	out << endl;
	out << endl << endl;
}

bool loopjudge(int* count,int n)
{
	int i;
	for (i = 0; i < n; i++)
		if (count[i] == 0)
			break;
	if (i >= n)
	{
		cout << "�γ����л�·" << endl;
		return false;
	}
	return true;
}

int lasttime()
{
	int count = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 5; j++)
			if (stu_table[i][j].flag == false)
				count++;
	return count;
}

void insertcourse(int n)
{
	int weekday = 0, i, j, judge = 0;
	for (j = 0; j < 5;)
	{
		if (list[n].times == 0 || list[n].times < 3 || list[n].times == 4)
			break;
		judge = 0;
		for (i = 2; i < 10 && list[n].times != 0;)
		{
			if (stu_table[i][j].flag == false && stu_table[i + 1][j].flag == false && stu_table[i + 2][j].flag == false)
			{
				stu_table[i][j].name = list[n].coursename;
				stu_table[i + 1][j].name = list[n].coursename;
				stu_table[i + 2][j].name = list[n].coursename;
				stu_table[i][j].flag = true;
				stu_table[i + 1][j].flag = true;
				stu_table[i + 2][j].flag = true;
				list[n].times -= 3;
				judge = 1;
				if (list[n].times > 0)
				{
					j = (j - 3 > 0) ? (j - 3) : (j + 2);
					break;
				}
				if (list[n].times == 0 || list[n].times < 3)
					break;
			}
			i += 5;
		}
		if (judge == 0)
			j++;
	}
	for (; j < 5;)
	{
		if (list[n].times == 0)
			break;
		judge = 0;
		for (i = 0; i < 10 && list[n].times != 0;)
		{
			if (stu_table[i][j].flag == false && stu_table[i + 1][j].flag == false)
			{
				stu_table[i][j].name = list[n].coursename;
				stu_table[i + 1][j].name = list[n].coursename;
				stu_table[i][j].flag = true;
				stu_table[i + 1][j].flag = true;
				list[n].times -= 2;
				judge = 1;
				if (list[n].times > 0)
				{
					j = (j - 3 > 0) ? (j - 3) : (j + 2);
					break;
				}
			}
			i += 5;
		}
		if (judge == 0)
			j++;
	}
	if (list[n].times != 0)
	{
		for (; j < 5; j++)
		{
			if (list[n].times == 0)
				break;
			judge = 0;
			for (i = 0; i < 10; i++)
			{
				if (stu_table[i][j].flag == false)
				{
					stu_table[i][j].name = list[n].coursename;
					stu_table[i][j].flag = true;
					list[n].times--;
					judge = 1;
					if (list[n].times > 0)
					{
						j = (j - 3 > 0) ? (j - 3) : (j + 2);
						break;
					}
				}
			}
			if (judge == 0)
				j++;
		}
	}
}

bool Inserttable(Graphmtx<string>& G, const int n, ofstream &out)
{
	int i, j, w, v, a, b, term = 1;;
	int finishjudge;
	int* count = new int[n];
	LinkedQueue<int> que;
	for (i = 0; i < n; i++)
		count[i] = 0;
	for (i = 0; i < n; i++)					//�����γ�����ͼ
	{
		if (list[i].flag == true)
		{
			b = G.getVertexPos(list[i].courseID);
			for (j = 0; j < list[i].pre; j++)
			{
				a = G.getVertexPos(list[i].Prerequisite[j]);
				G.insertEdge(a, b);
				count[i]++;
			}
		}
	}

	while (1)
	{
		initialize();
		for (i = 0; i < n; i++)				//���Ź̶�ѧ�ڿγ�
			if (list[i].term == term)
			{
				if (lasttime() < list[i].times)
				{
					cout << "�γ̹��࣬�α�����" << endl;
					return false;
				}
				else
				{
					insertcourse(i);
					count[i] = -1;
				}
			}
		int full_or_not = 0;
		while (que.DeQueue(v))
		{
			if (lasttime() < list[i].times)
			{
				full_or_not = 1;
				break;
			}
			else
				insertcourse(v);
			count[v] = -1;
			w = G.getFirstNeighbor(v);
			while (w != -1)
			{
				count[w]--;
				w = G.getNextNeighbor(v, w);
			}
		}
		if (full_or_not == 1)
		{
			print(term, out);
			term++;
			continue;
		}
		finishjudge = 1;
		for (i = 0; i < n; i++)
			if (count[i] != -1)
				finishjudge = 0;
		if (finishjudge)
		{
			print(term, out);
			break;
		}
		//�ж��Ƿ��л�·
		if (loopjudge(count, n) == false)
			return false;
		for (i = 0; i < n; i++)
			if (count[i] == 0 && list[i].term == 0)
				que.EnQueue(i);
		while (que.DeQueue(v))
		{

			if (lasttime() < list[i].times)
			{
				full_or_not = 1;
				break;
			}
			else
			{
				insertcourse(v);
				count[v] = -1;
				w = G.getFirstNeighbor(v);
				while (w != -1)
				{
					count[w]--;
					w = G.getNextNeighbor(v, w);
				}
			}
		}
		if (full_or_not == 1)
		{
			print(term, out);
			term++;
			continue;
		}
		print(term, out);
		finishjudge = 1;
		for (i = 0; i < n; i++)
			if (count[i] != -1)
				finishjudge = 0;
		if (finishjudge)
			break;
		term++;
	}
	return true;
}
int main()
{
	ifstream in;
	in.open("timetable.txt", ios::in);
	if (!in.is_open())
	{
		cout << "���ļ�ʧ��" << endl;
		exit(-1);
	}
	ofstream out;
	out.open("student.txt", ios::out);
	if (!out.is_open())
	{
		cout << "���ļ�ʧ��" << endl;
		exit(-1);
	}

	Graphmtx<string> G;
	char temp[DefaultSize];
	int i = 0, n;
	while (!in.eof())
	{
		int j = 0;
		stringstream ss;
		in.getline(temp,DefaultSize,'\n');
		if (strlen(temp) < 1)
			break;
		ss << temp;
		ss >> list[i].courseID >> list[i].coursename;
		ss >> list[i].times;
		if (!ss.good())
		{
			cout << "�������ע��γ��������пո�" << endl;
			in.close();
			out.close();
			exit(-1);
		}
		ss >> list[i].term;
		if (!ss.eof())
			list[i].flag = true;
		if (list[i].flag == true && list[i].term != 0)
		{
			cout << "ָ���γ�ѧ�ڿγ̲�Ӧ�������޿�" << endl;
			in.close();
			out.close();
			exit(-1);
		}
		while (!ss.eof())
		{
			ss >> list[i].Prerequisite[j];
			j++;
			list[i].pre++;
		}
		i++;
	}
	n = i;
	for (i = 0; i < n; i++)
		G.insertVertex(list[i].courseID);
	if (Inserttable(G, n,out) == false)
	{
		in.close();
		out.close();
		exit(-1);
	}






	in.close();
	out.close();
	return 0;
}