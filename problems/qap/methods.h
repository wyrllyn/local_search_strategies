#ifndef METHODS_H
#define METHODS_H

#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

void init_sol(vector<int> * sol, int n);

long calculate_cost(int ** D, int ** F, vector<int> sol);

bool isIntoVect(vector<int> v, int val);

int betterSols(int** D, int ** F, vector<int> sol, vector<pair<int,int> > possibilities, long comparative_cost);
int betterSols_neutral(int** D, int ** F, vector<int> sol, vector<pair<int,int> > possibilities, long comparative_cost);

int ran(vector<long> v, long c) ;

//returns index
int checkBetter(int** D, int ** F, vector<int> sol, vector<pair<int,int> > possibilities, long * bestCost, long currentCost, long xcost,  bool * modif);

int checkBetter2(int** D, int ** F, vector<int> sol, vector<pair<int,int> > possibilities, long * bestCost, long currentCost, long xcost, bool * modif);

int checkWorst(int** D, int ** F, vector<int> sol, vector<pair<int,int> > possibilities, long * bestCost, long currentCost, long xcost, bool * modif);

int checkWorst2(int** D, int ** F, vector<int> sol, vector<pair<int,int> > possibilities, long * bestCost, long currentCost, long xcost,  bool * modif);

int indexOfMaxValue(vector<int> v);

int indexOfMaxValue2(vector<int> v);

long updateCost(int **D, int** F, vector<int> sol, int ti, int tj);

#endif