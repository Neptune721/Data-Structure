#include <iostream>
#include <string>
#include <fstream>
#include<vector>
using namespace std;
/***************************************************************************
  函数名称：search(string passage, string keyWord);
  功    能：对passage中出现的keyWord进行计数；
  输入参数：文章passage,关键词keyWord;
  返 回 值：//
  说    明:进行关键词的搜索和计数；
***************************************************************************/
void search(string passage, string keyWord)
{
	int count = 0;
	for (int j = 0; j < passage.length(); j++)
	{
		int i = 0;
		while (keyWord[i] == passage[j])
		{
			i++, j++;
			if (i == keyWord.length())
			{
				count++;
			}
		}
	}
	cout << endl;
	cout << "在源文件中共检索到:" << count << "个关键字“" << keyWord << "”" << endl;
	return ;
}
/*void GetFailure(const string& s, int* f)  
{
	
	int j = 0, k = -1;
	f[0] = -1;
	while (j < (s.length() - 1))
		if (k == -1 || s[k] == s[j])
			f[++j] = ++k;
		else
			k = f[k];
}

int KMP_FIND(const string& ob, const string& pat)
{
	int n = pat.length(), m = ob.length();
	int* f = new int[n];
	GetFailure(pat, f);
	int i = 0, j = 0;
	while (i < m && j < n && (m - i) >= (n - j))
	{
		if (j == -1 || ob[i] == pat[j])
		{
			i++; j++;
		}
		else
			j = f[j];
	}
	delete[] f;
	if (j < n)
		return -1;
	else
		return i - j;
}*/
/***************************************************************************
  函数名称：main()
  功    能：建立文本文件并进行写入，读取，进行系统的基本实现；
  输入参数：文章passage,关键词keyWord，文本文件名fileName;
  返 回 值：//
  说    明://
***************************************************************************/
int main()
{
	ofstream out;
	string fileName;
	char text;
	string passage;
	int i=0;
	cout << "关键字检索系统" << endl;
	cout << "请输入文件名：";
	cin >> fileName;
	out.open(fileName, ios::out);
	if (!out)
	{
		cerr << "文件不能被打开" << endl;
		abort();   //中止当前的过程，返回一个错误代码
	}
	cout << endl;
	cout << "请输入一段英文（以先回车，后Ctrl+Z，再回车结尾）:" << endl;
	cin.get(text);  //去输入文件名后换行符
		while (cin.get(text))
		{
			string tmp;
			if (text == '\n') 
				i = 0;
			else i++;
			out << text;
			tmp = text;
			passage = passage + tmp;
			//out.put(text);
			if (i == 50 && text != '\n')
			{
				//out.put('\n');
				out << '\n';
				i = 0;
			}
		}
	out.close();                //关闭文本文件
	cin.clear();               //清除输入终止符
	cout << "本段文本已保存在文本文件“"<<fileName<<"”中。" << endl;
	cout << endl;
	string keyWord;
	cout << "请输入要检索的关键字:";
	cin >> keyWord;
	cout << endl;
	cout << "显示源文件“" << fileName << "”：" << endl;
	cout << endl; 
	cout << passage;
	search(passage, keyWord);
	system("pause");
	//cout << "****"<<keyWord<<"******";
	return 0;
}

