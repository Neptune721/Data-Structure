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
	friend istream& operator>>(istream&, student& student)               //��������
	{                                                               
		cin >> student.number >> student.name >> student.gender>>student.age>>student.type;
		return cin;
	}
	friend ostream& operator<<(ostream&, student& student)              //�������
	{
		cout<<student.number<<"       "<< student.name<<"   "<<student.gender<<"      "<< student.age << "      "<< student.type;
		return cout;
	}
};
template<typename T>
struct LinkNode                                    //������洢�ṹ
{
	T data;                                       //���洢������
	LinkNode<T>* link;                           //ָ�룬ָ����һ���
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
	List() { first = new LinkNode<T>; }                  //��������
	List(const T & x) { first = new LinkNode<T>(x); }    //���캯��
	List(List<T> & L);                              //���ƹ��캯��
	~List() { makeEmpty(); }                         //��������
	void makeEmpty();                             //��������Ϊ�ձ�
	int Length()const;                            //��������ĳ���
	LinkNode<T>* getHead()const{return first;}  //���ظ���ͷ���ĵ�ַ
    LinkNode<T>* Search(T x);                    //����������x��Ԫ��
	LinkNode<T>* Locate(int i);                 //������i��Ԫ�صĵ�ַ
    bool getData(int i, T& x);              //ȡ����i��Ԫ�ص�ֵ
    void setData(int i, T& x);                   //��x�޸ĵ�i��Ԫ�ص�ֵ
    bool Insert(int i, T& x);                    //�ڵ�i��Ԫ�غ����x
    bool Remove(int i, T& x);                    //ɾ����i��Ԫ�أ�x���ظ�Ԫ�ص�ֵ
	bool Judge_Insert(int i);                    //�Բ��빦����������ȷ�����ж�
	bool Judge(int i);                           //��ɾ�������Һ��޸Ĺ�����������ȷ�����ж�
	bool IsEmpty()const                         //�б�շ񣿿��򷵻�true
{
	return first->link == NULL ? true: false;
}
	bool IsFull()const { return false; }           //�ж����񣿲����򷵻�false
    void output();                              //���
    List<T>& operator=(List<T>&L);            //���غ�������ֵ
private:
	LinkNode<T>* first;
};
/***************************************************************************
  �������ƣ�List(List<T> & L);
  ��    �ܣ����ƹ��캯������ʼ��
  ���������//
  �� �� ֵ��//
  ˵    ����������ĳ�ʼ��
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
  �������ƣ�makeEmpty()
  ��    �ܣ�ɾ������
  ���������//
  �� �� ֵ��//
  ˵    ��:������ɾ��
***************************************************************************/
template<class T>
void List<T>:: makeEmpty()                          //ɾ������
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
  �������ƣ�Length()const;
  ��    �ܣ����������
  ���������//
  �� �� ֵ��������
  ˵    ��://
***************************************************************************/
template<class T>
int List<T>::Length()const                   //��������ĳ���
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
  �������ƣ�Search(T x)��
  ��    �ܣ���������Ϊx�Ľ���������е�λ�ã�
  �������������x
  �� �� ֵ������x���ڵĽ��
  ˵    ��:���������򷵻�NULL
***************************************************************************/
template<class T>
LinkNode<T>* List<T>:: Search(T x)
{
	LinkNode<T>* current = first->link;
	while (current != NULL)                       //����Ѱ������Ϊx�Ľ��
		if (current->data == x)break;
		else current = current->link;
	return current;
};
/***************************************************************************
  �������ƣ�Locate(int i)��
  ��    �ܣ��ҵ������е�i�����;
  �������������i;
  �� �� ֵ����i�����ָ��;
  ˵    ��:���������򷵻�NULL
***************************************************************************/
template<class T>
LinkNode<T>* List<T>:: Locate(int i)            //�ҵ������е�i�����
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
  �������ƣ�getData(int i, T& x) 
  ��    �ܣ���õ�i������������Ϣ��
  �������������i;
  �� �� ֵ���Ҳ�������false���ҵ�����true;
  ˵    ��:��i������ֵ������Ԫ��x�У�
