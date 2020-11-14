#include "syscall.h"

int main()
{
	char a[50];
	ReadString(a,10);
	PrintString(a);
	return 0;
}
