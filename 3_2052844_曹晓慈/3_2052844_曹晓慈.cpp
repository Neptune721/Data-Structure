#include <iostream>
#include <assert.h>
using namespace std;
const int Length=5, Width=5;
int in_x,in_y,out_x, out_y;
int maze[Length + 2][Width + 2] = {0};
int mark[Length + 2][Width + 2] = {0};
struct Point                        //定义代表坐标点的结构体
{
	int x, y;
	friend ostream& operator<<(ostream&, Point& Point)  //坐标点输出的重载
	{   
		cout << " - - >(" << Point.x << "," << Point.y << ")";
		return cout;
	}
};
template <class Type> class Stack;
template <class Type> class StackNode      //栈结点
{
	friend class Stack<Type>;     //声明栈为友元
private:
	Type data; //结点数据                   
	StackNode<Type>* link; //结点链指针
	StackNode
	(Type d = 0, StackNode<Type>* l = NULL) : data(d), link(l) { }
};
template <class Type> class Stack
{
public:
	Stack() : top(NULL) { }          //构造函数
	~Stack();                       //析构函数
	void Push(const Type& item);    //入栈               
	Type Pop();                     //出栈
	Type GetTop();                 //获得栈顶元素
	void Output();                  //对当前栈进行从上到下的遍历输出
	int IsEmpty() const            //判断当前栈是否为空
	{
		return top == NULL;
	}
private:
	StackNode<Type>* top; //栈顶指针
};
/***************************************************************************
  函数名称：~Stack();
  功    能：销毁
  输入参数：//
  返 回 值：//
  说    明:当对象被销毁时，会自动调用析构函数
***************************************************************************/
template <class Type> Stack<Type>::~Stack()
{
	StackNode<Type>* p;
	while(top != NULL) //逐结点回收
	{
		p = top;
		top = top->link;
		delete p;
	}
}
/***************************************************************************
  函数名称：Push(const Type& item);
  功    能：入栈
  输入参数：数据item
  返 回 值：//
  说    明:item入栈作为栈顶；
***************************************************************************/
template <class Type> void Stack<Type>::Push(const Type& item)
{
	top = new StackNode<Type>(item, top);
	//新结点链入top之前, 并成为新栈顶
}
/***************************************************************************
  函数名称：Pop();
  功    能：出栈;
  输入参数：//
  返 回 值：返回出栈的元素
  说    明://
***************************************************************************/
template <class Type> Type Stack<Type>::Pop()
{
	assert(!IsEmpty());  //判断栈是否为空
	StackNode<Type>* p = top;
	Type retvalue = p->data; //暂存栈顶数据
	top = top->link; //修改栈顶指针
	delete p;
	return retvalue; //释放, 返回数据
}
/***************************************************************************
  函数名称：GetTop();
  功    能：获得栈顶元素
  输入参数：//
  返 回 值：返回栈顶元素
  说    明://
***************************************************************************/
template <class Type> Type Stack<Type>::GetTop()
{
	assert(!IsEmpty());  //判断栈是否为空
	return top->data;
}
/***************************************************************************
  函数名称：Output();
  功    能：对栈从栈顶开始遍历输出；
  输入参数：//
  返 回 值：//
  说    明://
***************************************************************************/
template <class Type> void Stack<Type>::Output()
{
	assert(!IsEmpty());  //判断栈是否为空
	while (top != NULL)  //遍历并进行输出
	{
		Type tmp = Pop();
		cout << tmp;
	}
}
struct Offsets
{
	int a, b; // a和b是x,y方向的偏移
};
Offsets direction[8] = 
{
	{-1, 0}, // 北：{-1, 0, "N"}
	{0, 1}, // 东：{0, 1, "E"}
	{1, 0}, // 南：{1, 0, "S"}
	{0, -1}, // 西：{0, -1, "W"}
};
/***************************************************************************
  函数名称：seekpath(int x,int y,Stack<Point>& OUT);
  功    能：回溯法寻找迷宫路径；
  输入参数：入口;
  返 回 值：true或false;
  说    明:详情见项目文档
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
  函数名称：main();
  功    能：进行格式输出和基本逻辑的实现；
  输入参数：//
  返 回 值：//
  说    明://
***************************************************************************/
int main()
{
	Stack<Point> Out;
	cout << "迷宫地图" << endl;
	maze[1][1] = maze[2][1] = maze[3][1] = maze[3][2] = maze[3][3] = maze[4][3] = maze[4][4] = maze[4][5] = maze[5][5] = 1;
	in_x=1,in_y=1,out_x = 5, out_y = 5;
	int x = in_x, y = in_y;
	mark[x][y] = 1;
	for (int i = 0; i <= 6; i++)
	{
		cout << "      "<<i<<"列";
	}
	cout << endl;
	for (int i = 0; i <= 6; i++)
	{
		cout << i << "行    ";
		for (int j = 0; j <= 6; j++)
		{
			if (maze[i][j] == 1)
				cout << "#        ";
			else
				cout << "×       ";
		}
		cout << endl;
	}
	cout << endl;
	cout << "迷宫路径" << endl;
	cout << endl;
	seekpath(x, y,Out);
	cout << "(" << in_x << "," << in_y << ")";
	Out.Output();
	system("pause");
}