#include "Number.h"
using namespace std;
class Integer;
class DEcimal;
class Complex;
//��J���N�ƾǦ�
void Number::setInput(const string& line)
{
	input.clear();
	istringstream ss(line);
	string in, temp;
	//�����Ů�
	while (ss >> in)
		temp += in;
	//�N�t���ন'!'
	for (int i = 0; i < temp.size(); i++)
	{
		if (i != temp.size() - 1)
		{
			//i������0�Btemp[i]����'-'  ��  temp[i]='-'�Btemp[i+1]='-'
			if ((!i && temp[i] == '-') || ((temp[i] < '0' || temp[i] == '^') && temp[i] != ')' && temp[i + 1] == '-'))
			{
				if (i && temp[i] != '-' || ((temp[i] < '0' || temp[i] == '^') && temp[i] != ')' && temp[i + 1] == '-'))
					input += temp[i++];	//input += '-'(�)
				input += '#';			//input += '#'(�t��)
				continue;
			}
		}
		input += temp[i];
	}
}

//�P�_�r��B�ഫ��Ǧ�
void Number::computInput()
{
	vector<string> _operator, postfix;//stack���|  _operator(���|�����B��l)  postfix(��Ǧ�)
	vector<int> operatorPriority;//�s���|���B��l���u������
	int nowPriority;//�s��e�B��l�u������
	for (int i = 0; i < input.size(); i++)
	{
		//�J�B�⤸������X�� postfix(��Ǧ�)
		if (input[i] <= '9' && input[i] >= '0' || input[i] == '.')
		{
			string temp;
			int j = i;
			while (j < input.size() && (input[j] <= '9' && input[j] >= '0' || input[j] == '.'))
			{
				temp += input[j];//��e�B�⤸
				j++;
			}
			postfix.push_back(temp);
			i = j - 1;
		}
		//�J�k�A��')'��Xstack����operator��')'
		else if (input[i] == ')')
		{
			while (!_operator.empty())
			{
				int top = _operator.size() - 1;
				if (_operator[top] == "(") {
					_operator.pop_back();
					operatorPriority.pop_back();
					break;
				}
				postfix.push_back(_operator[top]);
				_operator.pop_back();
				operatorPriority.pop_back();
			}
		}
		//��L���p�G����B��l�u�����ǡA�çP�_�n�s�J�B��l���|�ο�X�ܫ�Ǧ�
		else {
			switch (input[i])
			{
			case'(':	//���A���u���סG6
				nowPriority = priority[6];
				break;
			case'#':	//�t�����u���סG5
				nowPriority = priority[5];
				break;
			case'i':	//�곡�u���סG4
				nowPriority = priority[4];
				break;
			case'!':	//�����u���סG3
				nowPriority = priority[3];
				break;
			case'^':	//�����u���סG2
				nowPriority = priority[2];
				break;
			case'*':	//�������u���סG1
				nowPriority = priority[1];
				break;
			case'/':	//�������u���סG1
				nowPriority = priority[1];
				break;
			case'+':	//�[�����u���סG0
				nowPriority = priority[0];
				break;
			case'-':	//����u���סG0
				nowPriority = priority[0];
				break;
			}
			//stack�̤W��B��l�u���� �j�󵥩� ��e�B��l�u���� �� ��X��postfix(��Ǧ�)
			//�Y�̤W��B��l�����A���A�h�������|�B��l
			if (!operatorPriority.empty())
			{
				while (operatorPriority[operatorPriority.size() - 1] != 6
					&& operatorPriority[operatorPriority.size() - 1] >= nowPriority)
				{
					postfix.push_back(_operator[_operator.size() - 1]);
					_operator.pop_back();
					operatorPriority.pop_back();
					if (operatorPriority.empty())
						break;
				}
			}
			string operat;//���|operator
			operat = input[i];//char ��s string
			_operator.push_back(operat);//���|��e�B��l��_operator
			operatorPriority.push_back(nowPriority);//���|�B��l�u���צ�operatorPriority
		}
	}
	while (!(_operator.empty()))
	{
		postfix.push_back(_operator[_operator.size() - 1]);
		_operator.pop_back();
		operatorPriority.pop_back();
	}
	
	//�B���Ǧ�
	vector<Fraction> stack;//stack[���|�����j��(���ƫ��A)]
	for (int i = 0; i < postfix.size(); i++)
	{
		if ((postfix[i][0] < '0' || postfix[i][0] == '^' || postfix[i][0] == 'i') && !stack.empty())
		{
			if (postfix[i][0] == '#') //�t��
			{
				changeSign(stack[stack.size() - 1]);
			}
			else if (postfix[i][0] == 'i') //�곡
			{
				stack[stack.size() - 1] = toImag(stack[stack.size() - 1]);
			}
			else if (postfix[i][0] == '!')
			{
				stack[stack.size() - 1] = fracFac(stack[stack.size() - 1]);
			}
			else if (stack.size() >= 2)
			{
				switch (postfix[i][0])
				{
				case'+':
					stack[stack.size() - 2] = fracAdd(stack[stack.size() - 2], stack[stack.size() - 1]);
					stack.pop_back();
					break;
				case'-':
					stack[stack.size() - 2] = fracSub(stack[stack.size() - 2], stack[stack.size() - 1]);
					stack.pop_back();
					break;
				case'*':
					stack[stack.size() - 2] = fracMul(stack[stack.size() - 2], stack[stack.size() - 1]);
					stack.pop_back();
					break;
				case'/':
					stack[stack.size() - 2] = fracDiv(stack[stack.size() - 2], stack[stack.size() - 1]);
					stack.pop_back();
					break;
				case'^':
					stack[stack.size() - 2] = fracPow(stack[stack.size() - 2], stack[stack.size() - 1]);
					stack.pop_back();
					break;
				default:
					break;
				}
			}
		}
		else
		{
			stack.push_back(posToStack(postfix[i]));
		}

		if (i == postfix.size() - 1)
			fracAns = stack[0];
	}
}

