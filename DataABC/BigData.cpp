#include "BigData.h"

BigData::BigData(INT_64 value)
	: _value(value)
{
	_strData.resize(21, '0');
	sprintf((char *)_strData.c_str(), "%+lld", value);
}

BigData::BigData(const char *num_str)
	: _value(0)
{
	if (NULL == num_str)
		return;
	
	char *str = (char *)num_str;
	while (isspace(*str))
		++str;
	
	char symbol = '+';
	if ('-' == *str || '+' == *str)
		symbol = *(str++);

	while ('0' == *str)
		++str;

	_strData.resize(strlen(str) + 1);
	char *dst = (char *)_strData.c_str();
	*(dst++) = symbol;
	while (*str >= '0' && *str <= '9')
	{
		_value = _value * 10 + *str - '0';
		*(dst++) = *(str++);
	}
	if ('-' == symbol)
		_value = 0 - _value;
	_strData.resize(strlen(_strData.c_str()));
	
	if (_strData.size() == 1)
		_strData.append(1, '0');
}
	
BigData::BigData(const BigData &bigdata)
{
	_value = bigdata._value;
	_strData = bigdata._strData;
}

BigData & BigData::operator=(const BigData &bigdata)
{
	if (this != &bigdata)
	{
		_value = bigdata._value;
		_strData = bigdata._strData;	
	}
	return *this;
}

bool BigData::isINT64Overflow() const
{
	if (_strData.size() > 20)
		return true;
	if (_strData.size() == 20)
	{
		string max("+9223372036854775807");
		string min("-9223372036854775808");
		char *tmp = (char *)_strData.c_str();
		if ('-' == tmp[0])
			return _strData < min;
		else
			return _strData > max;
	}

	return false;
}

ostream & operator<<(ostream &os, BigData &bigdata)
{
	if (!bigdata.isINT64Overflow())
		os << bigdata._value;
	else
	{
		const char *tmp = bigdata._strData.c_str();
		if ('+' == *tmp)
			++tmp;
		cout << tmp;
	}
	
}

BigData operator+(const BigData &left, const BigData &right)
{
	//1.左右操作数均未溢出
	if (!left.isINT64Overflow() && !right.isINT64Overflow())
	{
		//同号且溢出的情况
		if (
			((left._value > 0 && right._value > 0) && (INT_64_MAX - left._value < right._value)) ||
			((left._value < 0 && right._value < 0) && (INT_64_MIN - left._value > right._value))
		)
		{
			//do nothing
		}
		//不会溢出
		else
			return BigData(left._value + right._value);
	
	}

	//2.左右操作数有一个溢出或均溢出
	return BigData(Add(left._strData, right._strData).c_str());
}
	
string Add(const string &left, const string &right)
{
	int LSize = left.size();
	int RSize = right.size();
	
	const char *Left = left.c_str();
	const char *Right = right.c_str();

	char symbol;
	//同号
	if (*Left == *Right)
	{
		if (LSize < RSize)
		{
			swap(LSize, RSize);
			swap(Left, Right);
		}
	
		symbol = *Left;
		string rs;
		rs.resize(LSize + 1);
		char *ret = (char *)rs.c_str();
		ret[0] = symbol;

		int carry = 0;
		for (int i = 1; i < LSize; ++i)
		{
			int sum;
			if (i < RSize)
				sum = Left[LSize - i] - '0' + Right[RSize - i] - '0' + carry;
			else
				sum = Left[LSize - i] - '0' + carry;
			carry = sum / 10;
			sum %= 10;
			ret[LSize + 1 - i] = sum + '0';
		}
		ret[1] = carry + '0';
		return rs;
	}
	//异号
	else
	{	
		string l(Left);
		string r(Right);
		
		if ('-' == *Left)
		{
			char *tmp = (char *)l.c_str();
			tmp[0] = '+';
			return Sub(r, l);	//转换为同正号相减	
		}
		else
		{
			char *tmp = (char *)r.c_str();
			tmp[0] = '+';
			return Sub(l, r);	//转换为同正号相减
		}
	}
}

BigData operator-(const BigData &left, const BigData &right)
{
	//1.左右操作数均未溢出
	if (!left.isINT64Overflow() && !right.isINT64Overflow())
	{
		//同号且结果溢出的情况
		if (
			((left._value > 0 && right._value > 0) && (INT_64_MAX - left._value < right._value)) ||
			((left._value < 0 && right._value < 0) && (INT_64_MIN - left._value > right._value))
		)
		{
			//do nothing
		}
		//不会溢出
		else
			return BigData(left._value - right._value);
	}
	//2.有一个操作数溢出或均溢出
	return BigData(Sub(left._strData, right._strData).c_str());
}

