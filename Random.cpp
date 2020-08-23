#include <iostream>
#include <Windows.h>
#include <string>
#include <tchar.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;
int main( int argc, TCHAR *argv[] )
{
    fstream File;
	File.open("RandomValues.txt", ios::in | ios::out);
    if (!File.is_open())
    cerr << "failed to open file\n";

    
	srand( time( NULL ) );
	int n = 0;
	n=_tstoi(argv[1]);
//	cout<<n<<endl; //prints value given as parameter
	int r=0;
	cout<<endl;
	for(int i=0;i<n;i++)
	{
		r=rand() % 100;
		File<<r<<" ";
		//cout<<r<<"values "; checking if values are read correctly
       
		
	}
	CloseHandle( File );
	return 0;
}
