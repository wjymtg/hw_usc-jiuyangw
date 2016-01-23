#include <iostream>
#include <fstream>
#include <sstream>
#include <malloc.h>

using namespace std;

int main(int argc, char* argv[])
{
	if(argc < 3){
    	cerr << "Please provide an input and output file." << endl;
    	return 1;
  	}
  	ifstream input(argv[1]);
  	ofstream output(argv[2]);

  	int floors;
  	int *floorsizes;
  	string ***trojans;
  	string curr;
  	int **pcounter;

  	input >> floors;
  	trojans = new string**[floors];
  	pcounter = new int*[floors];

  	//you will need to keep track of how many people are on each floor.
  	floorsizes = new int[floors];

	for (int i = 0; i < floors; i++) {
  		floorsizes[i] = 0;
		trojans[i] = NULL;
  	}
  	while(getline(input, curr)){
    	stringstream ss;
    	ss << curr;
    	ss >> curr;
  	  	if(curr == "MOVEIN"){
	  		int i,k;
			ss >> i;
	 	    ss >> k;
		  	if (ss.fail()) {
		  		output << "Error - incorrect command" << endl;
		  	}
		  	else {
		  	  	if(i >= floors || i < 0){
		  	  		output << "Error - floor i does not exist." << endl;
		  	  	}
		  	  	else if(trojans[i] != NULL){
		 	  		output << "Error - floor i is not empty" << endl;
		  	  	}
		  	  	else{				//initialize floor i
		  	  		floorsizes[i] = k;
		  	  	 	trojans[i] = new string*[k];
		  	  	 	pcounter[i] = new int[k];
		  	  	 	for(int j = 0; j < k; j++){
		  	  	 		trojans[i][j] = NULL;
		  	  	 		pcounter[i][j] = 0;
		  	  	 	}
		  	  }
		  	}
	  	}
	  	else if (curr == "MOVEOUT") {
	  		int i;
	  		ss >> i;
	  		if(ss.fail()){
	  			output << "Error - incorrect command" << endl;
	  		}
	  		else{
	  			if(i >= floors || i < 0){
		  	  		output << "Error - floor i does not exist." << endl;
		  	  	}
		  	  	else if(floorsizes[i] == 0){
		  	  		output << "Error - floor i is empty" << endl;
		  	  	}
		  	  	else{			//dellocation
		  	  		for(int j = 0; j < floorsizes[i]; j++){	
		  	  			delete [] trojans[i][j];
		  	  		}
		  	  		delete [] pcounter[i];
		  	  		delete [] trojans[i];
		  	  		trojans[i] = NULL;
		  	  		floorsizes[i] = 0;
		  	  	}

	  		}
	  	}
	  	else if (curr == "OBTAIN") {
	  		int i,j,k;
	  		ss >> i;
	  		ss >> j;
	  		ss >> k;
	  		if(ss.fail()){
	  			output << "Error - incorrect command" << endl;
	  		}
	  		else{
	  			if(i >= floors || i < 0){
		  	  		output << "Error - floor i does not exist." << endl;
		  	  	}
		  	  	else if(floorsizes[i] == 0){
		  	  		output << "Error - floor i is empty" << endl;
		  	  	}
		  	  	else if(trojans[i][j] != NULL){
		  	  		output << "Error - student already has possessions." << endl;
		  	  	}
		  	  	else{
		  	  		trojans[i][j] = new string[k];
		  	  		pcounter[i][j] = k;
		  	  		for(int a = 0; a < k; a++){
		  	  			ss >> trojans[i][j][a];
		  	  		}
		  	  	}
	  		}
	  	}
	  	else if (curr == "OUTPUT") {
	  		int i,j;
	  		ss >> i;
	  		ss >> j;
	  		if(ss.fail()){
	  			output << "Error - incorrect command" << endl;
	  		}
	  		else{
	  			if(i >= floors || i < 0){
	  				output << "Error - no such student." << endl;
	  			}
	  			else if(j < 0 || j >= floorsizes[i]){
	  				output << "Error - no such student." << endl;
	  			}
	  			else if(pcounter[i][j] == 0){
	  				output << "Error - student has no possessions." << endl;
	  			}
	  			else{
	  				for(int k = 0; k < pcounter[i][j]; k++){
 						output << trojans[i][j][k] << endl;
	  				}
	  			}
	  		}
	  	}
	  	else{
	  		output << "Error - incorrect command" << endl;
	  	}
  	}

  	for(int i = 0; i < floors; i++){	//deallocation
  		if(floorsizes[i] != 0){
  			for(int j = 0; j < floorsizes[i]; j++){	
			  	delete [] trojans[i][j];
			}
			delete [] trojans[i];
			delete [] pcounter[i];
		}
  	}
  	delete [] trojans;
  	delete [] pcounter;
  	delete [] floorsizes;
  	return 0;
}
