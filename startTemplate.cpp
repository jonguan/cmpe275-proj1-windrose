// windrose pseudocode

// speed bucket function [5 buckets]
// direction [divide 360 in number of sectors]


int main(...){
	load file

	for (file: files){
		loadFile(file);
	}
	//number of files
	// frequency (month, week, day)
	// start date


}

data = loadFile(data.dat);

for (d : data){
	s = speedBucket(data)
	d = directionBucket(data)
	m[s][d]++;

}
