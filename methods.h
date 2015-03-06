#ifndef METHODS_H
#define METHODS_H

#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

void init_sol(vector<int> * sol, int n);

int64_t calculate_cost(int ** D, int ** F, vector<int> sol);

bool isIntoVect(vector<int> v, int val);

int betterSols(int** D, int ** F, vector<int> sol, vector<pair<int,int>> possibilities, int64_t comparative_cost);

int indexOfMaxValue(vector<int> v);

int indexOfMaxValue2(vector<int> v);

int64_t updateCost(int **D, int** F, vector<int> sol, int ti, int tj);

#endif