#include "Complex.h"
#include "Integer.h"
#include "Decimal.h"
using namespace std;
//Constructor
Complex::Complex() :Number()
{
	assign();
}
Complex::Complex(string input) : Number(input)
{
	assign();
}
Complex::~Complex() {}

string Complex::getAns()const
{
	return ans;
}

Fraction Complex::getFrac()const
{
	return fracAns;
}

string Complex::getInput()const
{
	return input;
}

void Complex::assign()
{
	ans = getCom();
}

void Complex::print(ostream& out)const
{
	string ret = getAns();
	out << ret;
}

Complex& Complex::operator=(Integer& r)
{
	errorTyep = r.errorTyep;
	fracAns = r.getFrac();
	input = r.getInput();
	assign();
	return *this;
}

Complex& Complex::operator=(DEcimal& r)
{
	errorTyep = r.errorTyep;
	fracAns = r.getFrac();
	input = r.getInput();
	assign();
	return *this;
}

Complex& Complex::operator=(Complex& r)
{
	errorTyep = r.errorTyep;
	fracAns = r.fracAns;
	input = r.input;
	assign();
	return *this;
}

Complex& Complex::operator=(string& r)
{
	if (input == r)
		return *this;
	setInput(r);
	computInput();
	assign();
	return *this;
}

Complex operator+(Complex& left, Complex& right)
{
	Complex ret;
	ret.fracAns = ret.fracAdd(left.getFrac(), right.getFrac());
	ret.assign();
	return ret;
}

Complex operator+(Complex& left, Integer& right)
{
	Complex ret = left;
	ret.fracAns = ret.fracAdd(ret.fracAns, ret.posToStack(right.getInt()));
	ret.assign();
	return ret;
}

Complex operator+(Integer& left, Complex& right)
{
	return right + left;
}

Complex operator+(Complex& left, DEcimal& right)
{
	Complex ret = left;
	ret.fracAns = ret.fracAdd(ret.fracAns, right.getReal());
	ret.assign();
	return ret;
}

Complex operator+(DEcimal& left, Complex& right)
{
	return right + left;
}

Complex operator-(Complex& left, Complex& right)
{
	Complex ret;
	ret.fracAns = ret.fracSub(left.getFrac(), right.getFrac());
	ret.assign();
	return ret;
}

Complex operator-(Complex& left, Integer& right)
{
	Complex ret;
	ret.fracAns = ret.fracSub(left.getFrac(), ret.posToStack(right.getInt()));
	ret.assign();
	return ret;

}

Complex operator-(Complex& left, DEcimal& right)
{
	Complex ret;
	ret.fracAns = ret.fracSub(left.getFrac(), right.getReal());
	ret.assign();
	return ret;
}

Complex operator-(Integer& left, Complex& right)
{
	Complex ret;
	ret.fracAns = ret.fracSub(ret.posToStack(left.getInt()), right.getFrac());
	ret.assign();
	return ret;
}
Complex operator-(DEcimal& left, Complex& right)
{
	Complex ret;
	ret.fracAns = ret.fracSub(left.getReal(),right.getFrac());
	ret.assign();
	return ret;
}

Complex operator*(Complex& left, Complex& right)
{
	Complex ret;
	ret.fracAns = ret.fracMul(left.getFrac(), right.getFrac());
	ret.assign();
	return ret;
}

Complex operator*(Complex& left, Integer& right)
{
	Complex ret;
	ret.fracAns = ret.fracMul(left.getFrac(), ret.posToStack(right.getInt()));
	ret.assign();
	return ret;
}

Complex operator*(Integer& left, Complex& right)
{
	return right*left;
}

Complex operator*(Complex& left, DEcimal& right)
{
	Complex ret;
	ret.fracAns = ret.fracMul(left.getFrac(), right.getReal());
	ret.assign();
	return ret;
}

Complex operator*(DEcimal& left, Complex& right)
{
	return right*left;
}

Complex operator/(Complex& left, Complex& right)
{
	Complex ret;
	ret.fracAns = ret.fracDiv(left.getFrac(), right.getFrac());
	ret.assign();
	return ret;
}

Complex operator/(Complex& left, Integer& right)
{
	Complex ret;
	ret.fracAns = ret.fracDiv(left.getFrac(), ret.posToStack(right.getInt()));
	ret.assign();
	return ret;
}

Complex operator/(Integer& left, Complex& right)
{
	Complex ret;
	ret.fracAns = ret.fracDiv(ret.posToStack(left.getInt()), right.getFrac());
	ret.assign();
	return ret;
}

Complex operator/(Complex& left, DEcimal& right)
{
	Complex ret;
	ret.fracAns = ret.fracDiv(left.getFrac(), right.getReal());
	ret.assign();
	return ret;
}

Complex operator/(DEcimal& left, Complex& right)
{
	Complex ret;
	ret.fracAns = ret.fracDiv(left.getReal(), right.getFrac());
	ret.assign();
	return ret;
}


Complex Power(Complex& left, Integer& right)
{
	Complex ret1;
	ret1.setFrac(left.fracPow(left.getFrac(), right.posToStack(right.getInt())));
	return ret1;
}

Complex Power(Complex& left, DEcimal& right)
{
	Fraction ret = right.getReal();
	Complex ret1;
	if (ret.denominator == "0" || ret.denominator == "1" || (ret.denominator == "2" && ret.numerator == "1"))
	{
		ret1.setFrac(left.fracPow(left.getFrac(), ret));
		return ret1;
	}
	else
	{
		cout << "Illegal Pow(a,b)" << endl;
		return ret1;
	}
}

Complex Power(Complex& left, Complex& right)
{
	Fraction ret = right.getReal();
	Complex ret1;
	if (right.getComSign() == false && (ret.denominator == "0"||ret.denominator == "1" || (ret.denominator == "2" && ret.numerator == "1")))
	{
		ret1.setFrac(left.fracPow(left.getFrac(), ret));
		return ret1;
	}
	else
	{
		cout << "Illegal Pow(a,b)" << endl;
		return ret1;
	}
}

Complex Power(Complex& left, string& right)
{
	Complex temp(right);
	Fraction ret = temp.getReal();
	Complex ret1;
	if (temp.getComSign() == false && (ret.denominator == "0" || ret.denominator == "1" || (ret.denominator == "2" && ret.numerator == "1")))
	{
		ret1.setFrac(left.fracPow(left.getFrac(), ret));
		return ret1;
	}
	else
	{
		cout << "Illegal Pow(a,b)" << endl;
		return ret1;
	}
}

Integer Factorial(Complex& a)
{
	Fraction ret = a.getReal();
	Integer ret1;
	if (a.getComSign() == false && ret.sign == false && (ret.denominator == "1"|| ret.denominator == "0"))
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