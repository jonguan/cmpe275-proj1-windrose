%module windrosebin
%include cpointer.i
%include carrays.i
%array_class(int, intArray);
%{
#include <string>
#include "omp.h"
    extern int const NUM_ROWS = 6;
    extern int const NUM_COLS = 16;
    extern void printLines();
    extern int speedBucket(float data);
    extern int directionBucket(float degrees);
    extern int dirNumFiles(char *directory);
    extern int m[NUM_ROWS][NUM_COLS];
    extern int n[NUM_COLS];
    extern int o[NUM_ROWS];
    extern int p[NUM_ROWS*NUM_COLS];
    typedef std::string station;
    typedef std::string format(const char* fmt, ...);
    extern void allocate();
    extern void check(char *arg1,char* argv2,int argc);
    extern void calc(char *argv1, char *argv3,int argc);
    extern void printLines();
    %}
extern int directionBucket(float degrees);
extern void allocate();
extern void check(char *arg1,char* argv2,int argc);
extern void calc(char *argv1, char *argv3,int argc);
extern void printLines();