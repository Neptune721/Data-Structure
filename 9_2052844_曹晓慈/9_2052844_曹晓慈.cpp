#include <iostream>
#include<vector>
using namespace std;
typedef struct BiTNode
{
	int data;
	BiTNode* lchild, * rchild;	//���Һ���ָ��
}Node, * BST;
/***************************************************************************
  �������ƣ�BSTInsert(Node*& p, int element);
  ��    �ܣ������������Ĳ���;
  ������������p������Ԫ��element
  �� �� ֵ��true��false;
  ˵    ��://
***************************************************************************/
bool BSTInsert(Node*& p, int element)
{
	if (NULL == p) // ����
	{
		p = new Node;
		p->data = element;
		p->lchild = p->rchild = NULL;
		return true;
	}
	if (element == p->data) // BST�в�������ȵ�ֵ
		return false;
	if (element < p->data)  // �ݹ�
		return BSTInsert(p->lchild, element);
	return BSTInsert(p->rchild, element); // �ݹ�
}
/***************************************************************************
  �������ƣ�CreatBST(Node *&T,vector<int> storage,int n);
  ��    �ܣ������������Ĵ���;
  ��������������ڵ�T����������storage��������Ŀn��
  �� �� ֵ��//
  ˵    ��://
***************************************************************************/
void CreatBST(Node *&T,vector<int> storage,int n)
{
	T = NULL;
	for (int i = 0; i < n; i++)                   //�����������ĳ�ʼ��
	{
		bool a=BSTInsert(T, storage[i]);
		if (a == 0)
		{
			cout << "The input key<" << storage[i] << ">is have in!" << endl;
		}
	}
}
/***************************************************************************
  �������ƣ�inOrderTraverse(BST T);
  ��    �ܣ������������������;
  �����������T��
  �� �� ֵ��//
  ˵    ��:�����������԰���С�����������;
***************************************************************************/
void inOrderTraverse(BST T)
{
	if (T)                            //��������ĵݹ��㷨
	{
		inOrderTraverse(T->lchild);
		cout << T->data << "->";
		inOrderTraverse(T->rchild);
	}
}
/***************************************************************************
  �������ƣ�BSTSearch(BST T, int element);
  ��    �ܣ��ڶ���������T�в���Ԫ��element;
  �����������T������Ԫ��element��
  �� �� ֵ��true��false;
  ˵    ��://
***************************************************************************/
bool BSTSearch(BST T, int element)
{
	bool a=0, b=0;
	if (T == NULL)
	{
		return false;
	}
	if (T->data == element) //�����ɹ���return
		return true;
	else if (element > T->data)    //�ݹ�����
		return BSTSearch(T->rchild, element);
	else                         //�ݹ�����
		return BSTSearch(T->lchild, element);	
}
void output()
{
	cout << "**              ����������                 **" << endl;
	cout << "============================================" << endl;
	cout << "**            ��ѡ��Ҫִ�еĲ�����         **" << endl;
	cout << "**             1 --- ��������������        **" << endl;
	cout << "**             2 --- ����Ԫ��              **" << endl;
	cout << "**             3 --- ��ѯԪ��              **" << endl;
	cout << "**             4 --- �˳�����              **" << endl;
	cout << "============================================" << endl;
}
/***************************************************************************
  �������ƣ�main();
  ��    �ܣ������߼�ʵ�ֺͲ���ѡ��;
  ���������//
  �� �� ֵ��//
  ˵    ��://
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
			case 1:                                              //��������������      
			{
				int tmp,i=0;
				vector<int> storage(1000,-1);
				cout << "Please input key to creat Bsort_Tree����0��β��:" << endl;
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
				cout << "��������ȷ������"<<endl;
				break;
			}
		}
		cout << "Please select:";
		cin >> choice;
	}
	system("pause");
	return 0;
}