#include "Integer.h"
#include "Decimal.h"
#include "Complex.h"
using namespace std;
//Constructor
Integer::Integer():	Number()
{
	ans = "0";
}
Integer::Integer(string input):Number(input)
{
	ans = getInt();
}
Integer::~Integer(){}

void Integer::assign()
{
	ans = getInt();
}

string Integer::getAns()const
{
	return ans;
}

Fraction Integer::getFrac()const
{
	return fracAns;
}

string Integer::getInput()const
{
	return input;
}

void Integer::print(ostream& out) const
{
	string ret = getAns();
	out << ret;
}

Integer& Integer::operator=(Integer& r)
{
	errorTyep = r.errorTyep;
	fracAns = r.fracAns;
	input = r.input;
	assign();
	return *this;
}

Integer& Integer::operator=(DEcimal& r)
{
	errorTyep = r.errorTyep;
	fracAns = r.getFrac();
	input = r.getInput();
	assign();
	return *this;
}

Integer& Integer::operator=(Complex& r)
{
	errorTyep = r.errorTyep;
	fracAns = r.getFrac();
	input = r.getInput();
	assign();
	return *this;
}

Integer& Integer::operator=(string& r)
{
	setInput(r);
	computInput();
	assign();
	return *this;
}

Integer operator+(Integer& left, Integer& right)
{
	Integer ret;
	ret.setInput(left.getInt() + '+' + right.getInt());
	ret.computInput();
	ret.assign();
	return ret;
}

Integer operator-(Integer& left, Integer& right)
{
	Integer ret;
	ret.setInput(left.getInt() + '-' + right.getInt());
	ret.computInput();
	ret.assign();
	return ret;
}

Integer operator*(Integer& left, Integer& right)
{
	Integer ret;
	ret.setInput(left.getInt() + '*' + right.getInt());
	ret.computInput();
	ret.assign();
	return ret;
}

Integer operator/(Integer& left, Integer& right)
{
	Integer ret;
	ret.setInput(left.getInt() + '/' + right.getInt());
	ret.computInput();
	ret.assign();
	return ret;
}

Complex Power(Integer& left, Integer& right)
{
	Complex ret;
	ret.setFrac( left.fracPow(left.posToStack(left.getInt()), right.posToStack(right.getInt())));
	return ret;
}

Complex Power(Integer& left, DEcimal& right)
{
	Fraction ret = right.getReal();
	Complex ret1;
	if (ret.denominator == "0" || ret.denominator == "1" || (ret.denominator == "2" && ret.numerator == "1"))
	{
		ret = left.fracPow(left.posToStack(left.getInt()), ret);
		ret1.setFrac(ret);
		return ret1;
	}
	else
	{
		cout << "Illegal Pow(a,b)" << endl;
		return ret1;
	}
}

Complex Power(Integer& left, Complex& right)
{
	Fraction ret = right.getReal();
	Complex ret1;
	if (right.getComSign() == false && (ret.denominator == "0" || ret.denominator == "1" || (ret.denominator == "2" && ret.numerator == "1")))
	{
		ret1.setFrac(left.fracPow(left.posToStack(left.getInt()), ret));
		return ret1;
	}
	else
	{
		cout << "Illegal Pow(a,b)" << endl;
		return ret1;
	}
}

Complex Power(Integer& left, string& right)
{
	Complex temp(right);
	Fraction ret = temp.getReal();
	Complex ret1;
	if (temp.getComSign() == false && (ret.denominator == "0" || ret.denominator == "1" || (ret.denominator == "2" && ret.numerator == "1")))
	{
		ret1.setFrac(left.fracPow(left.posToStack(left.getInt()), ret));
		return ret1;
	}
	else
	{
		cout << "Illegal Pow(a,b)" << endl;
		return ret1;
	}
}

Integer Factorial(Integer& a)
{
	Fraction ret = a.posToStack(a.getInt());
	Integer ret1;
	if (ret.sign == false && (ret.denominator == "0" || ret.denominator == "1"))
	{
		ret1.setFrac(a.fracFac(ret));
		return ret1;
	}
	else
	{
		cout << "Illegal Fac(a)" << endl;
		return ret1;
	}
}

Integer Factorial(string& s)
{
	Complex temp(s);
	Integer ret1;
	Fraction ret = temp.getReal();
	if (temp.getComSign() == false && ret.sign == false && (ret.denominator == "1" || ret.denominator == "0"))
	{
		ret1.setFrac(ret1.fracFac(ret));
		return ret1;
	}
	else
	{
		cout << "Illegal Fac(a)" << endl;
		return ret1;
	}
}