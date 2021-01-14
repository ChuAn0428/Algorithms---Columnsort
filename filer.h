#include "utility.h"

#ifndef FILER_H 
#define FILER_H
//header file FILER.H for class filer
//a class object can create a file of a specified
//number of random integers in a specified range

class filer
{
public:
	void makefile(int n, int range, string file_name)
	{
		ofstream pfile;
		pfile.open(file_name);
		srand(int(time(NULL)));
		for (int i = 0; i < n; i++)
		{
			pfile << next_number(range) << endl;
		}
		pfile.close();
	}
	//precondition: n, range, and file_name have
	//been set;
	//postcondition: n random integers in the range 0-range,
	//inclusive, have been written to a file named file_name,
	//one per line;

private:
	int next_number(int range)
	{
		return (rand() % (range + 1));
	}
	//precondition:	range has been set to a nonnegative value
	//postcondition:	returns a random integer in the range
	//0-range, inclusive

};
#endif //FILER_H
#pragma once
#pragma once
