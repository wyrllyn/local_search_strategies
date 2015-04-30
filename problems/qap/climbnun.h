#ifndef CLIMBNUN_H
#define CLIMBNUN_H

#include "methods.h"
#include <algorithm>   


long nun_first(int ** D, int ** F, vector<int> * sol);

long nun_ME(int** D, int ** F, vector<int> * sol);

long nun_best(int** D, int ** F, vector<int> * sol);

long stoch_ME(int** D, int ** F, vector<int> * sol);

#endif