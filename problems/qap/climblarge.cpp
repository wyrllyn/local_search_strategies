#include "climblarge.h"

//int MAX_ITER = 10000;

extern vector<long> iter;


/*long large_first(int ** D, int ** F, vector<int> * sol) {

	long cost = calculate_cost(D,F,(*sol));
	long tmpcost;
	bool ok = false;
	cout << "INIT Cost = " << cost  << endl;
	vector<pair<pair<int,int>,pair<int,int> > > poss;
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
		//cout << "iteration " << cmp << " cost is = " << cost << " (large_first)"<< endl;
		while(!ok) {
			tmpcost = cost;
			index = rand() % size_for_swap;

			pair<int,int> s1 = poss[index].first;
			pair<int,int> s2 = poss[index].second;

			tmpcost -= updateCost(D,F, *sol, s1.first, s1.second);
			iter_swap((*sol).begin() + s1.first, (*sol).begin() + s1.second);
			tmpcost += updateCost(D,F, *sol, s1.first, s1.second);

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
				int tmpcost2 = tmpcost ;
				tmpcost2 -= updateCost(D,F, *sol, s2.first, s2.second);
				iter_swap((*sol).begin() + s2.first, (*sol).begin() + s2.second);
				tmpcost2 += updateCost(D,F, *sol, s2.first, s2.second);

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

	//cout << "-------- number of iterations (ls_first) = " << cmp << endl;
	return cost;
}*/

long large_first(int ** D, int ** F, vector<int> * sol) {
	long cost = calculate_cost(D,F,(*sol));
	int cmp = 0;

	vector<pair<int,int> > poss1;
	vector<pair<int,int> > poss2;
	for (int i = 0; i < (*sol).size() - 1; i++) {
		for (int j = i + 1; j < (*sol).size(); j++) {
			if (i != j) {
				poss1.push_back(make_pair(i,j));
				poss2.push_back(make_pair(i,j));
			}
		}
	}

	vector<pair <pair <int,int>, pair<int,int> > > swaps;

	while(true) {
		swaps.clear();
		iter.push_back(cost);
		cout << cmp << " : cost = " << cost << endl;
		long tmpcost = cost;

		for (int i = 0; i < poss1.size(); i++) {
			iter_swap((*sol).begin() + poss1[i].first, (*sol).begin() + poss1[i].second);
			tmpcost = calculate_cost(D,F,(*sol));
			if (tmpcost < cost) {
				swaps.push_back(make_pair(poss1[i], poss1[i]));
			}	

			for (int j = 0; j < poss2.size(); j++) {

				int tmpcost2 = tmpcost;

				iter_swap((*sol).begin() + poss2[j].first, (*sol).begin() + poss2[j].second);
				tmpcost2 = calculate_cost(D,F,(*sol));

				iter_swap((*sol).begin() + poss2[j].first, (*sol).begin() + poss2[j].second);

				if (tmpcost2 < cost) {
					swaps.push_back(make_pair(poss1[i], poss2[j]));
				}
			}
			iter_swap((*sol).begin() + poss1[i].first, (*sol).begin() + poss1[i].second);

		}
		if (swaps.size() == 0) break;
		int ind = rand() % swaps.size();

		iter_swap((*sol).begin() + swaps[ind].first.first, (*sol).begin() + swaps[ind].first.second);
		if (swaps[ind].first != swaps[ind].second) {
			//cout << "2 moves  : " << swaps[ind].first.first << " , " << swaps[ind].first.second << " and "  << swaps[ind].second.first << " , "  <<  swaps[ind].second.second << endl;
			iter_swap((*sol).begin() + swaps[ind].second.first, (*sol).begin() + swaps[ind].second.second);
		}
		else {
			//cout << "1 move" << endl;
		}

		cost = calculate_cost(D,F,(*sol));
		cmp++;
	}

	//cout << "final cost = " << cost << endl;
	return cost;
}

