#include "ls.h"

// local search with first
int64_t ls_first(int ** D, int ** F, vector<int> * sol) {
	int64_t cost = calculate_cost(D,F,(*sol));
	int64_t tmpcost;
	bool ok = false;
	cout << "INIT Cost = " << cost  << endl;

	//vector pair for each swap possibilities + size of reachable 
	// size for swap = size of the vector
	vector<pair<int,int>> possibilities;
	for (int i = 0; i < (*sol).size() - 1; i++) {
		for (int j = i + 1; j < (*sol).size(); j++) {
			if (i != j)	possibilities.push_back(make_pair(i,j));
		}
	}

	int size_for_swap = possibilities.size();
	int cmp = 0;
	while(true) {
		int index;
		ok = false;
		while(!ok) {
			index = rand() % size_for_swap;
			iter_swap((*sol).begin() + possibilities[index].first, (*sol).begin() + possibilities[index].second);

			tmpcost = calculate_cost(D,F,(*sol));
			if(tmpcost < cost) {
				cost = tmpcost;
				ok = true;
			}
			else {
				iter_swap((*sol).begin() + possibilities[index].first, (*sol).begin() + possibilities[index].second);
				pair<int,int> tmp_pair = make_pair(possibilities[index].first, possibilities[index].second);
				possibilities.erase(possibilities.begin()+index);
				possibilities.push_back(tmp_pair);
				size_for_swap--;
			}			
			if(size_for_swap == 0) break;
		}

		if(size_for_swap == 0) break;
		size_for_swap = possibilities.size();
		cmp++;
	}

	cout << "-------- number of iterations (ls_first) = " << cmp << endl;
	return cost;
}

int64_t climber_best(int** D, int ** F, vector<int> * sol) {
	int64_t cost = calculate_cost(D,F,(*sol));

	int cmp = 0;
	pair<int,int> tmp_pair = make_pair(0,0);

	vector<pair<int,int>> possibilities;
	for (int i = 0; i < (*sol).size() - 1; i++) {
		for (int j = i + 1; j < (*sol).size(); j++) {
			if (i != j) {
				possibilities.push_back(make_pair(i,j));
			}
		}
	}

	while(true) {
		int best_it = -1;
		int bestcost = cost;
		int64_t tmpcost;
	//	cout << cost << endl;
		for (int i = 0; i < possibilities.size(); i++) {
			tmpcost = cost;
			tmpcost -= updateCost(D,F,(*sol), possibilities[i].first,possibilities[i].second );
			iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
			tmpcost += updateCost(D,F,(*sol), possibilities[i].first,possibilities[i].second );
			if (tmpcost < bestcost) {
				bestcost = tmpcost;
				best_it = i;
			}
			iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
		}
		if (best_it == -1) break;
		iter_swap((*sol).begin() + possibilities[best_it].first, (*sol).begin() + possibilities[best_it].second);
		cost = bestcost;
		cmp++;
		// used when cycles...
	//	if (cmp > 1500) break;
	}
	cout << "-------- number of iterations (climber_best) = " << cmp << endl;

	return cost;
}

int64_t climber_worst(int** D, int ** F, vector<int> * sol) {
	int64_t cost = calculate_cost(D,F,(*sol));

	int cmp = 0;
	pair<int,int> tmp_pair = make_pair(0,0);

	vector<pair<int,int>> possibilities;
	for (int i = 0; i < (*sol).size() - 1; i++) {
		for (int j = i + 1; j < (*sol).size(); j++) {
			if (i != j) {
				possibilities.push_back(make_pair(i,j));
			}
		}
	}

	while(true) {
		int best_it = -1;
		int wcost = -1;
		int64_t tmpcost;
		//cout << cmp << " : cost = " << cost << endl;
		for (int i = 0; i < possibilities.size(); i++) {
			tmpcost = cost;
			tmpcost -= updateCost(D,F,(*sol), possibilities[i].first,possibilities[i].second );
			iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
			tmpcost += updateCost(D,F,(*sol), possibilities[i].first,possibilities[i].second );
			if (tmpcost > wcost && tmpcost < cost) {
			//	cout << "-------- wcost = " << wcost << " tmpcost = " << tmpcost << " cost = " << cost << endl;
				wcost = tmpcost;
				best_it = i;
			}
			iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
		}
		if (best_it == -1) break;
		iter_swap((*sol).begin() + possibilities[best_it].first, (*sol).begin() + possibilities[best_it].second);
		cost = wcost;
		cmp++;
		// used when cycles...
	//	if (cmp > 1500) break;
	}
	cout << "-------- number of iterations (climber_worst) = " << cmp << endl;

	return cost;
}

