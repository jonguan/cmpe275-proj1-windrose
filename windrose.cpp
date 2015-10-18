#include <stdio.h>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <cstdlib>
<<<<<<< HEAD
#include <string.h>
=======
#include <cstring>
#include <string>
>>>>>>> 7f8f4258e834123e8797e9a76128642ad04488a3
#include <sstream>
#include <sys/types.h>
#include <dirent.h>
#include <cstdarg>

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

	int m[6][16];
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
	for (int i = 1; i<= numfiles; i++) {
		std::string filename  = format("./%smesonet-201301%02d_%s.csv", argv[1], i, argv[3]);
		printf("%s\n", filename.c_str());
		std::ifstream datafile(filename.c_str());
		double spd, dir; char c;

<<<<<<< HEAD
#pragma parallel for
	while ((datafile >> spd >> c >> dir) && (c == ',')){
		m[speedBucket(spd)][directionBucket(dir)] ++;
=======
		while ((datafile >> spd >> c >> dir) && (c == ',')){		
			m[speedBucket(spd)][directionBucket(dir)] ++;
		}	
>>>>>>> 7f8f4258e834123e8797e9a76128642ad04488a3
	}
	


	// OPTIONAL: print out the results
#pragma parallel for
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


