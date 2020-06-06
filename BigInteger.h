#include <string>
#define MAX 10000 // for strings

using namespace std;
//-------------------------------------------------------------
class BigInteger
{
private:
	string number;
	bool sign;
public:
	BigInteger(); // empty constructor initializes zero
	BigInteger(string s); // "string" constructor
	BigInteger(string s, bool sin); // "string" constructor
	BigInteger(int n); // "int" constructor
	void setNumber(string s);
	const string& getNumber(); // retrieves the number
	void setSign(bool s);
	const bool& getSign();
	BigInteger absolute(); // returns the absolute value
	void operator = (BigInteger b);
	bool operator == (BigInteger b);
	bool operator != (BigInteger b);
	bool operator > (BigInteger b);
	bool operator < (BigInteger b);
	bool operator >= (BigInteger b);
	bool operator <= (BigInteger b);
	BigInteger& operator ++(); // prefix
	BigInteger  operator ++(int); // postfix
	BigInteger& operator --(); // prefix
	BigInteger  operator --(int); // postfix
	BigInteger operator + (BigInteger b);
	BigInteger operator - (BigInteger b);
	BigInteger operator * (BigInteger b);
	BigInteger operator / (BigInteger b);
	BigInteger operator % (BigInteger b);
	BigInteger& operator += (BigInteger b);
	BigInteger& operator -= (BigInteger b);
	BigInteger& operator *= (BigInteger b);
	BigInteger& operator /= (BigInteger b);
	BigInteger& operator %= (BigInteger b);
	BigInteger& operator [] (int n);
	BigInteger operator -(); // unary minus sign
	operator string(); // for conversion from BigInteger to string

