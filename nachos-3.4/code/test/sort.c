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
    int i, j, tmp, n,count,select;
    PrintString("Nhap n: ");
    n = ReadInt();
    /* first initialize the array, in reverse sorted order */
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
    /* then sort! */
	
    for (i = 0; i < n-1; i++)       
    	for (j = 0; j < n-i-1; j++)  
        	if (A[j] > A[j+1] && select==1||A[j] < A[j+1] && select==0){
			tmp = A[j];
	      		A[j] = A[j + 1];
	      		A[j + 1] = tmp;
		}
            
    PrintString("Mang sau khi sap xep\n");
    for (i = 0; i < n; i++)
    {
	PrintInt(A[i]);
	PrintString("\t");     
    }    
    return 0;	/* and then we're done -- should be 0! */
}
