#ifndef _IMAGE_INDIVIDUAL_H_
#define _IMAGE_INDIVIDUAL_H_

#include "constants.h"


using namespace std;

class ImageIndividual{
public:
	vector<vector<int> > genes;
	long fit;
	ImageIndividual();
	ImageIndividual(vector<vector<int> > genes);
	ImageIndividual(const ImageIndividual& other);
	ImageIndividual(vector<vector<int> > geneSet1, vector<vector<int> > geneSet2);

	long fitness();

	void computeFitness();

	vector<vector<int> > getFirstHalf(int xpoint) const;

	vector<vector<int> > getLastHalf(int xpoint) const;

	ImageIndividual dumbCross(const ImageIndividual& other) const;
	ImageIndividual cross(const ImageIndividual& other) const;

	void mutate();

	void print();

	void convolve();
};
#endif