/***********************************************
***************** �� �Ƽƹ�@ �� ***************
************************************************/
//������곡
Fraction Number::toImag(Fraction f)
{
	if (f.denominator == "0" && f.numerator == "0")
		return f;
	f.comSign = true;

	f.imag.denominator = f.denominator;
	f.imag.numerator = f.numerator;
	f.imag.sign = f.sign;
	f.sign = false;
	f.denominator = f.numerator = "0";
	return f;
}

//�곡��곡
void Number::imagToReal(Fraction f, Fraction& a)
{
	a.numerator = f.imag.numerator;
	a.denominator = f.imag.denominator;
	a.sign = f.imag.sign;
	return;
}

//�곡��곡
void Number::realToImag(Fraction& f, Fraction a)
{
	if (a.numerator == "0" && a.denominator == "0")
	{
		f.imag.numerator = "0";
		f.imag.denominator = "0";
		f.comSign = false;
		return;
	}
	f.imag.numerator = a.numerator;
	f.imag.denominator = a.denominator;
	f.imag.sign = a.sign;
	f.comSign = true;
	return;
}

//�Ƽƥ[�k
Fraction Number::comAdd(Fraction left, Fraction right)
{
	Fraction ans, a, b;
	left.comSign = right.comSign = false;
	imagToReal(left, a);
	imagToReal(right, b);

	ans = fracAdd(left, right); //�곡�ۥ[
	a = fracAdd(a, b); //�곡�ۥ[

	realToImag(ans, a);
	if (ans.imag.numerator != "0" && ans.imag.denominator != "0")
		ans.comSign = true;
	return ans;
}

//�Ƽƴ�k
Fraction Number::comSub(Fraction left, Fraction right)
{
	Fraction ans, a, b;
	left.comSign = right.comSign = false;
	imagToReal(left, a);
	imagToReal(right, b);

	ans = fracSub(left, right); //�곡�۴�
	a = fracSub(a, b); //�곡�۴�

	realToImag(ans, a);
	if (ans.imag.numerator != "0" && ans.imag.denominator != "0")
		ans.comSign = true;
	return ans;
}

//�Ƽƭ��k
Fraction Number::comMul(Fraction left, Fraction right)
{
	Fraction ans, a, b;
	left.comSign = right.comSign = false;
	imagToReal(left, a);
	imagToReal(right, b);
	Fraction t1 = fracMul(left, right), t2 = fracMul(a, b);
	ans = fracSub(fracMul(left, right), fracMul(a, b));	//�곡
	a = fracAdd(fracMul(left, b), fracMul(right, a));	//�곡
	if (a.denominator != "0")
		a = about(a);
	if (ans.denominator != "0")
		ans = about(ans);

	realToImag(ans, a);
	if (ans.imag.numerator != "0" && ans.imag.denominator != "0")
		ans.comSign = true;
	return ans;
}

//�Ƽư��k
Fraction Number::comDiv(Fraction left, Fraction right)
{
	Fraction ans, temp, a, b, p;
	left.comSign = right.comSign = false;
	imagToReal(left, a);
	imagToReal(right, b);
	// p=2
	p.numerator = "2";
	p.denominator = "1";

	ans = fracAdd(fracMul(left, right), fracMul(a, b));	//�곡
	temp = fracSub(fracMul(right, a), fracMul(left, b));//�곡

	Fraction t1 = fracAdd(fracPow(right, p), fracPow(b, p)), t2 = fracPow(right, p), t3 = fracPow(b, p);

	ans = fracDiv(ans, fracAdd(fracPow(right, p), fracPow(b, p))); //�곡
	temp = fracDiv(temp, fracAdd(fracPow(right, p), fracPow(b, p))); //�곡

	realToImag(ans, temp);
	if (ans.imag.numerator != "0" && ans.imag.denominator != "0")
		ans.comSign = true;
	return ans;
}

