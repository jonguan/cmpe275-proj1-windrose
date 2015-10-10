#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main(){

	ifstream infile;
	infile.open("20130101.csv");

	ofstream outfile;
	outfile.open("temp_read.txt");

	if(!(infile.is_open())){
		exit(EXIT_FAILURE);
	}

	char word[50];
	infile >> word;
	while(infile.good()){ 	
		infile >> word;
		outfile << word << "\n";
	}

	outfile.close();
	infile.close();
	return 0;
}
