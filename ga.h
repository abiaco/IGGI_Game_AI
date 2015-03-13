#ifndef _GA_H_
#define _GA_H_

#include "ImageIndividual.h"
#include "constants.h"

#define T ImageIndividual


using namespace std;

class GA {
public:
    vector<T> population;

    GA();

    void generateRandomPopulation();
    void fillRandomPop();

	vector<T> selectImageIndividuals();
	vector<T> cross(vector<ImageIndividual> selected);
	vector<T> randomCross(vector<ImageIndividual> selected);
	void applyMutations(vector<T> pop);
	T getFittest();
    void evolve();
};

#endif
