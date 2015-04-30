#ifndef CLIMBN_H
#define CLIMBN_H

#include "methods.h"
#include <algorithm>   

long first(int ** D, int ** F, vector<int> * sol);

long best(int** D, int ** F, vector<int> * sol);

long worst(int** D, int ** F, vector<int> * sol);

long clone_first(int ** D, int ** F, vector<int> * sol);

long stoch_first(int ** D, int ** F, vector<int> * sol);

long stoch_best(int ** D, int ** F, vector<int> * sol);

long stoch_worst(int ** D, int ** F, vector<int> * sol);

#endif