	string mod(BigInteger& a, BigInteger& b) {
		/*重新实现，使用减法实现*/
		BigInteger temp = a;
		while (true)
		{
			if (greater(temp, b) != 1)
			{
				return temp;
			}
			temp = subtract(temp, b);
		}
	}
	//返回 a/b a%b <商，余数>
	pair<string ,string> divide(BigInteger& a, BigInteger& b) {
		BigInteger temp = BigInteger("0");//商
		BigInteger a_temp = BigInteger(a);
		BigInteger b_temp = BigInteger(b);
		if (b.greater(b,a))//如果除数大于被除数返回0 余数为被除数本身
		{
			return make_pair("0",a.getNumber());
		}
		if (a.equals(a,b))
		{
			return make_pair("1", "0");
		}
		if (a.getNumber().size() == b.getNumber().size())
		{
			while (a_temp >= b)
			{
				a_temp = a_temp - b;
				temp = temp + 1;
			}
			return make_pair(temp.getNumber(), a_temp.getNumber());
		}
		int differenceInLength = abs((int)(a.getNumber().size() - b.getNumber().size()));//计算两者相差的位数，这个位数至少为1
		//实现思路，先将除数倍乘到与被除数相差一位，然后再做减法直到小于了
		//相当于实现正常人工计算除法一样，步骤是先提高除数位次，做减法得到当前位的值
		//时间复杂度近似为n(x),x为除数与被除数位数差
		BigInteger result = BigInteger("0");
				
		for (size_t i = 0; i < differenceInLength; i++)
		{
			int differenceInLength2 = abs((int)(a_temp.getNumber().size() - b.getNumber().size()));
			int d = differenceInLength2 - 1;
			string One = "1";
			if (differenceInLength2 != 0)
			{
				One.append(differenceInLength2 - 1, '0');
			}
			BigInteger correntLevel = BigInteger(One);
			BigInteger b_buf = b * correntLevel;
			BigInteger sbsturtTimes = 0;
			while (a_temp >= b_buf)
			{
				a_temp = a_temp - b_buf;
				sbsturtTimes = sbsturtTimes + 1;
			}
			result = result + (sbsturtTimes * correntLevel);
		}
		return make_pair(result.getNumber(), a_temp.getNumber());
	}
	//返回 a/b a%b <商，余数>
	pair<string, string> divide(BigInteger a, BigInteger b) {
		BigInteger temp = BigInteger("0");//商
		BigInteger a_temp = BigInteger(a);
		BigInteger b_temp = BigInteger(b);
		if (b.greater(b, a))//如果除数大于被除数返回0 余数为被除数本身
		{
			return make_pair("0", a.getNumber());
		}
		if (a.equals(a, b))
		{
			return make_pair("1", "0");
		}
		if (a.getNumber().size() == b.getNumber().size())
		{
			while (a_temp >= b)
			{
				a_temp = a_temp - b;
				temp = temp + 1;
			}
			return make_pair(temp.getNumber(), a_temp.getNumber());
		}
		int differenceInLength = abs((int)(a.getNumber().size() - b.getNumber().size()));//计算两者相差的位数，这个位数至少为1
		//实现思路，先将除数倍乘到与被除数相差一位，然后再做减法直到小于了
		//相当于实现正常人工计算除法一样，步骤是先提高除数位次，做减法得到当前位的值
		//时间复杂度近似为n(x),x为除数与被除数位数差
		BigInteger result = BigInteger("0");

		for (size_t i = 0; i < differenceInLength; i++)
		{
			int differenceInLength2 = abs((int)(a_temp.getNumber().size() - b.getNumber().size()));
			int d = differenceInLength2 - 1;
			string One = "1";
			if (differenceInLength2 != 0)
			{
				One.append(differenceInLength2 - 1, '0');
			}
			BigInteger correntLevel = BigInteger(One);
			BigInteger b_buf = b * correntLevel;
			BigInteger sbsturtTimes = 0;
			while (a_temp >= b_buf)
			{
				a_temp = a_temp - b_buf;
				sbsturtTimes = sbsturtTimes + 1;
			}
			result = result + (sbsturtTimes * correntLevel);
		}
		return make_pair(result.getNumber(), a_temp.getNumber());
	}
	static const BigInteger ZERO;    // 大整数常量0
	static const BigInteger ONE;    // 大整数常量1
	static const BigInteger TWO;    // 大整数常量2
	static const BigInteger TEN;    // 大整数常量10
	BigInteger modpow(BigInteger base, BigInteger exp, BigInteger n) {
		BigInteger result = BigInteger("1");
		result = ex_Mod(base, exp, n, result);
		return result;
	}
	BigInteger modInverse(BigInteger a, BigInteger m) {
		BigInteger x = ONE;
		BigInteger y = ONE;
		BigInteger gcd = e_gcd(a, m, x,y);
		x = x / gcd;
		//m  = /*m.*/abs();
		if (x  < ZERO) {//如果小于零
			x = x+(m);
		}
		return x % m;
	}
private:
	bool equals(BigInteger n1, BigInteger n2);
	bool less(BigInteger n1, BigInteger n2);
	bool greater(BigInteger n1, BigInteger n2);
	string add(string number1, string number2);
	string subtract(string number1, string number2);
	string multiply(string n1, string n2);
	pair<string, long long> divide(string n, long long den);
	string toString(long long n);
	long long toInt(string s);
	BigInteger my_abs() {
		BigInteger re = BigInteger(*this);
		if (re.getSign() == true)
		{
			re.setSign(false);
		}
		return re;
	}
	BigInteger ex_Mod(BigInteger& base, BigInteger& exp, BigInteger& n, BigInteger& result) {

		if (exp == (ZERO)) {
			return ONE;
		}
		while (1)
		{
			if (exp == (ONE))
			{
				exp = exp - (ONE);
				result = (result * (base)) % (n);
				return result;
			}
			char ar = exp.getNumber()[exp.getNumber().size() - 1] - '0';
			if ((ar & 0x01) == 0) {//如果为偶数
				base = (base * (base)) % (n);
				exp = exp / (TWO);
			}
			else {//奇数
				exp = exp - (ONE);
				result = (result * (base)) % (n);
			}

		}
		return result;
	}
	BigInteger e_gcd(BigInteger& a, BigInteger& b, BigInteger& x,BigInteger& y) {
		if (b == ZERO) {
			x =   BigInteger("1");
			y =   BigInteger("0");
			return a;
		}
		BigInteger c = a % b;
		BigInteger ans = e_gcd(b, c, x,y);
		BigInteger temp = x;
		x = y;
		y = temp-((a / b)*x);
		return ans;
	}
};

