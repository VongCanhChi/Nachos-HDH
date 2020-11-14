#include "syscall.h"

int main()
{
	int i=33;
	PrintString("Dec\tChar\n");
	PrintString("------------\n");
	PrintInt(32);
	PrintString("\t");
	PrintString("Space");
	PrintString("\n");
	for(i;i<=126;i++)
	{
		PrintInt(i);
		PrintString("\t");
		PrintChar(i);
		PrintString("\n");
	}
	return 0;
}
