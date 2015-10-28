# cmpe275-proj1-windrose

## To compile:
g++ -fopenmp windrose.cpp -o windrose.out  

Possible files include 
  windrose.cpp  -- csv parsing file with openmp
  windrosebin.cpp -- binary parsing file with openmp
  windrosebin_reduc.cpp -- binary parsing file with openmp and 3D arrays for reduction

## To run:
OMP_NUM_THREADS=2 ./windrose.out dataDirectory stationID hour
OMP_NUM_THREADS=2 ./windrose.out csvdata/ AP061 0800

## Sample input
head -n 10 mesonet-20020621_0800.csv
Sandy         UT	H0070	1.34	110.00	40.54	-111.51
WNCT Studios           Greenville    NC	H0092	0.45	100.00	35.61	-77.37  
WNCT Studios           Greenville    NC	H0092	0.45	220.00	35.61	-77.37  
WSLS Studios           Roanoke       VA	H0097	0.45	100.00	37.27	-79.94  
WNCT Studios           Greenville    NC	H0092	0.89	180.00	35.61	-77.37  
WSLS Studios           Roanoke       VA	H0097	0.00	320.00	37.27	-79.94  
WNCT Studios           Greenville    NC	H0092	1.34	70.00	35.61	-77.37  
WSLS Studios           Roanoke       VA	H0097	0.00	320.00	37.27	-79.94  
Black River Electric   Fredericktown MO	H0003	0.00	230.00	37.51	-90.33  
BlueStar Systems       Milford      OH	H0344	0.00	240.00	39.19	-84.21  

## Sample output
60f81dcbfb56:cmpe275-proj1-windrose jsx039$ g++ -fopenmp windrose.cpp -o windrose.out  
60f81dcbfb56:cmpe275-proj1-windrose jsx039$ time ./windrose.out csvdata/ AP061 0800
./csvdata/mesonet-20020621_0800.csv  
./csvdata/mesonet-20040621_0800.csv  
./csvdata/mesonet-20130621_0800.csv  
./csvdata/mesonet-20120621_0800.csv  
./csvdata/mesonet-20060621_0800.csv  
./csvdata/mesonet-20140621_0800.csv  
./csvdata/mesonet-20080621_0800.csv  
./csvdata/mesonet-20100621_0800.csv  
AP061 0 7  
AP061 0 6  
AP061 0 8  
AP061 0 8  
AP061 0 6  
AP061 0 7  
AP061 0 8  
AP061 1 6  
AP061 0 7  
AP061 0 6  
./csvdata/mesonet-20030621_0800.csv  
AP061 0 8  
AP061 1 6  
AP061 0 7  
AP061 0 8  
AP061 0 6  
AP061 0 6  
AP061 0 8  
AP061 0 8  
AP061 0 6  
AP061 0 7  
./csvdata/mesonet-20050621_0800.csv  
AP061 0 6  
AP061 0 8  
AP061 0 7  
AP061 0 8  
AP061 0 8  
AP061 0 8  
AP061 0 8  
AP061 0 6  
AP061 0 6  
AP061 0 8  
AP061 0 7  
AP061 0 8  
AP061 0 8  
AP061 0 8  
AP061 0 8  
./csvdata/mesonet-20070621_0800.csv  
AP061 1 6  
AP061 0 6  
AP061 1 6  
AP061 0 7  
AP061 1 6  
AP061 1 6  
./csvdata/mesonet-20090621_0800.csv  
AP061 1 7  
AP061 1 7  
AP061 1 6  
AP061 1 7  
./csvdata/mesonet-20110621_0800.csv  
AP061 0 13  
AP061 0 13  
AP061 0 13  
AP061 0 13  
AP061 0 13  
AP061 0 13  
AP061 0 13  
AP061 0 13  
AP061 0 13  
AP061 0 13  
AP061 0 13  
AP061 0 13  
0 0 0 0 0 0 10 8 17 0 0 0 0 12 0 0  
0 0 0 0 0 0 7 3 0 0 0 0 0 0 0 0  
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0  
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0  
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0  
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0  

real	0m1.664s  
user	0m8.092s  
sys	0m0.159s  
 
