#include <iostream>
#include<vector>
//#include <string>
//#include <cmath>
using namespace std;

typedef struct BiTNode
{
	char data;	//结点数据域（符号）
	string combine_data;	//结点数据域（数值，可大于9）
	BiTNode* lchild, * rchild;	//左右孩子指针
}*BiTree;
typedef struct StackNode
{
	BiTree data_tree;	//存储的是二叉树
	char data_op;	//存储的是符号
	StackNode* next;
}*LinkStack;
/***************************************************************************
  函数名称：InitStack(LinkStack& S);
  功    能：栈的初始化；
  输入参数：初始化的栈S;
  返 回 值：1;
  说    明://
***************************************************************************/
int InitStack(LinkStack& S)
{
	S = NULL;
	return 1;
}
/***************************************************************************
  函数名称：Push_tree(LinkStack& S, BiTree e);
  功    能：二叉树入栈；
  输入参数：栈S，入栈二叉树e;
  返 回 值：1;
  说    明://
***************************************************************************/
int Push_tree(LinkStack& S, BiTree e)//二叉树入栈
{
	LinkStack p = new StackNode;
	p->data_tree = e;
	p->next = S;
	S = p;
	return 1;
}
/***************************************************************************
  函数名称：Push_op(LinkStack& S, char e);
  功    能：运算符号入栈；
  输入参数：栈S，进展符号e;
  返 回 值：1;
  说    明://
***************************************************************************/
int Push_op(LinkStack& S, char e)//字符（运算符号）入栈
{
	LinkStack p = new StackNode;
	p->data_op = e;
	p->next = S;
	S = p;
	return 1;
}
/***************************************************************************
  函数名称：Pop_tree(LinkStack& S, BiTree& T1);
  功    能：二叉树出栈；
  输入参数：栈S，出栈二叉树T1;
  返 回 值：1;
  说    明://
***************************************************************************/
int Pop_tree(LinkStack& S, BiTree& T1)//二叉树出栈
{
	if (S == NULL)	return 0;
	LinkStack p = S;
	T1 = p->data_tree;
	S = S->next;
	delete p;
	return 1;
}
/***************************************************************************
  函数名称：Pop_op(LinkStack& S, char& ch);
  功    能：运算符号出栈；
  输入参数：栈S，出栈运算符号ch;
  返 回 值：1;
  说    明://
***************************************************************************/
int Pop_op(LinkStack& S, char& ch)//运算符号出栈
{
	if (S == NULL)	return 0;
	LinkStack p = S;
	ch = p->data_op;
	S = S->next;
	delete p;
	return 1;
}
/***************************************************************************
  函数名称：GetTop_op(LinkStack S);
  功    能：获得栈顶运算符号op；
  输入参数：栈S;
  返 回 值：栈顶符号;
  说    明://
***************************************************************************/
char GetTop_op(LinkStack S)//取栈顶元素
{
	if (S != NULL)	return S->data_op;
	else return ' ';
}
/***************************************************************************
  函数名称：GetTop_tree(LinkStack S);
  功    能：获得栈顶二叉树；
  输入参数：栈S;
  返 回 值：栈顶二叉树的数据;
  说    明://
***************************************************************************/
BiTree GetTop_tree(LinkStack S)
{
	if (S != NULL)	return S->data_tree;
	else return NULL;
}
/***************************************************************************
  函数名称：CreateExpTree(BiTree& T, BiTree a, BiTree b, char theta);
  功    能：创建表达式二叉树；
  输入参数：左孩子a,右孩子b和储存符号theta;
  返 回 值：//
  说    明://
***************************************************************************/
void CreateExpTree(BiTree& T, BiTree a, BiTree b, char theta)//a是左孩子，b是右孩子,theta是数据域,创建以T为根结点的二叉树（存储符号）
{
	BiTree L = new BiTNode;
	L->data = theta;
	L->lchild = a;
	L->rchild = b;
	T = L;
}
/***************************************************************************
  基本同上
***************************************************************************/
void CreateExpTree_str(BiTree& T, BiTree a, BiTree b, string theta)//创建以T为根结点的二叉树（存储数值，可大于9）a是左孩子，b是右孩子,theta是数据域
{
	BiTree L = new BiTNode;
	L->combine_data = theta;
	L->lchild = a;
	L->rchild = b;
	T = L;
}
/***************************************************************************
  函数名称：Precede(char top, char ch);
  功    能：运算符优先级比较；
  输入参数：top是栈顶元素，ch是需要比较的元素;
  返 回 值：'<'或‘=’或‘>'
  说    明://
***************************************************************************/
char Precede(char top, char ch)//top是栈顶元素，ch是需要比较的元素
{
	if (ch == ')' && top == '(')	return '=';
	else if (ch == ')')	return '>';
	if (top == ' ' || top == '(' || ch == '(') return '<';
	if (ch == '#')	return '>';
	if (top == '+' || top == '-') {
		if (ch == '+' || ch == '-')    return '>';
		else if (ch == '/' || ch == '*')	return '<';
	}
	else if (top == '*' || top == '/')    return '>';
}
/***************************************************************************
  函数名称：InitExpTree(char ep[], LinkStack& expt, LinkStack& optr);
  功    能：创建表达式树；
  输入参数：表达式ep[],表达式栈expt和运算符栈optr;
  返 回 值：//
  说    明:详情见项目文档
***************************************************************************/
void InitExpTree(char ep[], LinkStack& expt, LinkStack& optr)//expt栈(根结点)，optr栈(运算符)
{
	int n = strlen(ep);
	int i = 0;
	BiTree T = NULL;	//树根
	BiTree T1 = NULL;	//左子树
	BiTree T2 = NULL;	//右子树
	char ch = ' ';	//弹出的符号
	string combine_str = "";	//存储数值，可大于9
	while (i != n)
	{
		if (ep[i] >= '0' && ep[i] <= '9') {		//数值（二叉树），进入expt栈中
			combine_str += ep[i];
			if (ep[i + 1] >= '0' && ep[i + 1] <= '9') {	//下一位仍是数字，需连接
				i++;
				continue;
			}
			CreateExpTree_str(T, NULL, NULL, combine_str);
			combine_str = "";	//建完数值的二叉树后string要置空
			Push_tree(expt, T);
			i++;
		}
		else {
			switch (Precede(GetTop_op(optr), ep[i]))		//比较优先级
			{
				case '<':
					Push_op(optr, ep[i]);
					i++;
					break;
				case '>':
					Pop_op(optr, ch);	//弹出上一个字符
					Pop_tree(expt, T1);	//弹出上两个数值（二叉树）
					Pop_tree(expt, T2);
					CreateExpTree(T, T2, T1, ch);	//以data_tree为根，连接T1和T2两颗子树
					Push_tree(expt, T);		//最后把T放进expt栈中
					break;
				case '=':
					Pop_op(optr, ch);
					i++;
					break;
				default:
					break;
			}
		}
	}
}
/***************************************************************************
  函数名称：PostOrder(BiTree T);
  功    能：后序遍历树T；
  输入参数：树T;
  返 回 值：//
  说    明:对树T进行后序遍历;
***************************************************************************/
void PostOrder(BiTree T) //表达式树的后序遍历
{
	if (T)
	{
		PostOrder(T->lchild);
		PostOrder(T->rchild);
		if (T->lchild == NULL && T->rchild == NULL) {
			cout << T->combine_data;
		}
		else cout << T->data ;
	}
}
/***************************************************************************
  函数名称：PreOrder(BiTree T);
  功    能：前序遍历树T；
  输入参数：树T;
  返 回 值：//
  说    明:对树T进行前序遍历;
***************************************************************************/
void PreOrder(BiTree T)//表达式树的前序遍历
{
	if (T)
	{
		if (T->lchild == NULL && T->rchild == NULL) {
			cout << T->combine_data ;
		}
		else cout << T->data ;
		PostOrder(T->lchild);
		PostOrder(T->rchild);
	}
}
/***************************************************************************
  函数名称：main();
  功    能：格式输出，表达式输入和基本逻辑实现；
  输入参数：//
  返 回 值：//
  说    明://
***************************************************************************/
int main()
{
	LinkStack expt;
	InitStack(expt);	//初始化expt栈(根结点)
	LinkStack optr;
	InitStack(optr);	//初始化optr栈(运算符)
	int i = 0;
	const int SIZE = 500;
	char ep[SIZE];
	cout << "请输入表达式:          ";
	cin >> ep;
	cout << endl;
	while (ep[i] != '\0')
		i++;
	ep[i] = '#';
	ep[i + 1] = '\0';
	InitExpTree(ep, expt, optr);	//构建表达式树
	BiTree T = NULL;
	Pop_tree(expt, T);	//获取最后建好的二叉树
	cout << "波兰表达式:            ";
	PreOrder(T);
	cout << endl<<endl;
	cout << "初始的中缀表达式:      " ;	 //初始中缀表达式;
	for (int j = 0; j < i; j++)
		cout << ep[j];
	cout << endl << endl;
	cout << "逆波兰表达式:          ";
	PostOrder(T);		//后序遍历结果
	cout << endl << endl;
	system("pause");
	return 0;
}