//
//  windrose_file.cpp
//  
//
//  Created by Akshar Joshi on 10/15/15.
//
//
#include <stdio.h>
#include <iostream>     // std::cout
#include <fstream>      // std::ifstream
#include <cstdlib>
#include <string.h>
#include <sstream>

using namespace std;

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
    int NUM_THREADS=5;
    // zero out array
    memset(m, 0, sizeof(m));
    // Scrub input
    
    std::ifstream datafilename("input.txt");
    
    if(datafilename.fail()){
        printf("Error in file");
    }
    std::string fname;
    
    //cout<<"file name is: \n";
    
    pthread_t threads[NUM_THREADS];
    int rc;
    int i;
    
//#pragma parallel for collapse (2)
    for( i=0; i < NUM_THREADS; i++ ){
        // READ CSV FILES
        while( getline (datafilename,fname) )
        {
            //load file
            //cout<< fname << "\n";
            //printf("%s",fname);
            std::ifstream datafile(fname.c_str());
            
            double spd, dir; char c;
            
            while ((datafile >> spd >> c >> dir) && (c == ',')){
                m[speedBucket(spd)][directionBucket(dir)] ++;
            }
        }
    }
    pthread_exit(NULL);
    return 0;
}


/*
#pragma parallel 
{
    while( getline (datafilename,fname) )
    {
        //load file
        //cout<< fname << "\n";
        //printf("%s",fname);
        std::ifstream datafile(fname.c_str());
        
        double spd, dir; char c;
        
        while ((datafile >> spd >> c >> dir) && (c == ',')){
            m[speedBucket(spd)][directionBucket(dir)] ++;
        }
    }
}
    //exit;
    // OPTIONAL: print out the results
    /*for (int j = 0; j < 6; j++) {
        for (int k = 0; k < 16; k++){
            printf("%d ", m[j][k]);
        }
        printf("\n");
    }*/
    
//    return 0;
    
    // for (file: files){
    // 	loadFile(file);
    // }
    //number of files
    // frequency (month, week, day)
    // start date
    
    
//}

