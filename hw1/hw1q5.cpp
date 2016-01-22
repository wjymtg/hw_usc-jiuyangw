#include <iostream>
#include <cstring> 
#include <fstream>

using namespace std;


void reverseprint(ifstream &infile, int n){
	if(n <= 0) return;
	string str = "";
	infile >> str;
	reverseprint(infile, n-1);
	cout << str << endl;
}

int main(int argc, char* argv[]){
	if(argc < 2){
    	cerr << "Please enter filename." << endl;
    	return 1;
  	}
  	int number;
  	ifstream infile(argv[1]);
  	if(!infile){
  		cerr << "Error reading file!" << endl;
  		return 1;
  	}
  	infile >> number;
  	reverseprint(infile, number);
  	return 0;
}
