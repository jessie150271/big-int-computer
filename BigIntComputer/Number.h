#ifndef NUMBER_H
#define NUMBER_H
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip> 
#include <algorithm>


const int priority[] = { 0,1,2,3,4,5,6 };
//優先順序 括號6(直到遇反括號才輸出) > 負號5 > 虛部(i)4 > 階乘3 > 次方2 > 乘、除1 > 加、減0
//使用迴圈，取出中序式的字元，遇運算元直接輸出；堆疊運算子與左括號
//堆疊中運算子優先順序若大於等於讀入的運算子優先順序的話，直接輸出堆疊中的運算子，再將讀入的運算子置入堆疊；
//遇右括號輸出堆疊中的運算子至左括號。

struct ImagPart
{
	ImagPart& operator=(const ImagPart&r)	
	{
		this->sign = r.sign;
		this->numerator = r.numerator;
		this->denominator = r.denominator;
		return *this;
	}
	bool sign = false; //預設為正數
	std::string numerator = "0";	//虛部分子
	std::string denominator = "0";	//虛部分母
};

struct Fraction
{
	Fraction& operator=(const Fraction& r)	
	{
		this->sign = r.sign;
		this->numerator = r.numerator;
		this->denominator = r.denominator;
		this->comSign = r.comSign;
		this->imag = r.imag;
		return *this;
	}
	Fraction() 
	{
		numerator = "0";
		denominator = "0";
	}
	bool sign = false; //預設為正數
	std::string numerator = "0";	//分子
	std::string denominator = "0"; //分母

	bool comSign = false; // 預設為不是複數
	ImagPart imag;//虛部
};

class Number
{
public:
	Number();
	Number(std::string);
	~Number();

	std::string name;//存變數名稱
	int errorTyep = -1;//錯誤編號
	void setInput(const std::string&);//輸入數學式	
	void computInput();//運算					
	std::string printAns();//輸出答案(含防呆)	
	std::string getInt();	
	std::string getDec();	
	std::string getCom();	
	Fraction getFrac();	
	Fraction getReal();	
	bool getComSign();	
	void setFrac(Fraction&);


	virtual void assign();				
	virtual void print(std::ostream&)const;	

	friend std::ostream& operator<<(std::ostream& outputStream, const Number&); //輸出	
	friend std::istream& operator>> (std::istream& inputStream, Number&); //輸入			


	//複數↓
	Fraction toImag(Fraction);//分數轉虛部				
	void imagToReal(Fraction, Fraction&);//虛部轉實部	
	void realToImag(Fraction&, Fraction);//實部轉虛部	
	Fraction comAdd(Fraction, Fraction);//複數加法		
	Fraction comSub(Fraction, Fraction);//複數減法		
	Fraction comMul(Fraction, Fraction);//複數乘法		
	Fraction comDiv(Fraction, Fraction);//複數除法		
	Fraction comPow(Fraction, Fraction);//複數次方		

	//根號↓
	Fraction comRoot(Fraction, bool);//複數開根號(極座標方法)	
	Fraction fracRoot(Fraction, bool);//分數開根號				

	//分數↓
	Fraction posToStack(std::string);//整數or小數轉分數		
	Fraction fracPow(Fraction, Fraction);//分數次方		
	Fraction fracFac(Fraction);//階乘					
	Fraction fracAdd(Fraction, Fraction);//分數加法		
	Fraction fracSub(Fraction, Fraction);//分數減法		
	Fraction fracMul(Fraction, Fraction);//分數乘法		
	Fraction fracDiv(Fraction, Fraction);//分數除法		
	std::string gcd(std::string, std::string);//取最大公因數	
	Fraction about(Fraction);//約分						
	void changeSign(Fraction&);							
	bool sign(std::string&);//正負號判斷						

	//整數↓
	std::string getRoot120(std::string);//取得一整數開根號至小數點後150位		
	std::string printRoot(std::string);//開根號輸出小數點後100位				
	std::string mod(std::string, std::string);//大數取餘數		
	std::string pow(std::string, std::string);//大數次方		
	std::string fac(std::string);//大數階乘				
	int multiply(int x, std::vector<int> &ans, int res_size);	
	std::string add(std::string, std::string);//大數加法	
	std::string sub(std::string, std::string);//大數減法	
	std::string mul(std::string, std::string);//大數乘法	
	std::string div(std::string, std::string);//大數除法	
	int cmp(std::string, std::string);//大數比較		
	std::string get110Dec(Fraction);				
	std::string get100Dec(Fraction);				
	std::string get10Dec(Fraction);				
protected:
	Fraction fracAns;
	std::string input;
	//存輸入字串(無空格 '#'代表負號)
};
#include "BISA.h"
#include "Integer.h"
#include "Decimal.h"
#include "Complex.h"
#endif // !NUMBER_H
