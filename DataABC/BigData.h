#ifndef __BIGDATA_H__
#define __BIGDATA_H__

#include <iostream>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

typedef long long INT_64;
const long long INT_64_MAX = 0x7fffffffffffffff;
const long long INT_64_MIN = 0x8000000000000000;

class BigData
{
	friend ostream & operator<<(ostream &os, BigData &bigdata);

	friend BigData operator+(const BigData &left, const BigData &right);
	friend BigData operator-(const BigData &left, const BigData &right);
	friend BigData operator*(const BigData &left, const BigData &right);
	friend BigData operator/(const BigData &left, const BigData &right);

	friend string Mul(const string &left, const string &right);
	friend string Div(const string &left, const string &right);

public:
	BigData(INT_64 value);

	BigData(const char *num_str = "");
	
	BigData(const BigData &bigdata);
	
	BigData & operator=(const BigData &bigdata);
private:
	bool isINT64Overflow() const;
	
private:
	INT_64 _value;
	string _strData;
};


string Add(const string &left, const string &right);
string Sub(const string &left, const string &right);
string Mul(const string &left, const string &right);
string Div(const string &left, const string &right);

bool isLeftBig(const char *left, int lSize, const char *right, int rSize);
char SubLoop(char *left, int lSize, const char *right, int rSize);


#endif	//__BIGDATA_H__
