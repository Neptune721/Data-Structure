#include <iostream>
#include <string>
#include <fstream>
#include<vector>
using namespace std;
/***************************************************************************
  �������ƣ�search(string passage, string keyWord);
  ��    �ܣ���passage�г��ֵ�keyWord���м�����
  �������������passage,�ؼ���keyWord;
  �� �� ֵ��//
  ˵    ��:���йؼ��ʵ������ͼ�����
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
	cout << "��Դ�ļ��й�������:" << count << "���ؼ��֡�" << keyWord << "��" << endl;
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
  �������ƣ�main()
  ��    �ܣ������ı��ļ�������д�룬��ȡ������ϵͳ�Ļ���ʵ�֣�
  �������������passage,�ؼ���keyWord���ı��ļ���fileName;
  �� �� ֵ��//
  ˵    ��://
***************************************************************************/
int main()
{
	ofstream out;
	string fileName;
	char text;
	string passage;
	int i=0;
	cout << "�ؼ��ּ���ϵͳ" << endl;
	cout << "�������ļ�����";
	cin >> fileName;
	out.open(fileName, ios::out);
	if (!out)
	{
		cerr << "�ļ����ܱ���" << endl;
		abort();   //��ֹ��ǰ�Ĺ��̣�����һ���������
	}
	cout << endl;
	cout << "������һ��Ӣ�ģ����Ȼس�����Ctrl+Z���ٻس���β��:" << endl;
	cin.get(text);  //ȥ�����ļ������з�
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
	out.close();                //�ر��ı��ļ�
	cin.clear();               //���������ֹ��
	cout << "�����ı��ѱ������ı��ļ���"<<fileName<<"���С�" << endl;
	cout << endl;
	string keyWord;
	cout << "������Ҫ�����Ĺؼ���:";
	cin >> keyWord;
	cout << endl;
	cout << "��ʾԴ�ļ���" << fileName << "����" << endl;
	cout << endl; 
	cout << passage;
	search(passage, keyWord);
	system("pause");
	//cout << "****"<<keyWord<<"******";
	return 0;
}

