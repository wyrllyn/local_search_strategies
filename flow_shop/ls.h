#ifndef LS_H
#define LS_H

#include "methods.h"

long first(int ** d, int jobs, int machs, vector<int> * sol);

long best(int ** d, int jobs, int machs, vector<int> * sol);

long worst(int ** d, int jobs, int machs, vector<int> * sol);

///////////////////////////////////////////////////
long nun_first(int ** d, int jobs, int machs, vector<int> * sol);

long nun_best(int ** d, int jobs, int machs, vector<int> * sol);

long nun_me(int ** d, int jobs, int machs, vector<int> * sol);

////////////////////////////////////////////////////

long large_first(int ** d, int jobs, int machs, vector<int> * sol);

long large_best(int ** d, int jobs, int machs, vector<int> * sol);

long large_worst(int ** d, int jobs, int machs, vector<int> * sol);


#endif