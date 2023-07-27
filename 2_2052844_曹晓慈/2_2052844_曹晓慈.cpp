#include <iostream>
using namespace std;

class Node
{
public:
	Node* next;
	int data;
};

class CircleList
{
private:
	Node* head;
	int length;
public:
	CircleList()
	{
		head = new Node();
		head->next = head;
		head->data = 0;
		length = 0;
	}
	~CircleList()
	{
		delete(head);
	}
	void createCircleList(int n);  //创建单向循环链表 
	void traverseNode(); 		   //遍历链表
	void insertNode(int n, int data);//在制定位置插入结点
	Node* Locate(int i);            //寻找循环链表中第i个结点
	Node* getHead();
	int Length();
	int getLength();               //得到链表长度
	bool isEmpty();                //判断链表是否为空 
};
/***************************************************************************
  函数名称：Length();
  功    能：获得链表长度
  输入参数：//
  返 回 值：链表长度
  说    明://
***************************************************************************/
int CircleList::Length()
{
	int k = 0;
	Node* p = head->next;
	if (p->next == p)
	{
		length = 1;
		return 1;
	}
	if (p->next->next == p)
	{
		length = 2;
		return 2;
	}
	while (p != head)
	{
		p = p->next;
		k++;
	}
	length = k;
	return k;
}
/***************************************************************************
  函数名称：getHead()
  功    能：获得头指针
  输入参数：//
  返 回 值：头结点指针;
  说    明://
***************************************************************************/
Node* CircleList::getHead()
{
	return head;
}
/***************************************************************************
  函数名称：Locate(int i)；
  功    能：找到链表中第i个结点;
  输入参数：个数i;
  返 回 值：第i个结点指针;
  说    明:若不存在则返回NULL
***************************************************************************/
Node* CircleList::Locate(int i)
{
	if (i < 0)
		return NULL;
	Node* current = head;
	int k = 0;
	while (current != NULL && k < i)
	{
		current = current->next;
		k++;
	}
	return current;
}
/***************************************************************************
  函数名称：createCircleList(int n)；
  功    能：创建循环链表;
  输入参数：长度n;
  返 回 值：//
  说    明:建立一个含n+1个结点的循环链表；
***************************************************************************/
void CircleList::createCircleList(int n)     //创建的最后将尾结点指向头结点 
{
	if (n < 0)
	{
		cout << "你输入的长度不正确 " << endl;
	}
	else
	{
		int m = 0;
		length = n;
		Node* p, * q;
		p = head;
		while (m != n)
		{
			m++;
			q = new Node();
			q->data = m;
			p->next = q;
			q->next = head;
			p = q;
		}
	}
}
/***************************************************************************
  函数名称：traverseNode()；
  功    能：遍历循环链表;
  输入参数：//
  返 回 值：//
  说    明:遍历循环链表并进行相应输出;
***************************************************************************/
void CircleList::traverseNode()  //遍历链表 
{
	Node* p;
	p = head->next;
	if (p->next == p)
	{
		cout << p->data;
		return;
	}
	if (p->next->next == p)
	{
		cout << p->data << "     ";
		cout << p->next->data;
		return;
	}
	while (p != head)
	{
		cout << p->data<<"     ";
		p = p->next;
	}
	cout << endl;
}
/***************************************************************************
  函数名称：getLength()；
  功    能：返回链表长度;
  输入参数：//
  返 回 值：链表长度;
  说    明://
***************************************************************************/
int CircleList::getLength()     //返回循环链表长度
{
	return length;
}
/***************************************************************************
  函数名称：isEmpty()；
  功    能：判断链表是否为空;
  输入参数：//
  返 回 值：true或false;
  说    明://
***************************************************************************/
bool CircleList::isEmpty()      //判断是否为空
{
	return head == head->next;
}
/***************************************************************************
  函数名称：Josephus(CircleList& Js, int N, int M, int S, int K)；
  功    能：利用循环链表对人进行循环淘汰;
  输入参数：总人数N，起始位置S，幸存人数K，死亡数字M
  返 回 值：//
  说    明:详情见项目说明文档
***************************************************************************/
void Josephus(CircleList& Js, int N, int M, int S, int K)
{
	Node* p = Js.Locate(S), * pre = NULL;
	Node* first = Js.getHead();
	int i, j;
	for (i = 1; i <= N - K; i++)    //外圈循环计算死亡人数
	{
		for (j = 1; j < M; j++)    //内圈循环进行报数的记录
		{
			pre = p;
			p = p->next;
			if (p == first)       //跳过头结点
			{
				p = p->next;
			}
		}
		cout << "第" << i << "个死者的位置是：  " << p->data << endl;
		pre->next = p->next;
		if (first->next == p)           //保证头结点的next指针指向还存在的节点
			first->next = p->next;
		//cout << p->next->data << "****" << endl;
		//cout << first->next->data << "****" << endl;
		delete p;
		p = NULL;
		p = pre->next;
		if (p == first)                  //计数跳过头结点
			p = p->next;
		
	}
}
/***************************************************************************
  函数名称：main（）
  功    能：进行输入，输入正误判断，程序的基本逻辑实现和输出；
  输入参数：总人数N，起始位置S，幸存人数K，死亡数字M
  返 回 值：//
  说    明://
***************************************************************************/
int main()
{
	CircleList list;
	int N, S, M, K;
	cout << "现有N人围成一圈，从第S个人开始依次报数，报M的人出局，再由下一人开始报数，如此循环，直至剩下K个人为止" << endl;
	cout << endl;
	cout << "请输入生死游戏的总人数N：";
	while (1)                                                      //错误处理
	{
		cin >> N;
		if (cin.fail() || N < 1)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入错误，请再次输入总人数N : " << endl;
			continue;
		}
		break;
	}
	list.createCircleList(N);
	cout << "请输入游戏开始的位置S：  ";
	while (1)                                                      //错误处理
	{
		cin >> S;
		if (cin.fail() || S < 1||S>N)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入错误，请再次输入游戏开始的位置S : " ;
			continue;
		}
		break;
	}
	cout << "请输入死亡数字M:         ";
	while (1)                                                      //错误处理
	{
		cin >> M;
		if (cin.fail() || M < 1 || M>N)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入错误，请再次输入死亡数字M :  " ;
			continue;
		}
		break;
	}
	cout << "请输入剩余的生者人数K：  ";
	while (1)                                             //错误处理
	{
		cin >> K;
		if (cin.fail() || K < 1 || K>N)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入错误，请再次输入剩余的生者人数K :  ";
			continue;
		}
		break;
	}
	cout << endl;
	Josephus(list, N, M, S, K);
	list.Length();
	cout << "最后剩下：   " << list.getLength() << "人" << endl;
	cout << "最后的生者位置为：";
	list.traverseNode();
	return 0;
}