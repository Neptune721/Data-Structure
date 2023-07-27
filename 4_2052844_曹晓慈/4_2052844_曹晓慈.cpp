#include <iostream>
#include <vector>
using namespace std;
int N,sum=0;
/***************************************************************************
  函数名称：output(vector<int> &vec);
  功    能：进行N皇后解答后的输出；
  输入参数：记录好位置的vec数组
  返 回 值：//
  说    明://
***************************************************************************/
void output(vector<int> &vec)
{
	vector<vector<int>> mark(N+1, vector<int>(N+1, 0));
	for (int i = 1; i <= N; i++) 
	{
			//mark[i][vec[i]] = 1;
		mark[vec[i]][i] = 1;
	}
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			if (mark[i][j] == 1)
				cout << "* ";
			else
				cout << "0 ";
		}
		cout << endl;
	}
	cout << endl;
}
/***************************************************************************
  函数名称：check(int t,vector<int> &vec);
  功    能：检查皇后位置是否满足要求
  输入参数：第t个皇后，和皇后所在位置的数组vec;
  返 回 值：0或1
  说    明:0为不满足要求，1满足
***************************************************************************/
int check(int t,vector<int> &vec)
{
	for (int j = 1; j < t; j++)
	{
		if ((vec[j] == vec[t]) || (abs(vec[j] - vec[t]) == abs(j - t)))
			return 0;
	}
	return 1;
}
/***************************************************************************
  函数名称：BackTrace(int t,vector<int> &vec);
  功    能：回溯法寻找可行的摆法
  输入参数：摆好的皇后数t，记录皇后摆的位置vec;
  返 回 值：//
  说    明:详情见项目文档
***************************************************************************/
void BackTrace(int t,vector<int> &vec)
{
	if (t > N)
	{
		sum++;
		output(vec);
	}
	else
	{
		for (int i = 1; i <= N; i++)
		{
			vec[t] = i;
			if (check(t,vec))
			{
				BackTrace(t + 1,vec);
			}
		}
	}
}
/***************************************************************************
  函数名称：main();
  功    能：主要逻辑的实现，输入，输入错误判断和格式化输出；
  输入参数：皇后数目N;
  返 回 值：//
  说    明://
***************************************************************************/
int main()
{
	cout << "现有N*N的棋盘，放入N个皇后，要求所有皇后不在同一行.列和同一斜线上!" << endl;
	cout << endl;
	cout << "请输入皇后的个数(大于等于4）:";
	while (1)
	{
		cin >> N;
		if (cin.fail() || N < 4)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入错误，请再次输入皇后的个数(大于等于4） :" << endl;
			continue;
		}
		break;
	}
	cout << endl;
	cout << "皇后摆法:" << endl;
	cout << endl;
	vector<int> vec(N+1, 0);
	BackTrace(1,vec);
	cout << "共有" << sum << "种解法!" << endl;
	system("pause");
	return 0;
}
