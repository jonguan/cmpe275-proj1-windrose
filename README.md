# cmpe275-proj1-windrose

## To compile:
g++ -fopenmp windrose.cpp -o windrose.out

## To run:
OMP_NUM_THREADS=2 ./windrose.out csvdata/ 0 0800

## Sample input
head -n 10 20130101_0000.csv

0.00,0.00  
0.45,46.00  
0.00,340.00  
0.00,264.00  
0.00,132.00  
0.00,148.00  
5.36,309.00  
0.00,271.00  
0.00,143.00  
1.79,34.00  

## Sample output
60f81dcbfb56:cmpe275-proj1-windrose jsx039$ g++ -fopenmp windrose.cpp -o windrose.out  
60f81dcbfb56:cmpe275-proj1-windrose jsx039$ time OMP_NUM_THREADS=2 ./windrose.out csvdata/ 0 0800  
./csvdata/mesonet-20130101_0800.csv  
./csvdata/mesonet-20130106_0800.csv  
./csvdata/mesonet-20130102_0800.csv  
./csvdata/mesonet-20130107_0800.csv  
./csvdata/mesonet-20130103_0800.csv  
./csvdata/mesonet-20130108_0800.csv  
./csvdata/mesonet-20130104_0800.csv  
./csvdata/mesonet-20130109_0800.csv  
./csvdata/mesonet-20130105_0800.csv  
./csvdata/mesonet-20130110_0800.csv  
50793 19534 21967 18439 22051 17750 22182 20153 27731 24513 30967 27062 31508 23928 26138 21143  
14924 9556 9233 7833 7784 6470 8241 9270 13060 12643 15673 14018 15292 11858 11641 9767  
5443 3333 3231 2866 3204 2315 3045 3613 5527 5500 6766 6087 7007 5370 4960 4065  
1898 913 1000 904 1004 702 1088 1232 1990 1832 2231 2073 2271 1851 1631 1331  
607 477 438 349 457 309 428 697 1026 1049 1024 901 1135 779 729 452  
541 276 195 383 302 188 351 516 845 752 835 613 701 482 383 258  
  
real	0m0.920s  
user	0m1.804s  
sys	0m0.014s  

 
