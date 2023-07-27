#include <iostream>
#include <string>
using namespace std;

template<typename T>
class BiNode 
{
public:
	T data;                        //���洢�����ݣ�����ĿΪ����
	BiNode* lchild, * rchild;      //lchildָ�����ӣ�rchildָ�����ֵ�
};

template<typename T>
class BinaryTree
{
private:
	BiNode<T>* root;
public:
	BinaryTree() { root = NULL;  }                            //���캯��
	BiNode<T>* Search(T name, BiNode<T> *p);                 //���Ҵ洢����Ϊname�Ľ�㲢����
	BiNode<T>* Find_Parent(BiNode<T>* child,BiNode<T>* p);  //��pΪ���ڵ���ҽ��child
	void CreatBinaryTree(T name);                          //����������
	void Perfect(T name);                                  //����A������name�ļ���
	void AddMember();                                      //����B����ӳ�Ա
	void Delete_Family(T name);                           //����C�Ľ�ɢ�ֲ���ͥ
	void Delete_Child(BiNode<T>* p);                     //ɾ��p����Ӧ�����к���
	void Change();                                       //����D���޸�����                                   
	void Show_child(BiNode<T>* p);                       //չʾp����Ӧ�����к���
};
/***************************************************************************
  �������ƣ�CreatBinaryTree(T name);
  ��    �ܣ�������������
  �������������name;
  �� �� ֵ��//
  ˵    ��:���ж������Ĵ�����
***************************************************************************/
template<typename T>
void BinaryTree<T>::CreatBinaryTree(T name)
{
	root = new BiNode<T>;
	root->data = name;
}
/***************************************************************************
  �������ƣ�Search(T name, BiNode<T>* p);
  ��    �ܣ���pΪ������������Ϊname�Ľ�㣻
  ������������ҵ�����name�����ҳ����ĸ��ڵ�p��
  �� �� ֵ�����ҵ��򷵻�name��Ӧ����ָ�룬���򷵻�NULL
  ˵    ��://
***************************************************************************/
template<typename T>
BiNode<T>* BinaryTree<T>::Search(T name, BiNode<T>* p)
{
	BiNode<T>* ans = NULL, * temp = p;
	if (p->data == name)					//ǡ�ô��뺯���ļ�ͥ��Աkey�������ҵĳ�Ա����
		return p;
	while (temp->rchild) {            //���ֵ�ָ���в��ϵݹ�Ѱ��
		ans = Search(name, temp->rchild);
		if (ans)              //�ҵ��ó�Ա
			return ans;
		temp = temp->rchild;//δ�ҵ��������Ѱ���ֵ�ָ��ֱ������Ѱ�����Ѱ����
	}
	temp = p;
	if (temp->lchild)
		ans = Search(name, temp->lchild);
	return ans;
}
/***************************************************************************
  �������ƣ�Find_Parent(BiNode<T>* child,BiNode<T>* p);
  ��    �ܣ���pΪ��������childָ����ĸ���㣻
  ������������ӽ��child�����ҳ����ĸ��ڵ�p��
  �� �� ֵ�����ҵ��򷵻�child������Ӧ����ָ�룬���򷵻�NULL
  ˵    ��://
***************************************************************************/
template<typename T>
BiNode<T>* BinaryTree<T>::Find_Parent(BiNode<T>* child,BiNode<T>* p)
{
	if (p == NULL || child == NULL) 
		return NULL;
	BiNode<T>* q = p->lchild;
	BiNode<T>* s=NULL;          //ѭ���ӵ��ֵ������ݹ������������� 
	while (q != NULL && q != child) {
		if (Find_Parent(child, q) != NULL)
		{
			s = Find_Parent(child, q);
			return s; //�ҵ�˫�ף����� 
		}
		q = q->rchild;
	}
	if (q != NULL && q == child) return p; //�ҵ�˫�� 
	else return NULL; //δ�ҵ� 
}
/***************************************************************************
  �������ƣ�Perfect(T name);
  ��    �ܣ����Ƽ��ף�
  �����������Ҫ���Ƽ��׵�name��
  �� �� ֵ��//
  ˵    ��:��name�Ľ����Ӻ��ӽ�㣻
***************************************************************************/
template<typename T>
void BinaryTree<T>::Perfect(T name)
{
	BiNode<T>* p = Search(name, root);
	if (p == NULL)
		return;
	int num;
	T tmp;
	cout << "������"<<name<<"�Ķ�Ů����:";
	cin >> num;
	if (num == 0)
		return;
	BiNode<T>* q=NULL;
	cout << "����������" << name << "�Ķ�Ů������:";
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
	cout << name << "�ĵ�һ��������:";
	Show_child(p);
	cout << endl<<endl;
	return;
}
/***************************************************************************
  �������ƣ�AddMember()
  ��    �ܣ���ӳ�Ա��
  ���������//
  �� �� ֵ��//
  ˵    ��:Ϊ��ͥ��Ա��Ӻ��Ӳ��ӵ����к���֮��
***************************************************************************/
template<typename T>
void BinaryTree<T>::AddMember()
{
	T parent,child;
	cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�����:";
	cin >> parent;
	BiNode<T>* p = Search(parent, root);
	if (p == NULL)
	{
		cout << "���޴���" << endl << endl;
		return;
	}
	BiNode<T>* tmp = p;
	cout << "������" << p->data << "����ӵĶ��ӣ���Ů����������:";
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
	cout << parent << "�ĵ�һ��������:";
	Show_child(tmp);
	cout << endl<<endl;
	return;
}
/***************************************************************************
  �������ƣ�Delete_Family(T name)
  ��    �ܣ���ɢ�ֲ���ͥ��
  �����������ɢ�ļ�ͥ���ڸ�����name;
  �� �� ֵ��//
  ˵    ��:�ڼ�������ɾȥname���ڽ��������еĺ������ڽ��;
***************************************************************************/
template<typename T>
void BinaryTree<T>::Delete_Family(T name)
{
	BiNode<T>* p = Search(name, root);
	if(p==NULL)
	{
		cout << "���޴���" << endl<<endl;
		return;
	}
	cout << "Ҫ��ɢ��ͥ�����ǣ�" << p->data<<"     ";
	Show_child(p);
	cout << endl;
	BiNode<T>* q = Find_Parent(p, root);
	if (q->lchild == p)                //���ڵ�ĳ��Ӿ�ΪҪɾ���ļ�ͥ
	{
		if (p->rchild != NULL)           //�������ֵ�               
		{
			q->lchild = p->rchild;
			Delete_Child(p);            //ɾ���亢��
			delete p;
		}
		else                         //�������ֵ�
		{
			q->lchild = NULL;
			Delete_Child(p);       //ɾ���亢��
			delete p;
		}
		cout << endl;
		return;
	}
	else                           //Ҫɾ���ļ�ͥ��Ϊ����
	{
		q = q->lchild;
		while (q->rchild != p)
			q = q->rchild;        //qָ�����ָ��ָ��Ҫɾ���ļ�ͥ
		cout << q->data;
		if (p->rchild != NULL)   //�еܵ�
		{
			q->rchild = p->rchild;  //���½��н�������
			Delete_Child(p);       //ɾ���亢��
			delete p;
		}
		else                    //�޵ܵ�
		{
			q->rchild = NULL;
			Delete_Child(p);        //ɾ���亢��
			delete p;
		}
		cout << endl;
		return;
	}
}
/***************************************************************************
  �������ƣ�Delete_Child(BiNode<T>* p)��
  ��    �ܣ�ɾ��p�������к������ڵĽ�㣻
  �������������ָ��p;
  �� �� ֵ��//
  ˵    ��:�ڼ�������p�����к���;
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
  �������ƣ�Change()��
  ��    �ܣ�����������
  ���������//
  �� �� ֵ��//
  ˵    ��:�Լ�������ĳ����Ա�������ֵ��޸�;
***************************************************************************/
template<typename T>
void BinaryTree<T>::Change()
{
	cout << "������Ҫ�����������˵�Ŀǰ��������";
	T name;
	cin >> name;
	BiNode<T> *p = Search(name, root);
	if (p == NULL)
	{
		cout << "δ��ѯ��������������" << endl;
		return;
	}
	cout << "��������ĺ��������";
	cin >> p->data;
	cout << name << "�Ѹ���Ϊ" << p->data << endl;
	cout << endl;
}
/***************************************************************************
  �������ƣ�Show_child(BiNode<T>* p)
  ��    �ܣ��������p�������к��ӣ�
  ������������p;
  �� �� ֵ��//
  ˵    ��:��p�����к��ӱ������;
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
	cout << "**               ���׹���ϵͳ             **" << endl;
	cout << "============================================" << endl;
	cout << "**            ��ѡ��Ҫִ�еĲ�����        **" << endl;
	cout << "**           A ---���Ƽ���                **" << endl;
	cout << "**           B ---��Ӽ�ͥ��Ա            **" << endl;
	cout << "**           C ---��ɢ�ֲ���ͥ            **" << endl;
	cout << "**           D ---���ļ�ͥ��Ա����        **" << endl;
	cout << "**           E ---�˳�����                **" << endl;
	cout << "============================================" << endl;
	cout << "���Ƚ���һ�����ף�" << endl;
}
/***************************************************************************
  �������ƣ�main();
  ��    �ܣ������߼�ʵ�ֺͼ������Ľ�����
  �������������ancestor�Ͷ�Ӧ����ѡ��choice;
  �� �� ֵ��//
  ˵    ��://
***************************************************************************/
int main()
{
	output();
	BinaryTree<string> map;
	string ancestor;
	char choice;
	cout << "���������ȵ�����:";
	cin >> ancestor;
	cout << "�˼��׵�������:" << ancestor << endl;
	cout << endl; 
	map.CreatBinaryTree(ancestor);
	while (1)
	{
		cout << "��ѡ��Ҫִ�еĲ���:";
		cin >> choice;
		if (choice == 'E')
			break;
		else
		{
			string name;
			switch (choice)
			{
				case 'A':
					cout << "������Ҫ������ͥ���˵�����:";
					cin >> name;
					map.Perfect(name);    //����A���Ƽ���
					break;
				case 'B':
					map.AddMember();       //����B��ӳ�Ա
					break;
				case 'C':
					cout << "������Ҫɾ����ͥ���˵�����:";
					cin >> name;
					map.Delete_Family(name);  //����C��ɢ�ֲ���ͥ
					break;
				case 'D':
					map.Change();           //����D�ı�����
					break;
				default:
					cout << "��������ȷ������!" << endl;
					break;
			}
		}
	}
	system("pause");
}