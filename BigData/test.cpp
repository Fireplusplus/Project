#include "BigData.h"

void test()
{
/*	BigData b1(123);
	BigData b2(123);
	cout << b1 << endl;
	cout << b2 << endl;
	BigData b12 = b1 + b2;
	cout << b12 << endl;


	BigData b3("90000000100000002000000030000000400000005000000060000000");
	BigData b4("1000000090000000100000002000000030000000400000005000000060000000");
	cout << b3 << endl;
	cout << b4 << endl;
	BigData b34 = b3 + b4;
	cout << b34 << endl;

	cout << endl;
	BigData b5("-90000000100000002000000030000000400000005000000060000000");
	BigData b6("1000000090000000100000002000000030000000400000005000000060000000");
	cout << b5 << endl;
	cout << b6 << endl;
	BigData b56 = b5 + b6;
	cout << b56 << endl;
*/
//63 个 9   1
//63 个 9   10
	BigData b5("9999999999999999999999999999999999999999999999999999999999999991");
	BigData b6("99999999999999999999999999999999999999999999999999999999999999910");
	cout << b5 << endl;
	cout << b6 << endl;
	BigData b56 = b5 + b6;
	cout << b56 << endl;


}

void test1()
{
	BigData b1(123);
	BigData b2(345);
	cout << b1 << endl;
	cout << b2 << endl;
	BigData b3 = b1 - b2;
	cout << b3 << endl;
	BigData b4 = b2 - b1;
	cout << b4 << endl;
	
	cout << endl;

	BigData b5("-99999999999999999999999999999920000000300000004000000050000000600000007000000080000000");
	//BigData b6("1000000020000000300000004000000050000000600000007000000080000000");
	BigData b6("");
	cout << b5 << endl;
	cout << b6 << endl;
	BigData b7 = b5 - b6;
	cout << b7 << endl;



}

void test2()
{
/*	BigData b1(123);
	BigData b2(456);
	cout << b1 << endl;
	cout << b2 << endl;
	BigData b3 = b1 * b2;
	cout << b3 << endl;

	cout << endl;
*/
/*
	BigData b4("9");
	BigData b5("-100000002000000030000000400000005000000060000006000000070000000");
	BigData b6 = b4 * b5;
	cout << b4 << endl;
	cout << b5 << endl;
	cout << b6 << endl;
*/

	BigData b4("-999");
	BigData b5("-9999999999999999999999999999999999999999999999999999999999999999");
	BigData b6 = b4 * b5;
	cout << b4 << endl;
	cout << b5 << endl;
	cout << b6 << endl;
}

void test3()
{
	BigData b1(2222);
	BigData b2(22);
	cout << b1 << endl;
	cout << b2 << endl;
	BigData b3 = b1 / b2;
	cout << b3 << endl;
	BigData b4 = b2 / b1;
	cout << b4 << endl;

	cout << "--------------------------------" << endl;

	BigData b5("-22222222222222222222222222222222222222222222222222222222222");
	BigData b6("222222222222222222222222222222222222222222222222222222222222222");
	cout << b5 << endl;
	cout << b6 << endl;
	BigData b7 = b5 / b6;
	cout << b7 << endl;
	BigData b8 = b6 / b5;
	cout << b8 << endl;


/*	BigData b1("22222222222222222222222222222222222222222222222222222222222222222");
	BigData b2("33");
	cout << b1 << endl;
	cout << b2 << endl;
	
	BigData b3 = b1 / b2;
	cout << b3 << endl;
	
	BigData b4 = b2 / b1;
	cout << b4 << endl;
*/
/*
	BigData b1("1000000020000000300000004000000050000000600000007000000080000000");
	BigData b2("-4000000050000000600000007000000080000000");
	cout << b1 << endl;
	cout << b2 << endl;
	
	BigData b3 = b1 / b2;
	cout << b3 << endl;
	
	BigData b4 = b2 / b1;
	cout << b4 << endl;
*/
/*	BigData b1("1000000000000000000000000000000000000000000000000000000000000000");
	BigData b2("4");
	cout << b1 << endl;
	cout << b2 << endl;

//	try
//	{
		BigData b3 = b1 / b2;
		cout << b3 << endl;
//	}
//	catch(...)
//	{
//		cout << "error: div 0" << endl;
//	}
	BigData b4 = b2 / b1;
	cout << b4 << endl;

*/
/*	BigData b1("-1000000000000000000000000000000000000000000000000000000000000000");
	BigData b2("25000000");
	cout << b1 << endl;
	cout << b2 << endl;
	BigData b3 = b1 / b2;
	cout << b3 << endl;
	BigData b4 = b2 / b1;
	cout << b4 << endl;
*/
}



int main()
{
	//test();
	//test1();
	//test2();
	//test3();
	BigData b(-2222222222223456);
	cout << b << endl;

	return 0;
}