//�ƼƦ���
Fraction Number::comPow(Fraction a, Fraction b)
{
	if (b.numerator == "1" && b.denominator == "2")
		return comRoot(a, b.sign);
	else if (b.denominator == "0")
	{
		Fraction f;
		f.numerator = f.denominator = "1";
		return f;
	}
	else if (b.denominator != "1")
		cout << "Illegal Power(a,b)" << endl;

	//if (right == "0.5" || right == "1/2")  return root(left);
	int tempPow = 0, count = 0;

	for (int i = 0; i < b.numerator.size(); i++)   //�r������
	{
		tempPow *= count;
		tempPow += (b.numerator[i] - '0');
		count = 10;
	}

	Fraction ans, t, temp;
	Fraction basisTwo = comMul(a, a);  //�G����
	string ts = "0.";
	ts.insert(ts.end(), 110, '0');
	imagToReal(basisTwo, t);
	if (get110Dec(t) == ts)
		realToImag(basisTwo, temp);
	if (get110Dec(basisTwo) == ts)
	{
		imagToReal(temp, basisTwo);
	}

	int i;
	if (tempPow % 2 == 0)
	{
		ans = basisTwo;
		i = 1;
	}
	else
	{
		ans = a;
		i = 0;
	}
	tempPow /= 2;

	for (i; i < tempPow; i++)
	{
		imagToReal(basisTwo, t);
		if (get110Dec(t) == ts)
			realToImag(basisTwo, temp);
		if (get110Dec(basisTwo) == ts)
		{
			imagToReal(temp, basisTwo);
		}
		ans = comMul(ans, basisTwo);
	}

	if (b.sign)
	{
		Fraction i;
		i.numerator = i.denominator = "1";
		return comDiv(i, ans);
	}

	return ans;
}


/***********************************************
***************** �� �Ƽƹ�@ �� ***************
************************************************/



/***********************************************
***************** �� �ڸ���@ �� ***************
************************************************/

//���ƶ}�ڸ�
Fraction Number::fracRoot(Fraction f, bool sign)
{
	if (f.comSign)
		return comRoot(f, sign);
	if (f.sign)
	{
		Fraction t;
		f.sign = false;
		f = fracRoot(f, sign);
		realToImag(t, f);
		return t;
	}
	string t1, t2, s;
	t1 = getRoot120(f.numerator);
	t2 = getRoot120(f.denominator);
	s.insert(s.end(), 50, '0');
	size_t f1, f2;
	f1 = t1.find('.');
	f2 = t2.find('.');
	if (t1.substr(f1 + 1, 50) == s && t2.substr(f2 + 1, 50) == s)
	{
		f.numerator.assign(t1.begin(), t1.begin() + f1);
		f.denominator.assign(t2.begin(), t2.begin() + f2);
		if (sign)
		{
			string temp = f.denominator;
			f.denominator = f.numerator;
			f.numerator = temp;
		}
		return f;
	}
	else
	{
		t1.erase(f1, 1);
		t2.erase(f2, 1);
		if (sign)
			f.numerator = t2, f.denominator = t1;
		else
			f.numerator = t1, f.denominator = t2;
	}
	if (f.denominator != "0")
		f = about(f);
	return f;
}

//�Ƽƶ}�ڸ�
Fraction Number::comRoot(Fraction a, bool sign)
{
	//a:�곡 b:�곡
	//t1: x^2+y^2 = root(a^2+b^2)
	//t2: 2*x*y = b
	Fraction x, y, b, t1, t, p;
	a.comSign = false;
	imagToReal(a, b);
	p.numerator = "2", p.denominator = "1";
	bool k = false;
	t1 = fracRoot(fracAdd(fracPow(a, p), fracPow(b, p)), k);
	t = fracRoot(fracAdd(t1, b), k);
	b = fracRoot(fracSub(t1, b), k);
	if (a.sign)
	{
		x = fracDiv(fracSub(t, b), p);
		y = fracSub(t, x);
		realToImag(x, y);
	}
	else
	{
		y = fracDiv(fracSub(t, b), p);
		x = fracSub(t, y);
		realToImag(x, y);
	}
	p.numerator = "1";
	
	if (sign)
		return fracDiv(p, x);
	return x;
}

/***********************************************
***************** �� �ڸ���@ �� ***************
************************************************/



/***********************************************
***************** �� ���ƹ�@ �� ***************
************************************************/
//��Ǧ�string �ন���l�B��������
Fraction Number::posToStack(string pos)
{
	//�P�_�O�_���p��
	int index = 0;
	for (int i = 0; i < pos.size() - 1; i++)
	{
		if (pos[i] == '.')
		{
			index = i;
			break;
		}
	}
	Fraction f;
	if (index == 0 || pos == "0")
	{
		if (pos != "0")
		{
			f.numerator.assign(pos);
			f.denominator = "1";
		}
		else
			f.denominator = "0";
	}
	else
	{
		string a = "1";
		pos.erase(pos.begin() + index);
		for (int i = pos.size() - index; i > 0; i--)
			a.push_back('0');
		f.denominator.assign(a);
		while (pos.size())
		{
			if (pos[0] == '0')
				pos.erase(pos.begin());
			else if (pos[0] != '0')
				break;
		}
		f.numerator.assign(pos);
	}
	if (f.denominator != "0")
		f = about(f);//����
	return f;
}

//�t��
void Number::changeSign(Fraction& f)
{
	if (f.numerator != "0" && f.denominator != "0")
		f.sign = !f.sign;
	if (f.comSign)
		if (f.imag.numerator != "0" && f.imag.denominator != "0")
			f.imag.sign = !f.imag.sign;
}

