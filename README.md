# IGGI_Game_AI

This is the one-week project for the IGGI Game AI module. A Genetic Algorithm which evolves HeightMaps.

Most is described in the report, however, one aspect needs mentioning: how to add new Individual classes for the GA to process properly.

Rather easy:

The class must have two members: a vector of genes (stl kind of vector), named genes, depicting the chromosome, containing whatever type of gene one may wish to have, and a fitness (named fit) of type long - but can be adjusted.

Assuming the class is named Individual, the following functions hsould be present and implemented in order to ensure proper functionality:

  Individual();
	Individual(vector<vector<int> > genes); //not necessarily vector<vector<int> >, can be vector<anything>.
	Individual(const Individual& other);
	Individual(vector<vector<int> > geneSet1, vector<vector<int> > geneSet2); //same as above

	long fitness(); //can have any return type provided you give a comparison method and operator.

	void computeFitness();

	vector<vector<int> > getFirstHalf(int xpoint) const; //same as above

	vector<vector<int> > getLastHalf(int xpoint) const; //same as above

	Individual dumbCross(const Individual& other) const;
	Individual cross(const Individual& other) const;

	void mutate();

	void print();

	void convolve();
	
As long as the user-defined class implements these functions properly, the GA will be perfectly happy to evolve a solution.
Enjoy!
