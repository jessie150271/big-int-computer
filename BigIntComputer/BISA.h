#ifndef BISA_H
#define BISA_H
//大數加、減法實作
#include <iostream>
#include <string>
#include <vector>

struct N
{
	std::string bigNum;
	bool sign;
};

class BigIntAddSub
{
public:
	BigIntAddSub();
	BigIntAddSub(std::string);
	std::string bigIntAdd(N, N);
	std::string bigIntSub(N, N);
	N getNumber();

private:
	N num;
};

#endif // !BISA_H