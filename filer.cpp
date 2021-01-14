/*
Author: Chu-An Tsai
Integer file generator
*/

#include "utility.h"
#include "filer.h"

int main()
{
	filer f;
	int n, range;
	string file_name;

	cout << "How many numbers to put in the file:";
	cin >> n;
	cout << "The upper limit :";
	cin >> range;
	cout << "The name of the file:";
	cin >> file_name;

	f.makefile(n, range, file_name);

	return 0;
}