//����
Fraction Number::about(Fraction f)
{
	if (f.numerator.size() > 150 && f.denominator.size() > 150)
	{
		long long s1 = f.numerator.size(), s2 = f.denominator.size();
		s1 -= s2;
		f.numerator.erase(f.numerator.begin() + 150 + s1, f.numerator.end());
		f.denominator.erase(f.denominator.begin() + 150, f.denominator.end());
	}
	string g = gcd(f.numerator, f.denominator);
	int c1 = cmp(g, f.numerator), c2 = cmp(g, f.denominator);
	f.numerator = div(f.numerator, g);
	f.denominator = div(f.denominator, g);

	return f;
}

//�̤j���]��GCD
string Number::gcd(string a, string b)
{
	if (b == "0")
		return a;
	else
		return gcd(b, mod(a, b));
}

//���l�� left%right
string Number::mod(string left, string right)
{
	string a = left;
	a += 'r';//�[�@�ӧP�_�r��
	return div(a, right);
}

//���t���P�_
bool Number::sign(string& str)
{
	bool s = false;
	if (str[0] == '-')
	{
		s = true;
		str.erase(str.begin());
	}
	return s;
}

//���Ʀ���
Fraction Number::fracPow(Fraction a, Fraction b)
{


	if ((b.denominator != "1"&&b.denominator != "0")&&!(b.numerator == "1" && b.denominator == "2") || 
		(b.comSign && b.imag.denominator!="0"))
	{
		if (errorTyep == -1)
			errorTyep = 2;
		return a;
	}
	if (a.comSign)
		return comPow(a, b);
	if (b.numerator == "1" && b.denominator == "2")
		return fracRoot(a, b.sign);
	else if (b.denominator == "0")
	{
		a.numerator = a.denominator = "1";
		a.sign = false;
		return a;
	}
	if (mod(b.numerator, "2") == "0")
		a.sign = false;

	a.numerator = pow(a.numerator, b.numerator);
	a.denominator = pow(a.denominator, b.numerator);

	if (a.denominator != "0")
		a = about(a);//����

	if (b.sign)
	{
		string temp;
		temp = a.denominator;
		a.denominator = a.numerator;
		a.numerator = temp;
	}
	return a;
}

//����
Fraction Number::fracFac(Fraction f)
{
	string s = get100Dec(f);
	f = posToStack(s);
	if (f.denominator == "0" && f.numerator == "0")
	{
		Fraction ret;
		ret.numerator = "1"; 
		ret.denominator = "1";
		return ret;
	}
	
	if (f.denominator != "1" || f.comSign == true || f.sign)
	{
		if (errorTyep == -1)
			errorTyep = 1;
	}
	else
		f.numerator = fac(f.numerator);
	return f;
}

//���ƥ[�k
Fraction Number::fracAdd(Fraction left, Fraction right)
{
	if (left.comSign || right.comSign)
		return comAdd(left, right);
	Fraction f;
	//�٭�t��
	if (left.sign)
		left.numerator.insert(0, "-");
	if (right.sign)
		right.numerator.insert(0, "-");

	int c = cmp(left.denominator, right.denominator);
	if (c == 0)//�Y�����ۦP�A���l�����ۥ[
	{
		f.numerator = add(left.numerator, right.numerator);
		f.denominator = left.denominator;
	}
	else if (left.numerator == "0" && left.denominator == "0")
	{
		right.sign = sign(right.numerator);
		return right;
	}
	else if (right.numerator == "0" && right.denominator == "0")
	{
		left.sign = sign(left.numerator);
		return left;
	}
	else//�Y�������ۦP�A�q����ۥ[
	{
		f.denominator = mul(left.denominator, right.denominator);
		left.numerator = mul(left.numerator, right.denominator);
		right.numerator = mul(right.numerator, left.denominator);
		f.numerator = add(left.numerator, right.numerator);
	}
	f.sign = sign(f.numerator);
	if (f.numerator == "0")
		f.denominator = "0";
	if (f.denominator != "0")
		f = about(f);//����
	return f;
}

//���ƴ�k
Fraction Number::fracSub(Fraction left, Fraction right)
{
	if (left.comSign || right.comSign)
		return comSub(left, right);
	Fraction f;
	//�٭�t��
	if (left.sign)
		left.numerator.insert(0, "-");
	if (right.sign)
		right.numerator.insert(0, "-");

	int c = cmp(left.denominator, right.denominator);
	if (c == 0)//�Y�����ۦP�A���l�����ۥ[
	{
		f.numerator = sub(left.numerator, right.numerator);
		f.denominator = left.denominator;
	}
	else if (left.numerator == "0" && left.denominator == "0")
	{
		right.sign = !sign(right.numerator);
		return right;
	}
	else if (right.numerator == "0" && right.denominator == "0")
	{
		left.sign = sign(left.numerator);
		return left;
	}
	else//�Y�������ۦP�A�q����۴�
	{
		f.denominator = mul(left.denominator, right.denominator);
		left.numerator = mul(left.numerator, right.denominator);
		right.numerator = mul(right.numerator, left.denominator);
		f.numerator = sub(left.numerator, right.numerator);
	}
	f.sign = sign(f.numerator);
	if (f.numerator == "0")
		f.denominator = "0";
	if (f.denominator != "0")
		f = about(f);//����
	return f;
}

