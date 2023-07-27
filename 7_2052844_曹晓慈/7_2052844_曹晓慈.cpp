#include <iostream>
#include<vector>
//#include <string>
//#include <cmath>
using namespace std;

typedef struct BiTNode
{
	char data;	//��������򣨷��ţ�
	string combine_data;	//�����������ֵ���ɴ���9��
	BiTNode* lchild, * rchild;	//���Һ���ָ��
}*BiTree;
typedef struct StackNode
{
	BiTree data_tree;	//�洢���Ƕ�����
	char data_op;	//�洢���Ƿ���
	StackNode* next;
}*LinkStack;
/***************************************************************************
  �������ƣ�InitStack(LinkStack& S);
  ��    �ܣ�ջ�ĳ�ʼ����
  �����������ʼ����ջS;
  �� �� ֵ��1;
  ˵    ��://
***************************************************************************/
int InitStack(LinkStack& S)
{
	S = NULL;
	return 1;
}
/***************************************************************************
  �������ƣ�Push_tree(LinkStack& S, BiTree e);
  ��    �ܣ���������ջ��
  ���������ջS����ջ������e;
  �� �� ֵ��1;
  ˵    ��://
***************************************************************************/
int Push_tree(LinkStack& S, BiTree e)//��������ջ
{
	LinkStack p = new StackNode;
	p->data_tree = e;
	p->next = S;
	S = p;
	return 1;
}
/***************************************************************************
  �������ƣ�Push_op(LinkStack& S, char e);
  ��    �ܣ����������ջ��
  ���������ջS����չ����e;
  �� �� ֵ��1;
  ˵    ��://
***************************************************************************/
int Push_op(LinkStack& S, char e)//�ַ���������ţ���ջ
{
	LinkStack p = new StackNode;
	p->data_op = e;
	p->next = S;
	S = p;
	return 1;
}
/***************************************************************************
  �������ƣ�Pop_tree(LinkStack& S, BiTree& T1);
  ��    �ܣ���������ջ��
  ���������ջS����ջ������T1;
  �� �� ֵ��1;
  ˵    ��://
***************************************************************************/
int Pop_tree(LinkStack& S, BiTree& T1)//��������ջ
{
	if (S == NULL)	return 0;
	LinkStack p = S;
	T1 = p->data_tree;
	S = S->next;
	delete p;
	return 1;
}
/***************************************************************************
  �������ƣ�Pop_op(LinkStack& S, char& ch);
  ��    �ܣ�������ų�ջ��
  ���������ջS����ջ�������ch;
  �� �� ֵ��1;
  ˵    ��://
***************************************************************************/
int Pop_op(LinkStack& S, char& ch)//������ų�ջ
{
	if (S == NULL)	return 0;
	LinkStack p = S;
	ch = p->data_op;
	S = S->next;
	delete p;
	return 1;
}
/***************************************************************************
  �������ƣ�GetTop_op(LinkStack S);
  ��    �ܣ����ջ���������op��
  ���������ջS;
  �� �� ֵ��ջ������;
  ˵    ��://
***************************************************************************/
char GetTop_op(LinkStack S)//ȡջ��Ԫ��
{
	if (S != NULL)	return S->data_op;
	else return ' ';
}
/***************************************************************************
  �������ƣ�GetTop_tree(LinkStack S);
  ��    �ܣ����ջ����������
  ���������ջS;
  �� �� ֵ��ջ��������������;
  ˵    ��://
***************************************************************************/
BiTree GetTop_tree(LinkStack S)
{
	if (S != NULL)	return S->data_tree;
	else return NULL;
}
/***************************************************************************
  �������ƣ�CreateExpTree(BiTree& T, BiTree a, BiTree b, char theta);
  ��    �ܣ��������ʽ��������
  �������������a,�Һ���b�ʹ������theta;
  �� �� ֵ��//
  ˵    ��://
***************************************************************************/
void CreateExpTree(BiTree& T, BiTree a, BiTree b, char theta)//a�����ӣ�b���Һ���,theta��������,������TΪ�����Ķ��������洢���ţ�
{
	BiTree L = new BiTNode;
	L->data = theta;
	L->lchild = a;
	L->rchild = b;
	T = L;
}
/***************************************************************************
  ����ͬ��
***************************************************************************/
void CreateExpTree_str(BiTree& T, BiTree a, BiTree b, string theta)//������TΪ�����Ķ��������洢��ֵ���ɴ���9��a�����ӣ�b���Һ���,theta��������
{
	BiTree L = new BiTNode;
	L->combine_data = theta;
	L->lchild = a;
	L->rchild = b;
	T = L;
}
/***************************************************************************
  �������ƣ�Precede(char top, char ch);
  ��    �ܣ���������ȼ��Ƚϣ�
  ���������top��ջ��Ԫ�أ�ch����Ҫ�Ƚϵ�Ԫ��;
  �� �� ֵ��'<'��=����>'
  ˵    ��://
***************************************************************************/
char Precede(char top, char ch)//top��ջ��Ԫ�أ�ch����Ҫ�Ƚϵ�Ԫ��
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
  �������ƣ�InitExpTree(char ep[], LinkStack& expt, LinkStack& optr);
  ��    �ܣ��������ʽ����
  ������������ʽep[],���ʽջexpt�������ջoptr;
  �� �� ֵ��//
  ˵    ��:�������Ŀ�ĵ�
