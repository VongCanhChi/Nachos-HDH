// pcb.h 
//  Process Control Block
//	Save all information to control the process
// All rights reserved.


#ifndef PCB_H
#define PCB_H

#include "thread.h"
#include "synch.h"

// Process Control Block
class PCB
{
private:
    Semaphore* joinsem;         //semaphore cho qua trinh join
    Semaphore* exitsem;         //semaphore cho qua trinh exit
    Semaphore	*mutex;         //semaphore cho qua trinh truy xuat doc quyen  
    int exitcode;		
    Thread* thread;             //Tien trinh cua chuong trinh    
    int numwait;                //So tien trinh da join
    int	pid;
    char FileName[32];          // Ten cua tien trinh
  
public:
    int parentID;               // ID cua tien trinh cha
    
    int	JoinStatus;	//Trang thai co Join voi tien trinh nao khong? neu co thi gia tri chinh la ID cua tien trinh ma no Join
    
    PCB(int id);               // Contructor
    ~PCB();                     // Destructor

    int Exec(char *filename, int pID);        //Tao mot thread moi
    int GetID();                //Tra ve ProcessID cua tien trình goi thuc hien
    int GetNumWait();           //Tra ve so luong tien trinh dang cho

    void JoinWait();            //Tien trình cha đoi tien trinh con ket thuc
    void ExitWait();            //Tien trinh con ket thuc

    void JoinRelease();         //Bao cho tien trinh cha thuc thi tiep
    void ExitRelease();         //Cho phep tien trinh con ket thuc

    void IncNumWait();          //Tang so tien trinh cho
    void DecNumWait();          //Giam so tien trinh cho

    void SetExitCode(int ec);   //Dat exitcode của tiến trình
    int GetExitCode();          //Tra ve exitcode
    
    char* GetNameThread();

    void SetFileName(char* filename);    // Set ten tien trinh
    char* GetFileName();                 // Tra ve ten tien trinh


};

//*********************************************************************************************************************
void MyStartProcess(int pID);
#endif // PCB_H
