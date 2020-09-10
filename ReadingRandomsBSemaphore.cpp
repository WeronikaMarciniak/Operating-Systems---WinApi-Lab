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
DWORD Average(LPVOID* arg)  
{  
      WaitForSingleObject(hSemaphore, INFINITE); 
      double Average = 0;
      double Sum = 0;
      for (unsigned int i = 0; i < Values.size(); i++) { 
    //cout << Values[i] << " "; checking, if the values from the file are being read correctly
	   Sum+=Values[i];
	   }
      Average = Sum/Values.size();
    cout<<"The average of given values is: "<<Average;  
    ReleaseSemaphore(hSemaphore,1,NULL);
    return 0;
}  
DWORD Minimum(LPVOID* arg)  
{  
       
     WaitForSingleObject(hSemaphore, INFINITE); 
	 double MIN=Values[0];
     for(unsigned int j=0;j<Values.size();j++)
     {
	    if(MIN>Values[j])
       	{
		MIN=Values[j];
    	}
}
cout<<endl;
cout<<"Minimum value is "<<MIN;  
      ReleaseSemaphore(hSemaphore,1,NULL);
    return 0;
}  
DWORD Maximum(LPVOID* arg)  
{  
    
    WaitForSingleObject(hSemaphore, INFINITE);
     double MAX=Values[0];
     for(unsigned int k=0;k<Values.size();k++)
    {
	   if(MAX<Values[k])
     	{
		MAX=Values[k];
    	}
    }
cout<<endl;
cout<<"Maximum value is "<<MAX;  
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
    
hSemaphore=CreateSemaphore(NULL,0,3,NULL); 
HANDLE hThreads[3];  
DWORD threadID1,threadID2,threadID3; 
// calculate average of values-first thread
hThreads[0]=CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Average, &hSemaphore, 0, &threadID1);
// finding minimum - second thread
hThreads[1]=CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Minimum, &hSemaphore, 0, &threadID2);
// finding maximum - third thread
hThreads[2]=CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Maximum, &hSemaphore, 0, &threadID3);
ReleaseSemaphore(hSemaphore,1,NULL);  
WaitForMultipleObjects(3, hThreads, TRUE, INFINITE);  
for( int i=0; i < THREADCOUNT; i++ ){

        CloseHandle(hThreads[i]);
    }
CloseHandle(hSemaphore);  

File.close();

return 0;
}

