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
DWORD ValueOperations(LPVOID* arg)
{  
      HANDLE hMutex = (HANDLE)(*arg);   
      WaitForSingleObject(hMutex, INFINITE); 
      double Average = 0;
      double Sum = 0;
      for (unsigned int i = 0; i < Values.size(); i++) { 
    //cout << Values[i] << " "; checking, if the values from the file are being read correctly
	   Sum+=Values[i];
	   }
      Average = Sum/Values.size();
      cout<<"The average of given values is: "<<Average;
      
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
   
   
hMutex=CreateMutex(NULL, FALSE, NULL);
HANDLE hThread;  
DWORD threadID;
hThread=CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ValueOperations, &hMutex, 0, &threadID);
ReleaseMutex(hMutex); 
WaitForSingleObject(hThread, INFINITE);  
CloseHandle(hMutex);  
CloseHandle(hThread);
    
return 0;
}