string Sub(const string &left, const string &right)
{
	string left_tmp = left;
	int LSize = left.size();
	int RSize = right.size();
	
	char *Left = (char *)left_tmp.c_str();
	char *Right = (char *)right.c_str();
	
	int symbol;

	//同号
	if (*Left == *Right)
	{
		//计算最终结果符号
		symbol = '-';
		if ('+' == *Left)
		{
			if (
				(left.size() > right.size()) ||
				(left.size() == right.size() && left > right)
			)
				symbol = '+';
		}
		else
		{
			if (
				(left.size() < right.size()) ||
				(left.size() == right.size() && left < right)
			)
				symbol = '+';
		}

		if (LSize < RSize)
		{
			swap(LSize, RSize);
			swap(Left, Right);
		}
		
		string rs;
		rs.resize(LSize);
		
		char *dst = (char *)rs.c_str();
		dst[0] = symbol;
		
		int sub; 
		int carry = 0;
		for (int i = 1; i < LSize; ++i)
		{
			Left[LSize - i] -= carry;
			if (i < RSize)
				sub = Left[LSize - i] - Right[RSize - i];
			else
				sub = Left[LSize - i] - '0';
			if (sub < 0)
			{
				if (Left[LSize - i  - 1] >= '0' && Left[LSize - i - 1] <= '9')
				{
					carry = 1;
					sub += 10;
				}
				else
					sub = 0 - sub;
			}
			else
				carry = 0;
			dst[LSize - i] = sub + '0';
		}

		return rs;
	}
	else	//异号
	{
		if ('+' == *Left)
		{
			string r(Right);
			char *tmp = (char *)r.c_str();
			tmp[0] = '+';
			return Add(left, r);
		}
		else
		{
			string l(Left);
			char *tmp = (char *)l.c_str();
			tmp[0] = '+';
			string ret = Add(l, right);
			tmp = (char *)ret.c_str();
			if ('-' == *tmp)
				*tmp = '+';
			else
				*tmp = '-';
			return ret;
		}
	}
}

BigData operator*(const BigData &left, const BigData &right)
{
	//1.左右操作数均未溢出
	if (!left.isINT64Overflow() && !right.isINT64Overflow())
	{
		//结果未溢出
		if (INT_64_MAX / llabs(left._value) >= llabs(right._value))	
		{
			return BigData(left._value * right._value);
		}
		//结果溢出在下面处理
	}

	//2.有一个操作数溢出或两个均溢出还有结果溢出
	return BigData(Mul(left._strData, right._strData).c_str());
}

string Mul(const string &left, const string &right)
{
	char *Left = (char *)left.c_str();
	char *Right = (char *)right.c_str();

	char symbol = '+';
	if (*Left != *Right)
		symbol = '-';
	int LSize = left.size();
	int RSize = right.size();
	if (LSize > RSize)
	{
		swap(LSize, RSize);
		swap(Left, Right);
	}

	//99
	//99999
	BigData ret("");
	for (int i = 1; i < LSize; ++i)
	{
		int l = Left[LSize - i] - '0';
		int carry = 0;
		string tmp;
		tmp.resize(RSize, '0');
		char *ptmp = (char *)tmp.c_str();

		for (int j = 1; j < RSize; ++j)
		{
			int mul = l * (Right[RSize - j] - '0') + carry;
			carry = mul / 10;
			mul %= 10;
			ptmp[RSize - j] = mul + '0';	
		}
		ptmp[0] = carry + '0';
		for (int k = 1; k < i; ++k)
			tmp.append(1, '0');
		
		BigData tmp_right(tmp.c_str());
		ret  = ret + tmp_right;
	}
	string rs = ret._strData;
	*(char *)(rs.c_str()) = symbol;
	
	return rs;
}

BigData operator/(const BigData &left, const BigData &right)
{
	//1.左右操作数均未溢出
	if (!left.isINT64Overflow() && !right.isINT64Overflow())
	{	
		if (0 == right._value)
			throw 0;
		return BigData(left._value / right._value);
	}
	//2.有一个溢出或两个都溢出
	return BigData(Div(left._strData, right._strData).c_str());
}

string Div(const string &left, const string &right)
{	
	BigData rs("0");

	string new_left(left);

	char *l = (char *)new_left.c_str();
	char *r = (char *)right.c_str();
	int rSize = right.size();

	char symbol = '+';
	if (*l != *r)
		symbol = '-';

	++l;
	++r;

	int DataLen = --rSize;
	int offset = 0;
	while (isLeftBig(l, strlen(l), r, rSize))
	{
		if (isLeftBig(l, DataLen, r, rSize))
		{
			string tmp;
			tmp.resize(strlen(l), '0');
			char *t = (char *)tmp.c_str();

			t[DataLen - 1] = SubLoop(l, DataLen, r, rSize);	
			rs = rs + BigData(t);
		
			DataLen = rSize;
			offset = -1;
		
			BigData tmp_big(l);
			new_left = tmp_big._strData;
			l = (char *)new_left.c_str();
			++l;
		}
		else
		{
			DataLen++;
		}
		++offset;
	}
	
	BigData ret(rs._strData.c_str());
	char *sym = (char *)ret._strData.c_str();
	*sym = symbol;
	return ret._strData;
}

bool isLeftBig(const char *left, int lSize, const char *right, int rSize)
{
	if (lSize > rSize)
		return true;
	if (lSize == rSize && strncmp(left, right, lSize) >= 0)
		return true;
	return false;
}

char SubLoop(char *left, int lSize, const char *right, int rSize)
{
	char cnt = '0';
	string rs;
	rs.resize(lSize, '0');

	char *dst = (char *)rs.c_str();
	int sub; 
	int carry = 0;
	while (isLeftBig(left, lSize, right, rSize))
	{
		for (int i = 1; i <= lSize; ++i)
		{
			left[lSize - i] -= carry;
			if (i <= rSize)
				sub = left[lSize - i] - right[rSize - i];
			else
				sub = left[lSize - i] - '0';
			if (sub < 0)
			{
				if (i < lSize)
				{
					carry = 1;
					sub += 10;
				}
				else
					sub = 0 - sub;
			}
			else
				carry = 0;
			dst[lSize - i] = sub + '0';
		}
		int index = 0;
		while (index < lSize)
		{
			left[index] = dst[index];
			++index;
		}
		while ('0' == *left)
		{
			++left;
			--lSize;
		}
		++cnt;
	}
	return cnt;
}
	
