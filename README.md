Columnsort implementation

Columnsort works as follows. It begins with n = r*s values placed in an r * s matrix (2-D array – you'll need to look up somewhere how to handle 2-D arrays in C++), where
r mod s = 0 and r >= 2(s - 1)^2

Columnsort involves 8 steps:

1. Sort the values in each column.

2. "Transpose" the matrix by reading s values at a time in column-major order and putting them back into the matrix in row-major order.

3. Sort the new columns.

4. Reverse step 2 – access in row-major order and insert in column-major order.

5. Sort the new columns.

6. Access the values in column-major order and shift the values down (and up to the top of the next column) by floor(r / 2) positions.

7. Sort the new columns.

8. Reverse the shift of step 6, that is, access the values in column-major order and shift them up by floor(r / 2) positions. The extra column will go away and the result will be values that, in column-major order, are sorted.



filer.cpp is used to create 3 different files each containing 100,000 random integers with maximum numeric value of 32,000.

Use Heapsort.cpp to sort those 3 files created by filer.cpp

Implement Columnsort.cpp to sort the same 3 files created by filer.cpp and compare the result with output file from Heapsort.