//���ƭ��k
Fraction Number::fracMul(Fraction left, Fraction right)
{
	if (left.comSign || right.comSign)
		return comMul(left, right);
	Fraction f;
	if (left.sign && right.sign)
		f.sign = false;
	else if (left.sign || right.sign)
		f.sign = true;
	else f.sign = false;



	f.numerator = mul(left.numerator, right.numerator);
	f.denominator = mul(left.denominator, right.denominator);

	if (f.numerator == "0"&&f.denominator == "0")
		f.sign = false;

	if (f.denominator != "0")
		f = about(f);//����
	return f;
}

//���ư��k
Fraction Number::fracDiv(Fraction left, Fraction right)
{
	if (right.denominator == "0"&&right.imag.denominator == "0")
	{
		if (errorTyep == -1)
			errorTyep = 3;
		return left;
	}
	if (left.comSign || right.comSign)
		return comDiv(left, right);
	Fraction f;
	if (left.sign && right.sign)
		f.sign = false;
	else if (left.sign || right.sign)
		f.sign = true;
	else f.sign = false;

	//���ۭ������� �~�ۭ������l

	f.numerator = mul(left.numerator, right.denominator);
	f.denominator = mul(left.denominator, right.numerator);

	if (f.denominator != "0")
		f = about(f);//����
	return f;
}
/***********************************************
***************** �� ���ƹ�@ �� ***************
************************************************/



/***********************************************
***************** �� ��ƹ�@ �� ***************
************************************************/
//�j�Ʀ���
string Number::pow(string left, string right)
{
	if (right == "1")
		return left;
	if (right == "2")
		return mul(left, left);

	int tempPow = 0, count = 10;

	for (int i = 0; i < right.size(); i++)   //�r������
	{
		tempPow *= count;
		tempPow += (right[i] - '0');
	}

	int ret = tempPow / 2;
	return mul(pow(left, to_string(ret)), pow(left, to_string(tempPow - ret)));
	//}
	////if (right == "0.5" || right == "1/2")  return root(left);
	//if (right == "0") return "1";

	//int tempPow = 0, count = 10;

	//for (int i = 0; i < right.size(); i++)   //�r������
	//{
	//	tempPow *= count;
	//	tempPow += (right[i] - '0');
	//}

	//string ans;
	//int i;
	//if (tempPow % 2 == 0)
	//{
	//	ans = mul(left, left);
	//	i = 1;
	//}
	//else
	//{
	//	ans = left;
	//	i = 0;
	//}
	//tempPow /= 2;

	//string basisTwo = mul(left, left);  //�G����

	//for (i; i < tempPow; i++)
	//	ans = mul(ans, basisTwo);

	//return ans;
}

//�j�ƶ���
string Number::fac(string str)
{
	int n = 0, count = 0;
	for (int i = 0; i<str.size(); i++)
	{
		n *= count;
		n += (str[i] - '0');
		count = 10;
	}
	vector<int> ans;
	ans.push_back(1);
	int res_size = 1;
	for (int x = 2; x <= n; x++)
		res_size = multiply(x, ans, res_size);

	str.clear();
	for (int i = res_size - 1; i >= 0; i--)
		str += ans[i] + '0';
	return str;
}

//����function
int Number::multiply(int x, vector<int> &ans, int res_size)
{
	int carry = 0;
	for (int i = 0; i < res_size; i++)
	{
		int prod = ans[i] * x + carry;
		ans[i] = prod % 10;
		carry = prod / 10;
	}
	while (carry)
	{
		ans.push_back(carry % 10);
		carry = carry / 10;
		res_size++;
	}
	return res_size;
}

//�j�ƥ[�k left+fight
string Number::add(string left, string right)
{
	BigIntAddSub A(left), B(right);
	return A.bigIntAdd(A.getNumber(), B.getNumber());
}

//�j�ƴ�k left-right
string Number::sub(string left, string right)
{
	BigIntAddSub A(left), B(right);
	return A.bigIntSub(A.getNumber(), B.getNumber());
}

