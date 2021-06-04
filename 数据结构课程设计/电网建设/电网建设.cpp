#include <iostream>
#include <cstring>
using namespace std;

const int DefaultSize = 1000;
const int DefaultVertics = 500;
const float maxWeight = 65535;

template <class T, class E>
class Graphmtx{
	friend istream& operator >>(istream& in, Graphmtx<T, E>& G);
	friend ostream& operator<<(ostream& out, Graphmtx<T, E>& G);
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
	E getWeight(int v1, int v2)
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
		if (numVertices == maxVertices || numEdges == maxVertices * (maxVertices - 1) / 2)
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
	bool insertEdge(int v1, int v2, E cost);
	bool removeVertex(int v);
	bool removeEdge(int v1, int v2);
private:
	int maxVertices;
	int numEdges;
	int numVertices;
	T* VerticesList;
	E** Edge;
};

template <class T, class E>
Graphmtx<T, E>::Graphmtx(int sz)
{
	maxVertices = sz;
	numVertices = 0;
	numEdges = 0;
	int i, j;
	VerticesList = new T[maxVertices];
	Edge = (E**)new E * [maxVertices];
	for (i = 0; i < maxVertices; i++)
		Edge[i] = new E[maxVertices];
	for (i = 0; i < maxVertices; i++)
		for (j = 0; j < maxVertices; j++)
			Edge[i][j] = (i == j) ? 0 : maxWeight;
}
template <class T, class E>
int Graphmtx<T, E>::getFirstNeighbor(int v)
{
	if (v != -1)
	{
		for (int col = 0; col < numVertices; col++)
			if (Edge[v][col] > 0 && Edge[v][col] < maxWeight)
				return col;
	}
	return -1;
}

template<class T, class E>
int Graphmtx<T, E>::getNextNeighbor(int v, int w)		 //��������v��ĳ�ڽӶ���w����һ���ڽӶ���
{
	if (v != -1 && w != -1)
	{
		for (int col = w + 1; col < numVertices; col++)
			if (Edge[v][col] > 0 && Edge[v][col] < maxWeight)
				return col;
	}
	return -1;
}

template <class T, class E>
bool Graphmtx<T, E>::insertVertex(const T& vertex)	//���˶��� vertex
{

	if (numVertices == maxVertices) 	// �������, ������
		return false;
	VerticesList[numVertices++] = vertex;
	return true;
}
template <class T, class E>
bool Graphmtx<T, E>::removeVertex(int v)		//ɾȥ����v����������������ı�
{
	if(v < 0 || v >= numVertices)//v����ͼ��, ��ɾ��
		return false;
	if (numVertices == 1)//ֻʣһ������, ��ɾ��
		return false;
	int i, j;
	VerticesList[v] = VerticesList[numVertices - 1];//�������ɾ���ý��
	for (i = 0; i < numVertices; i++)// ��ȥ��v���������
		if (Edge[i][v] > 0 && Edge[i][v] < maxWeight)//�����һ�����v��
			numEdges--;
	for (i = 0; i < numVertices; i++)
		Edge[i][v] = Edge[i][numVertices - 1];
	numVertices--;		//��������1
	for (j = 0; j < numVertices; j++)//����������v��
		Edge[v][j] = Edge[numVertices][j];
	return true;
}
template <class T, class E >
bool Graphmtx<T, E>::insertEdge(int v1, int v2, E cost)
{
	if (v1 > -1 && v1< numVertices && v2>-1 && v2 < numVertices && Edge[v1][v2] == maxWeight)
	{
		Edge[v1][v2] = Edge[v2][v1] = cost;
		numEdges++;
		return true;
	}
	else
		return false;
}

template <class T, class E>
bool Graphmtx<T, E>::removeEdge(int v1, int v2)	//��ͼ��ɾȥ��(v1,v2)
{
	if (v1 > -1 && v1 < numVertices && v2> -1 && v2 < numVertices && Edge[v1][v2]> 0 && Edge[v1][v2] < maxWeight)
	{
		Edge[v1][v2] = Edge[v2][v1] = maxWeight;
		numEdges--;
		return true;
	}
	else
		return false;
}

//ͨ��������������in����n��������Ϣ��e������ߵ���Ϣ�������ڽӾ����ʾ��ͼG,�ڽӾ����ʼ���Ĺ����Ѿ��ڹ��캯������ɡ�
template <class T, class E>
istream& operator>> (istream& in, Graphmtx<T, E>& G)
{
	int i, j, k, n, m;
	T e1, e2;
	E weight;
	in >> n >> m;
	for (i = 0; i < n; i++) //�������������
	{
		in >> e1;
		G.insertVertex(e1);
	}
	i = 0;
	while (i < m)
	{
		in >> e1 >> e2 >> weight;
		j = G.getVertexPos(e1);
		k = G.getVertexPos(e2);
		if (j == -1 || k == -1)
			cout << "�����˵���Ϣ������������!" << endl;
		else
		{
			G.insertEdge(j, k, weight);
			i++;
		}
	}
	return in;
}