//local search with max expand, with random
// accepts some deteriorations 
int64_t ls_ME_climber(int** D, int ** F, vector<int> * sol) {
	int64_t cost = calculate_cost(D,F,(*sol));

	int cmp = 0;
	pair<int,int> tmp_pair = make_pair(0,0);

	vector<pair<int,int>> possibilities;
	vector<int> better;
	for (int i = 0; i < (*sol).size() - 1; i++) {
		for (int j = i + 1; j < (*sol).size(); j++) {
			if (i != j) {
				possibilities.push_back(make_pair(i,j));
				better.push_back(0);
			}
		}
	}

	while(true) {
		cout << "iteration " << cmp << " cost is = " << cost  << " (ME climber)"<< endl;
		for (int i = 0; i < possibilities.size(); i++) {
			int64_t tmpcost = cost;
			tmpcost -= updateCost(D,F,(*sol), possibilities[i].first,possibilities[i].second ); 
			iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
			tmpcost += updateCost(D,F,(*sol), possibilities[i].first,possibilities[i].second );

			if (tmpcost < cost) better[i] = betterSols(D, F, (*sol),possibilities, tmpcost);
			else better[i] = 0;
			iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
		}
		int index = indexOfMaxValue2(better);
		tmp_pair = make_pair(possibilities[index].first, possibilities[index].second);
		// end of LS
		if (index == -1) break;
		cost -= updateCost(D, F, (*sol), possibilities[index].first, possibilities[index].second);
		iter_swap((*sol).begin() + possibilities[index].first, (*sol).begin() + possibilities[index].second);
		cost += updateCost(D, F, (*sol), possibilities[index].first, possibilities[index].second);
		cmp++;
		// used when cycles...
		//if (cmp > 1500) break;
	}
	cout << "-------- number of iterations = " << cmp << endl;

	return cost;
}

int64_t ls_ME_large(int** D, int ** F, vector<int> * sol) {
	int64_t cost = calculate_cost(D,F,(*sol));

	int cmp = 0;
	pair<int,int> tmp_pair = make_pair(0,0);

	vector<pair<int,int>> possibilities;
	vector<int> better;
	for (int i = 0; i < (*sol).size() - 1; i++) {
		for (int j = i + 1; j < (*sol).size(); j++) {
			if (i != j) {
				possibilities.push_back(make_pair(i,j));
				better.push_back(0);
			}
		}
	}

	while(true) {
		cout << "iteration " << cmp << " cost is = " << cost << " (ME large)"<< endl;
		for (int i = 0; i < possibilities.size(); i++) {
			if (tmp_pair != possibilities[i]) {
				iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
				better[i] = betterSols(D, F, (*sol),possibilities, cost);
				iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
			}
			else {
				better[i] = 0;
			}
		}
		int index = indexOfMaxValue2(better);
		tmp_pair = make_pair(possibilities[index].first, possibilities[index].second);
		// end of LS
		if (index == -1) {
			cout << "----------------- END" << endl;
			int best_it = -1;
			int bestcost = cost;
			int64_t tmpcost;
			for (int i = 0; i < possibilities.size(); i++) {
				tmpcost = cost;
				tmpcost -= updateCost(D,F,(*sol), possibilities[i].first,possibilities[i].second );
				iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
				tmpcost += updateCost(D,F,(*sol), possibilities[i].first,possibilities[i].second );
				if (tmpcost < bestcost) {
					bestcost = tmpcost;
					best_it = i;
				}
				iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
			}
			if (best_it != -1) iter_swap((*sol).begin() + possibilities[best_it].first, (*sol).begin() + possibilities[best_it].second);
			cost = bestcost;
			break;
		}
		cost -= updateCost(D, F, (*sol), possibilities[index].first, possibilities[index].second);
		iter_swap((*sol).begin() + possibilities[index].first, (*sol).begin() + possibilities[index].second);
		cost += updateCost(D, F, (*sol), possibilities[index].first, possibilities[index].second);
		cmp++;
		// used when cycles...
		if (cmp > 1500) break;
	}
	cout << "-------- number of iterations = " << cmp << endl;

	return cost;
}

/*
//local search with max expand, without random 
int64_t ls_ME(int** D, int ** F, vector<int> * sol) {
	int64_t cost = calculate_cost(D,F,(*sol));

	int cmp = 0;
	pair<int,int> tmp_pair = make_pair(0,0);

	vector<pair<int,int>> possibilities;
	vector<int> better;
	for (int i = 0; i < (*sol).size() - 1; i++) {
		for (int j = i + 1; j < (*sol).size(); j++) {
			if (i != j) {
				possibilities.push_back(make_pair(i,j));
				better.push_back(0);
			}
		}
	}

	while(true) {
		cout << cmp << endl;
		cout << "cost is = " << cost << endl;
		for (int i = 0; i < possibilities.size(); i++) {
			if (tmp_pair != possibilities[i]) {
				iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
				better[i] = betterSols(D, F, (*sol),possibilities, cost);
				iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
			}
			else {
				better[i] = 0;
			}
		}
		int index = indexOfMaxValue(better);
		tmp_pair = make_pair(possibilities[index].first, possibilities[index].second);
		if (index == -1) break;
		cost -= updateCost(D, F, (*sol), possibilities[index].first, possibilities[index].second);
		iter_swap((*sol).begin() + possibilities[index].first, (*sol).begin() + possibilities[index].second);
		cost += updateCost(D, F, (*sol), possibilities[index].first, possibilities[index].second);
		cmp++;
	}
	cout << "-------- number of iterations = " << cmp << endl;

	return cost;
}

*/