//�j�ƭ��k left*right
string Number::mul(string left, string right)
{
	//�P�_���t��
	bool mulSign = false;//�s���t���Adefault������(false)
	if (left[0] == '-'&&right[0] == '-')
	{
		left.erase(left.begin());
		right.erase(right.begin());
	}
	else if (left[0] == '-')
	{
		left.erase(left.begin());
		mulSign = true;
	}
	else if (right[0] == '-')
	{
		right.erase(right.begin());
		mulSign = true;
	}

	//�j�ƭ��k��@
	int integer[10] = { 0,1,2,3,4,5,6,7,8,9 };
	vector<int> num;
	int now = 0, next, index;
	for (int j = right.size() - 1; j >= 0; j--)
	{
		index = right.size() - j - 1;
		for (int i = left.size() - 1; i >= 0; i--, index++)
		{
			next = 0;
			if (integer[left[i] - '0'] != 0 && integer[right[j] - '0'] != 0) //�J�s�i��
			{
				now += integer[left[i] - '0'] * integer[right[j] - '0'];
			}
			if (now >= 10)//�W�L10�N�i���next
			{
				next += now / 10;
				now %= 10;
			}
			if (num.size() <= index)
				num.push_back(now);
			else
			{
				num[index] += now;
				if (num[index] >= 10)//�W�L10�N�i���next
				{
					next += num[index] / 10;
					num[index] %= 10;
				}
			}
			now = next;
		}
		while (now > 0)
		{
			num.push_back(now % 10);
			now /= 10;
		}
	}
	while (now > 0)
	{
		num.push_back(now % 10);
		now /= 10;
	}


	//����vector<int>���নstring
	string strNum;
	bool zero = true;
	for (int i = num.size() - 1; i >= 0; i--)
	{
		if (num[i] != 0)
			zero = false;
		if (!zero)
			strNum += num[i] + '0';
		else if (i == 0)
			strNum = "0";
	}
	if (mulSign && strNum != "0")
		return "-" + strNum; //�ۭ����G���t��
	return strNum;	//�ۭ����G������
}

//�j�ư��k left/right �����l�ƥ\��
string Number::div(string left, string right)
{
	bool r = false;//�P�_�O�_�n���l��
	if (left[left.size() - 1] == 'r')
	{
		r = true;
		left.pop_back();
	}

	if (right == "0")
	{
		cout << "Illegal input!" << endl;
		return "0";
	}
	//�P�_���t��
	bool divSign = false;//�s���t���Adefault������(false)
	if (left[0] == '-'&&right[0] == '-')
	{
		left.erase(left.begin());
		right.erase(right.begin());
	}
	else if (left[0] == '-')
	{
		left.erase(left.begin());
		divSign = true;
	}
	else if (right[0] == '-')
	{
		right.erase(right.begin());
		divSign = true;
	}

	string rem; //�l��
				//�P�_�j�p
	int c = cmp(left, right);
	if (c == 0)//��Ƭ۵�
	{
		rem = "0";
		if (r)
			return rem;
		if (divSign)
			return "-1";
		return "1";
	}
	else if (c == 1)//����>�Q����
	{
		rem = left;
		if (r)
			return rem;
		return "0";
	}
	else
	{
		string rem = left, R = right;
		string quotient;
		int s = left.size() - right.size() + 1;
		for (int i = 0; i < s - 1; i++) //�Y���פ��@�ˡA�Nleft�ɹs�ܻPright�@�˪�
			R.push_back('0');
		while (s--)
		{
			string a, m;
			for (int i = 9; i >= 0; i--)
			{
				a = '0' + i;
				m = mul(R, a);
				c = cmp(m, rem);
				if (c >= 0)
				{
					quotient += a;
					rem = sub(rem, m);
					break;
				}
			}
			R.pop_back();
		}
		if (r)
			return rem;

		if (quotient[0] == '0')
			quotient.erase(quotient.begin());

		if (divSign)
			return "-" + quotient;
		return quotient;
	}
}

//Intent: �j�Ƥ��
//Per: ��J��ӫD�t���
//Post: 0:�۵� 1:left<right -1:left>right
int Number::cmp(string left, string right)
{
	int size1 = left.size();
	int size2 = right.size();

	if (size1 > size2)
		return -1;
	else if (size1 < size2)
		return 1;
	else if (size1 == size2)
	{
		for (int i = 0; i < size1; i++)
		{
			if (left[i] > right[i])
				return -1;
			else if (left[i] < right[i])
				return 1;
			else if (i == size1 - 1)
				return 0;
		}
	}
}
/***********************************************
***************** �� ��ƹ�@ �� ***************
************************************************/

string Number::get110Dec(Fraction f)
{
	if (f.numerator == "0" && f.denominator == "0")
	{
		string s;
		s.assign(110, '0');
		return "0." + s;
	}
	string temp;
	string quotient = div(f.numerator, f.denominator);
	int len = quotient.length();
	if (cmp(f.numerator, f.denominator) == 1 && f.numerator != "0")
	{
		temp = "0.";
		while (cmp(f.numerator, f.denominator) == 1)
		{
			temp += '0';
			f.numerator += '0';
		}
		if (temp[temp.size() - 1] == '0')
			temp.pop_back();
		f.numerator.insert(f.numerator.end(), 110, '0');
		quotient = div(f.numerator, f.denominator);
		temp += quotient;
		return temp.assign(temp, 0, len + 111);
	}
	else
	{
		f.numerator.insert(f.numerator.end(), 110, '0');
		quotient = div(f.numerator, f.denominator);
		quotient.insert(len, ".");
		return quotient.assign(quotient, 0, len + 111);
	}

}

