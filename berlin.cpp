#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <limits>
#include <vector>
#include "berlin.h"

using namespace std;

int taillePopulation = 100;
int maxGeneration = 1000;
double tauxMut = 0.01;

double distanceVille(Ville v1, Ville v2)
{
    double distance;
    distance = sqrt(pow((v1.x - v2.x),2) + pow((v1.y - v2.y),2));
    return distance;
}


vector<vector<int> > voisinsImmediat(vector<int> solution)
{
//    vector<vector<int> > voisins;
//    for (int i = 0; i < solution.size() - 1; i++)
//    {
//        vector<int> voisin = solution;
//        swap(voisin[i], voisin[i + 1]);
//        voisins.push_back(voisin);
//    }
//    return voisins;
	vector<vector<int> > voisins;
    for (int i = 0; i < solution.size() - 1; i++) {
        for (int j = i + 1; j < solution.size(); j++) {
            vector<int> voisin = solution;
            reverse(voisin.begin() + i, voisin.begin() + j + 1);
            voisins.push_back(voisin);
        }
    }
    return voisins;
}

vector<int> meilleurVoisin(vector<int> solution, vector<Ville> villes)
{
	vector<int> meilleurVoisin;
	double meilleurDistance = numeric_limits<double>::infinity();
    for (int i = 0; i < solution.size() - 1; i++) {
        for (int j = i + 1; j < solution.size(); j++) {
            vector<int> voisin = solution;
            reverse(voisin.begin() + i, voisin.begin() + j + 1);
            double distanceVoisin = coutVilleAVisiter(voisin,villes); 
			if(distanceVoisin < meilleurDistance){
				meilleurDistance = distanceVoisin;
				meilleurVoisin = voisin;
			}
        }
    }
    return meilleurVoisin;
}

double coutVilleAVisiter(vector<int> solution, vector<Ville> villes)
{
    double distance = 0;
    for (int i = 0; i < solution.size() - 1; i++) // on arrete dans la ville avant derniere car on calcule la distance de deux villes consecutives
    {
        distance = distance + distanceVille(villes[solution[i]], villes[solution[i + 1]]);
    }
    // on doit ajouter la distance entre la premiere ville et la derniere pour avoir un circuit
    distance = distance + distanceVille(villes[solution.back()], villes[solution.front()]);
    return distance;
}


vector<int> escaladeSimple(vector<int> solutionInit, vector<Ville> villes)
{
    vector<int> solutionAct = solutionInit;
    double distanceAct = coutVilleAVisiter(solutionAct, villes);
    bool trouve = true;
    while (trouve)
    {
        trouve = false;
        vector<vector<int> > voisins = voisinsImmediat(solutionAct);
        for (int i = 0; i < voisins.size(); i++)
        {
            double distanceVoisin = coutVilleAVisiter(voisins[i], villes);
            if (distanceVoisin < distanceAct)
            {
                distanceAct = distanceVoisin;
                solutionAct = voisins[i];
                trouve = true;
                break;
            }
        }
    }
    return solutionAct;
}

vector<int> escaladeComplet(vector<int> solutionInit, vector<Ville> villes)
{
    vector<int> solutionAct = solutionInit;
    while (true)
    {
		vector<int> meilleurV = meilleurVoisin(solutionAct, villes);
		double distanceAct = coutVilleAVisiter(solutionAct, villes);
		double distanceMeilleurVoisin = coutVilleAVisiter(meilleurV, villes);
        if(distanceMeilleurVoisin < distanceAct){
        	solutionAct = meilleurV;
		} else break;
    }
    return solutionAct;
}


vector<int> genererUnVoisin(vector<int> solution)
{
    for (int i = 0; i < solution.size() - 1; i++) {
        for (int j = i + 1; j < solution.size(); j++) {
            reverse(solution.begin() + i, solution.begin() + j + 1);
        }
    }
	
    return solution;	
}


vector<int> recuitSimule(vector<int> solutionInit, vector<Ville> villes, double tempInit, double tempArret, double facteurRefroidissement , int N )
{
	int n = solutionInit.size();
    vector<int> solutionAct = solutionInit;
    double distanceAct = coutVilleAVisiter(solutionAct, villes);
    double T = tempInit;
    int Essais = pow((N/2),2);
    while (T > tempArret)
    {
        for (int i = 0; i < Essais; i++)
        {
        	vector<int> voisin = solutionAct;
    		int k = rand() % n;
    		int l = rand() % n;
    		swap(voisin[k], voisin[l]);
            double distanceVoisin = coutVilleAVisiter(voisin, villes);
            double DE = distanceVoisin - distanceAct;
            double A = rand() /(double) RAND_MAX;
            double p = exp(-DE/T);
            if (DE < 0 || A <= exp(-DE/T))
            {
                solutionAct = voisin;
                distanceAct = distanceVoisin;
            }
        }
        T = T * facteurRefroidissement;
        
    }
    return solutionAct;
}

