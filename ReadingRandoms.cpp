#include <iostream>
#include <Windows.h>
#include <string>
#include <tchar.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
using namespace std;

int main( int argc, TCHAR *argv[] )
{
// open the file
ifstream File("RandomValues.txt", ios::in);
if (!File.is_open())
    cerr << "failed to open file\n";

vector<int> Values;
  
// read the values 
int val;

while (File >> val){
    Values.push_back(val);
   
   }
    
// calculate average of values
double Average = 0;
double Sum = 0;
for (unsigned int i = 0; i < Values.size(); i++) { 
    //cout << Values[i] << " "; checking, if the values from the file are being read correctly
	Sum+=Values[i];
	}
Average = Sum/Values.size();
cout<<"The average of given values is: "<<Average;
File.close();
return 0;
}
