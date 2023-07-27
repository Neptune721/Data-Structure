#include <iostream>
#include<vector>
using namespace std;
typedef struct BiTNode
{
	int data;
	BiTNode* lchild, * rchild;	//左右孩子指针
}Node, * BST;
/***************************************************************************
  函数名称：BSTInsert(Node*& p, int element);
  功    能：二叉排序树的插入;
  输入参数：结点p，插入元素element
  返 回 值：true或false;
  说    明://
***************************************************************************/
bool BSTInsert(Node*& p, int element)
{
	if (NULL == p) // 空树
	{
		p = new Node;
		p->data = element;
		p->lchild = p->rchild = NULL;
		return true;
	}
	if (element == p->data) // BST中不能有相等的值
		return false;
	if (element < p->data)  // 递归
		return BSTInsert(p->lchild, element);
	return BSTInsert(p->rchild, element); // 递归
}
/***************************************************************************
  函数名称：CreatBST(Node *&T,vector<int> storage,int n);
  功    能：二叉排序树的创建;
  输入参数：树根节点T，储存数组storage，插入数目n；
  返 回 值：//
  说    明://
***************************************************************************/
void CreatBST(Node *&T,vector<int> storage,int n)
{
	T = NULL;
	for (int i = 0; i < n; i++)                   //二叉排序树的初始化
	{
		bool a=BSTInsert(T, storage[i]);
		if (a == 0)
		{
			cout << "The input key<" << storage[i] << ">is have in!" << endl;
		}
	}
}
/***************************************************************************
  函数名称：inOrderTraverse(BST T);
  功    能：中序遍历二叉排序树;
  输入参数：树T；
  返 回 值：//
  说    明:中序遍历后可以按从小到大输出数字;
***************************************************************************/
void inOrderTraverse(BST T)
{
	if (T)                            //中序遍历的递归算法
	{
		inOrderTraverse(T->lchild);
		cout << T->data << "->";
		inOrderTraverse(T->rchild);
	}
}
/***************************************************************************
  函数名称：BSTSearch(BST T, int element);
  功    能：在二叉排序树T中查找元素element;
  输入参数：树T，查找元素element；
  返 回 值：true或false;
  说    明://
***************************************************************************/
bool BSTSearch(BST T, int element)
{
	bool a=0, b=0;
	if (T == NULL)
	{
		return false;
	}
	if (T->data == element) //搜索成功，return
		return true;
	else if (element > T->data)    //递归搜索
		return BSTSearch(T->rchild, element);
	else                         //递归搜索
		return BSTSearch(T->lchild, element);	
}
void output()
{
	cout << "**              二叉排序树                 **" << endl;
	cout << "============================================" << endl;
	cout << "**            请选择要执行的操作：         **" << endl;
	cout << "**             1 --- 建立二叉排序树        **" << endl;
	cout << "**             2 --- 插入元素              **" << endl;
	cout << "**             3 --- 查询元素              **" << endl;
	cout << "**             4 --- 退出程序              **" << endl;
	cout << "============================================" << endl;
}
/***************************************************************************
  函数名称：main();
  功    能：基本逻辑实现和操作选择;
  输入参数：//
  返 回 值：//
  说    明://
***************************************************************************/
int main()
{
	output();
	BST T=NULL;
	int choice;
	cout << "Please select:";
	cin >> choice;
	while (choice!=4)
	{
		switch (choice)
		{
			case 1:                                              //建立二叉排序树      
			{
				int tmp,i=0;
				vector<int> storage(1000,-1);
				cout << "Please input key to creat Bsort_Tree（以0结尾）:" << endl;
				cin >> tmp;
				while (tmp != 0)
				{
					storage[i++] = tmp;
					cin >> tmp;
				}
				CreatBST(T, storage, i);
				cout << "Bsort_Tree is:" << endl;
				inOrderTraverse(T);
				cout << endl;
				break;
			}
			case 2:
			{
				int tmp;
				cout << "Please input key which inserted:     ";
				cin >> tmp;
				if (BSTInsert(T, tmp))
				{
					cout << "Bsort_Tree is:" << endl;
					inOrderTraverse(T);
					cout << endl;
				}
				else
					cout << "Insert failed!" << endl;
				break;
			}
			case 3:
			{
				int tmp;
				cout << "Please input key which searched:      ";
				cin >> tmp;
				if (BSTSearch(T, tmp))
					cout << "search success!" << endl;
				else
					cout << tmp << "  not exist!" << endl;
				break;
			}
			default:
			{
				cout << "请输入正确的命令"<<endl;
				break;
			}
		}
		cout << "Please select:";
		cin >> choice;
	}
	system("pause");
	return 0;
}