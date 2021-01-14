/*
CSCI 580 Algorithm Design, Analysis, and Implementation
Author: Chu-An Tsai
Columnsort
*/

#include "utility.h"

// r * s = 100000
// r mod s = 0
// r >= 2(s - 1)^2
//                  Try 3 different r,s pairs (personal experiment)
const int R = 4000;	//4000  //10000	//50000
const int S = 25;	//25	//10	//2


// Check if the array is actually sorted
bool SortCheck(short int array[R][S])
{
	int flag = 0;
	for (int j = 0; j < S; j++)
	{
		for (int i = 0; i < R - 1; i++)
		{
			// If it is not the last column, check with the next value and the value on the next column
			if (j < S - 1)
			{
				if (array[i][j] > array[i + 1][j] || array[i][j] > array[i][j + 1])
				{
					flag = flag + 1;
				}
			}
			// If it is the last column, check with the next value
			else
			{
				if (array[i][j] > array[i + 1][j])
				{
					flag = flag + 1;
				}
			}
		}
	}

	return flag == 0;
}

// Print out for checking the result (in small array only)
// To see if my code actually works step by step (This helps a lot)
// Test on a r = 9, s = 3 array
void printOutCheck(short int array[S][R], int i)
{
	cout << "Step " << i << ":" << endl << endl;
	
	if (i != 6 && i != 7)
	{
		// Transpose back
		short int arrayCheck[R][S];
		for (int j = 0; j < S; j++)
		{
			for (int i = 0; i < R; i++)
			{
				arrayCheck[i][j] = array[j][i];
			}
		}
		for (int i = 0; i < R; i++)
		{
			cout << "\t" << arrayCheck[i][0] << "\t" << arrayCheck[i][1] << "\t" << arrayCheck[i][2] << endl;
		}
	}
	else
	{
		short int arrayCheck[R][S + 1];
		for (int j = 0; j < S + 1; j++)
		{
			for (int i = 0; i < R; i++)
			{
				arrayCheck[i][j] = array[j][i];
			}
		}
		for (int i = 0; i < R; i++)
		{
			cout << "\t" << arrayCheck[i][0] << "\t" << arrayCheck[i][1] << "\t" << arrayCheck[i][2] << "\t" << arrayCheck[i][3] << endl;
		}
	}
	cout << endl;
}

// MaxHeapify
void MaxHeapify(short int array[], int n, int i)
{
	int leftChild = 2 * i + 1;
	int rightChild = 2 * i + 2;
	int largest = i;

	// If left child is larger
	if (array[leftChild] > array[largest] && leftChild < n)
	{
		largest = leftChild;
	}

	// If right child is larger
	if (array[rightChild] > array[largest] && rightChild < n)
	{
		largest = rightChild;
	}

	// If the largest is not root 
	if (largest != i)
	{
		swap(array[i], array[largest]);

		// Recursively does MaxHeapify
		MaxHeapify(array, n, largest);
	}
}

// HeapSort
void HeapSort(short int array[], int n)
{
	// Build max heap
	for (int i = n / 2 - 1; i >= 0; i--)
	{
		MaxHeapify(array, n, i);
	}
	// Put the largest element aside (to the end position)
	for (int i = n - 1; i > 0; i--)
	{
		swap(array[0], array[i]);
		MaxHeapify(array, i, 0);
	}
}