***************************************************************************/
template<class T>
bool List<T>:: getData(int i, T& x)              //Ѱ�������i����㲢���ýڵ��������Ϊx����
{
	if (i <= 0)return NULL;
	LinkNode<T>* current = Locate(i);
	if (current == NULL)return false;
	else { x = current->data; return true; }
};
/***************************************************************************
  �������ƣ�setData(int i, T& x) 
  ��    �ܣ��޸ĵ�i������������Ϣ;
  �������������i��ֵx;
  �� �� ֵ���Ҳ�������false���ҵ�����true;
  ˵    ��:��ֵx�������i��������Ϣ���У�
***************************************************************************/
template<class T>
void List<T>:: setData(int i, T& x)            //���б��i��Ԫ�ظ�ֵx�������޸Ĺ���
{
	if (i <= 0)return;
	LinkNode<T>* current = Locate(i);
	if (current == NULL)return;
	else current->data = x;
};
/***************************************************************************
  �������ƣ�Insert(int i, T& x)
  ��    �ܣ�����Ϣ��Ϊx�Ľ����뵽�����iλ��;
  �������������i��ֵx;
  �� �� ֵ���Ҳ�������false���ҵ�����true;
  ˵    ��://
***************************************************************************/
template<class T>
bool List<T>:: Insert(int i, T& x)                 //���빦��
{
	LinkNode<T>* current = Locate(i-1);             //�ҵ�����λ�õ�ǰһ�����
	if (current == NULL)return false;                 //����������return false
	LinkNode<T>* newNode = new LinkNode<T>(x);
	if (newNode == NULL)
	{
		cerr << "�洢�������!" << endl;
		exit(1);
	}
	newNode->link = current->link;                 //���в������
	current->link = newNode;
	return true;
};
/***************************************************************************
  �������ƣ�Remove(int i, T& x)
  ��    �ܣ�������ĵ�i��������ɾ����
  �������������i;
  �� �� ֵ���Ҳ�������false���ҵ�����true;
  ˵    ��:��ɾ��������Ϣ������i��;
***************************************************************************/
template<class T>
bool List<T>:: Remove(int i, T& x)                        //�Ƴ���i����㣬������ɾ���������ݸ���x
{
	LinkNode<T>* current = Locate(i - 1);                     //�ҵ���ɾ������ǰһ�����
	if (current == NULL || current->link == NULL)return false;
	LinkNode<T>* del = current->link;       
	current->link = del->link;                            //ɾ������
	x = del->data; 
	delete del;
	return true;
}
/***************************************************************************
  �������ƣ�output();
  ��    �ܣ���������б������
  ���������//
  �� �� ֵ��//
  ˵    ��://
***************************************************************************/
template<class T>
void List<T>::output()                                    //�������
{
	LinkNode<T>* current = first->link;
	while (current != NULL)
	{
		cout << current->data << endl;
		current = current->link;
	}
}
/***************************************************************************
  �������ƣ�Judge_Insert(int i);
  ��    �ܣ��жϲ���λ���Ƿ�Ϸ�
  �������������λ��i
  �� �� ֵ��true��false
  ˵    ��:�Բ����λ�ý����ж��Ƿ����㣻
***************************************************************************/
template<class T>
bool List<T>::Judge_Insert(int i)                     //�жϲ���λ���Ƿ�Ϸ�
{
	LinkNode<T>* current = Locate(i - 1);
	if (current == NULL)
		return false;
	else
		return true;
}
/***************************************************************************
  �������ƣ�Judge(int i) ��
  ��    �ܣ��ж�ɾ�������Һ��޸ĵĽ���λ���Ƿ�Ϸ�
  ���������ɾ�������һ��޸�λ��i
  �� �� ֵ��true��false
  ˵    ��://
***************************************************************************/
template<class T>
bool List<T>::Judge(int i)                           //�ж�ɾ�������Һ��޸ĵĽ���λ���Ƿ�Ϸ�
{
	LinkNode<T>* current = Locate(i);
	if (current == NULL)
		return false;
	else
		return true;
}
/***************************************************************************
  �������ƣ�main����
  ��    �ܣ������߼���ϵͳ��ʵ�֣�
  �����������������num��������Ϣ�Ͳ���ָ�
  �� �� ֵ��//
  ˵    ��://
***************************************************************************/
int main()
{
	int num,order;
	List<student> roster;                                    //��������
	cout << "�����뽨��������Ϣϵͳ��" << endl;
	cout << "�����뿼��������";
	while (1)
	{
		cin >> num;                                           //��������������
		if (cin.fail() || num < 1)                          //��������������ж�
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "����������ٴ����뿼������ :" << endl;
			continue;
		}
		break;
	}
	cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
	for (int i = 1; i <= num; i++)                        //��������г�ʼ��
	{
		student tmp;
		cin >> tmp;
		roster.Insert(i, tmp);
	}  
	cout << endl;
	cout << "����    " << "����    " << "�Ա�    " << "����    " << "�������    " << endl;
	roster.output();
	cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������" << endl;
	cin >> order;                                     //����Ҫ���еĲ���
	while (order !=0)                                   //����ѭ���������β������ܵ�����
	{
		switch (order)
		{
			case 1:                                                    //���빦��
			{
				int Insert_Location;
				student tmp;
				cout << "��������Ҫ����Ŀ�����λ��:";
				cin >> Insert_Location;                                     //�������λ��
				while (roster.Judge_Insert(Insert_Location)==0)             //����λ�úϷ������ж�
				{
					cout << "�������λ�ò��Ϸ�����������!" << endl;
					cout << "��������Ҫ����Ŀ�����λ��:";
					cin >> Insert_Location;
				}
				cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
				cin >> tmp;                                                            //������뿼���Ķ�Ӧ��Ϣ
				roster.Insert(Insert_Location, tmp);                                   //�������
				cout << endl;
				cout << "����    " << "����    " << "�Ա�    " << "����    " << "�������    " << endl;
				roster.output();                                                    //�Բ���������������
				break;
			}
			case 2:                                              //ɾ������
			{
				int Delete_Location;
				student tmp;
				cout << "������Ҫɾ���Ŀ����Ŀ���:";
				cin >> Delete_Location;                                           //����ɾ������λ��
				while (roster.Judge(Delete_Location) == 0)                       //ɾ������λ�úϷ��ж�
				{
					cout << "������Ŀ��Ų���������������!" << endl;
					cout << "��������Ҫɾ���Ŀ�����ѧ��:";
					cin >> Delete_Location;
				}
				roster.Remove(Delete_Location, tmp);                            //ɾ��������غ����ĵ���
				cout << endl;
				cout << "��ɾ���Ŀ�����Ϣ��:" << tmp << endl;                  
				cout << endl;
				cout << "����    " << "����    " << "�Ա�    " << "����    " << "�������    " << endl;
				roster.output();                                               //ɾ��������ı��������
				break;
			}
			case 3:                                                //���ҿ���
			{
				int Search_Location;
				student tmp;
				cout << "������Ҫ���ҵĿ����Ŀ���:";
				cin >> Search_Location;                                            //������ҿ���λ��
				while (roster.Judge(Search_Location) == 0)                        //������ҿ���λ�úϷ��ж�
				{
					cout << "��Ҫ���ҿ����Ŀ��Ų���������������!" << endl;
					cout << "��������Ҫ���ҵĿ�����ѧ��:";
					cin >> Search_Location;
				}
				cout << "����    " << "����    " << "�Ա�    " << "����    " << "�������    " << endl;
				roster.getData(Search_Location, tmp);                           //���ҹ��ܵ���
				cout << tmp;                                                   //������ҿ����������Ϣ    
				cout << endl;
				break;
			}
			case 4:
			{
				int Modify_Location;
				student tmp;
				cout << "������Ҫ�޸ĵĿ����Ŀ���:";
				cin >> Modify_Location;                                         //�����޸ĵĿ���λ��
				while (roster.Judge(Modify_Location) == 0)                      //�����޸ĵĿ���λ�úϷ��ж�
				{
					cout << "��Ҫ�޸Ŀ����Ŀ��Ų���������������!" << endl;
					cout << "��������Ҫ�޸ĵĿ�����ѧ��:";
					cin >> Modify_Location;
				}
				cout << "�ÿ�����Ϣ��" << endl;
				cout << "����    " << "����    " << "�Ա�    " << "����    " << "�������    " << endl;
				roster.getData(Modify_Location, tmp);                                 //��ÿ���ԭ��Ϣ�����
				cout << tmp;
				cout << endl;
				cout << "�����������޸ĺ����Ŀ��ţ��������Ա����估�������" << endl;
				cin >> tmp;                                                           //�����޸ĺ�������Ϣ
				roster.setData(Modify_Location, tmp);                                 //�Կ�����Ϣ�����޸�
				cout << endl;
				cout << "����    " << "����    " << "�Ա�    " << "����    " << "�������    " << endl;
				roster.output();                                                      //�������
				break;
			}
			case 5:
			{
				cout << "ͳ�ƺ�����ݣ�" << endl;
				roster.output();                                                      //���������ǰ����
				break;
			}
			default:
			{
				cout << "��������ȷ������";
				break;
			}
		}
			cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�ƣ�0Ϊȡ��������" << endl;
			cin >> order;                                                        //����Ҫ���еĲ���
	}
	return 0;
}