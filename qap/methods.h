#ifndef METHODS_H
#define METHODS_H

#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

void init_sol(vector<int> * sol, int n);

float calculate_cost(int ** D, int ** F, vector<int> sol);

bool isIntoVect(vector<int> v, int val);

int betterSols(int** D, int ** F, vector<int> sol, vector<pair<int,int> > possibilities, float comparative_cost);

int ran(vector<float> v, float c) ;

//returns index
int checkBetter(int** D, int ** F, vector<int> sol, vector<pair<int,int> > possibilities, float * bestCost, float currentCost, float xcost,  bool * modif);

int checkBetter2(int** D, int ** F, vector<int> sol, vector<pair<int,int> > possibilities, float * bestCost, float currentCost, float xcost, bool * modif);

int checkWorst(int** D, int ** F, vector<int> sol, vector<pair<int,int> > possibilities, float * bestCost, float currentCost, float xcost, bool * modif);

int checkWorst2(int** D, int ** F, vector<int> sol, vector<pair<int,int> > possibilities, float * bestCost, float currentCost, float xcost,  bool * modif);

int indexOfMaxValue(vector<int> v);

int indexOfMaxValue2(vector<int> v);

float updateCost(int **D, int** F, vector<int> sol, int ti, int tj);

#endif