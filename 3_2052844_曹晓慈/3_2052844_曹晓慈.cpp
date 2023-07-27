#include <iostream>
#include <assert.h>
using namespace std;
const int Length=5, Width=5;
int in_x,in_y,out_x, out_y;
int maze[Length + 2][Width + 2] = {0};
int mark[Length + 2][Width + 2] = {0};
struct Point                        //������������Ľṹ��
{
	int x, y;
	friend ostream& operator<<(ostream&, Point& Point)  //��������������
	{   
		cout << " - - >(" << Point.x << "," << Point.y << ")";
		return cout;
	}
};
template <class Type> class Stack;
template <class Type> class StackNode      //ջ���
{
	friend class Stack<Type>;     //����ջΪ��Ԫ
private:
	Type data; //�������                   
	StackNode<Type>* link; //�����ָ��
	StackNode
	(Type d = 0, StackNode<Type>* l = NULL) : data(d), link(l) { }
};
template <class Type> class Stack
{
public:
	Stack() : top(NULL) { }          //���캯��
	~Stack();                       //��������
	void Push(const Type& item);    //��ջ               
	Type Pop();                     //��ջ
	Type GetTop();                 //���ջ��Ԫ��
	void Output();                  //�Ե�ǰջ���д��ϵ��µı������
	int IsEmpty() const            //�жϵ�ǰջ�Ƿ�Ϊ��
	{
		return top == NULL;
	}
private:
	StackNode<Type>* top; //ջ��ָ��
};
/***************************************************************************
  �������ƣ�~Stack();
  ��    �ܣ�����
  ���������//
  �� �� ֵ��//
  ˵    ��:����������ʱ�����Զ�������������
***************************************************************************/
template <class Type> Stack<Type>::~Stack()
{
	StackNode<Type>* p;
	while(top != NULL) //�������
	{
		p = top;
		top = top->link;
		delete p;
	}
}
/***************************************************************************
  �������ƣ�Push(const Type& item);
  ��    �ܣ���ջ
  �������������item
  �� �� ֵ��//
  ˵    ��:item��ջ��Ϊջ����
***************************************************************************/
template <class Type> void Stack<Type>::Push(const Type& item)
{
	top = new StackNode<Type>(item, top);
	//�½������top֮ǰ, ����Ϊ��ջ��
}
/***************************************************************************
  �������ƣ�Pop();
  ��    �ܣ���ջ;
  ���������//
  �� �� ֵ�����س�ջ��Ԫ��
  ˵    ��://
***************************************************************************/
template <class Type> Type Stack<Type>::Pop()
{
	assert(!IsEmpty());  //�ж�ջ�Ƿ�Ϊ��
	StackNode<Type>* p = top;
	Type retvalue = p->data; //�ݴ�ջ������
	top = top->link; //�޸�ջ��ָ��
	delete p;
	return retvalue; //�ͷ�, ��������
}
/***************************************************************************
  �������ƣ�GetTop();
  ��    �ܣ����ջ��Ԫ��
  ���������//
  �� �� ֵ������ջ��Ԫ��
  ˵    ��://
***************************************************************************/
template <class Type> Type Stack<Type>::GetTop()
{
	assert(!IsEmpty());  //�ж�ջ�Ƿ�Ϊ��
	return top->data;
}
/***************************************************************************
  �������ƣ�Output();
  ��    �ܣ���ջ��ջ����ʼ���������
  ���������//
  �� �� ֵ��//
  ˵    ��://
***************************************************************************/
template <class Type> void Stack<Type>::Output()
{
	assert(!IsEmpty());  //�ж�ջ�Ƿ�Ϊ��
	while (top != NULL)  //�������������
	{
		Type tmp = Pop();
		cout << tmp;
	}
}
struct Offsets
{
	int a, b; // a��b��x,y�����ƫ��
};
Offsets direction[8] = 
{
	{-1, 0}, // ����{-1, 0, "N"}
	{0, 1}, // ����{0, 1, "E"}
	{1, 0}, // �ϣ�{1, 0, "S"}
	{0, -1}, // ����{0, -1, "W"}
};
/***************************************************************************
  �������ƣ�seekpath(int x,int y,Stack<Point>& OUT);
  ��    �ܣ����ݷ�Ѱ���Թ�·����
  ������������;
  �� �� ֵ��true��false;
  ˵    ��:�������Ŀ�ĵ�
***************************************************************************/
bool seekpath(int x,int y,Stack<Point>& OUT)
{

	if (x == out_x && y == out_y)
	{
		return true;
	}
	else
	{
		for (int i = 0; i < 8; i++)
		{
			x = x + direction[i].a;
			y = y + direction[i].b;
			if (maze[x][y] == 1 && mark[x][y] == 0)
			{
				mark[x][y] = 1;
				if (seekpath(x, y, OUT))
				{
					Point tmp = { x,y };
					OUT.Push(tmp);
					return true;
				}
			}
			else
			{
				x = x - direction[i].a;;
				y = y - direction[i].b;
			}
		}
	}
	return false;
}
/***************************************************************************
  �������ƣ�main();
  ��    �ܣ����и�ʽ����ͻ����߼���ʵ�֣�
  ���������//
  �� �� ֵ��//
  ˵    ��://
***************************************************************************/
int main()
{
	Stack<Point> Out;
	cout << "�Թ���ͼ" << endl;
	maze[1][1] = maze[2][1] = maze[3][1] = maze[3][2] = maze[3][3] = maze[4][3] = maze[4][4] = maze[4][5] = maze[5][5] = 1;
	in_x=1,in_y=1,out_x = 5, out_y = 5;
	int x = in_x, y = in_y;
	mark[x][y] = 1;
	for (int i = 0; i <= 6; i++)
	{
		cout << "      "<<i<<"��";
	}
	cout << endl;
	for (int i = 0; i <= 6; i++)
	{
		cout << i << "��    ";
		for (int j = 0; j <= 6; j++)
		{
			if (maze[i][j] == 1)
				cout << "#        ";
			else
				cout << "��       ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "�Թ�·��" << endl;
	cout << endl;
	seekpath(x, y,Out);
	cout << "(" << in_x << "," << in_y << ")";
	Out.Output();
	system("pause");
}