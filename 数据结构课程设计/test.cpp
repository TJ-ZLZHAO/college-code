#include<iostream>
using namespace std;
const int MAX = 100;
template <typename T>
class Stack                 //ģ����:ջ
{
public:
    Stack();                //Ĭ�Ϲ��캯��
    Stack(int n);           //���캯��,���ú���createStack(int n),��������Ϊn��ջ
    ~Stack();               //�鹹����
    int createStack(int n); //��������Ϊn��ջ
    int empty();            //�ж�ջ�Ƿ�Ϊ��
    int full();             //�ж�ջ�Ƿ�Ϊ��
    int push(T e);          //��Ԫ��eѹջ
    int pop(T& e);          //Ԫ�س�ջ��������e��
    T get_top();            //�õ�ջ��Ԫ��
    friend int isoperator(char& e);//�ж��ַ�e�Ƿ�Ϊ�����
    friend int isp(char& e);//����ջ������������ȼ�
    friend int icp(char& e);//����ջ������������ȼ�
    friend int compute(int x, char a, int y);//��ֵ����
private:
    T* elem;                //��������Ϊn������
    int n;                  //ջ��Ԫ�ص�������
    int top;                //ջ��ָ��
};
template<typename T>
Stack<T>::Stack()
{
    top = -1;
}
template<typename T>
Stack<T>::Stack(int n)
{
    createStack(n);
}
template<typename T>
Stack<T>::~Stack()
{
    n = 0;
    top = -1;
    delete[]elem;
}
template<typename T>
int Stack<T>::createStack(int n)
{
    if (n <= 0)
        return 0;
    this->n = n;
    top = -1;
    elem = new T[n];
    if (!elem)
        return 0;
    return 1;
}
template<typename T>
int Stack<T>::empty()
{
    return top == -1;
}
template<typename T>
int Stack<T>::full()
{
    return top >= n - 1;
}
template<typename T>
int Stack<T>::push(T e)
{
    if (top >= n - 1)
        return 0;
    elem[++top] = e;
    return 1;
}
template<typename T>
int Stack<T>::pop(T& e)
{
    if (top == -1)
        return 0;
    e = elem[top--];
    return 1;
}
template<typename T>
T Stack<T>::get_top()
{
    return elem[top];
};
int isoperator(char& e)        //�ж��Ƿ�Ϊ�����
{
    if (e == '+' || e == '-' || e == '*' || e == '/' || e == '(' || e == ')' || e == '#' || e == 'P' || e == 'N')
        return 1;      //�����������1
    else
        return 0;      //�������������0
}
int isp(char& e)               //����ջ������������ȼ�
{
    switch (e)
    {
        case '#':
            return 0; break;
        case '(':
            return 1; break;
        case '+':
        case '-':
            return 2; break;
        case '*':
        case '/':
            return 3; break;
        case 'P':
        case 'N':
            return 4; break;
        case ')':
            return 5; break;
        default:
            return -1; break;
    }
}
int icp(char& e)                 //����ջ������������ȼ�
{
    switch (e)
    {
        case '#':
            return 0; break;
        case ')':
            return 1; break;
        case '+':
        case '-':
            return 2; break;
        case '*':
        case '/':
            return 3; break;
        case 'P':
        case 'N':
            return 4; break;
        case '(':
            return 5; break;
        default:
            return -1; break;
    }
}
int compute(int x, char a, int y)
{
    switch (a)
    {
        case '+':                //����ӷ�
            return x + y; break;
        case '-':                //�������
            return x - y; break;
        case '*':                //����˷�
            return x * y; break;
        case '/':                //�������
            return x / y; break;
        default:
            return -1; break;
    }
}
int g1()
{
    char a, b, c;
    int i, j, f, value, firstOpnd, secondOpnd, m;
    Stack<char> OPTR(MAX);    //���������ջ
    Stack<int> OPND(MAX);     //����������ջ
    OPTR.push('#');           //'#'ѹջ
    cout << "��������׺���ʽ�� ";
    a = getchar();
    while (a != '#' || OPTR.get_top() != '#')
    {
        if (!isoperator(a))   //�������������Ϊ����������������ջ
            OPND.push(a - 48);//���ַ���ת��Ϊ��������
        else                  //�����������ջ��������Ƚ����ȼ���С
        {
            b = OPTR.get_top();//�õ������ջ��Ԫ��
            i = isp(b);       //ջ������������ȼ�
            j = icp(a);       //ջ������������ȼ�
            if (i < j)        //ջ����������ȼ��ߣ��������ջ
                OPTR.push(a);
            else
            {
                OPTR.pop(b);
                if (b != '(' && i == j || i > j)
                {
                    c = OPTR.get_top();
                    if ((c == '(' || c == '#') && (b == 'P' || b == 'N'))    /*cΪһԪ��
                                                                            �����������*/
                    {
                        OPND.pop(firstOpnd); //�õ�������
                        switch (b)
                        {
                            case 'P':            //����
                                f = firstOpnd * 1;
                                break;
                            case 'N':            //����
                                f = firstOpnd * (-1);
                                break;
                        }
                    }
                    else                     //cΪ��Ԫ�����
                    {
                        OPND.pop(secondOpnd); //�õ��ڶ�������
                        OPND.pop(firstOpnd);  //�õ���һ������
                        f = compute(firstOpnd, b, secondOpnd); //������ֵ
                    }
                    OPND.push(f);             //��ֵ���ѹջ
                    continue;
                }
            }
        }
        c = a;
        a = getchar();                         //������ȡ�ַ�
        while (!isoperator(a) && !isoperator(c))  /*��������ȡ�ַ���Ϊ���֣������λȨ
                                                  �õ���λ��*/
        {
            OPND.pop(m);
            m = m * 10 + a - 48;
            OPND.push(m);
            c = a;
            a = getchar();
        }

    }
    OPND.pop(value);
    return value;      //���ر��ʽ�Ľ��
}
int main()
{
    int a;
    a = g1();
    cout << "������Ϊ:  " << a << endl;
    return 0;
}