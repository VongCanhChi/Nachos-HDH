/* sort.c 
 *    Test program to sort a large number of integers.
 *
 *    Intention is to stress virtual memory system.
 *
 *    Ideally, we could read the unsorted array off of the file system,
 *	and store the result back to the file system!
 */

#include "syscall.h"


int main()
{   
    int A[100];
    int i, j, temp, n, count, select;
    PrintString("Nhap n: ");
    n = ReadInt();
    while (n > 100 || n <= 0) {
	PrintString("Nhap 0 < n <= 100. Nhap lai: ");
	n = ReadInt();
    }

    for (i = 0; i < n; i++)
    {
	count = i+1;
	PrintString("A[");
	PrintInt(count);
	PrintString("]: ");
        A[i] = ReadInt();
    }
    PrintString("Ban muon sap xep giam dan(0) hay tang dan(1)\n");
    PrintString("Nhap lua chon: ");
    select = ReadInt();
    while (select != 0 && select != 1) {
	PrintString("Lua chon 0 (giam) hoac 1 (tang). Nhap lai: ");
	select = ReadInt();
    }
    // Bubble sort
    if (select == 1) { // Sap xep tang dan.
	for (i = 0; i < n-1; i++)       
	   for (j = 0; j < n-i-1; j++)  
		if (A[j] > A[j+1]) {
			temp = A[j];
		      	A[j] = A[j + 1];
		      	A[j + 1] = temp;
		}
    } 
    else { // Sap xep giam dan.
	for (i = 0; i < n-1; i++)       
	    for (j = 0; j < n-i-1; j++)  
		if (A[j] < A[j+1]) {
			temp = A[j];
		      	A[j] = A[j + 1];
		      	A[j + 1] = temp;
		}
    }
         
    PrintString("Mang sau khi sap xep: \n");
    for (i = 0; i < n; i++)
    {
	PrintInt(A[i]);
	PrintString("\t");
    }    
    return 0;
}
