#include <iostream>
#include <string>
using namespace std;

template<typename T>
class BiNode 
{
public:
	T data;                        //结点存储的数据，该题目为名字
	BiNode* lchild, * rchild;      //lchild指向左孩子，rchild指向右兄弟
};

template<typename T>
class BinaryTree
{
private:
	BiNode<T>* root;
public:
	BinaryTree() { root = NULL;  }                            //构造函数
	BiNode<T>* Search(T name, BiNode<T> *p);                 //查找存储数据为name的结点并返回
	BiNode<T>* Find_Parent(BiNode<T>* child,BiNode<T>* p);  //以p为根节点查找结点child
	void CreatBinaryTree(T name);                          //创建二叉树
	void Perfect(T name);                                  //功能A的完善name的家谱
	void AddMember();                                      //功能B的添加成员
	void Delete_Family(T name);                           //功能C的解散局部家庭
	void Delete_Child(BiNode<T>* p);                     //删除p结点对应的所有孩子
	void Change();                                       //功能D的修改姓名                                   
	void Show_child(BiNode<T>* p);                       //展示p结点对应的所有孩子
};
/***************************************************************************
  函数名称：CreatBinaryTree(T name);
  功    能：创建二叉树；
  输入参数：数据name;
  返 回 值：//
  说    明:进行二叉树的创建；
***************************************************************************/
template<typename T>
void BinaryTree<T>::CreatBinaryTree(T name)
{
	root = new BiNode<T>;
	root->data = name;
}
/***************************************************************************
  函数名称：Search(T name, BiNode<T>* p);
  功    能：以p为根结点查找数据为name的结点；
  输入参数：查找的数据name，查找出发的根节点p；
  返 回 值：若找到则返回name对应结点的指针，否则返回NULL
  说    明://
***************************************************************************/
template<typename T>
BiNode<T>* BinaryTree<T>::Search(T name, BiNode<T>* p)
{
	BiNode<T>* ans = NULL, * temp = p;
	if (p->data == name)					//恰好传入函数的家庭成员key即是所找的成员名字
		return p;
	while (temp->rchild) {            //在兄弟指针中不断递归寻找
		ans = Search(name, temp->rchild);
		if (ans)              //找到该成员
			return ans;
		temp = temp->rchild;//未找到则继续搜寻其兄弟指针直至都搜寻完后搜寻孩子
	}
	temp = p;
	if (temp->lchild)
		ans = Search(name, temp->lchild);
	return ans;
}
/***************************************************************************
  函数名称：Find_Parent(BiNode<T>* child,BiNode<T>* p);
  功    能：以p为根结点查找child指向结点的父结点；
  输入参数：孩子结点child，查找出发的根节点p；
  返 回 值：若找到则返回child父结点对应结点的指针，否则返回NULL
  说    明://
***************************************************************************/
template<typename T>
BiNode<T>* BinaryTree<T>::Find_Parent(BiNode<T>* child,BiNode<T>* p)
{
	if (p == NULL || child == NULL) 
		return NULL;
	BiNode<T>* q = p->lchild;
	BiNode<T>* s=NULL;          //循长子的兄弟链，递归在子树中搜索 
	while (q != NULL && q != child) {
		if (Find_Parent(child, q) != NULL)
		{
			s = Find_Parent(child, q);
			return s; //找到双亲，返回 
		}
		q = q->rchild;
	}
	if (q != NULL && q == child) return p; //找到双亲 
	else return NULL; //未找到 
}
/***************************************************************************
  函数名称：Perfect(T name);
  功    能：完善家谱；
  输入参数：需要完善家谱的name；
  返 回 值：//
  说    明:给name的结点添加孩子结点；
***************************************************************************/
template<typename T>
void BinaryTree<T>::Perfect(T name)
{
	BiNode<T>* p = Search(name, root);
	if (p == NULL)
		return;
	int num;
	T tmp;
	cout << "请输入"<<name<<"的儿女个数:";
	cin >> num;
	if (num == 0)
		return;
	BiNode<T>* q=NULL;
	cout << "请依次输入" << name << "的儿女的姓名:";
	for (int i = 0; i < num; i++)
	{
		if (i == 0)
		{
			BiNode<T>* lchild = p->lchild = new BiNode<T>;
			cin >> tmp;
			lchild->data = tmp;
			q = lchild;
		}
		else
		{
			BiNode<T>* rchild = q->rchild = new BiNode<T>;
			cin >> tmp;
			rchild->data = tmp;
			q = rchild;
		}
	}
	cout << name << "的第一代子孙是:";
	Show_child(p);
	cout << endl<<endl;
	return;
}
/***************************************************************************
  函数名称：AddMember()
  功    能：添加成员；
  输入参数：//
  返 回 值：//
  说    明:为家庭成员添加孩子并接到已有孩子之后；
***************************************************************************/
template<typename T>
void BinaryTree<T>::AddMember()
{
	T parent,child;
	cout << "请输入要添加儿子（或女儿）的人的姓名:";
	cin >> parent;
	BiNode<T>* p = Search(parent, root);
	if (p == NULL)
	{
		cout << "查无此人" << endl << endl;
		return;
	}
	BiNode<T>* tmp = p;
	cout << "请输入" << p->data << "新添加的儿子（或女儿）的姓名:";
	cin >> child;
	if (p->lchild == NULL)
	{
		BiNode<T>* kid = p->lchild = new BiNode<T>;
		kid->data = child;
	}
	else
	{
		p = p->lchild;
		while (p->rchild != NULL)
			p = p->rchild;
		BiNode<T>* kid = p->rchild = new BiNode<T>;
		kid->data = child;
	}
	cout << parent << "的第一代子孙是:";
	Show_child(tmp);
	cout << endl<<endl;
	return;
}
/***************************************************************************
  函数名称：Delete_Family(T name)
  功    能：解散局部家庭；
  输入参数：解散的家庭所在父结点的name;
  返 回 值：//
  说    明:在家谱书中删去name所在结点和其所有的孩子所在结点;
***************************************************************************/
template<typename T>
void BinaryTree<T>::Delete_Family(T name)
{
	BiNode<T>* p = Search(name, root);
	if(p==NULL)
	{
		cout << "查无此人" << endl<<endl;
		return;
	}
	cout << "要解散家庭的人是：" << p->data<<"     ";
	Show_child(p);
	cout << endl;
	BiNode<T>* q = Find_Parent(p, root);
	if (q->lchild == p)                //父节点的长子就为要删除的家庭
	{
		if (p->rchild != NULL)           //长子有兄弟               
		{
			q->lchild = p->rchild;
			Delete_Child(p);            //删除其孩子
			delete p;
		}
		else                         //长子无兄弟
		{
			q->lchild = NULL;
			Delete_Child(p);       //删除其孩子
			delete p;
		}
		cout << endl;
		return;
	}
	else                           //要删除的家庭不为长子
	{
		q = q->lchild;
		while (q->rchild != p)
			q = q->rchild;        //q指针的右指针指向要删除的家庭
		cout << q->data;
		if (p->rchild != NULL)   //有弟弟
		{
			q->rchild = p->rchild;  //重新进行结点的连接
			Delete_Child(p);       //删除其孩子
			delete p;
		}
		else                    //无弟弟
		{
			q->rchild = NULL;
			Delete_Child(p);        //删除其孩子
			delete p;
		}
		cout << endl;
		return;
	}
}
/***************************************************************************
  函数名称：Delete_Child(BiNode<T>* p)；
  功    能：删除p结点的所有孩子所在的结点；
  输入参数：结点的指针p;
  返 回 值：//
  说    明:在家谱书中p的所有孩子;
***************************************************************************/
template<typename T>
void BinaryTree<T>::Delete_Child(BiNode<T>* p)
{
	if (p->lchild == NULL)
		return;
	p = p->lchild;
	BiNode<T>* q = p->rchild;
	BiNode<T>* tmp;
	delete p;
	while (q != NULL)
	{
		tmp = q->rchild;
		delete q;
		q = tmp;
	}
	return;
}
/***************************************************************************
  函数名称：Change()；
  功    能：更改姓名；
  输入参数：//
  返 回 值：//
  说    明:对家谱树的某个成员进行名字的修改;
***************************************************************************/
template<typename T>
void BinaryTree<T>::Change()
{
	cout << "请输入要更改姓名的人的目前的姓名：";
	T name;
	cin >> name;
	BiNode<T> *p = Search(name, root);
	if (p == NULL)
	{
		cout << "未查询到更改姓名的人" << endl;
		return;
	}
	cout << "请输入更改后的姓名：";
	cin >> p->data;
	cout << name << "已更名为" << p->data << endl;
	cout << endl;
}
/***************************************************************************
  函数名称：Show_child(BiNode<T>* p)
  功    能：遍历输出p结点的所有孩子；
  输入参数：结点p;
  返 回 值：//
  说    明:将p的所有孩子遍历输出;
***************************************************************************/
template<typename T> 
void BinaryTree<T>::Show_child(BiNode<T>* p)
{
	if (p->lchild != NULL)
	{
		p = p->lchild;
		cout << p->data << "    ";
	}
	else
		return;
	p = p->rchild;
	while (p != NULL)
	{
		cout << p->data<< "    ";
		p = p->rchild;
	}
	return;
}
void output()
{
	cout << "**               家谱管理系统             **" << endl;
	cout << "============================================" << endl;
	cout << "**            请选择要执行的操作：        **" << endl;
	cout << "**           A ---完善家谱                **" << endl;
	cout << "**           B ---添加家庭成员            **" << endl;
	cout << "**           C ---解散局部家庭            **" << endl;
	cout << "**           D ---更改家庭成员姓名        **" << endl;
	cout << "**           E ---退出程序                **" << endl;
	cout << "============================================" << endl;
	cout << "首先建立一个家谱！" << endl;
}
/***************************************************************************
  函数名称：main();
  功    能：基本逻辑实现和家谱树的建立；
  输入参数：祖先ancestor和对应操作选择choice;
  返 回 值：//
  说    明://
***************************************************************************/
int main()
{
	output();
	BinaryTree<string> map;
	string ancestor;
	char choice;
	cout << "请输入祖先的名字:";
	cin >> ancestor;
	cout << "此家谱的祖先是:" << ancestor << endl;
	cout << endl; 
	map.CreatBinaryTree(ancestor);
	while (1)
	{
		cout << "请选择要执行的操作:";
		cin >> choice;
		if (choice == 'E')
			break;
		else
		{
			string name;
			switch (choice)
			{
				case 'A':
					cout << "请输入要建立家庭的人的姓名:";
					cin >> name;
					map.Perfect(name);    //功能A完善家谱
					break;
				case 'B':
					map.AddMember();       //功能B添加成员
					break;
				case 'C':
					cout << "请输入要删除家庭的人的姓名:";
					cin >> name;
					map.Delete_Family(name);  //功能C解散局部家庭
					break;
				case 'D':
					map.Change();           //功能D改变姓名
					break;
				default:
					cout << "请输入正确的命令!" << endl;
					break;
			}
		}
	}
	system("pause");
}