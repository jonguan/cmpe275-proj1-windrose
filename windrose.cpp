#include <stdio.h>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <cstdlib>
#include <string>
#include <sstream>

// windrose pseudocode

// Divide speed into 5 buckets
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
	} else {
		return 4;
	}
}

// Divide 360 into 16 sectors
int directionBucket(float degrees) {
	int bucket = degrees / 22.5 ;
	return bucket;
}

// Main - load files and 
int main(int argc, char *argv[]){

	int m[5][16];
	// zero out array
	memset(m, 0, sizeof(m));
	// Scrub input
	if (argc != 2) {
		printf("USAGE: ./windrose datafile\n");
		return 0;
	}
	


	//load file
	std::ifstream datafile(argv[1]);
	double spd, dir; char c;

	while ((datafile >> spd >> c >> dir) && (c == ',')){		
		m[speedBucket(spd)][directionBucket(dir)] ++;
	}


	// OPTIONAL: print out the results
	for (int j = 0; j < 5; j++) {
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
