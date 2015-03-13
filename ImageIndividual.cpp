#include "ImageIndividual.h"


using namespace std;

ImageIndividual::ImageIndividual(){
	unsigned int time_ui = static_cast<unsigned int>(time(NULL));
	srand(time_ui);

	vector<int> temp;
	for (int i = 0; i < GENE_COUNT_WIDTH; i++){
		for (int j = 0; j < GENE_COUNT_HEIGHT; j++){
			temp.push_back(0 + (rand() % (int)(RANGE_LIMIT - 0 + 1)));
		}
		this->genes.push_back(temp);
		temp.clear();
	}
	convolve();
	computeFitness();
}

ImageIndividual::ImageIndividual( vector<vector<int> > genes){
	for (int i = 0; i < GENE_COUNT_WIDTH; i++){
		this->genes.push_back(genes[i]);
	}
	computeFitness();
}

ImageIndividual::ImageIndividual(const ImageIndividual& other){
	for (int i = 0; i < GENE_COUNT_WIDTH; i++){
		this->genes.push_back(other.genes[i]);
	}
	computeFitness();
}

ImageIndividual::ImageIndividual(vector<vector<int> > geneSet1, vector<vector<int> > geneSet2) {
	for (int i = 0; i < geneSet1.size(); i++)
		this->genes.push_back(geneSet1[i]);

	for (int i = 0; i < geneSet2.size(); i++)
		this->genes.push_back(geneSet2[i]);
	computeFitness();
}



long ImageIndividual::fitness(){
	return this->fit;
}

vector<vector<int> > ImageIndividual::getFirstHalf(int xpoint) const{

	vector<vector<int> > first;
	for (int i = 0; i <= xpoint; i++){
		first.push_back(genes[i]);
	}

	return first;
}

vector<vector<int> > ImageIndividual::getLastHalf(int xpoint) const{

	vector<vector<int> > last;

	for (int i = ++xpoint; i < GENE_COUNT_WIDTH; i++){
		last.push_back(genes[i]);
	}

	return last;
}

void ImageIndividual::mutate(){
	int i = getRandom(GENE_COUNT_WIDTH - 1);
	int j = getRandom(GENE_COUNT_HEIGHT - 1);
	genes[i][j] = getRandom(RANGE_LIMIT);
}

ImageIndividual ImageIndividual::cross(const ImageIndividual& other) const{
	ImageIndividual child(*this);
	vector<int> indexes;
	for (int n = 0; n < R_CROSS_NO; n++){
		int randm = getRandomAvoid(GENE_COUNT_WIDTH - 1, indexes);
		indexes.push_back(randm);
	}
	for (int n = 0; n < R_CROSS_NO; n++){
		child.genes[indexes[n]] = other.genes[indexes[n]];
	}
	indexes.clear();
	return child;
}


ImageIndividual ImageIndividual::dumbCross(const ImageIndividual& other) const{
	ImageIndividual child(this->getFirstHalf(CROSS_POINT), other.getLastHalf(CROSS_POINT));
	return child;
}

void ImageIndividual::print(){
	cout << "Individual: \n";
	for (int i = 0; i < GENE_COUNT_WIDTH; i++){
		for (int j = 0; j < GENE_COUNT_HEIGHT; j++){
			cout << genes[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

void ImageIndividual::computeFitness(){
	this->fit = 0;
    int high_places = 0, low_places = 0, nav_places = 0;
    int explored_width = 0, explored_height = 0;
    long sum = 0;

	while (explored_width < GENE_COUNT_WIDTH){
        while (explored_height < GENE_COUNT_HEIGHT){
            for (int i = explored_width; i < explored_width + CONVOLVE_WIDTH; i++){
                for(int j = explored_height; j < explored_height + CONVOLVE_HEIGHT; j++){
                    sum += genes[i][j];
                }
            }
            int avg = sum / (CONVOLVE_HEIGHT * CONVOLVE_WIDTH);
            if( avg < HIGH_LIMIT) high_places ++;
            if( avg >= HIGH_LIMIT && avg <= LOW_LIMIT) nav_places++;
            if( avg > LOW_LIMIT) low_places ++;

            explored_height += CONVOLVE_HEIGHT;
        }
        explored_width += CONVOLVE_WIDTH;
        explored_height = 0;
        sum = 0;
    }

    if (high_places < 3) this->fit = -1;
    else if(low_places < 3) this->fit = -1;
    else this->fit = nav_places;
}

void ImageIndividual::convolve(){
    int explored_width = 0, explored_height = 0;
    long sum = 0;
    while (explored_width < GENE_COUNT_WIDTH){
        while (explored_height < GENE_COUNT_HEIGHT){
            for (int i = explored_width; i < explored_width + CONVOLVE_WIDTH; i++){
                for(int j = explored_height; j < explored_height + CONVOLVE_HEIGHT; j++){
                    sum += genes[i][j];
                }
            }
            int avg = sum / (CONVOLVE_HEIGHT * CONVOLVE_WIDTH);
            for (int i = explored_width; i < explored_width + CONVOLVE_WIDTH; i++){
                for(int j = explored_height; j < explored_height + CONVOLVE_HEIGHT; j++){
                    genes[i][j] = avg;
                }
            }
            explored_height += CONVOLVE_HEIGHT;
        }
        explored_width += CONVOLVE_WIDTH;
        explored_height = 0;
        sum = 0;
    }
}
