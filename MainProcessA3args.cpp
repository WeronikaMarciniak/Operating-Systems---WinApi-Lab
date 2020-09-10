#include <windows.h>
#include <stdio.h>
#include <pthread.h>
#include <tchar.h>
#include <mutex>
#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
HANDLE hMutex; //used mutex object to implement spinlock
using namespace std;
SYSTEM_INFO siSysInfo;
int main(int argc, TCHAR *argv[])  
{  
   STARTUPINFO si1 = { 0 }, si2 = { 0 };
    si1.cb = sizeof si1;
    si2.cb = sizeof si2;
    PROCESS_INFORMATION pi1 = { 0 }, pi2 = { 0 };
    const TCHAR* target1 = _T("Random3args.exe");
    const TCHAR* target2 = _T("ReadingRandomsA3args.exe");
    int times=0;//second argument,defines time distance beetween generating numbers
    int repeat = 0;//third argument, defines how many times the numbers have to be generated and how many times the operations on values must be done
    
    times=_tstoi(argv[2]);
    repeat=_tstoi(argv[3]);
	times=times/0.001;
    
    hMutex = CreateMutex(NULL,0,NULL);
    for(int i=0;i<repeat;i++){
    	
   if (!CreateProcess(target1, GetCommandLine(), 0, FALSE, 0, CREATE_SUSPENDED, 0, 0, &si1, &pi1)) //CREATE_SUSPENDED argument makes process 1 hanging and waiting until process 2 excecute
    {
        cerr << "CreateProcess failed (" << GetLastError() << ").\n";
    }
    else
    {
           
         WaitForSingleObject(hMutex,INFINITE);  // process2 call WaitForSingleObject(hmutex) first to get mutex
        
        if (!CreateProcess(target2, GetCommandLine(), 0, FALSE, 0, 0, 0, 0, &si2, &pi2))//Process 2 is created and excecuted ...
        {
            cerr << "CreateProcess failed (" << GetLastError() << ").\n";
        }
        else
        {
        	
			
			WaitForSingleObject(pi2.hProcess, INFINITE);
            
            CloseHandle(pi2.hProcess); //process2 closes
            CloseHandle(pi2.hThread);
            
        }
        
        ReleaseMutex(hMutex);//mutex released, process1 unlocked
        ResumeThread(pi1.hThread); //Process 1 is resumed and executed 
        WaitForSingleObject(pi1.hProcess, INFINITE);
        
        CloseHandle(hMutex);
        CloseHandle(pi1.hProcess);//process 1 closes
        CloseHandle(pi1.hThread);
        
 
    }
    
    Sleep(times);
    
    }
    
    LARGE_INTEGER li;
    double PCFreq = 0.0;
    __int64 CounterStart = 0; 
    if(!QueryPerformanceFrequency(&li))
    cout << "QueryPerformanceFrequency failed!\n";

    PCFreq = double(li.QuadPart)/1000.0;

    QueryPerformanceCounter(&li);
    CounterStart = li.QuadPart;
    QueryPerformanceCounter(&li);
    double c= (li.QuadPart - CounterStart)/PCFreq;
    cout<<"Performance time: "<<c<< " miliseconds";
    
    
    return 0;
}
