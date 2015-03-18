#ifndef LS_H
#define LS_H

#include "methods.h"
#include <algorithm>   

float ls_ME(int** D, int ** F, vector<int> * sol);

float ls_best(int** D, int ** F, vector<int> * sol);

float ls_worst(int** D, int ** F, vector<int> * sol);

float ls_first(int ** D, int ** F, vector<int> * sol);



#endif