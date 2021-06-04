#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<cmath>
#include<queue>
#include <Windows.h>
#include <time.h>
#include <iomanip>
#define N 40 // ����/�Թ� �Ľ��� 
#define M 20 // ����/�Թ� �Ľ��� 
using namespace std;

class Node
{
public:
	int x, y; // �ڵ�����λ��	
	int F, G, H; // G:����㿪ʼ�����Ų���·�����ƶ���������ָ��������ƶ��ķѡ�
				 // H:���������Ǹ������ƶ����յ�B��Ԥ���ƶ��ķѣ�ʹ�������پ��롣 
				 // F = G + H 
	Node(int a, int b) :x(a), y(b) {}

	// ���ز�������ʹ���ȶ�����Fֵ��СΪ��׼ά�ֶ� 
	bool operator < (const Node& a) const
	{
		return F > a.F;
	}
};

// ����˸����� 
int dir[4][2] = { {-1, 0},  {0, -1},
		 {0, 1},   {1, 0} };
// ���ȶ��У����൱��open�� 
priority_queue<Node>que;
// ����
int qp[N][M] = { {0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1} ,
			{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1},
			{0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1},
			{0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1},
			{1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1},
			{0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1},
			{0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1},
			{1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1},
			{0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1},
			{0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0},
			{0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1},
			{0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1},
			{0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1},
			{1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			{0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0},
			{0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0},
			{0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1} ,
			{0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1},
			{0, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1},
			{0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1},
			{1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1},
			{0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1},
			{0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1},
			{1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1},
			{0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1},
			{0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0},
			{0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1},
			{0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1},
			{0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 0, 0},
			{0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1},
			{1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
			{0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
			{0, 1, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
			{1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0},
			{0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 1, 0} };
bool visit[N][M]; // ���������¼��close�� 
int valF[N][M];   // ��¼ÿ���ڵ��Ӧ��Fֵ
int path[N][M][2]; // �洢ÿ���ڵ�ĸ��ڵ�

int Manhuattan(int x, int y, int x1, int y1); // ���������پ��� 
bool NodeIsLegal(int x, int y, int xx, int yy); // �ж�λ�úϷ���
void A_start(int x0, int y0, int x1, int y1); // A*�㷨 
void PrintPath(int x1, int y1); // ��ӡ·��

/* ----------------������------------------- */
int main()
{
	fill(visit[0], visit[0] + N * M, false); // ��visit���鸳��ֵfalse
	fill(valF[0], valF[0] + N * M, 0); // ��ʼ��FȫΪ0 
	fill(path[0][0], path[0][0] + N * M * 2, -1); // ·��ͬ������ֵ-1 

	//  // ��� // �յ�
	int x0, y0, x1, y1;
	cout << "������㣺";
	cin >> x0 >> y0;
	cout << "�����յ㣺";
	cin >> x1 >> y1;
	x0--; y0--; x1--; y1--;

	if (!NodeIsLegal(x0, y0, x0, y0))
	{
		cout << "�Ƿ���㣡" << endl;
		return 0;
	}

	double run_time;
	LARGE_INTEGER time_start;	//��ʼʱ��
	LARGE_INTEGER time_over;	//����ʱ��
	double dqFreq;		//��ʱ��Ƶ��
	LARGE_INTEGER f;	//��ʱ��Ƶ��
	QueryPerformanceFrequency(&f);
	dqFreq = (double)f.QuadPart;
	QueryPerformanceCounter(&time_start);	//��ʱ��ʼ


	A_start(x0, y0, x1, y1);  // A*�㷨 


	QueryPerformanceCounter(&time_over);	//��ʱ����
	run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
	//����1000000�ѵ�λ���뻯Ϊ΢�룬����Ϊ1000000/��cpu��Ƶ��΢��
	cout << "����ʱ�䣺      " << run_time << endl;



	PrintPath(x1, y1);        // ��ӡ·�� 
}

/* ----------------�Զ��庯��------------------ */
void A_start(int x0, int y0, int x1, int y1)
{
	// ��ʼ����� 
	Node node(x0, y0);
	node.G = 0;
	node.H = Manhuattan(x0, y0, x1, y1);
	node.F = node.G + node.H;
	valF[x0][y0] = node.F;
	// ������open�� 
	que.push(node);

	while (!que.empty())
	{
		Node node_top = que.top(); que.pop();
		visit[node_top.x][node_top.y] = true; // ���ʸõ㣬����closed�� 
		if (node_top.x == x1 && node_top.y == y1) // �����յ� 
			break;

		// ����node_top��Χ��8��λ�� 
		for (int i = 0; i < 4; i++)
		{
			Node node_next(node_top.x + dir[i][0], node_top.y + dir[i][1]); // ����һ��node_top��Χ�Ľڵ� 
			// �ýڵ�����Ϸ� �� δ����close�� 
			if (NodeIsLegal(node_next.x, node_next.y, node_top.x, node_top.y) && !visit[node_next.x][node_next.y])
			{
				// �������㲢����node_top�ڵ㵽��ýڵ������ѵĴ��� 
				node_next.G =  int(abs(node_next.x - x0) + abs(node_next.y - y0));
				// ����ýڵ㵽�յ�������پ���
				node_next.H = Manhuattan(node_next.x, node_next.y, x1, y1);
				// ����㾭��node_top�͸ýڵ㵽���յ�Ĺ��ƴ���
				node_next.F = node_next.G + node_next.H;

				// node_next.F < valF[node_next.x][node_next.y] ˵���ҵ��˸��ŵ�·��������и���
				// valF[node_next.x][node_next.y] == 0 ˵���ýڵ㻹δ����open���У������ 
				if (node_next.F < valF[node_next.x][node_next.y] || valF[node_next.x][node_next.y] == 0)
				{
					// ����ýڵ�ĸ��ڵ� 
					path[node_next.x][node_next.y][0] = node_top.x;
					path[node_next.x][node_next.y][1] = node_top.y;
					valF[node_next.x][node_next.y] = node_next.F; // �޸ĸýڵ��Ӧ��valFֵ 
					que.push(node_next); // ����open��
				}
			}
		}
	}
}

void PrintPath(int x1, int y1)
{
	if (path[x1][y1][0] == -1 || path[x1][y1][1] == -1)
	{
		cout << "û�п���·����" << endl;
		return;
	}
	int x = x1, y = y1;
	int a, b;
	while (x != -1 || y != -1)
	{
		qp[x][y] = 2; // ������·���ϵĽڵ㸳ֵΪ2 
		a = path[x][y][0];
		b = path[x][y][1];
		x = a;
		y = b;
	}
	// ����ʾδ�����Ľڵ㣬 ����ʾ�ϰ�� ���ʾ���нڵ� 
	string s[3] = { "��", "��", "��" };
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			cout << s[qp[i][j]];
		cout << endl;
	}
}

int Manhuattan(int x, int y, int x1, int y1)
{
	//return (abs(x - x1) + abs(y - y1)) * 10;
	return pow(x - x1, 2) + pow(y - y1, 2);
}

bool NodeIsLegal(int x, int y, int xx, int yy)
{
	if (x < 0 || x >= N || y < 0 || y >= M) return false; // �жϱ߽� 
	if (qp[x][y] == 1) return false; // �ж��ϰ��� 
	// ���ڵ�ɶԽ��������ǵĹ������ڽڵ�����ϰ��� 
	if (x != xx && y != yy && (qp[x][yy] == 1 || qp[xx][y] == 1)) return false;
	return true;
}

