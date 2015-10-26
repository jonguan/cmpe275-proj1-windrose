#include <stdio.h>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <cstdarg>
#include "omp.h"

using namespace std;

int const NUM_ROWS = 6;
int const NUM_COLS = 16;

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

void printLines(int *arr){
	// OPTIONAL: print out the results
	// #pragma parallel for
	for (int j = 0; j < NUM_ROWS; j++) {
		for (int k = 0; k < NUM_COLS; k++){
			printf("%d ", arr[j * NUM_COLS + k] );
		}
		printf("\n");
	}
}

// windrose pseudocode

// Divide speed into 6 buckets
// Negative speeds are not allowed
int speedBucket(float data) {
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



	int m[NUM_ROWS][NUM_COLS];
	int n[NUM_COLS];
	int o[NUM_ROWS];
	int p[NUM_ROWS*NUM_COLS];

	// zero out array
	memset(m, 0, sizeof(m));
	memset(n, 0, sizeof(n));
	memset(o, 0, sizeof(o));
	memset(p, 0, sizeof(p));
	// Scrub input
	std::string help ("-h");
	if (argc != 4 || help.compare(argv[1]) == 0 ) {
		printf("USAGE: ./windrose datafiledirectory stationId HH00\n");
		printf("Enter 0 for null values\n");
		return 0;
	}

	string station = argv[2];

	//load files in directory
	#pragma omp parallel for
	for (int i = 2; i<= 14; i++) {
		std::string filename  = format("./%smesonet-20%02d0621_%s.dat", argv[1], i, argv[3]);
		printf("%s\n", filename.c_str());

		// Cache line is 64 bytes - approx 2 lines

		ifstream datafile(filename.c_str(), ios::ate | ios::binary);
		long datasize = datafile.tellg();
		datafile.seekg(0);
		vector<unsigned char> bytes(datasize, 0);
		datafile.read((char*)&bytes[0], bytes.size());

	
		for (int j = 0; j < datasize; j+=(5+4*sizeof(int))) 
		{
			int spd, dir, lat, lon; 

			// 5 bytes station id 
			// string stationid = string(1, bytes[j]);
			string stationid (reinterpret_cast<char const*>(&bytes[j]), 5);

			if (stationid == station) {
				// Intel CPU is little endian
				spd = (bytes[j+5]<<24)|(bytes[j+6]<<16)|(bytes[j+7]<<8)|(bytes[j+8]);
				dir = (bytes[j+9]<<24)|(bytes[j+10]<<16)|(bytes[j+11]<<8)|(bytes[j+12]);
				// printf("%s %d %d %d %d\n", stationid.c_str(), spd, dir, j+5, j+5+sizeof(int));

				int spdbckt = speedBucket(spd/100.);
				int dirbckt = directionBucket(dir/100.);

				#pragma omp critical
				{
					p[spdbckt* NUM_COLS + dirbckt]++;
				}	
			}
		}
		
		// datafile.seekg(0, std::ios::end);
		// size_t size = datafile.tellg();
		// std::string buffer(size, ' ');
		// datafile.seekg(0);
		// datafile.read(&buffer[0], size); 
		// std::stringstream ss(buffer);


		
		// char t; string stn, info;

		// string line;
		// while (getline(datafile, line))
		// {
		// 	stringstream buffer(line);
		// 	getline(buffer, info, '\t');
		// 	getline(buffer, stn, '\t');
		// 	buffer >> spd >> dir >> lat >> lon;

		// 	// disregard results not equal to station
		// 	if (station != stn){
		// 		continue;
		// 	}
		// 	int spdbckt = speedBucket(spd);
		// 	int dirbckt = directionBucket(dir);
		// 	// printf("%s %d %d\n", stn.c_str(), spdbckt, dirbckt);
			
		// 	#pragma omp critical
		// 	{
		// 			// m[spdbckt][dirbckt]++;
		// 		p[spdbckt* NUM_COLS + dirbckt]++;
		// 	}	
		// }
	}

	printLines(p);

  	return 0;

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


