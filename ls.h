#ifndef LS_H
#define LS_H

#include "methods.h"
#include <algorithm>   

int64_t ls_first(int ** D, int ** F, vector<int> * sol);

int64_t climber_best(int** D, int ** F, vector<int> * sol);

int64_t climber_worst(int** D, int ** F, vector<int> * sol);

int64_t ls_ME_large(int** D, int ** F, vector<int> * sol);

int64_t ls_ME_climber(int** D, int ** F, vector<int> * sol);


//int64_t ls_ME(int** D, int ** F, vector<int> * sol);


#endif