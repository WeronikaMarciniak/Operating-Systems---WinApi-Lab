#include <iostream>
#include <Windows.h>
#include <string>
#include <tchar.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
//this program calculates average value of numbers in file, finds minimum and maximum in the file using 3 threads
#define THREADCOUNT 3
using namespace std;
HANDLE hSemaphore; // using semaphore object to synchronize threads
vector<int> Values;
double Average,MIN,MAX;
SYSTEM_INFO siSysInfo;

DWORD Averages(LPVOID* arg)  
{  
      
      WaitForSingleObject(hSemaphore, INFINITE); 
      Average = 0;
      double Sum = 0;
      
      for (unsigned int i = 0; i < Values.size(); i++) { 
    //cout << Values[i] << " "; checking, if the values from the file are being read correctly
       Sum+=Values[i];
       }
      Average = Sum/Values.size();
    cout<<"The average of given values is: "<<Average<<endl; 
     
    ReleaseSemaphore(hSemaphore,1,NULL);
    return 0;
}  
DWORD Minimum(LPVOID* arg)  
{  
       
     WaitForSingleObject(hSemaphore, INFINITE); 
     MIN=Values[0];
     for(unsigned int j=0;j<Values.size();j++)
     {
        if(MIN>Values[j])
        {
        MIN=Values[j];
        }
}
cout<<endl;
cout<<"Minimum value is "<<MIN<<endl;  
      ReleaseSemaphore(hSemaphore,1,NULL);
    return 0;
}  
DWORD Maximum(LPVOID* arg)  
{  
    
    WaitForSingleObject(hSemaphore, INFINITE);
     MAX=Values[0];
     for(unsigned int k=0;k<Values.size();k++)
    {
       if(MAX<Values[k])
        {
        MAX=Values[k];
        }
    }
cout<<endl;
cout<<"Maximum value is "<<MAX<<endl;  
      ReleaseSemaphore(hSemaphore,1,NULL);  
    return 0;
}  
int main( int argc, TCHAR *argv[] )
{
// open the file
ifstream File("RandomValues.txt", ios::in);
if (!File.is_open())
    cerr << "failed to open file\n";
  
// read the values 
int val;

while (File >> val){
    Values.push_back(val);
   
   }
fstream Results;
Results.open("Results.txt", ios::in | ios::out );
if (!Results.is_open())
    cerr << "failed to open file\n";
 
  int n = 0;//first argument, defines, how many files needs to be generated
  int times=0;//second argument,defines time distance beetween generating numbers
  int repeat = 0;//third argument, defines how many times the numbers have to be generated and how many times the operations on values must be done
  n=_tstoi(argv[1]);
  times=_tstoi(argv[2]);
  repeat=_tstoi(argv[3]);
  GetSystemInfo(&siSysInfo);  
hSemaphore=CreateSemaphore(NULL,0,3,NULL); 
HANDLE hThreads[3];  
DWORD threadID1,threadID2,threadID3; 

//calculate average of values-first thread
hThreads[0]=CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Averages, &hSemaphore,0, &threadID1);
// finding minimum - second thread
hThreads[1]=CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Minimum, &hSemaphore, 0, &threadID2);
// finding maximum - third thread
hThreads[2]=CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Maximum, &hSemaphore, 0, &threadID3);
//}

ReleaseSemaphore(hSemaphore,1,NULL);  
WaitForMultipleObjects(THREADCOUNT, hThreads, TRUE, INFINITE);  
for( int i=0; i < THREADCOUNT; i++ ){

        CloseHandle(hThreads[i]);
    }
CloseHandle(hSemaphore);  
Results<<"Total numbers: "<<n<<" | Version:Multithreads | Machine: OEM ID: "<<siSysInfo.dwOemId<<" Processor Type: "<<siSysInfo.dwProcessorType<<" | Replies: "<<repeat<<" | Pause: "<<times<<endl;
Results<<"AVG "<<" MIN  "<<" MAX  "<<endl;
Results.close();
for(int i=0;i<repeat;i++){
Results.open("Results.txt", ios::in | ios::out | ios_base::app);	
Results<<Average<<"  "<<MIN<<"   "<<MAX<<endl;}
File.close();
Results.close();

return 0;
}

