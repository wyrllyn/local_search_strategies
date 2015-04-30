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

///////////////////////////////////////////

long first_stoch(int ** d, int jobs, int machs, vector<int> * sol);

long best_stoch(int ** d, int jobs, int machs, vector<int> * sol);

long worst_stoch(int ** d, int jobs, int machs, vector<int> * sol);

long me_stoch(int ** d, int jobs, int machs, vector<int> * sol);


/////////////////////////////////////////////////

long ls_first(int ** d, int jobs, int machs, vector<int> * sol);

long ls_worst(int ** d, int jobs, int machs, vector<int> * sol);

long ls_best(int ** d, int jobs, int machs, vector<int> * sol);

long ls_me(int ** d, int jobs, int machs, vector<int> * sol);


#endif