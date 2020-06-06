#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include "BigInteger.h"
#define MAX 10000 // for strings

// ���±�ʾΪ��̬������ֵ
const BigInteger BigInteger::ZERO = BigInteger(0);
const BigInteger BigInteger::ONE = BigInteger(1);
const BigInteger BigInteger::TWO = BigInteger(2);
const BigInteger BigInteger::TEN = BigInteger(10);
BigInteger::BigInteger() // empty constructor initializes zero
{
	number = "0";
	sign = false;
}
//-------------------------------------------------------------
BigInteger::BigInteger(string s) // "string" constructor
{
	if( isdigit(s[0]) ) // if not signed
	{
		setNumber(s);
		sign = false; // +ve
	}
	else
	{
		setNumber( s.substr(1) );
		sign = (s[0] == '-');
	}
}
//-------------------------------------------------------------
BigInteger::BigInteger(string s, bool sin) // "string" constructor
{
	setNumber( s );
	setSign( sin );
}
//-------------------------------------------------------------
BigInteger::BigInteger(int n) // "int" constructor
{
	stringstream ss;
	string s;
	ss << n;
	ss >> s;


	if( isdigit(s[0]) ) // if not signed
	{
		setNumber( s );
		setSign( false ); // +ve
	}
	else
	{
		setNumber( s.substr(1) );
		setSign( s[0] == '-' );
	}
}
//-------------------------------------------------------------
void BigInteger::setNumber(string s)
{
	number = s;
}
//-------------------------------------------------------------
const string& BigInteger::getNumber() // retrieves the number
{
	return number;
}
//-------------------------------------------------------------
void BigInteger::setSign(bool s)
{
	sign = s;
}
//-------------------------------------------------------------
const bool& BigInteger::getSign()
{
	return sign;
}
//-------------------------------------------------------------
// returns the absolute value
BigInteger BigInteger::absolute()
{
	return BigInteger( getNumber() ); // +ve by default
}
//-------------------------------------------------------------
void BigInteger::operator = (BigInteger b)
{
	setNumber( b.getNumber() );
	setSign( b.getSign() );
}
//-------------------------------------------------------------
bool BigInteger::operator == (BigInteger b)
{
	return equals((*this) , b);
}
//-------------------------------------------------------------
bool BigInteger::operator != (BigInteger b)
{
	return ! equals((*this) , b);
}
//-------------------------------------------------------------
bool BigInteger::operator > (BigInteger b)
{
	return greater((*this) , b);
}
//-------------------------------------------------------------
bool BigInteger::operator < (BigInteger b)
{
	return less((*this) , b);
}
//-------------------------------------------------------------
bool BigInteger::operator >= (BigInteger b)
{
	return equals((*this) , b)
		|| greater((*this), b);
}
//-------------------------------------------------------------
bool BigInteger::operator <= (BigInteger b)
{
	return equals((*this) , b) 
		|| less((*this) , b);
}
//-------------------------------------------------------------
// increments the value, then returns its value
BigInteger& BigInteger::operator ++() // prefix
{
	(*this) = (*this) + 1;
	return (*this);
}
//-------------------------------------------------------------
// returns the value, then increments its value
BigInteger BigInteger::operator ++(int) // postfix
{
	BigInteger before = (*this);

	(*this) = (*this) + 1;

	return before;
}
//-------------------------------------------------------------
// decrements the value, then return it
BigInteger& BigInteger::operator --() // prefix
{
	(*this) = (*this) - 1;
	return (*this);

}
//-------------------------------------------------------------
// return the value, then decrements it
BigInteger BigInteger::operator --(int) // postfix
{	
	BigInteger before = (*this);

	(*this) = (*this) - 1;

	return before;
}
//-------------------------------------------------------------
BigInteger BigInteger::operator + (BigInteger b)
{
	BigInteger addition;
	if( getSign() == b.getSign() ) // both +ve or -ve
	{
		addition.setNumber( add(getNumber(), b.getNumber() ) );
		addition.setSign( getSign() );
	}
	else // sign different
	{
		if( absolute() > b.absolute() )
		{
			addition.setNumber( subtract(getNumber(), b.getNumber() ) );
			addition.setSign( getSign() );
		}
		else
		{
			addition.setNumber( subtract(b.getNumber(), getNumber() ) );
			addition.setSign( b.getSign() );
		}
	}
	if(addition.getNumber() == "0") // avoid (-0) problem
		addition.setSign(false);

	return addition;
}
//-------------------------------------------------------------
BigInteger BigInteger::operator - (BigInteger b)
{
	b.setSign( ! b.getSign() ); // x - y = x + (-y)
	return (*this) + b;
}
//-------------------------------------------------------------
BigInteger BigInteger::operator * (BigInteger b)
{
	BigInteger mul;

	mul.setNumber( multiply(getNumber(), b.getNumber() ) );
	mul.setSign( getSign() != b.getSign() );

	if(mul.getNumber() == "0") // avoid (-0) problem
		mul.setSign(false);

	return mul;
}
//-------------------------------------------------------------
// Warning: Denomerator must be within "long long" size not "BigInteger"
BigInteger BigInteger::operator / (BigInteger b)
{
	
	BigInteger div = b;

	if (div.getNumber() == "0") // avoid (-0) problem
	{
		div.setSign(false);
	}
	else
	{
		BigInteger thisAbs = (*this).absolute();
		pair<string, string> re = divide((*this).absolute(), b.absolute());
		div = BigInteger(re.first);
		div.setSign((*this).sign ^ b.sign);
	}
	
	return div;
}
//-------------------------------------------------------------
// Warning: Denomerator must be within "long long" size not "BigInteger"
BigInteger BigInteger::operator % (BigInteger b)
{
	BigInteger div = b;

	if (div.getNumber() == "0") // avoid (-0) problem
	{
		div.setSign(false);
	}
	else
	{
		BigInteger absBig = ((*this).getSign() == true) ? (b - (*this)) : (*this);
		pair<string, string> re = divide(absBig, b.absolute());
		div = BigInteger(re.second);
		div.setSign((*this).sign ^ b.sign);
	}
	return div;
}
//-------------------------------------------------------------
BigInteger& BigInteger::operator += (BigInteger b)
{
	(*this) = (*this) + b;
	return (*this);
}
//-------------------------------------------------------------
BigInteger& BigInteger::operator -= (BigInteger b)
{
	(*this) = (*this) - b;
	return (*this);
}
//-------------------------------------------------------------
BigInteger& BigInteger::operator *= (BigInteger b)
{
	(*this) = (*this) * b;
	return (*this);
}
//-------------------------------------------------------------
BigInteger& BigInteger::operator /= (BigInteger b)
{
	(*this) = (*this) / b;
	return (*this);
}
//-------------------------------------------------------------
BigInteger& BigInteger::operator %= (BigInteger b)
{
	(*this) = (*this) % b;
	return (*this);
}
//-------------------------------------------------------------
BigInteger& BigInteger::operator [] (int n)
{
	return *(this + (n*sizeof(BigInteger)));
}
//-------------------------------------------------------------
BigInteger BigInteger::operator -() // unary minus sign
{
	return (*this) * -1;
}
//-------------------------------------------------------------
BigInteger::operator string() // for conversion from BigInteger to string
{
	string signedString = ( getSign() ) ? "-" : ""; // if +ve, don't print + sign
	signedString += number;
	return signedString;
}
//-------------------------------------------------------------

