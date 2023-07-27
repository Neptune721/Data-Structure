#include <iostream>

using namespace std;
template<typename T>
class List;
class student
{
	string number;
	string name;
	string gender;
	string age;
	string type;
	friend istream& operator>>(istream&, student& student)               //输入重载
	{                                                               
		cin >> student.number >> student.name >> student.gender>>student.age>>student.type;
		return cin;
	}
	friend ostream& operator<<(ostream&, student& student)              //输出重载
	{
		cout<<student.number<<"       "<< student.name<<"   "<<student.gender<<"      "<< student.age << "      "<< student.type;
		return cout;
	}
};
template<typename T>
struct LinkNode                                    //链表结点存储结构
{
	T data;                                       //结点存储的数据
	LinkNode<T>* link;                           //指针，指向下一结点
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
template<typename T>
class List
{
public:
	List() { first = new LinkNode<T>; }                  //析构函数
	List(const T & x) { first = new LinkNode<T>(x); }    //构造函数
	List(List<T> & L);                              //复制构造函数
	~List() { makeEmpty(); }                         //析构函数
	void makeEmpty();                             //将链表置为空表
	int Length()const;                            //计算链表的长度
	LinkNode<T>* getHead()const{return first;}  //返回附加头结点的地址
    LinkNode<T>* Search(T x);                    //搜索含数据x的元素
	LinkNode<T>* Locate(int i);                 //搜索第i个元素的地址
    bool getData(int i, T& x);              //取出第i个元素的值
    void setData(int i, T& x);                   //用x修改第i个元素的值
    bool Insert(int i, T& x);                    //在第i个元素后插入x
    bool Remove(int i, T& x);                    //删除第i个元素，x返回该元素的值
	bool Judge_Insert(int i);                    //对插入功能中输入正确与否的判断
	bool Judge(int i);                           //对删除、查找和修改功能中输入正确与否的判断
	bool IsEmpty()const                         //判表空否？空则返回true
{
	return first->link == NULL ? true: false;
}
	bool IsFull()const { return false; }           //判断满否？不满则返回false
    void output();                              //输出
    List<T>& operator=(List<T>&L);            //重载函数；赋值
private:
	LinkNode<T>* first;
};
/***************************************************************************
  函数名称：List(List<T> & L);
  功    能：复制构造函数，初始化
  输入参数：//
  返 回 值：//
  说    明：进行类的初始化
***************************************************************************/
template<typename T>
List<T>:: List(List<T> & L)
{
	T value;
	LinkNode<T>* srcptr = L.getHead();
	LinkNode<T>* destptr = first = new LinkNode<T>;
	while (srcptr->link != NULL)
	{
		value = srcptr->link->data;
		destptr->link = new LinkNode<T>(value);
		destptr = destptr->link;
		srcptr = srcptr->link;
	}
	destptr->link = NULL;
};
/***************************************************************************
  函数名称：makeEmpty()
  功    能：删除链表
  输入参数：//
  返 回 值：//
  说    明:将链表删除
***************************************************************************/
template<class T>
void List<T>:: makeEmpty()                          //删除链表
{
	LinkNode<T>* q;
	while (first->link != NULL)
	{
		q = first->link;
		first->link = q->link;
		delete q;
	}
};
/***************************************************************************
  函数名称：Length()const;
  功    能：获得链表长度
  输入参数：//
  返 回 值：链表长度
  说    明://
***************************************************************************/
template<class T>
int List<T>::Length()const                   //返回链表的长度
{
	LinkNode<T> *p = first->link;
	int count = 0;
	while (p != NULL)
	{
		p = p->link;
		count++;
	}
	return count;
};
/***************************************************************************
  函数名称：Search(T x)；
  功    能：搜索数据为x的结点在链表中的位置；
  输入参数：数据x
  返 回 值：数据x所在的结点
  说    明:若不存在则返回NULL
***************************************************************************/
template<class T>
LinkNode<T>* List<T>:: Search(T x)
{
	LinkNode<T>* current = first->link;
	while (current != NULL)                       //遍历寻找数据为x的结点
		if (current->data == x)break;
		else current = current->link;
	return current;
};
/***************************************************************************
  函数名称：Locate(int i)；
  功    能：找到链表中第i个结点;
  输入参数：个数i;
  返 回 值：第i个结点指针;
  说    明:若不存在则返回NULL
***************************************************************************/
template<class T>
LinkNode<T>* List<T>:: Locate(int i)            //找到链表中第i个结点
{
	if (i < 0)
		return NULL;
	LinkNode<T>* current = first;
	int k = 0;
	while (current != NULL && k < i)
	{
		current = current->link;
		k++;
	}
	return current;
};
/***************************************************************************
  函数名称：getData(int i, T& x) 
  功    能：获得第i个结点的数据信息；
  输入参数：个数i;
  返 回 值：找不到返回false，找到返回true;
  说    明:第i个结点的值保存在元素x中；
***************************************************************************/
template<class T>
bool List<T>:: getData(int i, T& x)              //寻找链表第i个结点并将该节点的数据作为x保存
{
	if (i <= 0)return NULL;
	LinkNode<T>* current = Locate(i);
	if (current == NULL)return false;
	else { x = current->data; return true; }
};
/***************************************************************************
  函数名称：setData(int i, T& x) 
  功    能：修改第i个结点的数据信息;
  输入参数：个数i，值x;
  返 回 值：找不到返回false，找到返回true;
  说    明:将值x赋予给第i个结点的信息域中；
***************************************************************************/
template<class T>
void List<T>:: setData(int i, T& x)            //给列表第i个元素赋值x，满足修改功能
{
	if (i <= 0)return;
	LinkNode<T>* current = Locate(i);
	if (current == NULL)return;
	else current->data = x;
};
/***************************************************************************
  函数名称：Insert(int i, T& x)
  功    能：将信息域为x的结点插入到链表的i位置;
  输入参数：个数i，值x;
  返 回 值：找不到返回false，找到返回true;
  说    明://
***************************************************************************/
template<class T>
bool List<T>:: Insert(int i, T& x)                 //插入功能
{
	LinkNode<T>* current = Locate(i-1);             //找到插入位置的前一个结点
	if (current == NULL)return false;                 //若不存在则return false
	LinkNode<T>* newNode = new LinkNode<T>(x);
	if (newNode == NULL)
	{
		cerr << "存储分配错误!" << endl;
		exit(1);
	}
	newNode->link = current->link;                 //进行插入操作
	current->link = newNode;
	return true;
};
/***************************************************************************
  函数名称：Remove(int i, T& x)
  功    能：将链表的第i个结点进行删除；
  输入参数：个数i;
  返 回 值：找不到返回false，找到返回true;
  说    明:被删除结点的信息保存在i中;
***************************************************************************/
template<class T>
bool List<T>:: Remove(int i, T& x)                        //移除第i个结点，并将被删除结点的数据给到x
{
	LinkNode<T>* current = Locate(i - 1);                     //找到被删除结点的前一个结点
	if (current == NULL || current->link == NULL)return false;
	LinkNode<T>* del = current->link;       
	current->link = del->link;                            //删除操作
	x = del->data; 
	delete del;
	return true;
}
/***************************************************************************
  函数名称：output();
  功    能：将链表进行遍历输出
  输入参数：//
  返 回 值：//
  说    明://
***************************************************************************/
template<class T>
void List<T>::output()                                    //遍历输出
{
	LinkNode<T>* current = first->link;
	while (current != NULL)
	{
		cout << current->data << endl;
		current = current->link;
	}
}
/***************************************************************************
  函数名称：Judge_Insert(int i);
  功    能：判断插入位置是否合法
  输入参数：插入位置i
  返 回 值：true或false
  说    明:对插入的位置进行判断是否满足；
***************************************************************************/
template<class T>
bool List<T>::Judge_Insert(int i)                     //判断插入位置是否合法
{
	LinkNode<T>* current = Locate(i - 1);
	if (current == NULL)
		return false;
	else
		return true;
}
/***************************************************************************
  函数名称：Judge(int i) ；
  功    能：判断删除、查找和修改的结点的位置是否合法
  输入参数：删除、查找或修改位置i
  返 回 值：true或false
  说    明://
***************************************************************************/
template<class T>
bool List<T>::Judge(int i)                           //判断删除、查找和修改的结点的位置是否合法
{
	LinkNode<T>* current = Locate(i);
	if (current == NULL)
		return false;
	else
		return true;
}
/***************************************************************************
  函数名称：main（）
  功    能：基本逻辑和系统的实现；
  输入参数：考生人数num，考生信息和操作指令；
  返 回 值：//
  说    明://
***************************************************************************/
int main()
{
	int num,order;
	List<student> roster;                                    //建立链表
	cout << "首先请建立考生信息系统：" << endl;
	cout << "请输入考生人数：";
	while (1)
	{
		cin >> num;                                           //考生人数的输入
		if (cin.fail() || num < 1)                          //人数输入正误的判定
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入错误，请再次输入考生人数 :" << endl;
			continue;
		}
		break;
	}
	cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
	for (int i = 1; i <= num; i++)                        //对链表进行初始化
	{
		student tmp;
		cin >> tmp;
		roster.Insert(i, tmp);
	}  
	cout << endl;
	cout << "考号    " << "姓名    " << "性别    " << "年龄    " << "报考类别    " << endl;
	roster.output();
	cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << endl;
	cin >> order;                                     //输入要进行的操作
	while (order !=0)                                   //进入循环以满足多次操作功能的需求
	{
		switch (order)
		{
			case 1:                                                    //插入功能
			{
				int Insert_Location;
				student tmp;
				cout << "请输入你要插入的考生的位置:";
				cin >> Insert_Location;                                     //输入插入位置
				while (roster.Judge_Insert(Insert_Location)==0)             //插入位置合法与否的判定
				{
					cout << "您输入的位置不合法请重新输入!" << endl;
					cout << "请输入你要插入的考生的位置:";
					cin >> Insert_Location;
				}
				cout << "请依次输入考生的考号，姓名，性别，年龄及报考类别！" << endl;
				cin >> tmp;                                                            //输入插入考生的对应信息
				roster.Insert(Insert_Location, tmp);                                   //插入操作
				cout << endl;
				cout << "考号    " << "姓名    " << "性别    " << "年龄    " << "报考类别    " << endl;
				roster.output();                                                    //对插入后的链表进行输出
				break;
			}
			case 2:                                              //删除考生
			{
				int Delete_Location;
				student tmp;
				cout << "请输入要删除的考生的考号:";
				cin >> Delete_Location;                                           //输入删除考生位置
				while (roster.Judge(Delete_Location) == 0)                       //删除考生位置合法判定
				{
					cout << "您输入的考号不存在请重新输入!" << endl;
					cout << "请输入你要删除的考生的学号:";
					cin >> Delete_Location;
				}
				roster.Remove(Delete_Location, tmp);                            //删除功能相关函数的调用
				cout << endl;
				cout << "您删除的考生信息是:" << tmp << endl;                  
				cout << endl;
				cout << "考号    " << "姓名    " << "性别    " << "年龄    " << "报考类别    " << endl;
				roster.output();                                               //删除后链表的遍历及输出
				break;
			}
			case 3:                                                //查找考生
			{
				int Search_Location;
				student tmp;
				cout << "请输入要查找的考生的考号:";
				cin >> Search_Location;                                            //输入查找考生位置
				while (roster.Judge(Search_Location) == 0)                        //输入查找考生位置合法判定
				{
					cout << "您要查找考生的考号不存在请重新输入!" << endl;
					cout << "请输入你要查找的考生的学号:";
					cin >> Search_Location;
				}
				cout << "考号    " << "姓名    " << "性别    " << "年龄    " << "报考类别    " << endl;
				roster.getData(Search_Location, tmp);                           //查找功能调用
				cout << tmp;                                                   //输出查找考生的相关信息    
				cout << endl;
				break;
			}
			case 4:
			{
				int Modify_Location;
				student tmp;
				cout << "请输入要修改的考生的考号:";
				cin >> Modify_Location;                                         //输入修改的考生位置
				while (roster.Judge(Modify_Location) == 0)                      //输入修改的考生位置合法判定
				{
					cout << "您要修改考生的考号不存在请重新输入!" << endl;
					cout << "请输入你要修改的考生的学号:";
					cin >> Modify_Location;
				}
				cout << "该考生信息：" << endl;
				cout << "考号    " << "姓名    " << "性别    " << "年龄    " << "报考类别    " << endl;
				roster.getData(Modify_Location, tmp);                                 //获得考生原信息并输出
				cout << tmp;
				cout << endl;
				cout << "请依次输入修改后考生的考号，姓名，性别，年龄及报考类别！" << endl;
				cin >> tmp;                                                           //输入修改后考生的信息
				roster.setData(Modify_Location, tmp);                                 //对考生信息进行修改
				cout << endl;
				cout << "考号    " << "姓名    " << "性别    " << "年龄    " << "报考类别    " << endl;
				roster.output();                                                      //遍历输出
				break;
			}
			case 5:
			{
				cout << "统计后的数据：" << endl;
				roster.output();                                                      //遍历输出当前链表
				break;
			}
			default:
			{
				cout << "请输入正确的命令";
				break;
			}
		}
			cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << endl;
			cin >> order;                                                        //输入要进行的操作
	}
	return 0;
}