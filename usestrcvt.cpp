#include "stdafx.h"
#include <stdio.h>
#include "iostream"
#include "StringConvert.h"
using namespace std;

int main() {

try
	{
		printf("%f\n", FromString<float>("-1,6251"));
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}

//	system("pause");
    return 0;
}
