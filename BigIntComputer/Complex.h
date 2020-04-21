#ifndef COMPLEX_H
#define COMPLEX_H
#include "Number.h"

class Integer;
class DEcimal;
class Complex : public Number
{
public:
	Complex();
	Complex(std::string);
	~Complex();

	std::string getAns()const;
	Fraction getFrac()const;
	std::string getInput()const;
	virtual void assign();
	virtual void print(std::ostream&)const;

	Complex& operator=(Integer&);
	Complex& operator=(DEcimal&);
	Complex& operator=(Complex&);
	Complex& operator=(std::string&);

	friend Complex operator+(Complex&, Complex&);
	friend Complex operator+(Complex&, Integer&);
	friend Complex operator+(Complex&, DEcimal&);
	friend Complex operator+(Integer&, Complex&);
	friend Complex operator+(DEcimal&, Complex&);

	friend Complex operator-(Complex&, Complex&);
	friend Complex operator-(Complex&, Integer&);
	friend Complex operator-(Complex&, DEcimal&);
	friend Complex operator-(Integer&, Complex&);
	friend Complex operator-(DEcimal&, Complex&);

	friend Complex operator*(Complex&, Complex&);
	friend Complex operator*(Complex&, Integer&);
	friend Complex operator*(Integer&, Complex&);
	friend Complex operator*(Complex&, DEcimal&);
	friend Complex operator*(DEcimal&, Complex&);

	friend Complex operator/(Complex&, Complex&);
	friend Complex operator/(Complex&, Integer&);
	friend Complex operator/(Integer&, Complex&);
	friend Complex operator/(Complex&, DEcimal&);
	friend Complex operator/(DEcimal&, Complex&);

	friend Complex Power(Complex& left, Integer& right);
	friend Complex Power(Complex& left, DEcimal& right);
	friend Complex Power(Complex& left, Complex& right);
	friend Complex Power(Complex& left, std::string& right);
	friend Integer Factorial(Complex& a);
	
private:
	std::string ans;
	
};
#endif // !COMPLEX_H