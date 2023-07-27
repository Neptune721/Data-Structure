#include <iostream>
#include <vector>
#include <time.h>　
using namespace std;
/***************************************************************************
  函数名称：swap(int &a, int &b);
  功    能：交换a和b；
  输入参数：元素a和b
  返 回 值：//
  说    明://
***************************************************************************/
void swap(int &a, int &b)
{
	int tmp;
	tmp = a;
	a = b;
	b = tmp;
}
/***************************************************************************
  函数名称：output(int sum, vector<int> storage, int count);
  功    能：格式化输出；
  输入参数：交换次数sum，交换后的数组storage和数组大小count
  返 回 值：//
  说    明://
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
  函数名称：BubbleSort(vector<int> arr,int count);
  功    能：冒泡排序；
  输入参数：数组arr和数组大小count;
  返 回 值：//
  说    明:详情见项目文档
***************************************************************************/
void BubbleSort(vector<int> arr,int count)     //冒泡排序
{
	int sum = 0;
	clock_t start, end;
	start = clock();
	for(int i=0;i<count-1;i++)     //双层循环
		for (int j = 0; j < count - 1 - i; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				swap(arr[j], arr[j + 1]); //数据交换
				sum++;
			}
		}
	end = clock();
	//output(sum, storage, count);
	cout << "冒泡排序所用时间:       " << end - start << endl;
	cout << "冒泡排序交换次数:       " << sum<<endl;
}
/***************************************************************************
  函数名称：SelectionSort(vector<int> arr, int count);
  功    能：选择排序；
  输入参数：数组arr和数组大小count;
  返 回 值：//
  说    明:详情见项目文档
***************************************************************************/
void SelectionSort(vector<int> arr, int count)    //选择排序
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
	cout << "选择排序所用时间:       " << end - start << endl;
	cout << "选择排序交换次数:       " << sum << endl;
}
/***************************************************************************
  函数名称：StraightInsertion(vector<int> arr, int count);
  功    能：直接插入排序；
  输入参数：数组arr和数组大小count;
  返 回 值：//
  说    明:详情见项目文档
***************************************************************************/
void StraightInsertion(vector<int> arr, int count)          //直接插入排序
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
	cout << "直接插入排序所用时间:   " << end - start << endl;
	cout << "直接插入排序交换次数:   " << sum << endl;
}
void ShellSort(vector<int> arr, int count)       //希尔排序
{
	int i, j, gap,sum=0;
	int tmp;
	clock_t start, end;
	start = clock();
	gap = count / 2;//设置增量
	while (gap > 0)//出口
	{
		for (i = gap; i < count; i++)//对所有组采用直接插入排序
		{
			tmp = arr[i];//对相隔d个为止一组采用直接插入排序
			j = i - gap;
			while (j >= 0 && arr[j] > tmp)
			{
				arr[j + gap] = arr[j];
				sum++;
				j = j - gap;
			}
			arr[j + gap] = tmp;
		}
		gap = gap / 2;//减小增量
	}
	end = clock();
	//output(sum, storage, count);
	cout << "希尔排序所用时间:       " << end - start << endl;
	cout << "希尔排序交换次数:       " << sum << endl;
}
void QuickSort(vector<int> &storage,int left,int right,int &sum,int count)           //快速排序
{
	if (left < right)
	{
		int i = left, j = right, x = storage[left];
		while (i < j)
		{
			while (i < j && storage[j] >= x) // 从右向左找第一个小于x的数
				j--;
			if (i < j)
			{
				storage[i++] = storage[j];
				sum++;
			}
			while (i < j && storage[i] < x) // 从左向右找第一个大于等于x的数
				i++;
			if (i < j)
			{
				storage[j--] = storage[i];
				sum++;
			}
		}
		storage[i] = x;
		sum++;
		QuickSort(storage, left, i - 1,sum,count); // 递归调用
		QuickSort(storage, i + 1, right,sum,count);
	}
}
void adjust(vector<int>& arr, int len, int index)
{
	int left = 2 * index + 1; // index的左子节点
	int right = 2 * index + 2;// index的右子节点

	int maxIdx = index;
	if (left<len && arr[left] > arr[maxIdx])     maxIdx = left;
	if (right<len && arr[right] > arr[maxIdx])     maxIdx = right;

	if (maxIdx != index)
	{
		swap(arr[maxIdx], arr[index]);
		adjust(arr, len, maxIdx);
	}

}
// 堆排序
void HeapSort(vector<int> arr, int size)
{
	int sum=0;
	clock_t start, end;
	start = clock();
	// 构建大根堆（从最后一个非叶子节点向上）
	for (int i = size / 2 - 1; i >= 0; i--)
	{
		adjust(arr, size, i);
	}
	// 调整大根堆
	for (int i = size - 1; i >= 1; i--)
	{
		swap(arr[0], arr[i]);           // 将当前最大的放置到数组末尾
		sum++;
		adjust(arr, i, 0);          // 将未完成排序的部分继续进行堆排序
	}
	end = clock();
	cout << "堆排序所用时间:         " << end - start << endl;
	cout << "堆排序交换次数:         " << sum << endl;
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
		//临界位置
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

		//非临界位置
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
void MergeSort(vector<int> &arr,int start,int end,int &sum)              //归并排序
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
void RadixSort(vector<int> arr,int n)             //基数排序
{
	int maxbit = MaxBit(arr, n);
	vector<int> tmp(n, 0);
	vector<int> count(10, 0); //计数器
	int i, j, k;
	int radix = 1;
	clock_t start, end;
	start = clock();
	for (i = 1; i <= maxbit; i++) //进行d次排序
	{
		for (j = 0; j < 10; j++)
			count[j] = 0;                //每次分配前清空计数器
		for (j = 0; j < n; j++)
		{
			k = (arr[j] / radix) % 10; //统计每个桶中的记录数
			count[k]++;
		}
		for (j = 1; j < 10; j++)
			count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
		for (j = n - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中
		{
			k = (arr[j] / radix) % 10;
			tmp[count[k] - 1] = arr[j];
			count[k]--;
		}
		for (j = 0; j < n; j++) //将临时数组的内容复制到data中
			arr[j] = tmp[j];
		radix = radix * 10;
	}
	end = clock();
	cout << "基数排序所用时间:       " << end - start << endl;
	cout << "基数排序交换次数:       0" << endl;
}
void output()
{
	cout << "**                   排序算法比较                **" << endl;
	cout << "===================================================" << endl;
	cout << "**                   1 ---冒泡排序               **" << endl;
	cout << "**                   2 ---选择排序               **" << endl;
	cout << "**                   3 ---直接插入排序           **" << endl;
	cout << "**                   4 ---希尔排序               **" << endl;
	cout << "**                   5 ---快速排序               **" << endl;
	cout << "**                   6 ---堆排序                 **" << endl;
	cout << "**                   7 ---归并排序               **" << endl;
	cout << "**                   8 ---基数排序               **" << endl;
	cout << "**                   9 ---退出程序               **" << endl;
	cout << "===================================================" << endl;
	cout << endl;
}
int main()
{
	int count,sum=0,choice;
	output();
	cout << "请输入要产生的随机数的个数;";
	while (1)                                                      //错误处理
	{
		cin >> count;
		if (cin.fail() || count < 1 )
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入错误，请再次输入产生的随机数的个数 :  ";
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
	cout << "请选择排序算法:         ";
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
				cout << "快速排序所用时间:       " << end - start << endl;
				cout << "快速排序交换次数:       " << sum << endl;
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
				cout << "归并排序所用时间:       " << end - start << endl;
				cout << "归并排序交换次数:       " << sum << endl;
				break;
			}
			case 8:
			{
				RadixSort(storage, count);
				break;
			}
			default:
			{
				cout << "请输入正确的命令";
				break;
			}
		}
		cout << endl;
		cout << "请选择排序算法:         ";
		cin >> choice;
	}
	system("pause");
	return 0;
}