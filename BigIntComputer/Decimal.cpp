#include "Decimal.h"
#include "Integer.h"
#include "Complex.h"
using namespace std;
//Constructor
DEcimal::DEcimal() :Number()
{
	assign();
}
DEcimal::DEcimal(string input) : Number(input)
{
	assign();
}
DEcimal::~DEcimal() {}

string DEcimal::getAns() const
{
	return ans;
}

Fraction DEcimal::getFrac()const
{
	return fracAns;
}

string DEcimal::getInput()const
{
	return input;
}

void DEcimal::assign()
{
	ans = getDec();
}

void DEcimal::print(ostream& out)const
{
	string ret = getAns();
	out << ret;
}


DEcimal& DEcimal::operator=(Integer& r)
{
	errorTyep = r.errorTyep;
	fracAns = r.getReal();
	input = r.getInput();
	assign();
	return *this;
}

DEcimal& DEcimal::operator=(DEcimal& r)
{
	errorTyep = r.errorTyep;
	fracAns = r.fracAns;
	input = r.input;
	assign();
	return *this;
}

DEcimal& DEcimal::operator=(Complex& r)
{
	errorTyep = r.errorTyep;
	fracAns = r.getReal();
	input = r.getInput();
	assign();
	return *this;
}

DEcimal& DEcimal::operator=(string& r)
{
	if (input == r)
		return *this;
	setInput(r);
	computInput();
	assign();
	return *this;
}

DEcimal operator+(Integer& left, DEcimal& right)
{
	return right + left;
}

DEcimal operator+(DEcimal& left, Integer& right)
{
	DEcimal ret;
	ret.fracAns = ret.fracAdd(left.getReal(), ret.posToStack(right.getInt()));
	ret.assign();
	return ret;
}
DEcimal operator+(DEcimal& left, DEcimal& right)
{
	DEcimal ret;
	ret.fracAns = ret.fracAdd(left.getReal(), right.getReal());
	ret.assign();
	return ret;
}

DEcimal operator-(Integer& left, DEcimal& right)
{
	DEcimal ret;
	ret.fracAns = ret.fracSub(ret.posToStack(left.getInt()), right.getReal());
	ret.assign();
	return ret;

}

DEcimal operator-(DEcimal& left, Integer& right)
{
	DEcimal ret;
	ret.fracAns = ret.fracSub(left.getReal(), right.posToStack(right.getInt()));
	ret.assign();
	return ret;
	
}

DEcimal operator-(DEcimal& left, DEcimal& right)
{
	DEcimal ret;
	ret.fracAns = ret.fracSub(left.getReal(), right.getReal());
	ret.assign();
	return ret;
}

DEcimal operator*(Integer& left, DEcimal& right)
{
	return right*left;
}

DEcimal operator*(DEcimal& left, Integer& right)
{
	DEcimal ret;
	ret.fracAns = ret.fracMul(left.getReal(), right.posToStack(right.getInt()));
	ret.assign();
	return ret;
}

DEcimal operator*(DEcimal& left, DEcimal& right)
{
	DEcimal ret;
	ret.fracAns = ret.fracMul(left.getReal(), right.getReal());
	ret.assign();
	return ret;
}

DEcimal operator/(Integer& left, DEcimal& right)
{
	DEcimal ret;
	ret.fracAns = ret.fracDiv(left.posToStack(left.getInt()), right.getReal());
	ret.assign();
	return ret;
}

DEcimal operator/(DEcimal& left, Integer& right)
{
	DEcimal ret;
	ret.fracAns = ret.fracDiv(left.getReal(), right.posToStack(right.getInt()));
	ret.assign();
	return ret;
}

DEcimal operator/(DEcimal& left, DEcimal& right)
{
	DEcimal ret;
	ret.fracAns = ret.fracDiv(left.getReal(), right.getReal());
	ret.assign();
	return ret;
}

Complex Power(DEcimal& left, Integer& right)
{
	Complex ret1;
	ret1.setFrac(left.fracPow(left.getReal(), right.posToStack(right.getInt())));
	return ret1;
}

Complex Power(DEcimal& left, DEcimal& right)
{
	Fraction ret = right.getReal();
	Complex ret1;
	if (ret.denominator == "0" || ret.denominator == "1" || (ret.denominator == "2" && ret.numerator == "1"))
	{
		ret1.setFrac(left.fracPow(left.getReal(), ret));
		return ret1;
	}
	else
	{
		cout << "Illegal Pow(a,b)" << endl;
		return ret1;
	}
}

Complex Power(DEcimal& left, Complex& right)
{
	Fraction ret = right.getReal();
	Complex ret1;
	if (right.getComSign() == false && (ret.denominator == "0" || ret.denominator == "1" || (ret.denominator == "2" && ret.numerator == "1")))
	{
		ret1.setFrac(left.fracPow(left.getReal(), ret));
		return ret1;
	}
	else
	{
		cout << "Illegal Pow(a,b)" << endl;
		return ret1;
	}
}

Complex Power(DEcimal& left, string& right)
{
	Complex temp(right);
	Fraction ret = temp.getReal();
	Complex ret1;
	if (temp.getComSign() == false && (ret.denominator == "0" || ret.denominator == "1" || (ret.denominator == "2" && ret.numerator == "1")))
	{
		ret1.setFrac(left.fracPow(left.getReal(), ret));
		return ret1;
	}
	else
	{
		cout << "Illegal Pow(a,b)" << endl;
		return ret1;
	}
}

Integer Factorial(DEcimal& a)
{
	Fraction ret = a.getReal();
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