string Number::get100Dec(Fraction f)
{
	string get110 = get110Dec(f);
	string s;
	size_t index;
	index = get110.find('.');
	s.assign(105, '9');
	if (s == get110.substr(index + 1, 105))
	{
		get110.assign(get110.begin(), get110.begin() + index);
		get110 = add(get110, "1");
		get110 += '.';
		get110.insert(get110.end(), 110, '0');
	}
	s.assign(10, '9');
	if (s == get110.substr(index + 100, 10))
	{
		string temp;
		temp.assign(get110.begin(), get110.begin() + index); //�p���I�e
		get110 = get110.substr(index + 1, 110);
		while (get110[0] == '0')
		{
			get110.erase(get110.begin());
		}
		get110 = add(get110, "1");						 
		if (get110.size() > 110)
		{
			string a;
			a = get110[0];
			get110.erase(get110.begin());
			temp = add(temp, a);
		}
			
		temp += '.';
		temp += get110;
		get110 = temp;
	}
	return get110.assign(get110, 0, get110.size() - 10);
}

string Number::get10Dec(Fraction f)
{
	string get100 = get100Dec(f);
	return get100.assign(get100, 0, get100.size() - 90);
}

string Number::getRoot120(string s)
{
	string ans;
	int len1;
	s.length() % 2 == 0 ? len1 = s.length() / 2 : len1 = s.length() / 2 + 1;
	s.insert(s.end(), 300, '0');
	int len = s.length();
	int i, j;
	int x[300] = {}, y[600] = {};
	for (i = 0, j = len - 1; j >= 0; i++)
	{
		x[i] = s[j] - '0';
		if (j - 1 >= 0)    x[i] = x[i] + (s[j - 1] - '0') * 10;
		if (j - 2 >= 0)    x[i] = x[i] + (s[j - 2] - '0') * 100;
		if (j - 3 >= 0)    x[i] = x[i] + (s[j - 3] - '0') * 1000;
		j -= 4;
	}
	int xlen = len, ylen = 0, head = 0;
	while (xlen >= 0 && x[xlen] == 0) xlen--;
	for (j = (len - 1) / 8, i = j * 2; j >= 0; j--, i -= 2)
	{
		ylen++;
		for (int p = ylen; p >= 1; p--)
			y[p] = y[p - 1];
		y[0] = 0;
		if (xlen < j)
		{
			if (!head)
				ans.push_back('0'), head = 1;
			else
				ans = ans + "0000";
			continue;
		}
		int l = 0, r = 9999, p;
		int z[300]; // z = (y*10 + p)*p;
		while (l <= r)
		{
			p = (l + r) / 2;
			y[0] += p;
			z[0] = 0;
			for (int q = 0; q <= ylen + 5; q++)
			{
				z[q] += p*y[q];
				z[q + 1] = z[q] / 10000;
				z[q] %= 10000;
			}
			int chflag = 0;
			for (int q = ylen + 5; q >= 0; q--)
			{
				if (z[q] > x[i + q])
				{
					chflag = 1;
					break;
				}
				else if (z[q] < x[i + q])
				{
					chflag = 0;
					break;
				}
			}
			y[0] -= p;
			if (chflag)
				r = p - 1;
			else
				l = p + 1;
		}
		p = l - 1;
		y[0] = p;
		z[0] = 0;
		for (int q = 0; q <= ylen + 5; q++)
		{
			z[q] += p*y[q];
			z[q + 1] = z[q] / 10000;
			z[q] %= 10000;
		}
		for (int q = ylen + 5; q >= 0; q--)
			x[i + q] -= z[q];
		for (int q = 0; q <= ylen + 5; q++)
		{
			while (x[i + q] < 0)
				x[i + q] += 10000, x[i + q + 1]--;
		}
		y[0] += p;
		for (int q = 0; q <= ylen + 5; q++)
		{
			if (y[q] >= 10000)
			{
				y[q + 1] += y[q] / 10000;
				y[q] %= 10000;
			}
		}
		ylen += 5;
		while (ylen >= 0 && y[ylen] == 0)    ylen--;
		while (xlen >= 0 && x[xlen] == 0)    xlen--;
		if (!head)
		{
			ans = ans + to_string(p);
			head = 1;
		}
		else
		{
			string str = to_string(p);
			for (int w = 0; w < 4 - str.length(); w++)
				ans.push_back('0');
			ans = ans + str;
		}
	}
	ans.insert(len1, ".");
	return ans;
}

