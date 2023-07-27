#include <iostream>
#include <vector>
#include <time.h>��
using namespace std;
/***************************************************************************
  �������ƣ�swap(int &a, int &b);
  ��    �ܣ�����a��b��
  ���������Ԫ��a��b
  �� �� ֵ��//
  ˵    ��://
***************************************************************************/
void swap(int &a, int &b)
{
	int tmp;
	tmp = a;
	a = b;
	b = tmp;
}
/***************************************************************************
  �������ƣ�output(int sum, vector<int> storage, int count);
  ��    �ܣ���ʽ�������
  �����������������sum�������������storage�������Сcount
  �� �� ֵ��//
  ˵    ��://
***************************************************************************/
void output(int sum, vector<int> storage, int count)
{
	for (int i = 0; i < count; i++)
		cout << storage[i] << " ";
	cout << endl;
	cout << sum;
	cout << endl;
}
/***************************************************************************
  �������ƣ�BubbleSort(vector<int> arr,int count);
  ��    �ܣ�ð������
  �������������arr�������Сcount;
  �� �� ֵ��//
  ˵    ��:�������Ŀ�ĵ�
***************************************************************************/
void BubbleSort(vector<int> arr,int count)     //ð������
{
	int sum = 0;
	clock_t start, end;
	start = clock();
	for(int i=0;i<count-1;i++)     //˫��ѭ��
		for (int j = 0; j < count - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]); //���ݽ���
				sum++;
			}
		}
	end = clock();
	//output(sum, storage, count);
	cout << "ð����������ʱ��:       " << end - start << endl;
	cout << "ð�����򽻻�����:       " << sum<<endl;
}
/***************************************************************************
  �������ƣ�SelectionSort(vector<int> arr, int count);
  ��    �ܣ�ѡ������
  �������������arr�������Сcount;
  �� �� ֵ��//
  ˵    ��:�������Ŀ�ĵ�
***************************************************************************/
void SelectionSort(vector<int> arr, int count)    //ѡ������
{
	int min= 0,sum=0;
	clock_t start, end;
	start = clock();
	for (int i = 0; i < count - 1; i++)
	{
		min = arr[i];
		for (int j = i; j <= count - 1; j++)
		{
			if (min > arr[j])
			{
				swap(min, arr[j]);
				sum++;
			}
		}
		arr[i] = min;
	}
	end = clock();
	//output(sum, storage, count);
	cout << "ѡ����������ʱ��:       " << end - start << endl;
	cout << "ѡ�����򽻻�����:       " << sum << endl;
}
/***************************************************************************
  �������ƣ�StraightInsertion(vector<int> arr, int count);
  ��    �ܣ�ֱ�Ӳ�������
  �������������arr�������Сcount;
  �� �� ֵ��//
  ˵    ��:�������Ŀ�ĵ�
***************************************************************************/
void StraightInsertion(vector<int> arr, int count)          //ֱ�Ӳ�������
{
	int sum = 0;
	clock_t start, end;
	start = clock();
	for (int i = 1; i < count; i++)
	{
		int tmp = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > tmp)
		{
			arr[j + 1] = arr[j];
			sum++;
			j--;
		}
		arr[j + 1] = tmp;
	}
	end = clock();
	//output(sum, storage, count);
	cout << "ֱ�Ӳ�����������ʱ��:   " << end - start << endl;
	cout << "ֱ�Ӳ������򽻻�����:   " << sum << endl;
}
void ShellSort(vector<int> arr, int count)       //ϣ������
{
	int i, j, gap,sum=0;
	int tmp;
	clock_t start, end;
	start = clock();
	gap = count / 2;//��������
	while (gap > 0)//����
	{
		for (i = gap; i < count; i++)//�����������ֱ�Ӳ�������
		{
			tmp = arr[i];//�����d��Ϊֹһ�����ֱ�Ӳ�������
			j = i - gap;
			while (j >= 0 && arr[j] > tmp)
			{
				arr[j + gap] = arr[j];
				sum++;
				j = j - gap;
			}
			arr[j + gap] = tmp;
		}
		gap = gap / 2;//��С����
	}
	end = clock();
	//output(sum, storage, count);
	cout << "ϣ����������ʱ��:       " << end - start << endl;
	cout << "ϣ�����򽻻�����:       " << sum << endl;
}
void QuickSort(vector<int> &storage,int left,int right,int &sum,int count)           //��������
{
	if (left < right)
	{
		int i = left, j = right, x = storage[left];
		while (i < j)
		{
			while (i < j && storage[j] >= x) // ���������ҵ�һ��С��x����
				j--;
			if (i < j)
			{
				storage[i++] = storage[j];
				sum++;
			}
			while (i < j && storage[i] < x) // ���������ҵ�һ�����ڵ���x����
				i++;
			if (i < j)
			{
				storage[j--] = storage[i];
				sum++;
			}
		}
		storage[i] = x;
		sum++;
		QuickSort(storage, left, i - 1,sum,count); // �ݹ����
		QuickSort(storage, i + 1, right,sum,count);
	}
}
void adjust(vector<int>& arr, int len, int index)
{
	int left = 2 * index + 1; // index�����ӽڵ�
	int right = 2 * index + 2;// index�����ӽڵ�

	int maxIdx = index;
	if (left<len && arr[left] > arr[maxIdx])     maxIdx = left;
	if (right<len && arr[right] > arr[maxIdx])     maxIdx = right;

	if (maxIdx != index)
	{
		swap(arr[maxIdx], arr[index]);
		adjust(arr, len, maxIdx);
	}

}
// ������
void HeapSort(vector<int> arr, int size)
{
	int sum=0;
	clock_t start, end;
	start = clock();
	// ��������ѣ������һ����Ҷ�ӽڵ����ϣ�
	for (int i = size / 2 - 1; i >= 0; i--)
	{
		adjust(arr, size, i);
	}
	// ���������
	for (int i = size - 1; i >= 1; i--)
	{
		swap(arr[0], arr[i]);           // ����ǰ���ķ��õ�����ĩβ
		sum++;
		adjust(arr, i, 0);          // ��δ�������Ĳ��ּ������ж�����
	}
	end = clock();
	cout << "����������ʱ��:         " << end - start << endl;
	cout << "�����򽻻�����:         " << sum << endl;
}
void Merge(vector<int> &arr, int start, int mid, int end,int &sum)
{
	int length = end - start + 1;
	int* temp_array = new int[length];
	for (int index = 0; index < length; index++)
	{
		temp_array[index] = arr[start + index];
	}
	int i = 0;
	int j = mid - start + 1;
	for (int k = start; k <= end; k++)
	{
		//�ٽ�λ��
		if (i == mid - start + 1)
		{
			arr[k] = temp_array[j++];
			sum++;
			continue;
		}
		if (j == end - start + 1)
		{
			arr[k] = temp_array[i++];
			sum++;
			continue;
		}

		//���ٽ�λ��
		if (temp_array[i] > temp_array[j])
		{
			arr[k] = temp_array[j++];
			sum++;
		}
		else
		{
			arr[k] = temp_array[i++];
			sum++;
		}

	}
	delete[] temp_array;
}
void MergeSort(vector<int> &arr,int start,int end,int &sum)              //�鲢����
{
	if (start >= end)
		return;
	int mid = (start + end) / 2;
	MergeSort(arr, start, mid,sum);
	MergeSort(arr, mid + 1, end,sum);
	Merge(arr, start, mid, end,sum);
}
int MaxBit(vector<int> arr, int count)
{
	int Bit = 1, tmp = 10;
	for (int i = 0; i < count; i++)
	{
		while (arr[i] >= tmp)
		{
			tmp = tmp * 10;
			Bit++;
		}
	}
	return Bit;
}
void RadixSort(vector<int> arr,int n)             //��������
{
	int maxbit = MaxBit(arr, n);
	vector<int> tmp(n, 0);
	vector<int> count(10, 0); //������
	int i, j, k;
	int radix = 1;
	clock_t start, end;
	start = clock();
	for (i = 1; i <= maxbit; i++) //����d������
	{
		for (j = 0; j < 10; j++)
			count[j] = 0;                //ÿ�η���ǰ��ռ�����
		for (j = 0; j < n; j++)
		{
			k = (arr[j] / radix) % 10; //ͳ��ÿ��Ͱ�еļ�¼��
			count[k]++;
		}
		for (j = 1; j < 10; j++)
			count[j] = count[j - 1] + count[j]; //��tmp�е�λ�����η����ÿ��Ͱ
		for (j = n - 1; j >= 0; j--) //������Ͱ�м�¼�����ռ���tmp��
		{
			k = (arr[j] / radix) % 10;
			tmp[count[k] - 1] = arr[j];
			count[k]--;
		}
		for (j = 0; j < n; j++) //����ʱ��������ݸ��Ƶ�data��
			arr[j] = tmp[j];
		radix = radix * 10;
	}
	end = clock();
	cout << "������������ʱ��:       " << end - start << endl;
	cout << "�������򽻻�����:       0" << endl;
}
void output()
{
	cout << "**                   �����㷨�Ƚ�                **" << endl;
	cout << "===================================================" << endl;
	cout << "**                   1 ---ð������               **" << endl;
	cout << "**                   2 ---ѡ������               **" << endl;
	cout << "**                   3 ---ֱ�Ӳ�������           **" << endl;
	cout << "**                   4 ---ϣ������               **" << endl;
	cout << "**                   5 ---��������               **" << endl;
	cout << "**                   6 ---������                 **" << endl;
	cout << "**                   7 ---�鲢����               **" << endl;
	cout << "**                   8 ---��������               **" << endl;
	cout << "**                   9 ---�˳�����               **" << endl;
	cout << "===================================================" << endl;
	cout << endl;
}
int main()
{
	int count,sum=0,choice;
	output();
	cout << "������Ҫ������������ĸ���;";
	while (1)                                                      //������
	{
		cin >> count;
		if (cin.fail() || count < 1 )
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "����������ٴ����������������ĸ��� :  ";
			continue;
		}
		break;
	}
	vector<int> storage(count, 0);
	vector<int> Substitute(count, 0);
	vector<int> Substitute1(count, 0);
	srand((unsigned int)(time(0)));
	for (int i = 0; i < count; i++)
	{
		storage[i] = rand();
		Substitute[i] = storage[i];
		Substitute1[i] = storage[i];
	}
	cout << endl;
	cout << "��ѡ�������㷨:         ";
	cin >> choice;
	while (choice != 9)
	{
		switch (choice)
		{
			case 1:
			{
				BubbleSort(storage, count);
				break;
			}
			case 2:
			{
				SelectionSort(storage, count);
				break;
			}
			case 3:
			{
				StraightInsertion(storage, count);
				break;
			}
			case 4:
			{
				ShellSort(storage, count);
				break;
			}
			case 5:
			{
				clock_t start, end;
				start = clock();
				QuickSort(Substitute, 0, count - 1, sum, count);
				end = clock();
				cout << "������������ʱ��:       " << end - start << endl;
				cout << "�������򽻻�����:       " << sum << endl;
				break;
			}
			case 6:
			{
				HeapSort(storage, count);
				break;
			}
			case 7:
			{
				sum = 0;
				clock_t start, end;
				start = clock();
				MergeSort(Substitute1, 0, count - 1, sum);
				end = clock();
				cout << "�鲢��������ʱ��:       " << end - start << endl;
				cout << "�鲢���򽻻�����:       " << sum << endl;
				break;
			}
			case 8:
			{
				RadixSort(storage, count);
				break;
			}
			default:
			{
				cout << "��������ȷ������";
				break;
			}
		}
		cout << endl;
		cout << "��ѡ�������㷨:         ";
		cin >> choice;
	}
	system("pause");
	return 0;
}