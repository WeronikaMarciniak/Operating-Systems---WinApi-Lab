#include <iostream>
#include <Windows.h>
#include <string>
#include <tchar.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;
SYSTEM_INFO siSysInfo;
int main( int argc, TCHAR *argv[] )
{
    fstream File;
	File.open("RandomValues.txt", ios::in | ios::out);
    if (!File.is_open())
    cerr << "failed to open file\n";
	srand( time( NULL ) );
	
    int n = 0;//first argument, defines, how many files needs to be generated
	int times=0;//second argument,defines time distance beetween generating numbers
	
    n=_tstoi(argv[1]);
	times=_tstoi(argv[2]);
	
	int r=0;
		for(int i=0;i<n;i++)
	{
		r=rand() % 100;
		File<<r<<" ";
		//cout<<r<<"values "; //checking if values are read correctly
		
		
	}
	cout<<"Generating numbers with "<<times<<" seconds..."<<endl;
	 
	File.close();

	return 0;
}