bool BigInteger::equals(BigInteger n1, BigInteger n2)
{
	return n1.getNumber() == n2.getNumber()
		&& n1.getSign() == n2.getSign();
}

//-------------------------------------------------------------
bool BigInteger::less(BigInteger n1, BigInteger n2)
{
	bool sign1 = n1.getSign();
	bool sign2 = n2.getSign();

	if(sign1 && ! sign2) // if n1 is -ve and n2 is +ve
		return true;

	else if(! sign1 && sign2)
		return false;

	else if(! sign1) // both +ve
	{
		if(n1.getNumber().length() < n2.getNumber().length() )
			return true;
		if(n1.getNumber().length() > n2.getNumber().length() )
			return false;
		return n1.getNumber() < n2.getNumber();
	}
	else // both -ve
	{
		if(n1.getNumber().length() > n2.getNumber().length())
			return true;
		if(n1.getNumber().length() < n2.getNumber().length())
			return false;
		return n1.getNumber().compare( n2.getNumber() ) > 0; // greater with -ve sign is LESS
	}
}
//-------------------------------------------------------------
bool BigInteger::greater(BigInteger n1, BigInteger n2)
{
	return ! equals(n1, n2) && ! less(n1, n2);
}

//-------------------------------------------------------------
// adds two strings and returns their sum in as a string
string BigInteger::add(string number1, string number2)
{
	string add = (number1.length() > number2.length()) ?  number1 : number2;
	char carry = '0';
	int differenceInLength = abs( (int) (number1.size() - number2.size()) ); //������Ҫ��ͷ�����0�ĸ���

	if(number1.size() > number2.size())//λ��С����Ҫλ�����루ͷ����0��
		number2.insert(0, differenceInLength, '0'); // put zeros from left
	else
		number1.insert(0, differenceInLength, '0');
	for(int i=number1.size()-1; i>=0; --i)
	{
		add[i] = ((carry-'0')+(number1[i]-'0')+(number2[i]-'0')) + '0';

		if(i != 0)//�����������λ�����ݵĸ�λ��
		{	
			if(add[i] > '9')//�ж��Ƿ������λ
			{
				add[i] -= 10;
				carry = '1';
			}
			else
				carry = '0';
		}
	}
	//
	if(add[0] > '9')//���ݸ�λ�Ƿ������λ
	{
		add[0]-= 10;
		add.insert(0,1,'1');
	}
	return add;
}

