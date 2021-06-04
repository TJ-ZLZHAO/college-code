#include <iostream>
#include <iomanip>
#include <time.h>
#include <Windows.h>
using namespace std;
int m = 50, p = 50;
struct offsets {
	int a, b;
	char* dir;
};
struct rec{
	int a, b;
	struct rec* link;
};
char a[4][2] = { "N","E","S","W" };
offsets movedir[8] = { {-1,0,a[0]}, {0,1,a[1]},{1,0,a[2]},{0,-1,a[3]} };
rec record, * current;
int** Maze = new int* [m + 2];
int** mark = new int* [m + 2];
int SeekPath(int x, int y)
{
	int i, g, h;
	char* dir;
	if (x == m && y ==p)
		return 1;
	for (i = 0; i < 8; i++)
	{
		g = x + movedir[i].a;
		h = y + movedir[i].b;
		dir = movedir[i].dir;
		if (Maze[g][h] == 0 && mark[g][h] == 0)
		{
			mark[g][h] = 1;
			if (SeekPath(g, h))
			{
				Maze[g][h] = 2;
				rec* newNode = new rec;
				if (newNode == NULL)
				{
					cout << "�����ڴ�ʧ��" << endl;
					exit(-1);
				}
				newNode->a = g;
				newNode->b = h;
				newNode->link = NULL;
				current->link = newNode;
				current = current->link;
				return 1;
			}
		}
	}
	return 0;
}

int main()
{
	if (Maze == NULL || mark == NULL)
	{
		cout << "�����ڴ�ʧ��" << endl;
		exit(-1);
	}
	int i, j;
	for (i = 0; i < m + 2; i++)
	{
		Maze[i] = new int[p + 2];
		if (Maze[i] == NULL)
		{
			cout << "�����ڴ�ʧ��" << endl;
			exit(-1);
		}
		mark[i] = new int[p + 2];
		if (mark[i] == NULL)
		{
			cout << "�����ڴ�ʧ��" << endl;
			exit(-1);
		}
	}
	record.link = NULL;
	current = &record;
	while (1)
	{
		cout << "�������Թ���������������";
		cin >> m >> p;
		if (!cin.good())
		{
			cout << "�����������������" << endl;
			cin.clear();
			cin.ignore(65535, '\n');
		}
		else
			break;
	}
	cout << "�������Թ���1����ǽ�ڣ�0����ͨ·" << endl;
	for (i = 0; i < m + 2; i++)
		for (j = 0; j < p + 2; j++)
		{

			while (1)
			{
				cin >> Maze[i][j];
				if (!cin.good() || Maze[i][j] > 1 || Maze[i][j] < 0)
				{
					cout << "������������λ�����¿�ʼ����" << endl;
					cin.clear();
					cin.ignore(65535, '\n');
				}
				else
					break;
			}
		}
	for (i = 0; i < m + 2; i++)
		for (j = 0; j < p + 2; j++)
			mark[i][j] = 0;
	mark[1][1] = 1;



	double run_time;
	LARGE_INTEGER time_start;	//��ʼʱ��
	LARGE_INTEGER time_over;	//����ʱ��
	double dqFreq;		//��ʱ��Ƶ��
	LARGE_INTEGER f;	//��ʱ��Ƶ��
	QueryPerformanceFrequency(&f);
	dqFreq = (double)f.QuadPart;
	QueryPerformanceCounter(&time_start);	//��ʱ��ʼ


	if (SeekPath(1, 1))
		Maze[1][1] = 2;


	QueryPerformanceCounter(&time_over);	//��ʱ����
	run_time = 1000000 * (time_over.QuadPart - time_start.QuadPart) / dqFreq;
	//����1000000�ѵ�λ���뻯Ϊ΢�룬����Ϊ1000000/��cpu��Ƶ��΢��
	Maze[0][1] = Maze[m][p + 1] = 1;
	cout << "����ʱ�䣺      " << run_time << endl;
	// ����ʾδ�����Ľڵ㣬 ����ʾ�ϰ�� ���ʾ���нڵ� 
	string s[3] = { "��", "��", "��" };
	for (int i = 1; i <= m; i++)
	{
		for (int j = 1; j <= p; j++)
			cout << s[Maze[i][j]];
		cout << endl;
	}
	cout << "�Թ���ͼ��" << endl << endl;
	cout << "        ";
	cout << setiosflags(ios::left);
	for (i = 0; i < p + 2; i++) {
		cout << i << setw(int(7 - int(i / 10))) << "��";
	}
	cout << endl;
	for (i = 0; i < m + 2; i++)
	{
		cout << i << setw(int(7 - int(i / 10))) << "��";
		for (j = 0; j < p + 2; j++)
		{
			switch (Maze[i][j]) {
				case 1:
					cout << "#       ";
					break;
				case 2:
					cout << "��      ";
					break;
				case 0:
					cout << "0       ";
					break;
			}
		}
		cout << endl;
	}
	if (Maze[1][1] == 2)
	{
		cout << endl << "�Թ�·����" << endl << endl;
		current = &record;
		cout << "<1,1>";
		while (current->link != NULL) {
			rec* tmp = &record;
			if (current->link != NULL && current->link->link == NULL)
				tmp = current;
			while (current->link != NULL)
			{
				current = current->link;
				if (current->link != NULL && current->link->link == NULL)
					tmp = current;
			}
			cout << " ---> " << "<" << current->a << "," << current->b << ">";
			tmp->link = NULL;
			delete current;
			current = &record;
		}
	}
	else
		cout << "�Թ���û����ڵ����ڵ�ͨ·" << endl;
	cout << endl;
	delete[] Maze;
	delete[] mark;
	return 0;
}