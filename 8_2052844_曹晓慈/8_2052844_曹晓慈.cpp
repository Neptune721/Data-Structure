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
	void creatVertice();    //A选项创建电网顶点
	void addEdge();          //B选项添加电路的网
	void creatTree();       //C选项构造最小生成树
	void DisplayTree(int begin);     //D选项显示最小生成树
	int getFirstNeighbor(int v); //给出顶点位置为v的第一个邻接顶点的位置，如果找不到则返回-1
	int getNextNeighbor(int v, int w); //给出顶点v的某邻接顶点w的下一个邻接点，找不到则返回-1
	int getStart_num() { return start_num; };
private:
	int numVertices;         //当前顶点数
	int numEdges;           //当前边数
	int count = 0;          //初始时最小生成树上的节点个数
	int Edge[MaxVertices][MaxVertices];  //记录边的权重
	int store[MaxVertices][MaxVertices] = { 0 };
	string start;           //开始结点
	int start_num;         //开始结点的序号
	vector <string> Vertices_Name; //储存结点序号对应的名字
};
/***************************************************************************
  函数名称：MST();
  功    能：数据初始化；
  输入参数：//
  返 回 值：//
  说    明:对类数据进行初始化
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
  函数名称：getFirstNeighbor(int v);
  功    能：获得顶点v的第一个邻接点；
  输入参数：顶点v
  返 回 值：邻接点所在邻接矩阵的列号；
  说    明://
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
  函数名称：getNextNeighbor(int v, int w)
  功    能：获得顶点v的除邻接点w的第一个邻接点；
  输入参数：顶点v，邻接点w
  返 回 值：邻接点所在邻接矩阵的列号；
  说    明://
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
  函数名称：creatVertice();
  功    能：创建顶点；
  输入参数：//
  返 回 值：//
  说    明:初始化创建图的顶点;
***************************************************************************/
void MST::creatVertice()
{
	string name;
	cout << "请输入顶点的个数:";
	cin >> numVertices;
	cout << "请依次输入各顶点的名称:" << endl;
	for (int i = 0; i < numVertices; i++)
	{
		cin >> name;
		Vertices_Name.push_back(name);
	}
	cout << endl;
}
/***************************************************************************
  函数名称：addEdge();
  功    能：添加顶点的边；
  输入参数：//
  返 回 值：//
  说    明:添加顶点之间的边并给予权重;
***************************************************************************/
void MST::addEdge()
{
	string name_a, name_b;
	int weight;
	cout << "请输入两个顶点及边:";
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
		cout << "请输入两个顶点及边:";
		cin >> name_a;
		cin >> name_b;
		cin >> weight;
	}
}
/***************************************************************************
  函数名称：creatTree();
  功    能：创建最小生成树；
  输入参数：//
  返 回 值：//
  说    明:用Prim算法给图创建最小生成树;
***************************************************************************/
void MST::creatTree()
{
	vector<int> visited(numVertices, 0);
	int min=0, tmp=0,newVertice_x=0,newVertice_y=0,mark=0,pos,high=0;
	cout << "请输入起始顶点:";
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
	cout << "生成Prim最小生成树!" << endl;
}
/***************************************************************************
  函数名称：DisplayTree(int begin);
  功    能：显示最小生成树;
  输入参数：第begin个顶点;
  返 回 值：//
  说    明:采用递归算法显示从begin结点开始的最小生成树路径;
***************************************************************************/
void MST::DisplayTree(int begin)
{
	int tmp = 0;
	if (getFirstNeighbor(begin)!=-1)
	{
		cout << Vertices_Name[begin] << "-(" << store[begin][getFirstNeighbor(begin)] << ")->" << Vertices_Name[getFirstNeighbor(begin)] << "     ";   //输出第一个邻接点
		DisplayTree(getFirstNeighbor(begin));       //沿第一个邻接点进行递归输出
		tmp = getFirstNeighbor(begin);               
		while (getNextNeighbor(begin, tmp) != -1)  //若有分支
		{
			cout << Vertices_Name[begin] << "-(" << store[begin][getNextNeighbor(begin, tmp)] << ")->" << Vertices_Name[getNextNeighbor(begin, tmp)] << "     ";
			DisplayTree(getNextNeighbor(begin,tmp));
			tmp = tmp + getNextNeighbor(begin, tmp);   //多分支时跳过前面已经调用过的分支避免陷入死循环
		}
	}
}
void output()
{
	cout << "**             电网造价模拟              **" << endl;
	cout << "===========================================" << endl;
	cout << "**           A---创建电网顶点            **" << endl;
	cout << "**           B---添加电网的边            **" << endl;
	cout << "**           C---构造最小生成树          **" << endl;
	cout << "**           D---显示最小生成树          **" << endl;
	cout << "**           E---退出  程序              **" << endl;
    cout << "===========================================" << endl<<endl;
}
/***************************************************************************
  函数名称：main();
  功    能：格式化输出，逻辑基本实现和操作选择;
  输入参数：//
  返 回 值：//
  说    明://
***************************************************************************/
int main()
{
	char order;
	MST Electricity_Grid;
	output();
	cout << "请选择操作:" ;
	cin>>order;
	while (order != 'E')
	{
		switch (order)
		{
			case 'A':
				Electricity_Grid.creatVertice();     //A功能创建节点
				break;
			case 'B':
				Electricity_Grid.addEdge();         //B功能创建边
				break;
			case 'C':
				Electricity_Grid.creatTree();    //C功能创建最小生成树
				break;
			case 'D':
				Electricity_Grid.DisplayTree(Electricity_Grid.getStart_num()); //D功能显示最小生成树
				cout << endl;
				break;
			default:
				cout << "请输入正确的命令:";
				break;
		}
		cout << "请选择操作:" ;
		cin >> order;
	}
	system("pause");
	return 0;
}