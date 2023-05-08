#include <iostream>
#include <fstream>
#include <algorithm>
#include "berlin.h"
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	

    ifstream file("berlin52");
    int n;
    file >> n;
    vector<Ville> villes(n);
    for (int i = 0; i < n; i++)
    {
    	int temp;
        file >> temp >> villes[i].x >> villes[i].y;
    }
    file.close();

	vector<int> solutionInit(n);
	for (int i = 0; i < n; i++)
    {	
    	solutionInit[i] = i;
    }
    
    printf("------Solution Algo escalade simple (2-opt)------\n");
    vector<int> solutionEscaladeSimple = escaladeSimple(solutionInit, villes);
    for (int i = 0; i < n; i++)
    {
    	printf("%d ",solutionEscaladeSimple[i]);
    }
    double distEscaladeSimple = coutVilleAVisiter(solutionEscaladeSimple,villes);
    printf("\n Distance: %lf", distEscaladeSimple);
    
    printf("\n\n");
    
	printf("------Solution Algo escalade complet (2-opt)------\n");
	vector<int> solutionEscaladeComplet = escaladeComplet(solutionInit, villes);
    for (int i = 0; i < n; i++)
    {
    	printf("%d ",solutionEscaladeComplet[i]);
    }
    double distEscaladeComplet = coutVilleAVisiter(solutionEscaladeComplet,villes);
    printf("\n Distance: %lf", distEscaladeComplet);
    
    printf("\n\n");
    
    printf("------Solution Algo recuit simule ------\n");
    double tempInit = 1000;
    double tempArret = 0.1;
    double facteurRefroidissement = 0.999;
    int N = 52;
    vector<int> solutionRecuitSimule = recuitSimule(solutionInit, villes, tempInit, tempArret, facteurRefroidissement , N );
	for (int i = 0; i < n; i++)
    {
    	printf("%d ",solutionRecuitSimule[i]);
    }
	double distRecuitSimule = coutVilleAVisiter(solutionRecuitSimule,villes);
    printf("\n Distance: %lf", distRecuitSimule);
    
    printf("\n");
    
    printf("------Solution Genetique------\n");
    Individu* solutionGenetique = genetique(villes);
    for (int i = 0; i < n; i++)
    {
    	printf("%d ",solutionGenetique->chemin[i]);
    }
    double distGenetique = coutVilleAVisiter(solutionGenetique->chemin,villes);
    printf("\n Distance: %lf", distGenetique);
    double distGenetique2 = solutionGenetique->coutChemin;
    printf("\n Distance2 : %lf", distGenetique2);
	return 0;
}

//#include <iostream>
//#include <cmath>
//#include <cstdlib>
//#include <ctime>
//#include <vector>
//#include <fstream>
//#include "berlin.h"
//using namespace std;
//
//struct Ville
//{
//  double x;
//  double y;
//};
//
//
//// Calcule la distance entre deux villes
//double distanceVille(Ville v1, Ville v2)
//{
//    double distance;
//    distance = sqrt(pow((v1.x - v2.x),2) + pow((v1.y - v2.y),2));
//    return distance;
//}
//
//
//// Calcule le coût total d'un itinéraire
//
//double coutVilleAVisiter(vector<int> solution, vector<Ville> villes)
//{
//    double distance = 0;
//    for (int i = 0; i < solution.size() - 1; i++) // on arrete dans la ville avant derniere car on calcule la distance de deux villes consecutives
//    {
//
//}
//
//// Algorithme de recuit simulé
//vector<int> simulated_annealing(vector<int> sol, vector<Ville> cities, double T0, double alpha, double Tmin) {
//  int n = cities.size();
//  vector<int> s = sol;
//  double E = coutVilleAVisiter(s, cities);
//  double T = T0;
//  while (T > Tmin) {
//    vector<int> s2 = s;
//    int i = rand() % n;
//    int j = rand() % n;
//    swap(s2[i], s2[j]);
//	
//    double E2 = coutVilleAVisiter(s2, cities);
//    double dE = E2 - E;
//    if (dE < 0) {
//      s = s2;
//      E = E2;
//    } else {
//      double p = exp(-dE / T);
//      if (rand() / (double)RAND_MAX < p) {
//        s = s2;
//        E = E2;
//      }
//    }
//    T *= alpha;
//  }
//  return s;
//}
//
//int main() {
//	ifstream file("berlin52");
//    int n;
//    file >> n;
//    vector<Ville> cities(n);
//    for (int i = 0; i < n; i++)
//    {
//    	int temp;
//        file >> temp >> cities[i].x >> cities[i].y;
//    }
//    file.close();
//    
//    vector<int> sol(n);
//	for (int i = 0; i < n; i++)
//    {	
//    	sol[i] = i;
//    }
//    
//    double T0 = 10000;
//double alpha = 0.99;
//double Tmin = 1e-40;
//
//// Résolution du problème avec l'algorithme de recuit simulé
//vector<int> solution = simulated_annealing(sol,cities, T0, alpha, Tmin);
//
//// Affichage de la solution
//cout << "Solution trouvée : ";
//for (int i = 0; i < solution.size(); i++) {
//cout << solution[i] << " ";
//}
//cout << endl;
//cout << "Coût de la solution : " << coutVilleAVisiter(solution, cities) << endl;
//    
//
//	return 0;
//}
//	
//	
	