//-------------------------------------------------------------
// subtracts two strings and returns their sum in as a string
string BigInteger::subtract(string number1, string number2)
{
	string sub = (number1.length()>number2.length())? number1 : number2;//λ���ߵ���Ϊ������
	int differenceInLength = abs( (int)(number1.size() - number2.size()) );//���ڼ������ݸ�λ��0

	if(number1.size() > number2.size())	//ִ�в�0
		number2.insert(0, differenceInLength, '0');

	else
		number1.insert(0, differenceInLength, '0');

	for(int i=number1.length()-1; i>=0; --i)
	{
		if(number1[i] < number2[i])//�����ǰλ������������ִ�����Ͻ�λ
		{
			number1[i] += 10;
			number1[i-1]--;
		}
		sub[i] = ((number1[i]-'0')-(number2[i]-'0')) + '0';
	}

	while(sub[0]=='0' && sub.length()!=1) //����ͷ�������0
		sub.erase(0,1);

	return sub;
}

//-------------------------------------------------------------
// multiplies two strings and returns their sum in as a string
string BigInteger::multiply(string n1, string n2)
{
	if(n1.length() > n2.length())//��֤n1Ϊ��С����
		n1.swap(n2);

	string res = "0";
	for(int i=n1.length()-1; i>=0; --i)//n1��λ����С
	{
		string temp = n2;
		int currentDigit = n1[i]-'0';
		int carry = 0;
		//n1��ÿһλ ��n2��ÿһλ��ˣ���˽����Ҫ�����ݵ�λ����0�����ÿһ��ֵ��Ӽ��ɵó����
		for(int j=temp.length()-1; j>=0; --j)
		{
			temp[j] = ((temp[j]-'0') * currentDigit) + carry;
			
			if(temp[j] > 9)
			{
				carry = (temp[j]/10);
				temp[j] -= (carry*10);
			}
			else
				carry = 0;
			temp[j] += '0'; //ת��Ϊ�ַ�
		}

		if(carry > 0)
			temp.insert(0, 1, (carry+'0'));
		
		temp.append((n1.length()-i-1), '0'); //���ݵ�λ����0�����ӵ�ǰ�����n1���ĵڼ�λ
		res = add(res, temp); //���
	}

	while(res[0] == '0' && res.length()!=1) //ȥ��ͷ����0
		res.erase(0,1);
	return res;
}

//�ѷ���
// divides string on long long, returns pair(qutiont, remainder)
pair<string, long long> BigInteger::divide(string n, long long den)
{
	long long rem = 0;
	string result; result.resize(MAX);
	
	for(int indx=0, len = n.length(); indx<len; ++indx)
	{
		rem = (rem * 10) + (n[indx] - '0');
		result[indx] = rem / den + '0';
		rem %= den;
	}
	result.resize( n.length() );

	while( result[0] == '0' && result.length() != 1)
		result.erase(0,1);

	if(result.length() == 0)
		result = "0";

	return make_pair(result, rem);
}

//-------------------------------------------------------------
// converts long long to string
string BigInteger::toString(long long n)
{
	stringstream ss;
	string temp;

	ss << n;
	ss >> temp;

	return temp;
}

//-------------------------------------------------------------
// converts string to long long
long long BigInteger::toInt(string s)
{
	long long sum = 0;

	for(int i=0; i<s.length(); i++)
		sum = (sum*10) + (s[i] - '0');

	return sum;
}

#endif
