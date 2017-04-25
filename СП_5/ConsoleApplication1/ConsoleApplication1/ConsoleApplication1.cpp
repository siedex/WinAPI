// ConsoleApplication1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int main()
{
	int a, b;
	cout << "Input two integers: ";
	cin >> a>> b;
	if (a == b)
	{
		cout<< "There is no min."<< endl; return 0;
	}
	if (a < b)
		cout << "min = " << a << endl;
	else
		cout << "min = " << b << endl;
	return 0;
}
