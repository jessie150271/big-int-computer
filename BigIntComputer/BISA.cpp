#include "BISA.h"
using namespace std;
BigIntAddSub::BigIntAddSub()
{
	num.bigNum = "0";
	num.sign = false;
}

BigIntAddSub::BigIntAddSub(string a)
{
	if (a[0] == '-')
	{
		num.sign = true;//-
		a.erase(a.begin());
	}
	else
		num.sign = false;//+
	num.bigNum = a;
}

N BigIntAddSub::getNumber()
{
	return num;
}

string BigIntAddSub::bigIntAdd(N A, N B)
{
	N ans, temp;
	int size1 = A.bigNum.size(), size2 = B.bigNum.size();
	if (A.sign && !B.sign)
	{
		A.sign = false;//-A→+A
		ans.bigNum = bigIntSub(B, A);
		return ans.bigNum;
	}
	else if (!A.sign && B.sign)
	{
		B.sign = false;//-B→+B
		ans.bigNum = bigIntSub(A, B);
		return ans.bigNum;
	}
	else
	{
		if (size1 >= size2)
		{
			ans = A;
			temp = B;
		}
		else
		{
			ans = B;
			temp = A;
		}
	}
	size1 = ans.bigNum.size();
	size2 = temp.bigNum.size();
	int i = size1 - 1, j = size2 - 1;

	for (i; i >= 0; i--, j--)
	{
		if (j >= 0)
			ans.bigNum[i] += temp.bigNum[j] - '0';
		if (ans.bigNum[i] > '9')
		{
			ans.bigNum[i] -= 10;
			if (i > 0)
				ans.bigNum[i - 1] += 1;
			else if (i == 0)
				ans.bigNum.insert(ans.bigNum.begin(), '1');
		}
	}
	if (ans.sign)
		return "-" + ans.bigNum;
	else
		return ans.bigNum;
}

string BigIntAddSub::bigIntSub(N A, N B)
{
	N ans, temp;
	int token = 0;//紀錄位數相同時從頭算起第一個不同的數字
	int size1 = A.bigNum.size(), size2 = B.bigNum.size();
	if (A.sign && !B.sign)//-A - B = -A + -B
	{
		B.sign = true;
		ans.bigNum = bigIntAdd(A, B);
		return ans.bigNum;
	}
	else if (!A.sign&&B.sign)//A - -B = A + B
	{
		B.sign = false;
		ans.bigNum = bigIntAdd(A, B);
		return ans.bigNum;
	}
	else if (A.sign&&B.sign)//-A - -B= -A + B = B-A
	{
		A.sign = B.sign = false;
		ans.bigNum = bigIntSub(B, A);
		return ans.bigNum;
	}
	else if (!A.sign && !B.sign)//A - B
	{
		if (size1 > size2)
		{
			ans = A;
			temp = B;
		}
		else if (size1 < size2)
		{
			ans = B;
			ans.sign = true;
			temp = A;
			size1 = ans.bigNum.size();
			size2 = temp.bigNum.size();
		}
		else if (size1 == size2)
		{
			for (int i = 0; i < size1; i++)
			{
				if (A.bigNum[i] > B.bigNum[i])
				{
					ans = A;
					temp = B;
					break;
				}
				else if (A.bigNum[i] < B.bigNum[i])
				{
					ans = B;
					temp = A;
					size1 = ans.bigNum.size();
					size2 = temp.bigNum.size();
					ans.sign = true;
					break;
				}
				else if (i == size1 - 1)
					return "0";
				token = i;
			}
		}
	}
	int i = size1 - 1, j = size2 - 1;
	for (i; i >= 0; i--, j--)
	{
		if (j >= 0)
			ans.bigNum[i] -= temp.bigNum[j] - '0';
		if (ans.bigNum[i] < '0')
		{
			ans.bigNum[i] += 10;
			if (i > 0)
				ans.bigNum[i - 1] -= 1;
		}
	}

	for (; ans.bigNum.size() > 1;)
	{
		if (ans.bigNum[0] == '0')
			ans.bigNum.erase(ans.bigNum.begin());
		else
			break;
	}
	if (ans.sign)
		return "-" + ans.bigNum;
	else
		return ans.bigNum;
}