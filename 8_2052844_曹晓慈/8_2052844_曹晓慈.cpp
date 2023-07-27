#include<iostream>
#include<vector>
using namespace std;
const int MaxVertices = 10;
const int MaxEdges = 50;
class MST
{
public:
	MST();
	//~MST() { delete Edge; };
	void creatVertice();    //Aѡ�����������
	void addEdge();          //Bѡ����ӵ�·����
	void creatTree();       //Cѡ�����С������
	void DisplayTree(int begin);     //Dѡ����ʾ��С������
	int getFirstNeighbor(int v); //��������λ��Ϊv�ĵ�һ���ڽӶ����λ�ã�����Ҳ����򷵻�-1
	int getNextNeighbor(int v, int w); //��������v��ĳ�ڽӶ���w����һ���ڽӵ㣬�Ҳ����򷵻�-1
	int getStart_num() { return start_num; };
private:
	int numVertices;         //��ǰ������
	int numEdges;           //��ǰ����
	int count = 0;          //��ʼʱ��С�������ϵĽڵ����
	int Edge[MaxVertices][MaxVertices];  //��¼�ߵ�Ȩ��
	int store[MaxVertices][MaxVertices] = { 0 };
	string start;           //��ʼ���
	int start_num;         //��ʼ�������
	vector <string> Vertices_Name; //��������Ŷ�Ӧ������
};
/***************************************************************************
  �������ƣ�MST();
  ��    �ܣ����ݳ�ʼ����
  ���������//
  �� �� ֵ��//
  ˵    ��:�������ݽ��г�ʼ��
***************************************************************************/
MST::MST()
{
	for (int i = 0; i < MaxVertices; i++)
		for (int j = 0; j < MaxVertices; j++)
			Edge[i][j] = 0;
	numEdges = 0;
	numVertices = 0;
}
/***************************************************************************
  �������ƣ�getFirstNeighbor(int v);
  ��    �ܣ���ö���v�ĵ�һ���ڽӵ㣻
  �������������v
  �� �� ֵ���ڽӵ������ڽӾ�����кţ�
  ˵    ��://
***************************************************************************/
int MST::getFirstNeighbor(int v)
{
	if (v != -1)
	{
		for (int col = 0; col < numVertices; col++)
			if (store[v][col] > 0)
				return col;
	}
	return -1;
}
/***************************************************************************
  �������ƣ�getNextNeighbor(int v, int w)
  ��    �ܣ���ö���v�ĳ��ڽӵ�w�ĵ�һ���ڽӵ㣻
  �������������v���ڽӵ�w
  �� �� ֵ���ڽӵ������ڽӾ�����кţ�
  ˵    ��://
***************************************************************************/
int MST::getNextNeighbor(int v, int w)
{
	if (v != -1 && w != -1)
	{
		for(int col=w+1;col<numVertices;col++)
			if (store[v][col] > 0)
				return col;
	}
	return -1;
}
/***************************************************************************
  �������ƣ�creatVertice();
  ��    �ܣ��������㣻
  ���������//
  �� �� ֵ��//
  ˵    ��:��ʼ������ͼ�Ķ���;
***************************************************************************/
void MST::creatVertice()
{
	string name;
	cout << "�����붥��ĸ���:";
	cin >> numVertices;
	cout << "��������������������:" << endl;
	for (int i = 0; i < numVertices; i++)
	{
		cin >> name;
		Vertices_Name.push_back(name);
	}
	cout << endl;
}
/***************************************************************************
  �������ƣ�addEdge();
  ��    �ܣ���Ӷ���ıߣ�
  ���������//
  �� �� ֵ��//
  ˵    ��:��Ӷ���֮��ı߲�����Ȩ��;
***************************************************************************/
void MST::addEdge()
{
	string name_a, name_b;
	int weight;
	cout << "�������������㼰��:";
	cin >> name_a;
	cin >> name_b;
	cin >> weight;
	while (name_a != "?" && name_b != "?" && weight != 0)
	{
		int i = 0, j = 0;
		while (name_a != Vertices_Name[i])
			i++;
		while (name_b != Vertices_Name[j])
			j++;
		Edge[i][j] = weight;
		Edge[j][i] = weight;
		cout << "�������������㼰��:";
		cin >> name_a;
		cin >> name_b;
		cin >> weight;
	}
}
/***************************************************************************
  �������ƣ�creatTree();
  ��    �ܣ�������С��������
  ���������//
  �� �� ֵ��//
  ˵    ��:��Prim�㷨��ͼ������С������;
***************************************************************************/
void MST::creatTree()
{
	vector<int> visited(numVertices, 0);
	int min=0, tmp=0,newVertice_x=0,newVertice_y=0,mark=0,pos,high=0;
	cout << "��������ʼ����:";
	cin >> start;
	count++;
	for (int i = 0; i < numVertices; i++)
		if (Vertices_Name[i] == start)
			pos = i;
	pos = start_num;
	visited[pos] = 1;
	while (count != numVertices)
	{
			mark = 0;
			for (int i = 0; i < numVertices; i++)
			{
				for (int j = 0; j < numVertices; j++)
				{
					if (visited[i] == 1 && visited[j] == 0 && i != j && Edge[i][j] != 0)
					{
						if (mark == 0)
						{
							min = Edge[j][i];
							mark = 1;
							newVertice_x = j;
							newVertice_y = i;
						}
						else
						{
							tmp = Edge[j][i];
							if (tmp < min)
							{
								min = tmp;
								newVertice_x = j;
								newVertice_y = i;
							}
						}
					}
				}
			}
			visited[newVertice_x] = 1;
			store[newVertice_y][newVertice_x] = Edge[newVertice_y][newVertice_x];
			count++;
	}
	cout << "����Prim��С������!" << endl;
}
/***************************************************************************
  �������ƣ�DisplayTree(int begin);
  ��    �ܣ���ʾ��С������;
  �����������begin������;
  �� �� ֵ��//
  ˵    ��:���õݹ��㷨��ʾ��begin��㿪ʼ����С������·��;
***************************************************************************/
void MST::DisplayTree(int begin)
{
	int tmp = 0;
	if (getFirstNeighbor(begin)!=-1)
	{
		cout << Vertices_Name[begin] << "-(" << store[begin][getFirstNeighbor(begin)] << ")->" << Vertices_Name[getFirstNeighbor(begin)] << "     ";   //�����һ���ڽӵ�
		DisplayTree(getFirstNeighbor(begin));       //�ص�һ���ڽӵ���еݹ����
		tmp = getFirstNeighbor(begin);               
		while (getNextNeighbor(begin, tmp) != -1)  //���з�֧
		{
			cout << Vertices_Name[begin] << "-(" << store[begin][getNextNeighbor(begin, tmp)] << ")->" << Vertices_Name[getNextNeighbor(begin, tmp)] << "     ";
			DisplayTree(getNextNeighbor(begin,tmp));
			tmp = tmp + getNextNeighbor(begin, tmp);   //���֧ʱ����ǰ���Ѿ����ù��ķ�֧����������ѭ��
		}
	}
}
void output()
{
	cout << "**             �������ģ��              **" << endl;
	cout << "===========================================" << endl;
	cout << "**           A---������������            **" << endl;
	cout << "**           B---��ӵ����ı�            **" << endl;
	cout << "**           C---������С������          **" << endl;
	cout << "**           D---��ʾ��С������          **" << endl;
	cout << "**           E---�˳�  ����              **" << endl;
    cout << "===========================================" << endl<<endl;
}
/***************************************************************************
  �������ƣ�main();
  ��    �ܣ���ʽ��������߼�����ʵ�ֺͲ���ѡ��;
  ���������//
  �� �� ֵ��//
  ˵    ��://
***************************************************************************/
int main()
{
	char order;
	MST Electricity_Grid;
	output();
	cout << "��ѡ�����:" ;
	cin>>order;
	while (order != 'E')
	{
		switch (order)
		{
			case 'A':
				Electricity_Grid.creatVertice();     //A���ܴ����ڵ�
				break;
			case 'B':
				Electricity_Grid.addEdge();         //B���ܴ�����
				break;
			case 'C':
				Electricity_Grid.creatTree();    //C���ܴ�����С������
				break;
			case 'D':
				Electricity_Grid.DisplayTree(Electricity_Grid.getStart_num()); //D������ʾ��С������
				cout << endl;
				break;
			default:
				cout << "��������ȷ������:";
				break;
		}
		cout << "��ѡ�����:" ;
		cin >> order;
	}
	system("pause");
	return 0;
}