long large_best(int** D, int ** F, vector<int> * sol) {
	long cost = calculate_cost(D,F,(*sol));

	bool modif;

	int cmp = 0;
	//pair<int,int> tmp_pair = make_pair(0,0);

	vector<pair<int,int> > possibilities;
	for (int i = 0; i < (*sol).size() - 1; i++) {
		for (int j = i + 1; j < (*sol).size(); j++) {
			if (i != j) {
				possibilities.push_back(make_pair(i,j));
			}
		}
	}

	vector<pair<int,int> > best_its;

	while(true) {
		iter.push_back(cost);
		cout << "iteration " << cmp << " cost is = " << cost << " (large_best)"<< endl;
		int best_it = -1;
		long bestcost = cost;
		long tmpcost;
		long tmpcost2;
		//long newCost = cost;
		best_its.clear();
		best_its.push_back(make_pair(-1,-1));

		for (int i = 0; i < possibilities.size(); i++) {
				tmpcost = cost;	
				iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
				tmpcost = calculate_cost(D,F,(*sol));

				if (tmpcost == bestcost && tmpcost < cost) {
					best_its.push_back(make_pair(i,-1));
				}

				else if (tmpcost < bestcost) {
					best_its.clear();
					bestcost = tmpcost;
				//	newCost = tmpcost;
					best_its.push_back(make_pair(i,-1));
				}

				for (int j = 0; j < possibilities.size(); j++) {
					if (i != j) {
						tmpcost2 = tmpcost;

						iter_swap((*sol).begin() + possibilities[j].first, (*sol).begin() + possibilities[j].second);
						tmpcost2 = calculate_cost(D,F,(*sol));

						if (tmpcost2 < bestcost) {
							best_its.clear();
							bestcost = tmpcost2;
							best_its.push_back(make_pair(i,j));
						}
						else if (tmpcost2 == bestcost && tmpcost2 < cost) {
							best_its.push_back(make_pair(i,j));
						}

						iter_swap((*sol).begin() + possibilities[j].first, (*sol).begin() + possibilities[j].second);
					}
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

	//	cout << "------" << best_its[0].first  << " " << best_its[0].second << endl;

		iter_swap((*sol).begin() + possibilities[best_its[0].first].first, (*sol).begin() + possibilities[best_its[0].first].second);
		if (best_its[0].second != -1) {
			iter_swap((*sol).begin() + possibilities[best_its[0].second].first, (*sol).begin() + possibilities[best_its[0].second].second);
		//	cout << "----------- 2moves" << endl;
		}
		cost = calculate_cost(D,F,(*sol)) ;
		//cout << cost << " vs " << bestcost << endl;
		cmp++;
		// used when cycles...
	//	if (cmp > MAX_ITER) break;
	}
	//cout << "-------- number of iterations (large_best) = " << cmp << endl;

	return cost;
}


long large_worst(int** D, int ** F, vector<int> * sol) {
	long cost = calculate_cost(D,F,(*sol));

	bool modif;

	int cmp = 0;
//	pair<int,int> tmp_pair = make_pair(0,0);

	vector<pair<int,int> > possibilities;
	for (int i = 0; i < (*sol).size() - 1; i++) {
		for (int j = i + 1; j < (*sol).size(); j++) {
			if (i != j) {
				possibilities.push_back(make_pair(i,j));
			}
		}
	}

	vector<pair<int,int> > w_its;

	while(true) {
		iter.push_back(cost);
		cout << "iteration " << cmp << " cost is = " << cost << " (large_worst)"<< endl;
		//if (cost != calculate_cost(D,F,(*sol)) ) break;
		int best_it = -1;
		long bestcost = -1;
		long tmpcost;
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

				if(indCheck != -1 && indCheck != i) {
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
			//cout << "----- 2 moves" << endl;
			iter_swap((*sol).begin() + possibilities[w_its[0].second].first, (*sol).begin() + possibilities[w_its[0].second].second);
			//cout << "---- swaps " << possibilities[w_its[0].first].first << "  " << possibilities[w_its[0].first].second << " and " << possibilities[w_its[0].second].first << " " << possibilities[w_its[0].second].second << endl;
		}
		cost = calculate_cost(D,F,(*sol));
		cmp++;
		// used when cycles...
	//	if (cmp > MAX_ITER) break;
	}
	//cout << "-------- number of iterations (large_worst) = " << cmp << endl;

	return cost;
}