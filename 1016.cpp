#include <iostream>
#include <cstring>
#include <cstdio>
#define MAX 10001
using namespace std;

char A[MAX] = { '0' }, B[MAX] = { '0' };
int lenA = 0, lenB = 0;
int res[MAX] = { 0 };
bool isGreater() {
	return strncmp(A, B, lenB) >= 0;//注意 lenB会因为移位而增大,所以不必担心
}
//把A当前的最高位和B的最高位对齐后相减
void sub() {
	//首先要找到A的最高位 和B进行对齐,由于在while循环里已经进行了大小的判断,此时最高位指的就是真正的最高位
	int i;
	for (i = 0; A[i] == '0'; ++i){}
	//此时begin和i都是最高位的下标 已经是和B对齐的了
	for (; i < lenB; ++i)
		A[i] = A[i] - B[i] + '0'; //注意 如果用 -= 的话 应该是 A[i] -= B[i] - '0'
								  //开始借位 把负数补全 从右向左借
	for (int i = lenB - 1; i >0; --i) 
		if (A[i]<'0')
		{
			A[i] += 10;
			A[i - 1]--;
		}
}

int main()
{
	cin >> A >> B;
	lenA = strlen(A);
	lenB = strlen(B);
	//若A小于B 直接输出0结束.
	if (lenA<lenB || (lenA == lenB && !isGreater())) {
		cout << 0 << endl; return 0;
	}
	int res_i = 0; //标记res数组正在处理的下标 0是最高位
	while (1) { //当最后对齐时break
				//开始对A和B的前lenB位进行循环减法

		while (isGreater()) {
			sub();
			++res[res_i];
		}
		++res_i;
		//若上一次的余数小于B的位数,则cot为0没有问题
		if (lenA == lenB)    //必须在减法循环结束之后立刻检验 因为移位之后lenB发生了变化 而且也没有必要
			break;
		//对B进行向右移动 注意lenB要增加1
		int j;
		for (j = lenB++; j > 0; --j)
			B[j] = B[j - 1];
		B[j] = '0';
	}
	bool flag = true;//表示以后有0不输出
	for (int i = 0; i < res_i; ++i)
	{
		if (flag && res[i] != 0)
			flag = false;//已经遇到了 第一个不是0的数 表示以后有0输出
		if (res[i] == 0) {
			if (!flag)
				cout << 0;
		}
		else
			cout << res[i];

	}
	cout << endl;
	return 0;
}