#ifndef LS_H
#define LS_H

#include "methods.h"
#include <algorithm>   

long ls_ME(int** D, int ** F, vector<int> * sol);

long ls_best(int** D, int ** F, vector<int> * sol);

long ls_worst(int** D, int ** F, vector<int> * sol);

long ls_first(int ** D, int ** F, vector<int> * sol);



#endif