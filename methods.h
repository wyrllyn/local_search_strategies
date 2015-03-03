#ifndef METHODS_H
#define METHODS_H

#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

void init_sol(vector<int> * sol, int n);

int64_t calculate_cost(int ** D, int ** F, vector<int> sol);



bool isIntoVect(vector<int> v, int val);

#endif