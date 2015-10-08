// windrose pseudocode

// speed bucket function [5 buckets]
// direction [divide 360 in number of sectors]

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
	} else if (data < 9) {
		return 4;
	} else {
		return 5;
	}
}

// Divide 360 into 8 sectors
int directionBucket(float degrees) {
	int bucket = degrees / 8;
	return bucket;
}

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