//static bool comparerIndividu(const Individu& a, const Individu& b) { 
//		return a.coutChemin > b.coutChemin; 
//}
//vector<Individu> mesurerAdaptation(vector<Individu> population, vector<Ville> villes ){
//	vector<Individu> evaluation;
//	for(int i=0; i<taillePopulation; i++){
//		Individu individu;
//		double cout =0;
//		cout = coutVilleAVisiter(population[i].chemin,villes);
//		individu.coutChemin = cout;
//		individu.chemin = population[i].chemin;
//		evaluation.push_back(individu);
//	}
//	sort(evaluation.begin(), evaluation.end(), comparerIndividu);
//	return evaluation;
//}
//
//
//Individu selection(vector<Individu> evaluation){
//	
//	int tailleTournoi = 2; 
//	vector<Individu> tournoi(tailleTournoi);
//	for(int j=0; j<tailleTournoi; j++){
//		int r = rand() % evaluation.size();
//		tournoi [j] = evaluation[r];
//	}
//	Individu meilleurIndividu = tournoi[0];
//	double meilleurCout = meilleurIndividu.coutChemin;
//	for(int j=1; j<tailleTournoi; j++){
//		double coutAct = tournoi[j].coutChemin;
//		if( coutAct < meilleurCout) {
//			meilleurIndividu = tournoi[j];
//			meilleurCout = coutAct;
//		}
//	}
//	return meilleurIndividu;
//	
//}
//
//
//Individu reproduire(Individu parent1, Individu parent2){
//	vector<int> ch = parent1.chemin;
//	int n = ch.size();
//	int c = rand() % (n+1);
//	Individu enfant;
//	enfant.chemin.resize(n);
//	
//	for (int i = 0; i < c; i++) {
//        enfant.chemin[i] = parent1.chemin[i];
//    }
//
//    // Ajout de la sous-chaîne de y
//    int j = c;
//    for (int i = 0; i < n; i++) {
//        if (find(enfant.chemin.begin(), enfant.chemin.end(), parent2.chemin[i]) == enfant.chemin.end()) {
//            enfant.chemin[j++] = parent2.chemin[i];
//        }
//    }
//	return enfant;
//}
//
//void mutation(Individu enfant){
//	int i;
//	int j;
//	while(i==j){
//		i = rand() % enfant.chemin.size();
//		j = rand() % enfant.chemin.size();
//	}
//	swap(enfant.chemin[i], enfant.chemin[j]);
//}
//
//vector<Individu> genererPopulation(vector<Ville> villes){
//	vector<Individu> population(taillePopulation);
//	for (int i = 0; i < taillePopulation; i++) {
//        vector<int> chemin(villes.size());
//        for (int j = 0; j < villes.size(); j++) {
//            chemin[j] = j;
//        }
//        random_shuffle(chemin.begin(), chemin.end());
//        population[i].chemin = chemin;
//        population[i].coutChemin = coutVilleAVisiter(chemin, villes);
//    }
//	return population;
//}
//
//Individu genetique(vector<Ville> villes){
//	vector<Individu> population = genererPopulation(villes);
//	
//	for(int gen = 0; gen< maxGeneration; gen++){
//		vector<Individu> ensembleIndividus = mesurerAdaptation(population, villes);
//		vector<Individu> nouvellePopulation;
//		for(int i=0; i<taillePopulation; i++){
//			Individu parent1 = selection(ensembleIndividus);
//			Individu parent2 = selection(ensembleIndividus);
//			Individu enfant = reproduire(parent1,parent2);
//			enfant.coutChemin = coutVilleAVisiter(enfant.chemin,villes);
//			double r = (double)rand() / RAND_MAX;
//			if( r < tauxMut ){
//				mutation(enfant);
//			}
//			nouvellePopulation.push_back(enfant);
//			printf("\n%d\n",nouvellePopulation.size());
//		}
//		printf("\npop gen %d \n",gen);
//			for(int k = 0; k<nouvellePopulation.size(); k++){
//				printf("%d ",nouvellePopulation[gen].chemin[k]);
//		}
//		population = nouvellePopulation;
//		
//	}
//	
//	population = mesurerAdaptation(population, villes);
//	
//	Individu meilleurIndividu = population[0];
//	for(int i=0; i<population.size(); i++){
//		Individu individu = population[i];
//		if(individu.coutChemin < meilleurIndividu.coutChemin){
//			meilleurIndividu = population[i];
//		}
//	}
//	
//	return meilleurIndividu;
//}



