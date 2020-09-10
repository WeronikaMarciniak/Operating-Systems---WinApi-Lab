#include <iostream>
#include <Windows.h>
#include <string>
#include <tchar.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
//this program calculates average value of numbers in file, finds minimum and maximum in the file using one thread
using namespace std;
HANDLE hMutex;
vector<int> Values;
double Average,MIN,MAX;
SYSTEM_INFO siSysInfo;
DWORD ValueOperations(LPVOID* arg)
{  
      HANDLE hMutex = (HANDLE)(*arg);   
      WaitForSingleObject(hMutex, INFINITE); 
      Average = 0;
      double Sum = 0;
      for (unsigned int i = 0; i < Values.size(); i++) { 
    //cout << Values[i] << " "; checking, if the values from the file are being read correctly
	   Sum+=Values[i];
	   }
      Average = Sum/Values.size();
      cout<<"The average of given values is: "<<Average;
      
      MIN=Values[0];
     for(unsigned int j=0;j<Values.size();j++)
     {
	    if(MIN>Values[j])
       	{
		MIN=Values[j];
    	}
    }
        cout<<endl;
      cout<<"Minimum value is "<<MIN; 
     
	 MAX=Values[0];
     for(unsigned int k=0;k<Values.size();k++)
    {
	   if(MAX<Values[k])
     	{
		MAX=Values[k];
    	}
    }
    
	cout<<endl;
    cout<<"Maximum value is "<<MAX;  
	  
    ReleaseMutex(hMutex); 
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
 
  int n = 0;//first argument, defines, how many numbers needs to be generated
  int times=0;//second argument,defines time distance beetween generating numbers
  int repeat = 0;//third argument, defines how many times the numbers have to be generated and how many times the operations on values must be done
  n=_tstoi(argv[1]);
  times=_tstoi(argv[2]);
  repeat=_tstoi(argv[3]);
  GetSystemInfo(&siSysInfo);  
   
hMutex=CreateMutex(NULL, FALSE, NULL);
HANDLE hThread;  
DWORD threadID;
hThread=CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ValueOperations, &hMutex, 0, &threadID);
ReleaseMutex(hMutex); 
WaitForSingleObject(hThread, INFINITE);  
CloseHandle(hMutex);  
CloseHandle(hThread);
Results<<"Total numbers: "<<n<<" | Version:Multithreads | Machine: OEM ID: "<<siSysInfo.dwOemId<<" Processor Type: "<<siSysInfo.dwProcessorType<<" | Replies: "<<repeat<<" | Pause: "<<times<<endl;
Results<<"AVG "<<" MIN  "<<" MAX  "<<endl;
Results.close();
for(int i=0;i<repeat;i++){
Results.open("Results.txt", ios::in | ios::out | ios_base::app);	
Results<<Average<<"  "<<MIN<<"   "<<MAX<<endl;}
Results.close();    
return 0;
}