template <class T,class E>
ostream& operator <<(ostream& out, Graphmtx<T, E>& G)
{
	int i, j, n, m;
	T e1, e2;
	E w;
	n = G.NumberOfVertices();
	m = G.NumberOfEdges();
	out << n << "," << m << endl;
	for (int i = 0; i < n; i++)
		for (j = i + 1; j < n; j++)
		{
			w = G.getWeight(i, j);
			if (w > 0 && w < maxWeight)
			{
				e1 = G.getValue(i);
				e2 = G.getValue(j);
				out << "(" << e1 << "," << e2 << "," << w << ")" << endl;
			}
		}
	return out;
}



struct MSTEdgeNode {
	int tail, head;
	float key;
	bool operator<=(MSTEdgeNode& R)
	{
		return key <= R.key;
	}
	bool operator >(MSTEdgeNode& R)
	{
		return key > R.key;
	}
};


class MinSpanTree {
protected:
	MSTEdgeNode* edgevalue;
	int maxSize, n;
public:
	MinSpanTree(int sz = DefaultSize - 1) :maxSize(sz), n(0)
	{
		edgevalue = new MSTEdgeNode[sz];
		if (edgevalue == NULL)
		{
			cout << "�����ڴ�ʧ��" << endl;
			exit(-1);
		}
	}
	int Insert(MSTEdgeNode& item);
	void display(Graphmtx<string, float>& G)
	{
		cout << "��С�������Ķ��㼰��Ϊ��" << endl << endl;
		for (int i = 0; i < n; i++)
			cout << G.getValue(edgevalue[i].tail) << "-<" << edgevalue[i].key << ">-" << G.getValue(edgevalue[i].head) << "        ";
		cout << endl;
	}
};


int MinSpanTree::Insert(MSTEdgeNode& item)
{
	if (n < maxSize)
	{
		edgevalue[n].tail = item.tail;
		edgevalue[n].head = item.head;
		edgevalue[n].key = item.key;
		n++;
		return 1;
	}
	else
		return 0;
}

template <class E>
class MinHeap {
public:
	MinHeap(int sz = DefaultSize);
	MinHeap(E arr[], int n);
	~MinHeap()
	{
		delete[]heap;
	}
	bool Insert(const E& x);
	bool RemoveMin(E& x);
	bool IsEmpty()const
	{
		return (currentSize == 0) ? true : false;
	}
	bool IsFull()const
	{
		return (currentSize == MaxHeapSize) ? true : false;
	}
	void makeEmpty()
	{
		currentSize = 0;
	}
private:
	E* heap;
	int currentSize;
	int MaxHeapSize;
	void siftDown(int start, int m);
	void siftUp(int start);
};

template <class E>
MinHeap<E>::MinHeap(int sz)
{
	MaxHeapSize = (DefaultSize < sz) ? sz : DefaultSize;
	heap = new E[MaxHeapSize];
	if (heap == NULL)
	{
		cerr << "�����ڴ�ʧ��" << endl;
		exit(-1);
	}
	currentSize = 0;
}

template <class E>
MinHeap<E>::MinHeap(E arr[], int n)
{
	MaxHeapSize = (DefaultSize < n) ? n : DefaultSize;
	heap = new E[MaxHeapSize];
	if (heap == NULL)
	{
		cerr << "�����ڴ�ʧ��" << endl;
		exit(-1);
	}
	for (int i = 0; i < n; i++)
		heap[i] = arr[i];
	currentSize = n;
	int currentPos = (currentSize - 2) / 2;
	while (currentPos >= 0)
	{
		siftDown(currentPos, currentSize - 1);
		currentPos--;
	}
}

template <class E>
void MinHeap<E>::siftDown(int start, int m)
{
	int i = start, j = 2 * i + 1;
	E temp = heap[i];
	while (j <= m)
	{
		if (j<m && heap[j]>heap[j + 1])
			j++;
		if (temp <= heap[j])
			break;
		else
		{
			heap[i] = heap[j];
			i = j;
			j = 2 * j + 1;
		}
	}
	heap[i] = temp;
}

