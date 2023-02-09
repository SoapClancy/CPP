#include "utils.h"
#include <iostream>

using namespace std;

void print(const char arr [], const size_t size, const string &delimiter)
{
	for (size_t i = 0; i < size; ++i)
	{
		cout << arr[i];
		if (i != size - 1)
		{
			cout << delimiter;
		}
		else
		{
			cout << endl;
		}
	}
}

void print(const char str[])
{
	cout << str << endl;
}
