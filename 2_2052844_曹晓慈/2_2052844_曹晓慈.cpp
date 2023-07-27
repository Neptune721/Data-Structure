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
	void createCircleList(int n);  //��������ѭ������ 
	void traverseNode(); 		   //��������
	void insertNode(int n, int data);//���ƶ�λ�ò�����
	Node* Locate(int i);            //Ѱ��ѭ�������е�i�����
	Node* getHead();
	int Length();
	int getLength();               //�õ�������
	bool isEmpty();                //�ж������Ƿ�Ϊ�� 
};
/***************************************************************************
  �������ƣ�Length();
  ��    �ܣ����������
  ���������//
  �� �� ֵ��������
  ˵    ��://
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
  �������ƣ�getHead()
  ��    �ܣ����ͷָ��
  ���������//
  �� �� ֵ��ͷ���ָ��;
  ˵    ��://
***************************************************************************/
Node* CircleList::getHead()
{
	return head;
}
/***************************************************************************
  �������ƣ�Locate(int i)��
  ��    �ܣ��ҵ������е�i�����;
  �������������i;
  �� �� ֵ����i�����ָ��;
  ˵    ��:���������򷵻�NULL
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
  �������ƣ�createCircleList(int n)��
  ��    �ܣ�����ѭ������;
  �������������n;
  �� �� ֵ��//
  ˵    ��:����һ����n+1������ѭ������
***************************************************************************/
void CircleList::createCircleList(int n)     //���������β���ָ��ͷ��� 
{
	if (n < 0)
	{
		cout << "������ĳ��Ȳ���ȷ " << endl;
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
  �������ƣ�traverseNode()��
  ��    �ܣ�����ѭ������;
  ���������//
  �� �� ֵ��//
  ˵    ��:����ѭ������������Ӧ���;
***************************************************************************/
void CircleList::traverseNode()  //�������� 
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
  �������ƣ�getLength()��
  ��    �ܣ�����������;
  ���������//
  �� �� ֵ��������;
  ˵    ��://
***************************************************************************/
int CircleList::getLength()     //����ѭ��������
{
	return length;
}
/***************************************************************************
  �������ƣ�isEmpty()��
  ��    �ܣ��ж������Ƿ�Ϊ��;
  ���������//
  �� �� ֵ��true��false;
  ˵    ��://
***************************************************************************/
bool CircleList::isEmpty()      //�ж��Ƿ�Ϊ��
{
	return head == head->next;
}
/***************************************************************************
  �������ƣ�Josephus(CircleList& Js, int N, int M, int S, int K)��
  ��    �ܣ�����ѭ��������˽���ѭ����̭;
  ���������������N����ʼλ��S���Ҵ�����K����������M
  �� �� ֵ��//
  ˵    ��:�������Ŀ˵���ĵ�
***************************************************************************/
void Josephus(CircleList& Js, int N, int M, int S, int K)
{
	Node* p = Js.Locate(S), * pre = NULL;
	Node* first = Js.getHead();
	int i, j;
	for (i = 1; i <= N - K; i++)    //��Ȧѭ��������������
	{
		for (j = 1; j < M; j++)    //��Ȧѭ�����б����ļ�¼
		{
			pre = p;
			p = p->next;
			if (p == first)       //����ͷ���
			{
				p = p->next;
			}
		}
		cout << "��" << i << "�����ߵ�λ���ǣ�  " << p->data << endl;
		pre->next = p->next;
		if (first->next == p)           //��֤ͷ����nextָ��ָ�򻹴��ڵĽڵ�
			first->next = p->next;
		//cout << p->next->data << "****" << endl;
		//cout << first->next->data << "****" << endl;
		delete p;
		p = NULL;
		p = pre->next;
		if (p == first)                  //��������ͷ���
			p = p->next;
		
	}
}
/***************************************************************************
  �������ƣ�main����
  ��    �ܣ��������룬���������жϣ�����Ļ����߼�ʵ�ֺ������
  ���������������N����ʼλ��S���Ҵ�����K����������M
  �� �� ֵ��//
  ˵    ��://
***************************************************************************/
int main()
{
	CircleList list;
	int N, S, M, K;
	cout << "����N��Χ��һȦ���ӵ�S���˿�ʼ���α�������M���˳��֣�������һ�˿�ʼ���������ѭ����ֱ��ʣ��K����Ϊֹ" << endl;
	cout << endl;
	cout << "������������Ϸ��������N��";
	while (1)                                                      //������
	{
		cin >> N;
		if (cin.fail() || N < 1)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "����������ٴ�����������N : " << endl;
			continue;
		}
		break;
	}
	list.createCircleList(N);
	cout << "��������Ϸ��ʼ��λ��S��  ";
	while (1)                                                      //������
	{
		cin >> S;
		if (cin.fail() || S < 1||S>N)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "����������ٴ�������Ϸ��ʼ��λ��S : " ;
			continue;
		}
		break;
	}
	cout << "��������������M:         ";
	while (1)                                                      //������
	{
		cin >> M;
		if (cin.fail() || M < 1 || M>N)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "����������ٴ�������������M :  " ;
			continue;
		}
		break;
	}
	cout << "������ʣ�����������K��  ";
	while (1)                                             //������
	{
		cin >> K;
		if (cin.fail() || K < 1 || K>N)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "����������ٴ�����ʣ�����������K :  ";
			continue;
		}
		break;
	}
	cout << endl;
	Josephus(list, N, M, S, K);
	list.Length();
	cout << "���ʣ�£�   " << list.getLength() << "��" << endl;
	cout << "��������λ��Ϊ��";
	list.traverseNode();
	return 0;
}