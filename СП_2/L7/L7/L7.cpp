// L7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <windows.h>
#include <iostream>

using namespace std;
int main()
{
	char big[] = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЬЫЬЭЮЯ";
	char sml[] = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
	CharToOem(big, big);
	CharToOem(sml, sml);
	cout << big << endl;
	cout << sml << endl;

    return 0;
}

