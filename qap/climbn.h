#ifndef CLIMBN_H
#define CLIMBN_H

#include "methods.h"
#include <algorithm>   

float first(int ** D, int ** F, vector<int> * sol);

float best(int** D, int ** F, vector<int> * sol);

float worst(int** D, int ** F, vector<int> * sol);

float clone_first(int ** D, int ** F, vector<int> * sol);

#endif