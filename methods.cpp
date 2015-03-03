#include "methods.h"

void init_sol(vector<int> *sol, int n) {
	int val = rand() % n;
	while((*sol).size() < n) {
		if(!isIntoVect((*sol),val)) 
			(*sol).push_back(val);
		else 
			val = rand() % n;
	}
}

int64_t calculate_cost(int ** D, int ** F, vector<int> sol ) {
	int64_t cost = 0;
	for (int i = 0; i < sol.size(); i++) {
		for (int j = 0; j < sol.size(); j++) {
			cost += D[i][j] * F[sol[i]][sol[j]];
		}
	}
	return cost;
}

bool isIntoVect(vector<int> v, int val) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == val) return true;
	}
	return false;
}