static bool comparerIndividu(const Individu* a, const Individu* b) { 
		return a->coutChemin > b->coutChemin; 
}
vector<Individu*> mesurerAdaptation(vector<Individu*>& population, vector<Ville>& villes ){
	vector<Individu*> evaluation;
	for(int i=0; i<taillePopulation; i++){
		Individu individu;
		double cout =0;
		cout = coutVilleAVisiter(population[i]->chemin,villes);
		individu.coutChemin = cout;
		individu.chemin = population[i]->chemin;
		evaluation.push_back(&individu);
	}
	sort(evaluation.begin(), evaluation.end(), comparerIndividu);
	return evaluation;
}


Individu* selection(vector<Individu*> evaluation){
	
	int tailleTournoi = 2; 
	vector<Individu*> tournoi(tailleTournoi);
	for(int j=0; j<tailleTournoi; j++){
		int r = rand() % evaluation.size();
		tournoi [j] = evaluation[r];
	}
	Individu* meilleurIndividu = tournoi[0];
	double meilleurCout = meilleurIndividu->coutChemin;
	for(int j=1; j<tailleTournoi; j++){
		double coutAct = tournoi[j]->coutChemin;
		if( coutAct < meilleurCout) {
			meilleurIndividu = tournoi[j];
			meilleurCout = coutAct;
		}
	}
	return meilleurIndividu;
	
}


Individu* reproduire(Individu* parent1, Individu* parent2){
	vector<int> ch = parent1->chemin;
	int n = ch.size();
	int c = rand() % (n+1);
	Individu* enfant;
	enfant->chemin.resize(n);
	
	for (int i = 0; i < c; i++) {
        enfant->chemin[i] = parent1->chemin[i];
    }

    // Ajout de la sous-chaîne de y
    int j = c;
    for (int i = 0; i < n; i++) {
        if (find(enfant->chemin.begin(), enfant->chemin.end(), parent2->chemin[i]) == enfant->chemin.end()) {
            enfant->chemin[j++] = parent2->chemin[i];
        }
    }
	return enfant;
}

void mutation(Individu* enfant){
	int i;
	int j;
	while(i==j){
		i = rand() % enfant->chemin.size();
		j = rand() % enfant->chemin.size();
	}
	swap(enfant->chemin[i], enfant->chemin[j]);
}

vector<Individu*> genererPopulation(vector<Ville>& villes){
	vector<Individu*> population(taillePopulation);
	for (int i = 0; i < taillePopulation; i++) {
        vector<int> chemin(villes.size());
        for (int j = 0; j < villes.size(); j++) {
            chemin[j] = j;
        }
        random_shuffle(chemin.begin(), chemin.end());
        population[i]->chemin = chemin;
        population[i]->coutChemin = coutVilleAVisiter(chemin, villes);
    }
	return population;
}

Individu* genetique(vector<Ville>& villes){
	vector<Individu*> population = genererPopulation(villes);
	
	for(int gen = 0; gen< maxGeneration; gen++){
		vector<Individu*> ensembleIndividus = mesurerAdaptation(population, villes);
		vector<Individu*> nouvellePopulation;
		for(int i=0; i<taillePopulation; i++){
			Individu* parent1 = selection(ensembleIndividus);
			Individu* parent2 = selection(ensembleIndividus);
			Individu* enfant = reproduire(parent1,parent2);
			enfant->coutChemin = coutVilleAVisiter(enfant->chemin,villes);
			double r = (double)rand() / RAND_MAX;
			if( r < tauxMut ){
				mutation(enfant);
			}
			nouvellePopulation.push_back(enfant);
			printf("\n%d\n",nouvellePopulation.size());
		}
		printf("\npop gen %d \n",gen);
			for(int k = 0; k<nouvellePopulation.size(); k++){
				printf("%d ",nouvellePopulation[gen]->chemin[k]);
		}
		population = nouvellePopulation;
		
	}
	
	population = mesurerAdaptation(population, villes);
	
	Individu* meilleurIndividu = population[0];
	for(int i=0; i<population.size(); i++){
		Individu* individu = population[i];
		if(individu->coutChemin < meilleurIndividu->coutChemin){
			meilleurIndividu = population[i];
		}
	}
	
	return meilleurIndividu;
}
