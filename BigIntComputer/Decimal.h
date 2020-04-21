#ifndef DEcimal_H
#define DEcimal_H
#include "Number.h"
class Integer;
class Complex;
class DEcimal : public Number
{
public:
	DEcimal();
	DEcimal(std::string);
	~DEcimal();

	std::string getAns()const;
	Fraction getFrac()const;
	std::string getInput()const;
	virtual void assign();
	virtual void print(std::ostream&)const;

	DEcimal& operator=(Integer&);
	DEcimal& operator=(DEcimal&);
	DEcimal& operator=(Complex&);
	DEcimal& operator=(std::string&);

	friend DEcimal operator+(Integer&, DEcimal&);
	friend DEcimal operator+(DEcimal&, Integer&);
	friend DEcimal operator+(DEcimal&, DEcimal&);

	friend DEcimal operator-(Integer&, DEcimal&);
	friend DEcimal operator-(DEcimal&, Integer&);
	friend DEcimal operator-(DEcimal&, DEcimal&);

	friend DEcimal operator*(Integer&, DEcimal&);
	friend DEcimal operator*(DEcimal&, Integer&);
	friend DEcimal operator*(DEcimal&, DEcimal&);

	friend DEcimal operator/(Integer&, DEcimal&);
	friend DEcimal operator/(DEcimal&, Integer&);
	friend DEcimal operator/(DEcimal&, DEcimal&);

	friend Complex Power(DEcimal& left, Integer& right);
	friend Complex Power(DEcimal& left, DEcimal& right);
	friend Complex Power(DEcimal& left, Complex& right);
	friend Complex Power(DEcimal& left, std::string& right);
	friend Integer Factorial(DEcimal& a);

private:
	std::string ans;
};

#endif // !DEcimal_H
