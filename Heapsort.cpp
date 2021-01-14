/*
Author: Chu-An Tsai
Implement Heapsort
*/

#include "utility.h"

bool SortCheck(short int arrayA[], int n)
{
    int flag = 0;
    for (int i = 0; i < n-1; i++)
    {
        if (arrayA[i] > arrayA[i+1])
        {
            flag = flag + 1;
        }
    }

    return flag == 0;
};


void heapify(short int arr[], int n, int i)
{
    int largest = i; // Initialize largest as root 
    int l = 2 * i + 1; // left = 2*i + 1 
    int r = 2 * i + 2; // right = 2*i + 2 

    // If left child is larger than root 
    if (l < n && arr[l] > arr[largest])
        largest = l;

    // If right child is larger than largest so far 
    if (r < n && arr[r] > arr[largest])
        largest = r;

    // If largest is not root 
    if (largest != i)
    {
        swap(arr[i], arr[largest]);

        // Recursively heapify the affected sub-tree 
        heapify(arr, n, largest);
    }
}

// main function to do heap sort 
void heapSort(short int arr[], int n)
{
    // Build heap (rearrange array) 
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // One by one extract an element from heap 
    for (int i = n - 1; i > 0; i--)
    {
        // Move current root to end 
        swap(arr[0], arr[i]);
        // call max heapify on the reduced heap 
        heapify(arr, i, 0);
    }
}

int main()
{
    // Read data from file
    ifstream dataFile;
    clock_t start, end;
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(3);
    dataFile.open("data1.txt");
    short int arrayA[100000];
    int count = 0;
   
    // Give a warning and exit if fail to read the file
    if (dataFile.fail())
    {
        cout << "Unable to find input file!";
        exit(1);
    }

    // Write the data into arrayA
    int temp;
    while (dataFile >> temp)
    {
        arrayA[count] = temp;
        count++;
    }

    dataFile.close();

    // Apply Heapsort
    int n = count;
    start = clock();
    heapSort(arrayA, n);
    end = clock();
    cout << "Time spent: " << (double)(end - start) / CLOCKS_PER_SEC << endl;

    // Check if the array is actually sorted
    if (SortCheck(arrayA, n) == 1) 
    {
        cout << "The array is sorted." << endl;
    }

    // Write sorted array into a .txt file
    ofstream pfile;
    pfile.open("data1sorted.txt");
    for (int i = 0; i < n; i++)
    {
        pfile << arrayA[i] << endl;
    }
    pfile.close();

    return 0;
}
