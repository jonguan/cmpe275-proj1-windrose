#include <stdio.h>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <dirent.h>
#include <cstdarg>
#include "omp.h"

inline std::string format(const char* fmt, ...){
    int size = 512;
    char* buffer = 0;
    buffer = new char[size];
    va_list vl;
    va_start(vl, fmt);
    int nsize = vsnprintf(buffer, size, fmt, vl);
    if(size<=nsize){ //fail delete buffer and try again
        delete[] buffer;
        buffer = 0;
        buffer = new char[nsize+1]; //+1 for /0
        nsize = vsnprintf(buffer, size, fmt, vl);
    }
    std::string ret(buffer);
    va_end(vl);
    delete[] buffer;
    return ret;
}


// windrose pseudocode

// Divide speed into 6 buckets
// Negative speeds are not allowed
int speedBucket(double data) {
	if (data < 0) return -1;

	// Stratified divide
	if (data < 1) {
		return 0;
	} else if (data < 3) {
		return 1;
	} else if (data < 5) {
		return 2;
	} else if (data < 7) {
		return 3;
	} else if (data < 9) {
		return 4;
	}else {
		return 5;
	}
}

// Divide 360 into 16 sectors
int directionBucket(float degrees) {
	int bucket = degrees / 22.5 ;
	return bucket;
}

// Main - load files and 
int main(int argc, char *argv[]){

	int const NUM_ROWS = 6;
	int const NUM_COLS = 16;

	int m[NUM_ROWS][NUM_COLS];
	// zero out array
	memset(m, 0, sizeof(m));
	// Scrub input
	std::string help ("-h");
	if (argc != 4 || help.compare(argv[1]) == 0 ) {
		printf("USAGE: ./windrose datafiledirectory stationId HH00\n");
		printf("Enter 0 for null values\n");
		return 0;
	}
	
	// Count number files in directory
	DIR *dp;
	struct dirent *ep;
	dp = opendir (argv[1]);
	int numfiles;
	if (dp == NULL){
		perror ("ERROR: Couldn't open directory\n");
		return 1;
	}
	while (ep = readdir (dp))
      	numfiles++;

    (void) closedir (dp);

	//load files in directory
	omp_set_num_threads(1);
	#pragma omp parallel for
	for (int i = 1; i<= 10; i++) {
		std::string filename  = format("./%smesonet-201301%02d_%s.csv", argv[1], i, argv[3]);
		printf("%s\n", filename.c_str());

		std::ifstream datafile(filename.c_str());
		// datafile.seekg(0, std::ios::end);
		// size_t size = datafile.tellg();
		// std::string buffer(size, ' ');
		// datafile.seekg(0);
		// datafile.read(&buffer[0], size); 

		// std::stringstream ss(buffer);

		std::stringstream buffer;
		buffer << datafile.rdbuf();
		
		// std::cout << buffer.str() << std::endl;

		double spd, dir; char c;

		while ((buffer >> spd >> c >> dir) && (c == ',')){	
			int spdbckt = speedBucket(spd);
			int dirbckt = directionBucket(dir);
			// #pragma omp critical	
			// m[spdbckt][dirbckt] ++;
		}	
	}
	


	// OPTIONAL: print out the results
	for (int j = 0; j < 6; j++) {
		for (int k = 0; k < 16; k++){
			printf("%d ", m[j][k]);
		}
		printf("\n");
	}

  return 0;

	// for (file: files){
	// 	loadFile(file);
	// }
	//number of files
	// frequency (month, week, day)
	// start date


}

int dirNumFiles(char *directory)
{
	DIR *dp;
	int i;
 	struct dirent *ep;     
  	dp = opendir ("./");

  	if (dp != NULL)
  	{
    	while (ep = readdir (dp))
      	i++;

    	(void) closedir (dp);
  	}
  	else
    	perror ("Couldn't open the directory");

  	printf("There's %d files in the current directory.\n", i);

  	return i;
}


