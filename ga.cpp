
#include "ga.h"
#include "constants.h"

using namespace std;
using namespace cv;

GA::GA(){
    generateRandomPopulation();
}


void GA::generateRandomPopulation(){

    for(int i = 0; i < POPULATION_SIZE; i++){
        T t;
        population.push_back(t);
    }
}

void GA::fillRandomPop(){
	int number = POPULATION_SIZE - population.size();
	cout << "adding " << POPULATION_SIZE - population.size() << "elements!\n";
    for(int i = 0; i < number; i++){
        T t;
        population.push_back(t);
	}
	cout << "population after adding: " << population.size() << "\n";
}

vector<T> GA::selectImageIndividuals(){

    vector<T> selected;
    int i = 0;
    while (i < population.size()){
        double maxfit = population[i].fitness();
        int maxfitindex = i;
        for (int j = i; j < i + TOURNAMENT_SIZE; j++){
            if (population[j].fitness() >= maxfit){
                maxfit = population[j].fitness();
                maxfitindex = j;
            }
        }
        selected.push_back(population[maxfitindex]);
        i += TOURNAMENT_SIZE;

    }
    cout<< "selected size: " << selected.size() << '\n';

    return selected;
}


vector<T> GA::cross(vector<T> selected){
	vector<T> new_pop;
	vector<int> mated;
	int elementsLeft = selected.size();
	int i, j;

	while (elementsLeft > 1){
		i = getRandomAvoid(selected.size() - 1, mated);
		mated.push_back(i);
		elementsLeft -= 1;
		j = getRandomAvoid(selected.size() - 1, mated);
		mated.push_back(j);
		elementsLeft -= 1;
		T child(selected[i].getFirstHalf(CROSS_POINT), selected[j].getLastHalf(CROSS_POINT));
		new_pop.push_back(selected[i].dumbCross(selected[j]));
	}
	return new_pop;
}


vector<T> GA::randomCross(vector<T> selected){
	vector<T> new_pop;
	vector<int> mated;
	int elementsLeft = selected.size();
	int i, j;

	while (elementsLeft > 1){
		i = getRandomAvoid(selected.size() - 1, mated);
		mated.push_back(i);
		elementsLeft -= 1;
		j = getRandomAvoid(selected.size() - 1, mated);
		mated.push_back(j);
		elementsLeft -= 1;
		new_pop.push_back(selected[i].cross(selected[j]));
	}
	return new_pop;
}

void GA::applyMutations(vector<T> pop){
    for (int i = 0; i < pop.size(); i++){
		int prob = getRandom(1000);
        if (prob == 950) pop[i].mutate();
    }
}


T GA::getFittest(){
    double maxFittness = population[0].fitness();
    int index = 0;
    for (int i = 1; i < population.size(); i++){
        if (population[i].fitness() > maxFittness){
            maxFittness = population[i].fitness();
            index = i;
        }
    }
    return population[index];
}


char* makeName(string name){
	char *a = new char[name.size() + 1];
		a[name.size()] = 0;
	memcpy(a, name.c_str(), name.size());
	return a;
}

int** makeArray(vector<vector<int> > vec){
	int** table = new int*[GENE_COUNT_WIDTH];
	for (int i = 0; i < GENE_COUNT_WIDTH; i++){
		table[i] = new int[GENE_COUNT_HEIGHT];
		for (int j = 0; j < GENE_COUNT_HEIGHT; j++){
			table[i][j] = vec[i][j];
		}
	}
	return table;
}


void GA::evolve(){
	Mat kernel;
	int kernel_size = 3;
	Mat::ones(kernel_size, kernel_size, CV_8UC1) / (float)(kernel_size*kernel_size);
	Point anchor = Point(-1, -1);
	double delta = 0;
	int ddepth = -1;
    cout<< "Population (size: " << population.size() << "):\n";
    cout << "\n";
    cin.ignore();
    int generation = 0;
    cout<< "got random population!";

    T fittest = getFittest();
    cout<< "got first fittest! Fitness: "<<fittest.fitness() <<" \n";

    while (fittest.fitness() < FITNESS_LIMIT){
        cout<< "generation: " << generation << endl;
        cout<< " starting evolution! \n";

        cout<< "\n______________________________\n";
        cout<< "Selecting: \n";
        vector<T> selected = selectImageIndividuals();
        cout<< "Done!\n";
        cout<< "\n______________________________\n";
        cout<< "Crossing: \n";
        vector<T> kids = randomCross(selected);
        cout<< "Done!\n";

        population.clear();
        cout<< "population cleared\n";
        for (int i = 0; i < selected.size(); i++)population.push_back(selected[i]);
        cout <<"added selected to new pop\n";
		cout << "current pop size after adding selected: " << population.size() << "\n";
        for (int i = 0; i < kids.size(); i++)population.push_back(kids[i]);
        cout<< "added kids to new pop\n";
		cout << "population size after adding kids: " << population.size() << "\n";
        cout <<"Filling rest of population:\n";
        fillRandomPop();
        cout<<"Done!\n";
        cout<< "New Population (size: " << population.size() <<"):\n";
        cout<<"Mutating:\n";
        applyMutations(population);
        cout <<"Done!\n";
        fittest = getFittest();
        cout<< "Current highest: " << fittest.fitness()<<endl;
        cout<< "got fittest! restarting! \n";
        cout<<"\n\n________________________________________________________\n\n";

		string winname = "images/Generation_" + to_string(generation) + ".jpg";
		fittest.convolve();
		Mat img(GENE_COUNT_WIDTH, GENE_COUNT_HEIGHT, CV_8UC1, makeArray(fittest.genes));
		namedWindow(makeName(winname), WINDOW_NORMAL);
		imshow(makeName(winname),img);
		waitKey();

        generation++;
        kids.clear();
        selected.clear();
    }
    fittest.print();
    cout<<fittest.fitness();
	Mat image(GENE_COUNT_WIDTH, GENE_COUNT_HEIGHT, CV_8UC1, makeArray(fittest.genes));
	//Mat dest_img;
	//filter2D(image, dest_img, ddepth, kernel, anchor, delta, BORDER_DEFAULT);
	string winname = "Generation_Final.jpeg";
	//imwrite(makeName(winname), image);
	namedWindow(winname, WINDOW_NORMAL);
	imshow(winname, image);
	waitKey();


}

int main(){
    GA alg;
    alg.evolve();
	cin.ignore();
	cvDestroyAllWindows();
    return 0;
}