***************************************************************************/
void InitExpTree(char ep[], LinkStack& expt, LinkStack& optr)//exptջ(�����)��optrջ(�����)
{
	int n = strlen(ep);
	int i = 0;
	BiTree T = NULL;	//����
	BiTree T1 = NULL;	//������
	BiTree T2 = NULL;	//������
	char ch = ' ';	//�����ķ���
	string combine_str = "";	//�洢��ֵ���ɴ���9
	while (i != n)
	{
		if (ep[i] >= '0' && ep[i] <= '9') {		//��ֵ����������������exptջ��
			combine_str += ep[i];
			if (ep[i + 1] >= '0' && ep[i + 1] <= '9') {	//��һλ�������֣�������
				i++;
				continue;
			}
			CreateExpTree_str(T, NULL, NULL, combine_str);
			combine_str = "";	//������ֵ�Ķ�������stringҪ�ÿ�
			Push_tree(expt, T);
			i++;
		}
		else {
			switch (Precede(GetTop_op(optr), ep[i]))		//�Ƚ����ȼ�
			{
				case '<':
					Push_op(optr, ep[i]);
					i++;
					break;
				case '>':
					Pop_op(optr, ch);	//������һ���ַ�
					Pop_tree(expt, T1);	//������������ֵ����������
					Pop_tree(expt, T2);
					CreateExpTree(T, T2, T1, ch);	//��data_treeΪ��������T1��T2��������
					Push_tree(expt, T);		//����T�Ž�exptջ��
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
  �������ƣ�PostOrder(BiTree T);
  ��    �ܣ����������T��
  �����������T;
  �� �� ֵ��//
  ˵    ��:����T���к������;
***************************************************************************/
void PostOrder(BiTree T) //���ʽ���ĺ������
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
  �������ƣ�PreOrder(BiTree T);
  ��    �ܣ�ǰ�������T��
  �����������T;
  �� �� ֵ��//
  ˵    ��:����T����ǰ�����;
***************************************************************************/
void PreOrder(BiTree T)//���ʽ����ǰ�����
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
  �������ƣ�main();
  ��    �ܣ���ʽ��������ʽ����ͻ����߼�ʵ�֣�
  ���������//
  �� �� ֵ��//
  ˵    ��://
***************************************************************************/
int main()
{
	LinkStack expt;
	InitStack(expt);	//��ʼ��exptջ(�����)
	LinkStack optr;
	InitStack(optr);	//��ʼ��optrջ(�����)
	int i = 0;
	const int SIZE = 500;
	char ep[SIZE];
	cout << "��������ʽ:          ";
	cin >> ep;
	cout << endl;
	while (ep[i] != '\0')
		i++;
	ep[i] = '#';
	ep[i + 1] = '\0';
	InitExpTree(ep, expt, optr);	//�������ʽ��
	BiTree T = NULL;
	Pop_tree(expt, T);	//��ȡ��󽨺õĶ�����
	cout << "�������ʽ:            ";
	PreOrder(T);
	cout << endl<<endl;
	cout << "��ʼ����׺���ʽ:      " ;	 //��ʼ��׺���ʽ;
	for (int j = 0; j < i; j++)
		cout << ep[j];
	cout << endl << endl;
	cout << "�沨�����ʽ:          ";
	PostOrder(T);		//����������
	cout << endl << endl;
	system("pause");
	return 0;
}