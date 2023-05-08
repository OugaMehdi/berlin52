
#include <vector>
using namespace std;

struct Ville
{
  double x;
  double y;
};



struct Individu{
	vector<int> chemin;
	double coutChemin;
};

double distanceVille(Ville v1, Ville v2);


vector< vector<int> > voisinsImmediat(vector<int> solution);
vector<int> meilleurVoisin(vector<int> solution);
vector<int> genererUnVoisin(vector<int> solution);

double coutVilleAVisiter(vector<int> solution, vector<Ville> villes); 

vector<int> escaladeSimple(vector<int> solutionInit, vector<Ville> villes);
vector<int> escaladeComplet(vector<int> solutionInit, vector<Ville> villes);
vector<int> recuitSimule(vector<int> solutionInit, vector<Ville> villes, double tempInit, double tempArret, double facteurRefroidissement , int N );


//vector<Individu> mesurerAdaptation(vector<Individu> population, vector<Ville> villes );
//Individu selection(vector<Individu> evaluation);
//Individu reproduire(Individu parent1, Individu parent2);
//void mutation(Individu enfant);
////vector<Individu> genererPopulation(vector<int> cheminInit);
//vector<Individu> genererPopulation(vector<Ville> villes);
//Individu genetique(vector<Ville> villes);

vector<Individu*> mesurerAdaptation(vector<Individu*>& population, vector<Ville>& villes );
Individu* selection(vector<Individu*> evaluation);
Individu* reproduire(Individu* parent1, Individu* parent2);
void mutation(Individu* enfant);
vector<Individu*> genererPopulation(vector<Ville>& villes);
Individu* genetique(vector<Ville>& villes);