template <class E>
void MinHeap<E>::siftUp(int start)
{
	int j = start, i = (j - 1) / 2;
	E temp = heap[j];
	while (j > 0)
	{
		if (heap[i] <= temp)
			break;
		else
		{
			heap[j] = heap[i];
			j = i; i = (i - 1) / 2;
		}
	}
	heap[j] = temp;
}

template <class E>
bool MinHeap<E>::Insert(const E& x)
{
	if (currentSize == MaxHeapSize)
	{
		cerr << "�洢�ռ�����" << endl;
		return false;
	}
	heap[currentSize] = x;
	siftUp(currentSize);
	currentSize++;
	return true;
}

template <class E>
bool MinHeap<E>::RemoveMin(E& x)
{
	if (!currentSize)
	{
		cout << "��Ԫ�ؿɹ�ɾ��" << endl;
		return false;
	}
	x = heap[0];
	heap[0] = heap[currentSize - 1];
	currentSize--;
	siftDown(0, currentSize - 1);
	return true;
}


template <class T,class E>
void Prim( Graphmtx<T, E>& G, MinSpanTree& MST)			//��С������Prim�㷨
{
	T u0;
	cout << "��������ʼ����";
	while (1)
	{
		cin >> u0;
		if (G.check(u0) == false)
			cout << "���㲻���ڣ�����������" << endl;
		else
			break;
	}
	MSTEdgeNode ed;
	int i, u, v, count;
	int n = G.NumberOfVertices();
	int m = G.NumberOfEdges();
	u = G.getVertexPos(u0);
	MinHeap<MSTEdgeNode> H(m);
	bool* Vmst = new bool[n];
	for (i = 0; i < n; i++)
		Vmst[i] = false;
	Vmst[u] = true;
	count = 1;
	do {
		v = G.getFirstNeighbor(u);
		while (v != -1)
		{
			if (Vmst[v] == false)
			{
				ed.tail = u;
				ed.head = v;
				ed.key = G.getWeight(u, v);
				H.Insert(ed);
			}
			v = G.getNextNeighbor(u, v);
		}
		while (H.IsEmpty() == false && count < n)
		{
			H.RemoveMin(ed);
			if (Vmst[ed.head] == false)
			{
				MST.Insert(ed);
				u = ed.head;
				Vmst[u] = true;
				count++;
				break;
			}
		}
	} while (count < n);
	cout << "����Prim��С����" << endl;
}

void createpoint(Graphmtx<string, float>& G, int& n)
{
	string name;
	int i;
	cout << "�����붥��ĸ�����";
	while (1)
	{
		cin >> n;
		if (!cin.good())
		{
			cout << "�����������������" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}
	cout << "����������������������" << endl;
	for (i = 0; i < n; i++) //�������������
	{
		while (1)
		{
			cin >> name;
			if (G.check(name) == true)
				cout << "���������ظ�������ظ��������������" << endl;
			else
				break;
		}
		G.insertVertex(name);
	}
}

void createedge(Graphmtx<string, float>& G)
{
	string name1,name2;
	int i = 0, j, k;
	float weight;
	cout << "��������\"? ? 0\"ʱ���������" << endl;
	while(1)
	{
		cout << "�������������㼰�ߣ�";
		cin >> name1 >> name2 >> weight;
		if (name1 == "?" && name2 == "?" && weight == 0)
			break;
		j = G.getVertexPos(name1);
		k = G.getVertexPos(name2);
		if (j == -1 || k == -1)
			cout << "�����˵���Ϣ������������!" << endl;
		else
		{
			if (G.insertEdge(j, k, weight) == false)
				cout << "������˱ߣ�����������" << endl;
		}
	}
}

int main()
{
	cout << "**                     �������ģ��ϵͳ                     **" << endl;
	cout << "==============================================================" << endl;
	cout << "**                     A---������������                     **" << endl;
	cout << "**                     B---��ӵ����ı�                     **" << endl;
	cout << "**                     C---������С������                   **" << endl;
	cout << "**                     D---��ʾ��С������                   **" << endl;
	cout << "**                     E---�˳�   ����                      **" << endl;
	cout << "==============================================================" << endl << endl;
	char ch;
	Graphmtx<string, float> tree;
	MinSpanTree MST;
	int flag = 1, n;
	while (flag)
	{
		cout << "��ѡ�������";
		cin >> ch;
		switch (ch)
		{
			case 'A':
				createpoint(tree, n);
				break;
			case 'B':
				createedge(tree);
				break;
			case 'C':
				Prim(tree, MST);
				break;
			case 'D':
				MST.display(tree);
				break;
			case 'E':
				flag = 0;
				break;
			default:
				cout << "�����������������";
				break;
		}
		cout << endl;
	}
	return 0;
}