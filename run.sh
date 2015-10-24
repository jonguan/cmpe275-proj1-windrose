#!/bin/bash

g++-5 windrose-reduction.cpp -o windrose.out -fopenmp -std=gnu++11

curr_dir=$PWD

#find files in currdir with .csv extension recursively
file_list=""
for entry in $(find $curr_dir -type f -name "*.csv")
do
	file_list="$file_list $entry"
done

#echo $file_list

time ./windrose.out $file_list


