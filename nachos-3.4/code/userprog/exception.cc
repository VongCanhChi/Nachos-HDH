// exception.cc 
//	Entry point into the Nachos kernel from user programs.
//	There are two kinds of things that can cause control to
//	transfer back to here from user code:
//
//	syscall -- The user code explicitly requests to call a procedure
//	in the Nachos kernel.  Right now, the only function we support is
//	"Halt".
//
//	exceptions -- The user code does something that the CPU can't handle.
//	For instance, accessing memory that doesn't exist, arithmetic errors,
//	etc.  
//
//	Interrupts (which can also cause control to transfer from user
//	code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"



void IncreasePC()
{
	int counter = machine->ReadRegister(PCReg);
   	machine->WriteRegister(PrevPCReg, counter);
    	counter = machine->ReadRegister(NextPCReg);
    	machine->WriteRegister(PCReg, counter);
   	machine->WriteRegister(NextPCReg, counter + 4);
}

// Ham sao chep vung nho User sang vung nho System.
char* User2System(int virtAddr, int limit)
{
	int i; //chi so index
	int oneChar;
	char* kernelBuf = NULL;
	kernelBuf = new char[limit + 1]; //can cho chuoi terminal
	if (kernelBuf == NULL)
		return kernelBuf;
		
	memset(kernelBuf, 0, limit + 1);
	
	for (i = 0; i < limit; i++)
	{
		machine->ReadMem(virtAddr + i, 1, &oneChar);
		kernelBuf[i] = (char)oneChar;
		if (oneChar == 0)
			break;
	}
	return kernelBuf;
}

// Ham sao chep vung nho System sang vung nho User.
int System2User(int virtAddr, int len, char* buffer)
{
	if (len < 0) return -1;
	if (len == 0)return len;
	int i = 0;
	int oneChar = 0;
	do{
		oneChar = (int)buffer[i];
		machine->WriteMem(virtAddr + i, 1, oneChar);
		i++;
	} while (i < len && oneChar != 0);
	return i;
}


