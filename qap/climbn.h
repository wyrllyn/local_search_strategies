#ifndef CLIMBN_H
#define CLIMBN_H

#include "methods.h"
#include <algorithm>   

int64_t first(int ** D, int ** F, vector<int> * sol);

int64_t best(int** D, int ** F, vector<int> * sol);

int64_t worst(int** D, int ** F, vector<int> * sol);

int64_t clone_first(int ** D, int ** F, vector<int> * sol);

#endif