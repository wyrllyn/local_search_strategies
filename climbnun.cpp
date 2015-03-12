#include "climbnun.h"

int64_t nun_first(int ** D, int ** F, vector<int> * sol) {
	
	int64_t cost = calculate_cost(D,F,(*sol));
	int64_t tmpcost;
	bool ok = false;

	vector<pair<pair<int,int>,pair<int,int>>> poss;
	for (int i = 0; i < (*sol).size(); i++) {
		for( int j = i + 1; j <  (*sol).size(); j++) {
			if (i != j) {
				for(int k = 0; k < (*sol).size() ; k++ ) {
					for (int l = k+1; l < (*sol).size(); l++) {
						if(k != l) {
							poss.push_back(make_pair(make_pair(i,j), make_pair(k,l)));
						}
					}
				}
			}
		}
	}
	int size_for_swap = poss.size();
	int cmp = 0;

	while(true) {
		int index;
		ok = false;
		cout << "iteration " << cmp << " cost is = " << cost << " (large_first)"<< endl;
		while(!ok) {
			tmpcost = cost;
			index = rand() % size_for_swap;

			pair<int,int> s1 = poss[index].first;
			pair<int,int> s2 = poss[index].second;

			iter_swap((*sol).begin() + s1.first, (*sol).begin() + s1.second);
			tmpcost = calculate_cost(D,F,(*sol));

			if(tmpcost >= cost) {
				iter_swap((*sol).begin() + s1.first, (*sol).begin() + s1.second);
				poss.erase(poss.begin()+index);
				poss.push_back(make_pair(s1,s2));
				size_for_swap--;
			}
			else {
				if(s1.first == s2.first && s1.second == s2.second) {
					if(tmpcost < cost) {
						cost = tmpcost;
						ok = true;
					}
					else {
						iter_swap((*sol).begin() + s1.first, (*sol).begin() + s1.second);
						poss.erase(poss.begin()+index);
						poss.push_back(make_pair(s1,s2));
						size_for_swap--;
					}

				}
				else {
					int tmpcost2 ;
					iter_swap((*sol).begin() + s2.first, (*sol).begin() + s2.second);
					tmpcost2 = calculate_cost(D,F,(*sol));

					if (tmpcost2 < cost) {
						ok = true;
						iter_swap((*sol).begin() + s2.first, (*sol).begin() + s2.second);
						cost = tmpcost;
					}
					else {
						iter_swap((*sol).begin() + s2.first, (*sol).begin() + s2.second);
						iter_swap((*sol).begin() + s1.first, (*sol).begin() + s1.second);
						poss.erase(poss.begin()+index);
						poss.push_back(make_pair(s1,s2));
						size_for_swap--;
					}
				}

			}
			if(size_for_swap == 0) break;
		}

		if(size_for_swap == 0) break;
		size_for_swap = poss.size();
		cmp++;
	}

	cout << "-------- number of iterations (ls_first) = " << cmp << endl;
	return cost;
}



int64_t nun_best(int** D, int ** F, vector<int> * sol) {
	int64_t cost = calculate_cost(D,F,(*sol));
	bool modif;
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
	vector<int> best_its;

	while(true) {
		cout << "iteration " << cmp << " cost is = " << cost << " (large_best_no_deter)"<< endl;
		int best_it = -1;
		int64_t bestcost = cost;
		int64_t tmpcost;
		//int64_t newCost = cost;
		best_its.clear();
		best_its.push_back(-1);

		for (int i = 0; i < possibilities.size(); i++) {

			// init into loop
			if (tmp_pair != possibilities[i]) {
				tmpcost = cost;
				
				// check neigh
				iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
				tmpcost = calculate_cost(D,F,(*sol));

				// only with better neigh
				if(tmpcost < cost) {
					if (tmpcost == bestcost) {
						best_its.push_back(i);
						//newCost = tmpcost;
					}

					if (tmpcost < bestcost) {
						best_its.clear();
						bestcost = tmpcost;
						//newCost = tmpcost;
						best_its.push_back(i);
					}

					modif = false;
					int indCheck = checkBetter(D, F, (*sol), possibilities, &bestcost, tmpcost, cost, &modif);

					if(indCheck != -1) {
						// if best cost changed into checkBetter
						if (modif) {
							best_its.clear();
							best_its.push_back(i);
						}
						else if (best_its[best_its.size() -1] != i)  best_its.push_back(i);
					}
				}
				//restore
				iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
			}			
		}

		for (int i = 0; i < best_its.size() ; i++) {
			int randInd = rand() % best_its.size();
			best_its[0] = best_its[randInd];
		}

		tmp_pair = make_pair(possibilities[best_its[0]].first, possibilities[best_its[0]].second);
		//apply best move
		if (best_its[0] == -1) {
			break;
		}
		iter_swap((*sol).begin() + possibilities[best_its[0]].first, (*sol).begin() + possibilities[best_its[0]].second);
		cost = calculate_cost(D,F,(*sol)) ;
		cmp++;
	}
	cout << "-------- number of iterations (large_best) = " << cmp << endl;

	return cost;

}

int64_t nun_ME(int** D, int ** F, vector<int> * sol) {
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
		cout << "iteration " << cmp << " cost is = " << cost << " (ME climber)"<< endl;
		for (int i = 0; i < possibilities.size(); i++) {
			int64_t tmpcost = cost;

			iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
			tmpcost = calculate_cost(D,F,(*sol));

			if (tmpcost < cost) {
				better[i] = betterSols(D, F, (*sol),possibilities, tmpcost);
				// add rank
			}
			else better[i] = 0;

			iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
		}
		int index = indexOfMaxValue2(better);
		tmp_pair = make_pair(possibilities[index].first, possibilities[index].second);
		// end of LS
		if (index == -1) break;

		iter_swap((*sol).begin() + possibilities[index].first, (*sol).begin() + possibilities[index].second);
		cost = calculate_cost(D,F,(*sol));
		cmp++;
	}
	cout << "-------- number of iterations = " << cmp << endl;

	return cost;
}