#include "climblarge.h"

//int MAX_ITER = 10000;

extern vector<int64_t> iter;


int64_t large_first(int ** D, int ** F, vector<int> * sol) {

	int64_t cost = calculate_cost(D,F,(*sol));
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
		iter.push_back(cost);
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

			if(s1.first == s2.first && s1.second == s2.second) {
				if(tmpcost < cost) {
					cost = tmpcost;
					ok = true;
					//cout << "------------ 1 move" << endl;
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
					cost = tmpcost2;
					//cout << "------------ 2 moves" << endl;
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

int64_t large_best(int** D, int ** F, vector<int> * sol) {
	int64_t cost = calculate_cost(D,F,(*sol));

	bool modif;

	int cmp = 0;
	//pair<int,int> tmp_pair = make_pair(0,0);

	vector<pair<int,int>> possibilities;
	for (int i = 0; i < (*sol).size() - 1; i++) {
		for (int j = i + 1; j < (*sol).size(); j++) {
			if (i != j) {
				possibilities.push_back(make_pair(i,j));
			}
		}
	}

	vector<pair<int,int>> best_its;

	while(true) {
		iter.push_back(cost);
		cout << "iteration " << cmp << " cost is = " << cost << " (large_best)"<< endl;
		int best_it = -1;
		int64_t bestcost = cost;
		int64_t tmpcost;
		//int64_t newCost = cost;
		best_its.clear();
		best_its.push_back(make_pair(-1,-1));
		for (int i = 0; i < possibilities.size(); i++) {

			// init into loop
			//if (tmp_pair != possibilities[i]) {
				tmpcost = cost;				
				// check neigh
				iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
				tmpcost = calculate_cost(D,F,(*sol));

				if (tmpcost == bestcost && tmpcost < cost) {
					best_its.push_back(make_pair(i,-1));
				//	newCost = tmpcost;
				}

				if (tmpcost < bestcost) {
					best_its.clear();
					bestcost = tmpcost;
				//	newCost = tmpcost;
					best_its.push_back(make_pair(i,-1));
				}

				modif = false;
				int indCheck = checkBetter2(D, F, (*sol), possibilities, &bestcost, tmpcost, cost, &modif);


				if(indCheck != -1) {
					//cout << i << " and " << indCheck << endl;
					if (modif) {
					//	cout << "---- modif" << endl;
						best_its.clear();						
					}
					best_its.push_back(make_pair(i, indCheck));
				//	newCost = tmpcost;
				}
				//restore
				iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
			//}			
		}

		for (int i = 0; i < best_its.size() ; i++) {
			int randInd = rand() % best_its.size();
			best_its[0].first = best_its[randInd].first;
			best_its[0].second = best_its[randInd].second;
		}

		//tmp_pair = make_pair(possibilities[best_its[0]].first, possibilities[best_its[0]].second);
		//apply best move
		if (best_its[0].first == -1) {
			break;
		}

		iter_swap((*sol).begin() + possibilities[best_its[0].first].first, (*sol).begin() + possibilities[best_its[0].first].second);
		if (best_its[0].second != -1) {
			iter_swap((*sol).begin() + possibilities[best_its[0].second].first, (*sol).begin() + possibilities[best_its[0].second].second);
			cout << "----------- 2moves" << endl;
		}
		cost = calculate_cost(D,F,(*sol)) ;
		cmp++;
		// used when cycles...
	//	if (cmp > MAX_ITER) break;
	}
	cout << "-------- number of iterations (large_best) = " << cmp << endl;

	return cost;
}


int64_t large_worst(int** D, int ** F, vector<int> * sol) {
	int64_t cost = calculate_cost(D,F,(*sol));

	bool modif;

	int cmp = 0;
//	pair<int,int> tmp_pair = make_pair(0,0);

	vector<pair<int,int>> possibilities;
	for (int i = 0; i < (*sol).size() - 1; i++) {
		for (int j = i + 1; j < (*sol).size(); j++) {
			if (i != j) {
				possibilities.push_back(make_pair(i,j));
			}
		}
	}

	vector<pair<int,int>> w_its;

	while(true) {
		iter.push_back(cost);
		cout << "iteration " << cmp << " cost is = " << cost << " (large_worst)"<< endl;
		if (cost != calculate_cost(D,F,(*sol)) ) break;
		int best_it = -1;
		int64_t bestcost = -1;
		int64_t tmpcost;
		w_its.clear();
		w_its.push_back(make_pair(-1,-1));

		for (int i = 0; i < possibilities.size(); i++) {

			// init into loop
		//	if (tmp_pair != possibilities[i]) {
				tmpcost = cost;
				
				// check neigh
				iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
				tmpcost = calculate_cost(D,F,(*sol));

				if (tmpcost == bestcost && tmpcost < cost) {
					w_its.push_back(make_pair(i,-1));
				}
				else if (tmpcost > bestcost && tmpcost < cost) {
					w_its.clear();
					bestcost = tmpcost;
					w_its.push_back(make_pair(i,-1));
				}

				modif = false;
				int indCheck = checkWorst2(D, F, (*sol), possibilities, &bestcost, tmpcost, cost, &modif);

				if(indCheck != -1) {
					if (modif) {
						w_its.clear();
					}
					w_its.push_back(make_pair(i, indCheck));
				}
				//restore
				iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
		//	}			
		}

		for (int i = 0; i < w_its.size() ; i++) {
			int randInd = rand() % w_its.size();
			w_its[0].first = w_its[randInd].first;
			w_its[0].second = w_its[randInd].second;
		}

		//tmp_pair = make_pair(possibilities[w_its[0]].first, possibilities[w_its[0]].second);
		//apply best move
		if (w_its[0].first == -1) {
			break;
		}

		iter_swap((*sol).begin() + possibilities[w_its[0].first].first, (*sol).begin() + possibilities[w_its[0].first].second);
		if (w_its[0].second != -1) {
			cout << "----- 2 moves" << endl;
			iter_swap((*sol).begin() + possibilities[w_its[0].second].first, (*sol).begin() + possibilities[w_its[0].second].second);
		}
		cost = calculate_cost(D,F,(*sol));
		cmp++;
		// used when cycles...
	//	if (cmp > MAX_ITER) break;
	}
	cout << "-------- number of iterations (large_worst) = " << cmp << endl;

	return cost;
}