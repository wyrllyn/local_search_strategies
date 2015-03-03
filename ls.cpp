#include "ls.h"

// local search with first
int64_t ls_first(int ** D, int ** F, vector<int> * sol) {
	int64_t cost = calculate_cost(D,F,(*sol));
	int64_t tmpcost;
	bool ok = false;
	cout << "init cost = " << cost  << endl;

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

	cout << "number of iterations = " << cmp << endl;
	return cost;
}