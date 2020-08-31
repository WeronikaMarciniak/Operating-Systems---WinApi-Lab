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
double MIN=Values[0],MAX=Values[0];
for(unsigned int j=0;j<Values.size();j++)
{
	if(MIN>Values[j])
	{
		MIN=Values[j];
	}
}
cout<<endl;
cout<<"Minimum value is "<<MIN;
for(unsigned int k=0;k<Values.size();k++)
{
	if(MAX<Values[k])
	{
		MAX=Values[k];
	}
}
cout<<endl;
cout<<"Maximum value is "<<MAX;
return 0;
}
