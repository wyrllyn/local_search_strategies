#include "ls.h"

int MAX_ITER = 10000;

int64_t ls_first(int ** D, int ** F, vector<int> * sol) {

	int64_t cost = calculate_cost(D,F,(*sol));
	int64_t ref_cost = cost;
	int64_t tmpcost;
	bool ok = false;
	cout << "INIT Cost = " << cost  << endl;
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
		if (cost < ref_cost) ref_cost = cost;
		cout << "---- ref_cost = " << ref_cost << endl;
		while(!ok) {
			//cout << " size .... = " << size_for_swap << endl;
			tmpcost = cost;		

			index = rand() % size_for_swap;
/////////////////
			pair<int,int> s1 = poss[index].first;
			pair<int,int> s2 = poss[index].second;

			iter_swap((*sol).begin() + s1.first, (*sol).begin() + s1.second);
			tmpcost = calculate_cost(D,F,(*sol));

			if(s1.first == s2.first && s1.second == s2.second) {
				if(tmpcost < ref_cost) {
					cout << "******************** tmpcost = " << tmpcost << endl;
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

				if (tmpcost2 < ref_cost) {
					cout << "******************** tmpcost2 = " << tmpcost2 << endl;
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
			if(size_for_swap == 0) break;
		}

		if(size_for_swap == 0) break;
		size_for_swap = poss.size();
		cmp++;
	}

	cout << "-------- number of iterations (ls_first) = " << cmp << endl;
	return cost;
}

int64_t ls_ME(int** D, int ** F, vector<int> * sol) {
	int64_t cost = calculate_cost(D,F,(*sol));
	int64_t ref_cost = cost;

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
		if (cost < ref_cost) ref_cost = cost;
		cout << "---- ref_cost = " << ref_cost << endl;
		for (int i = 0; i < possibilities.size(); i++) {
			if (tmp_pair != possibilities[i]) {
				iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
				better[i] = betterSols(D, F, (*sol),possibilities, ref_cost);
				iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
			}
			else {
				better[i] = 0;
			}
		}
		int index = indexOfMaxValue2(better);
		tmp_pair = make_pair(possibilities[index].first, possibilities[index].second);

		// end of LS : choose the best neigh
		if (index == -1) {
			int best_it = -1;
			int bestcost = cost;
			int64_t tmpcost;
			for (int i = 0; i < possibilities.size(); i++) {
				tmpcost = cost;
				iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
				tmpcost = calculate_cost(D,F,(*sol));

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

		iter_swap((*sol).begin() + possibilities[index].first, (*sol).begin() + possibilities[index].second);
		cost = calculate_cost(D,F,(*sol));
		cmp++;
	}
	cout << "-------- number of iterations = " << cmp << endl;

	return cost;
}

int64_t ls_best(int** D, int ** F, vector<int> * sol) {
	int64_t cost = calculate_cost(D,F,(*sol));
	int64_t ref_cost = cost;

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
		cout << "iteration " << cmp << " cost is = " << cost << " (large_best)"<< endl;
		if (cost < ref_cost) ref_cost = cost;

		int best_it = -1;
		int64_t bestcost = cost;
		int64_t tmpcost;
		int64_t newCost = cost;
		best_its.clear();
		best_its.push_back(-1);
		for (int i = 0; i < possibilities.size(); i++) {

			// init into loop
			if (tmp_pair != possibilities[i]) {
				tmpcost = cost;
				
				// check neigh
				iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
				tmpcost = calculate_cost(D,F,(*sol));

				if (tmpcost == bestcost && tmpcost < ref_cost) {
					best_its.push_back(i);
					newCost = tmpcost;
				}

				if (tmpcost < bestcost) {
					best_its.clear();
					bestcost = tmpcost;
					newCost = tmpcost;
					best_its.push_back(i);
				}

				modif = false;
				int indCheck = checkBetter(D, F, (*sol), possibilities, &bestcost, tmpcost, ref_cost, &modif);


				if(indCheck != -1) {
					if (modif) best_its.clear();
					best_its.push_back(i);
					newCost = tmpcost;
				}
				//restore
				iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
			}			
		}

		cout << "size = " << best_its.size() << endl;

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


int64_t ls_worst(int** D, int ** F, vector<int> * sol) {
	int64_t cost = calculate_cost(D,F,(*sol));
	int64_t ref_cost = cost;

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
		cout << "iteration " << cmp << " cost is = " << cost << " (large_worst)"<< endl;
		if (cost < ref_cost) ref_cost = cost;
		int best_it = -1;
		int64_t bestcost = -1;
		int64_t tmpcost;
		best_its.clear();
		best_its.push_back(-1);

		for (int i = 0; i < possibilities.size(); i++) {

			// init into loop
			if (tmp_pair != possibilities[i]) {
				tmpcost = cost;
				
				// check neigh
				iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
				tmpcost = calculate_cost(D,F,(*sol));

				if (tmpcost == bestcost && tmpcost < ref_cost) {
					best_its.push_back(i);
				}
				else if (tmpcost > bestcost && tmpcost < ref_cost) {
					best_its.clear();
					bestcost = tmpcost;
					best_its.push_back(i);
				}

				modif = false;
				int indCheck = checkWorst(D, F, (*sol), possibilities, &bestcost, tmpcost, ref_cost, &modif);

				if(indCheck != -1) {
					if (modif)  best_its.clear();
					best_its.push_back(i);
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
		cost = calculate_cost(D,F,(*sol));
		cmp++;
	}
	cout << "-------- number of iterations (large_worst) = " << cmp << endl;

	return cost;
}