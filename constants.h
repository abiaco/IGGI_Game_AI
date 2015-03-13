#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#define POPULATION_SIZE 100
#define RANGE_LIMIT 255
#define GENE_COUNT 64
#define GENE_COUNT_WIDTH 640
#define GENE_COUNT_HEIGHT 480
#define CROSS_POINT 240
#define TOURNAMENT_SIZE 2
#define R_CROSS_NO 240
#define FITNESS_LIMIT 40

#define HIGH_LIMIT 40
#define LOW_LIMIT 160

#define CONVOLVE_WIDTH 16
#define CONVOLVE_HEIGHT 12

#include <random>
#include <iostream>
#include <vector>
#include <time.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>

using namespace std;

inline bool contains(vector<int> v, int i){
	for (int j = 0; j < v.size(); j++){
		if (v[j] == i) return true;
	}
	return false;
}


inline int getRandom(int range) {
	unsigned int time_ui = static_cast<unsigned int>(time(NULL));
	srand(time_ui);
	return  0 + (rand() % (int)(range - 0 + 1));
}

inline int getRandomAvoid(int range, vector<int> toAvoid){
	unsigned int time_ui = static_cast<unsigned int>(time(NULL));
	srand(time_ui);
	int result = 0 + (rand() % (int)(range - 0 + 1));
	while (contains(toAvoid, result)){
		result = 0 + (rand() % (int)(range - 0 + 1));
	}
	return result;
}


#endif // _CONSTANTS_H_