string Number::printRoot(string s)
{
	string ans;
	int len1;
	s.length() % 2 == 0 ? len1 = s.length() / 2 : len1 = s.length() / 2 + 1;
	s.insert(s.end(), 200, '0');
	int len = s.length();
	int i, j;
	int x[300] = {}, y[300] = {};
	for (i = 0, j = len - 1; j >= 0; i++)
	{
		x[i] = s[j] - '0';
		if (j - 1 >= 0)    x[i] = x[i] + (s[j - 1] - '0') * 10;
		if (j - 2 >= 0)    x[i] = x[i] + (s[j - 2] - '0') * 100;
		if (j - 3 >= 0)    x[i] = x[i] + (s[j - 3] - '0') * 1000;
		j -= 4;
	}
	int xlen = len, ylen = 0, head = 0;
	while (xlen >= 0 && x[xlen] == 0) xlen--;
	for (j = (len - 1) / 8, i = j * 2; j >= 0; j--, i -= 2)
	{
		ylen++;
		for (int p = ylen; p >= 1; p--)
			y[p] = y[p - 1];
		y[0] = 0;
		if (xlen < j)
		{
			if (!head)
				ans.push_back('0'), head = 1;
			else
				ans = ans + "0000";
			continue;
		}
		int l = 0, r = 9999, p;
		int z[300]; // z = (y*10 + p)*p;
		while (l <= r)
		{
			p = (l + r) / 2;
			y[0] += p;
			z[0] = 0;
			for (int q = 0; q <= ylen + 5; q++)
			{
				z[q] += p*y[q];
				z[q + 1] = z[q] / 10000;
				z[q] %= 10000;
			}
			int chflag = 0;
			for (int q = ylen + 5; q >= 0; q--)
			{
				if (z[q] > x[i + q])
				{
					chflag = 1;
					break;
				}
				else if (z[q] < x[i + q])
				{
					chflag = 0;
					break;
				}
			}
			y[0] -= p;
			if (chflag)
				r = p - 1;
			else
				l = p + 1;
		}
		p = l - 1;
		y[0] = p;
		z[0] = 0;
		for (int q = 0; q <= ylen + 5; q++)
		{
			z[q] += p*y[q];
			z[q + 1] = z[q] / 10000;
			z[q] %= 10000;
		}
		for (int q = ylen + 5; q >= 0; q--)
			x[i + q] -= z[q];
		for (int q = 0; q <= ylen + 5; q++)
		{
			while (x[i + q] < 0)
				x[i + q] += 10000, x[i + q + 1]--;
		}
		y[0] += p;
		for (int q = 0; q <= ylen + 5; q++)
		{
			if (y[q] >= 10000)
			{
				y[q + 1] += y[q] / 10000;
				y[q] %= 10000;
			}
		}
		ylen += 5;
		while (ylen >= 0 && y[ylen] == 0)    ylen--;
		while (xlen >= 0 && x[xlen] == 0)    xlen--;
		if (!head)
		{
			ans = ans + to_string(p);
			head = 1;
		}
		else
		{
			string str = to_string(p);
			for (int w = 0; w < 4 - str.length(); w++)
				ans.push_back('0');
			ans = ans + str;
		}
	}
	ans.insert(len1, ".");
	return ans;
}

//Number��X����
string Number::printAns()
{
	if (errorTyep > 0)
	{
		switch (errorTyep)
		{
		case 1:
			return "Error (1) : �D����ƶ���";
			break;
		case 2:
			return "Error (2) : �D��Ʃ�0.5����";
			break;
		case 3:
			return "Error (3) : ���Ƥ��i��0";
			break;
		default:
			break;
		}
	}
	string s = "0.0000000000";
	Fraction temp;
	imagToReal(fracAns, temp);

	if (fracAns.comSign && get10Dec(temp) != s)
		return getCom();
	else if (fracAns.denominator != "1" && fracAns.denominator != "0")
	{
		string test = getDec();
		s.assign(100, '0');
		size_t index = test.find('.');
		if (test.substr(index + 1) == s)
		{
			return getInt();
		}
		return test;
	}
		
	else
		return getInt();
}

Number::Number():Number("0"){}
Number::Number(string input)
{
	setInput(input);
	computInput();
}
Number::~Number(){}


string Number::getInt()
{
	if (errorTyep > 0)
		return printAns();
	string ret;
	ret = get100Dec(fracAns);
	if (fracAns.sign)
		ret.insert(ret.begin(), '-');
	ret.assign(ret, 0, ret.size() - 101);
	if (ret == "-0")
		return "0";
	return ret;
}

string Number::getDec()
{
	if (errorTyep > 0)
		return printAns();
	string ret;
	ret = get100Dec(fracAns);
	if (fracAns.sign)
		ret.insert(ret.begin(), '-');
	string s = "-0.";
	s.insert(s.begin(), 100, '0');
	if (ret == s)
		ret.erase(ret.begin());
	return ret;
}

string Number::getCom()
{
	if (errorTyep > 0)
		return printAns();
	string s = "-0.0000000000";
	string ret1, ret2;
	if (fracAns.sign)
		ret1 += '-';
	else
		ret1 += ' ';
	ret1 += get10Dec(fracAns);
	Fraction temp;
	imagToReal(fracAns, temp);
	if (temp.sign)
		ret2 += '-';
	else
		ret2 += '+';
	ret2 += get10Dec(temp);
	if (ret1 == s)
		ret1.erase(ret1.begin());
	if (ret2 == s)
		ret2[0] = '+';
	return ret1 + " " + ret2 + "i";
}

void Number::assign() {}

void Number::print(ostream&)const {}


ostream& operator<<(ostream& outputStream, const Number& a)
{
	a.print(outputStream);
	return outputStream;
}

istream& operator>> (istream& inputStream, Number&a)
{
	string in;
	inputStream >> in;
	a.setInput(in);
	a.computInput();
	a.assign();
	return inputStream;
}


Fraction Number::getFrac()
{
	return fracAns;
}

Fraction Number::getReal()
{
	Fraction ret;
	ret.sign = fracAns.sign;
	ret.denominator = fracAns.denominator;
	ret.numerator = fracAns.numerator;
	return ret;
}


bool Number::getComSign()
{
	return fracAns.comSign;
}

void Number::setFrac(Fraction& f)
{
	fracAns = f;
}