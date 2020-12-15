// ptable.h 
//      Control process running include PCB table with MAX (10) element.
//      Constructor of PTable class will create parent process on 0 position.
//      From parent process, we will create other process by calling Exec().
// All rights reserved.


#ifndef PTABLE_H
#define PTABLE_H

#include "bitmap.h"
#include "pcb.h"
#include "synch.h"

#define MAXPROCESS 10

class PTable
{
private:
     BitMap *bm; //Danh dau vi tris da duowc su dung trong pcb
     PCB *pcb[MAXPROCESS];
     int psize;
     Semaphore *bmsem;//Dung de ngan chan truong hop nap 2 tien trinh cung luc

public:
     PTable(int size);		//Khoi tao size doi tuong pcb de luu size process. Gan gia tri ban dau la null. Nho khoi tao *bm va *bmsem de su dung
     ~PTable();			//Huy doi tuong da tao
		
     int ExecUpdate(char* filename);  //Khoi tao system call SC_Exit
     int ExitUpdate(int ec);          //Khoi tao system call SC_Exit
     int JoinUpdate(int pID);         //Khoi tao cho system call SC_Join

     int GetFreeSlot();      //Tim free slot đe luu thong tin cho tien trinh moi
     bool IsExist(int pID);  //Kiem tra ton tai processID nay khong?
     
     void Remove(int pID);   //Khi tien trinh ket thuc, thi xoa processID ra khoi mang quan ly no

    char* GetName(int pID);  //Tra ve ten cua tien trinh
};
#endif // PTABLE_H