// Columnsort
// Sort each row in the s*r array
void Columnsort(short int array[S][R])
{
	int rowCounter = 0;				// For array "transpose" and "shifting" use
	int columnCounter = 0;			// For array "transpose" and "shifting" use
	short int arrayNew[S + 1][R];	// For array "transpose" and "shifting" use
	int r = R;
	int s = S;

	// Step 1: Sort the values in each row, which is the original column
	for (int i = 0; i < s; i++)
	{
		HeapSort(array[i], r);
	}

	// Step 1 Check
	//printOutCheck(array, 1);

	// Step 2: Transpose the matrix from row-major order to column-major order
	for (int i = 0; i < s; i++)
	{
		for (int j = 0; j < r; j++)
		{
			if (rowCounter < s)
			{
				arrayNew[rowCounter][columnCounter] = array[i][j];
				rowCounter++;
			}
			else
			{
				rowCounter = 0;
				columnCounter++;
				j--;
			}
		}
	}

	// Step 2 Check
	//printOutCheck(arrayNew, 2);

	// Step 3: Sort the new rows (New columns indeed)
	for (int i = 0; i < s; i++)
	{
		HeapSort(arrayNew[i], r);
	}

	// Step 3 Check
	//printOutCheck(arrayNew, 3);

	// Step 4: Reverse step 2 
	rowCounter = 0;
	columnCounter = 0;
	for (int j = 0; j < r; j++)
	{
		for (int i = 0; i < s; )
		{
			if (columnCounter < r)
			{
				array[rowCounter][columnCounter] = arrayNew[i][j];
				columnCounter++;
				i++;
			}
			else
			{
				columnCounter = 0;
				rowCounter++;
			}
		}
	}

	// Step 4 Check
	//printOutCheck(array, 4);

	// Step 5: 	Sort the new rows (transposed-back columns)
	for (int i = 0; i < s; i++)
	{
		HeapSort(array[i], r);
	}

	// Step 5 Check
	//printOutCheck(array, 5);

	// Step 6: Shifting and filling the values
	// Fill the first half of the first row (column originally) with value -32766
	for (int i = 0; i < ((s + 1) / 2) + 1; i++)
	{
		for (int j = 0; j < (r / 2) + 1; j++)
		{
			arrayNew[i][j] = -32766;
		}
	}
	// Fill the bottom half of the last row (column originally) with value 32767
	for (int i = (s + 1) / 2; i < s + 1; i++)
	{
		for (int j = (r / 2); j < r; j++)
		{
			arrayNew[i][j] = 32767;
		}
	}
	// Shifting r / 2 positions
	int index = 0;
	int middle = r / 2;
	for (int i = 0; i < s; i++)
	{
		for (int j = 0; j < r; j++)
		{
			index = i * r + j + middle;
			rowCounter = index / r;
			columnCounter = index % r;
			arrayNew[rowCounter][columnCounter] = array[i][j];
		}
	}

	// Step 6 Check
	//printOutCheck(arrayNew, 6);

	// Step 7: Sort the new rows (columns)
	for (int i = 0; i < s + 1; i++)
	{
		HeapSort(arrayNew[i], r);
	}

	// Step 7 Check
	//printOutCheck(arrayNew, 7);

	// Step 8: Reverse the shifting of step 6
	for (int i = 0; i < s; i++)
	{
		for (int j = 0; j < r; j++)
		{
			index = i * r + j + middle;
			rowCounter = index / r;
			columnCounter = index % r;
			array[i][j] = arrayNew[rowCounter][columnCounter];
		}
	}

	// Step 8 Check
	//printOutCheck(array, 8);
}

int main()
{
	clock_t start, end;
	int count = 0;
	short int arrayA[R * S];
	short int array2D[R][S];
	short int trans2D[S][R];

	// Read data from the file
	ifstream dataFile;
	dataFile.open("data1.txt");

	// Give array warning and exit if fail to read the file
	if (dataFile.fail())
	{
		cout << "Unable to find input file!";
		exit(1);
	}

	// Write the data into arrayA
	int temp1;
	while (dataFile >> temp1)
	{
		arrayA[count] = temp1;
		count++;
	}

	dataFile.close();

	// Build 2D array
	for (int j = 0; j < S; j++)
	{
		for (int i = 0; i < R; i++)
		{
			// The r*s array
			array2D[i][j] = arrayA[j * R + i];
			// Transpose the 2D array to s*r for operation
			trans2D[j][i] = arrayA[j * R + i];
		}
	}

	/*
	// Check
	// Original array
	cout << "Original:" << endl << endl;
	for (int i = 0; i < R; i++)
	{
		cout << "\t" << array2D[i][0] << "\t" << array2D[i][1] << "\t" << array2D[i][2] << endl;
	}
	cout << endl << endl;
	*/

	double start_time = clock();

	// Apply Columnsort with the transposed array
	Columnsort(trans2D);

	double end_time = clock();
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(3);
	cout << "Time spent: " << ((double)(end_time - start_time)) / ((double)CLOCKS_PER_SEC);
	
	// Transpose back to r*s
	for (int j = 0; j < S; j++)
	{
		for (int i = 0; i < R; i++)
		{
			array2D[i][j] = trans2D[j][i];
		}
	}
	cout << endl;

	// Check if the array is actually sorted
	if (SortCheck(array2D) == 1)
	{
		cout << "Good job! The array is sorted." << endl;
	}
	else
	{
		cout << "Warning! The array is not sorted." << endl;
	}

	// Reshape to 1D array
	for (int i = 0; i < S; i++)
	{
		for (int j = 0; j < R; j++)
		{
			arrayA[i * R + j] = array2D[j][i];
		}
	}

	// Write sorted array into array .txt file
	ofstream resultFile;
	resultFile.open("Results1.txt");
	for (int i = 0; i < R * S; i++)
	{
		resultFile << arrayA[i] << endl;
	}
	resultFile.close();

	return 0;
}
