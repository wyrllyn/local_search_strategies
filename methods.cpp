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

// used in max expand
int betterSols(int** D, int ** F, vector<int> sol, vector<pair<int,int>> possibilities, int64_t comparative_cost) {
	int64_t solCost = calculate_cost(D,F,sol);
	//int64_t tmpcost;
	int64_t secondcost = solCost;
	int nb = 0;
	for (int i = 0; i < possibilities.size(); i++) {
	//	tmpcost = comparative_cost;

		secondcost = solCost;

		secondcost -= updateCost(D,F,sol, possibilities[i].first,possibilities[i].second );

		iter_swap(sol.begin() + possibilities[i].first, sol.begin() + possibilities[i].second);

		secondcost += updateCost(D,F,sol, possibilities[i].first,possibilities[i].second );

		//tmpcost = calculate_cost(D,F,sol);

		if (secondcost < comparative_cost) nb++;
		//if(secondcost != tmpcost) cout << "not ok " << endl;
		iter_swap(sol.begin() + possibilities[i].first, sol.begin() + possibilities[i].second);
	}
	return nb;
}

int indexOfMaxValue(vector<int> v) {
	int maxval = 0;
	int index = -1;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] > maxval) {
			index = i;
			maxval = v[i];
		}
	}
	return index;
}

int64_t updateCost(int **D, int** F, vector<int> sol, int ti, int tj) {
	int64_t sum = 0;
	for (int i = 0; i < sol.size(); i++) {
		sum += D[i][ti]*F[sol[i]][sol[ti]];
		sum += D[i][tj]*F[sol[i]][sol[tj]];
		if (ti != i) sum += D[ti][i]*F[sol[ti]][sol[i]];
		if (tj != i) sum += D[tj][i]*F[sol[tj]][sol[i]];
	}
	return sum;
}