// Ham xu ly ngoai le
void ExceptionHandler(ExceptionType which)
{
    	int type = machine->ReadRegister(2);
	
	switch (which) {
	case NoException:
		return;

	case PageFaultException:{
		DEBUG('a', "\n No valid translation found");
		printf("\n\n No valid translation found");
		interrupt->Halt();
		break;
	}
	case ReadOnlyException:{
		DEBUG('a', "\n Write attempted to page marked read-only");
		printf("\n\n Write attempted to page marked read-only");
		interrupt->Halt();
		break;
	}
	case BusErrorException:{
		DEBUG('a', "\n Translation resulted invalid physical address");
		printf("\n\n Translation resulted invalid physical address");
		interrupt->Halt();
		break;
	}
	case AddressErrorException:{
		DEBUG('a', "\n Unaligned reference or one that was beyond the end of the address space");
		printf("\n\n Unaligned reference or one that was beyond the end of the address space");
		interrupt->Halt();
		break;
	}
	case OverflowException:{
		DEBUG('a', "\nInteger overflow in add or sub.");
		printf("\n\n Integer overflow in add or sub.");
		interrupt->Halt();
		break;
	}
	case IllegalInstrException:{
		DEBUG('a', "\n Unimplemented or reserved instr.");
		printf("\n\n Unimplemented or reserved instr.");
		interrupt->Halt();
		break;
	}
	case NumExceptionTypes:{
		DEBUG('a', "\n Number exception types");
		printf("\n\n Number exception types");
		interrupt->Halt();
		break;
	}
	case SyscallException:
		switch (type){

		case SC_Halt:{
			DEBUG('a', "\nShutdown, initiated by user program. ");
			printf("\nShutdown, initiated by user program. ");
			interrupt->Halt();
			return;
		}
		case SC_ReadInt:{
                    char* buffer;
                    int MAX_BUFFER = 255; 
                    buffer = new char[MAX_BUFFER + 1];
                    int numbytes = gSynchConsole->Read(buffer, MAX_BUFFER);
                    int number = 0;
                    bool isNegative = false;
                    int firstNumIndex = 0;
                    int lastNumIndex = 0;
                    if(buffer[0] == '-') // Xu ly khi nhap so am.
                    {
                        isNegative = true;
                        firstNumIndex = 1;
                        lastNumIndex = 1;                        			   		
                    }
                                       
                    for(int i = firstNumIndex; i < numbytes; i++)				
                    {
			if(buffer[i] < '0' && buffer[i] > '9') // Neu nhap vao ky tu khong phai so thi bao loi va dung.
                        {
                            printf("\n\n The integer number is not valid");
                            DEBUG('a', "\n The integer number is not valid");
                            machine->WriteRegister(2, 0);
                            IncreasePC();
                            delete buffer;
                            return;
                        }
                        lastNumIndex = i;
                    }			
                    
                    // Chuyen chuoi ve so nguyen.
                    for(int i = firstNumIndex; i<= lastNumIndex; i++)
                    {
                        number = number * 10 + (int)(buffer[i] - 48);
                    }
                    
                    
                    if(isNegative) // Xu ly so am.
                    {
                        number = number * -1;
                    }
                    machine->WriteRegister(2, number);
                    IncreasePC();
                    delete buffer;
                    return;
		}

		case SC_PrintInt:{
		    
                    int number = machine->ReadRegister(4); // Doc so nguyen.
		    if(number == 0)
                    {
                        gSynchConsole->Write("0", 1); 
                        IncreasePC();
                        return;    
                    }
                    
                    
                    bool isNegative = false; 
                    int numberOfNum = 0; 
                    int firstNumIndex = 0; 
			
                    if(number < 0) // Xu ly so am.
                    {
                        isNegative = true;
                        number = number * -1; 
                        firstNumIndex = 1; 
                    } 	
                    
                    int t_number = number; 
                    while(t_number) // Dem so chu so cua so nguyen.
                    {
                        numberOfNum++;
                        t_number /= 10;
                    }
    
		    
                    char* buffer;
                    int MAX_BUFFER = 255;
                    buffer = new char[MAX_BUFFER + 1];
		    // Chuyen so thanh chuoi ky tu de in.
                    for(int i = firstNumIndex + numberOfNum - 1; i >= firstNumIndex; i--)
                    {
                        buffer[i] = (char)((number % 10) + 48);
                        number /= 10;
                    }
                    if(isNegative) // Xu ly so am.
                    {
                        buffer[0] = '-';
			buffer[numberOfNum + 1] = 0;
                        gSynchConsole->Write(buffer, numberOfNum + 1);
                        delete buffer;
                        IncreasePC();
                        return;
                    }
		    buffer[numberOfNum] = 0;	
                    gSynchConsole->Write(buffer, numberOfNum);
                    delete buffer;
                    IncreasePC();
                    return;        			
					
		}

		case SC_ReadChar:{

			int maxBytes = 255; // Doc toi da 255 ky tu.
			char* buffer = new char[255];
			int numBytes = gSynchConsole->Read(buffer, maxBytes);

			if(numBytes > 1) // Khi nhap nhieu hon 1 ky tu thi bao loi va dung.
			{
				printf("Chi duoc nhap duy nhat 1 ky tu!");
				DEBUG('a', "\nERROR: Chi duoc nhap duy nhat 1 ky tu!");
				machine->WriteRegister(2, 0);
			}
			else if(numBytes == 0) // Nhap ky tu roi thi bao loi va dung.
			{
				printf("Ky tu rong!");
				DEBUG('a', "\nERROR: Ky tu rong!");
				machine->WriteRegister(2, 0);
			}
			else
			{				
				char c = buffer[0];
				machine->WriteRegister(2, c);
			}

			delete buffer;
			
			break;
		}

		case SC_PrintChar:{
			
			char c = (char)machine->ReadRegister(4); 
			gSynchConsole->Write(&c, 1);
			break;

		}
		case SC_ReadString:{
			int virtAddr, length;
			char* buffer;
			virtAddr = machine->ReadRegister(4);
			length = machine->ReadRegister(5);
			buffer = User2System(virtAddr, length);
			gSynchConsole->Read(buffer, length);
			System2User(virtAddr, length, buffer);
			delete buffer;
			IncreasePC();
			return;
			
		}
		case SC_PrintString:{
			int virtAddr;
			char* buffer;
			virtAddr = machine->ReadRegister(4);
			buffer = User2System(virtAddr, 255);
			int length = 0;
			while (buffer[length] != 0) length++;
			gSynchConsole->Write(buffer, length + 1);
			delete buffer;
			break;
		}
		
		default:
			break;
		}
		IncreasePC();
	}
}
