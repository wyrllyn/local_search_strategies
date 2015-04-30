#include "ls.h"

int MAX_ITER = 100000;

extern vector<long> iter;


long ls_first(int ** D, int ** F, vector<int> * sol) {
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

	vector<pair<int,int> > swaps;
	vector<long> fcosts;

	long ref_cost = cost;


	while(true) {
		iter.push_back(cost);

		if (fcosts.size() < 5) fcosts.push_back(cost);
		else {
			//remove first
			fcosts.erase(fcosts.begin());
			fcosts.push_back(cost);
		}

		long max = fcosts[0];
		for (int i = 1; i < fcosts.size(); i++) {
			if (fcosts[i] > max) max = fcosts[i];
		}
	//	cout << "iteration " << cmp << " cost is = " << cost << " (large_first)"<< endl;
		if (cost < ref_cost) ref_cost = cost;
		swaps.clear();

		long tmpcost = cost;
		for (int i = 0; i < poss1.size(); i++) {

			iter_swap((*sol).begin() + poss1[i].first, (*sol).begin() + poss1[i].second);
			tmpcost = calculate_cost(D,F,(*sol));

			if (tmpcost < max) {
				//cout << "##################### tmp and max " << tmpcost << "inf " << max << endl;
			
			//	if (tmpcost < ref_cost) swaps.push_back(poss1[i]);
				if (tmpcost < cost) swaps.push_back(poss1[i]);

				for (int j = 0; j < poss2.size(); j++) {
					long tmpcost2;
					iter_swap((*sol).begin() + poss2[j].first, (*sol).begin() + poss2[j].second);
					tmpcost2 = calculate_cost(D,F,(*sol));

					iter_swap((*sol).begin() + poss2[j].first, (*sol).begin() + poss2[j].second);

					//if (tmpcost2 < ref_cost) {
					if (tmpcost2 < cost) {
						//add
						swaps.push_back(poss1[i]);
						break;
					}
				}
			}

			iter_swap((*sol).begin() + poss1[i].first, (*sol).begin() + poss1[i].second);
		}

		if (swaps.size() == 0) break;
		int ind = rand() % swaps.size();

		iter_swap((*sol).begin() + swaps[ind].first, (*sol).begin() + swaps[ind].second );

		cost = calculate_cost(D,F,(*sol));
		cmp++;
	}

//	cout << "final cost = " << cost << endl;
	return cost;
}

long ls_ME(int** D, int ** F, vector<int> * sol) {
	long cost = calculate_cost(D,F,(*sol));
	long ref_cost = cost;

	int cmp = 0;
	pair<int,int> tmp_pair = make_pair(0,0);

	vector<pair<int,int> > possibilities;
	vector<int> better;
	for (int i = 0; i < (*sol).size() - 1; i++) {
		for (int j = i + 1; j < (*sol).size(); j++) {
			if (i != j) {
				possibilities.push_back(make_pair(i,j));
				better.push_back(0);
			}
		}
	}

	vector<long> fcosts;

	while(true) {
		iter.push_back(cost);
		if (fcosts.size() < 5) fcosts.push_back(cost);
		else {
			//remove first
			fcosts.erase(fcosts.begin());
			fcosts.push_back(cost);
		}


		long max = fcosts[0];
		for (int i = 1; i < fcosts.size(); i++) {
			if (fcosts[i] > max) max = fcosts[i];
		}

		cout << "iteration " << cmp << " cost is = " << cost << " (ME large)"<< endl;
	//	cout << "---- max " << max << endl;
		if (cost < ref_cost) ref_cost = cost;
		//cout << "---- ref_cost = " << ref_cost << endl;
		for (int i = 0; i < possibilities.size(); i++) {
			if (tmp_pair != possibilities[i]) {
				iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
				int tmpc = calculate_cost(D,F,(*sol));
				if (tmpc > max) {
					better[i] = 0;
				//	cout << " too much" << tmpc << "   " << max << " c = " << cost << endl;
				}
				else {
					better[i] = betterSols(D, F, (*sol),possibilities, cost);
					//cout << "yay " << tmpc <<"   " << max << " c = " << cost << endl;
				//	cout << "----b " << better[i] << endl;
				}
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
			long tmpcost;
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
			iter.push_back(cost);
			break;
		}

		iter_swap((*sol).begin() + possibilities[index].first, (*sol).begin() + possibilities[index].second);
		cost = calculate_cost(D,F,(*sol));
		cmp++;
		//if (cmp > MAX_ITER) break;
	}
	//cout << "-------- number of iterations = " << cmp << endl;

	return cost;
}

long ls_ME2(int** D, int ** F, vector<int> * sol) {
	long cost = calculate_cost(D,F,(*sol));

	vector<long> tmprank;

	int cmp = 0;
	long ref_cost = cost;
	pair<int,int> tmp_pair = make_pair(0,0);

	vector<long> fcosts;
	vector<pair<int,int> > possibilities;
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
		if (tmprank.size() > 0) tmprank.clear();
		cout << "iteration " << cmp << " cost is = " << cost << " (ME large x')"<< endl;
		if (cost < ref_cost) ref_cost = cost;
		iter.push_back(cost);
		if (fcosts.size() < 5) fcosts.push_back(cost);
		else {
			//remove first
			fcosts.erase(fcosts.begin());
			fcosts.push_back(cost);
		}


		long max = fcosts[0];

		for (int i = 1; i < fcosts.size(); i++) {
			if (fcosts[i] > max) max = fcosts[i];
		}
		//cout << "iteration " << cmp << " cost is = " << cost << " (ME climber)"<< endl;
		for (int i = 0; i < possibilities.size(); i++) {
			long tmpcost = cost;

			iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
			tmpcost = calculate_cost(D,F,(*sol));

			if (tmpcost < max) {
				better[i] = betterSols(D, F, (*sol),possibilities, tmpcost);
				tmprank.push_back(tmpcost);
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
		pair<int,int> rn = make_pair(ran(tmprank, cost), tmprank.size());
		//cout << "-----" << rn.first << " " << rn.second << endl;
	//	vrank.push_back(rn);
		cmp++;
	}
	/////


	int best_it = -1;
	int bestcost = cost;
	long tmpcost;
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
	iter.push_back(cost);

	//cout << "-------- number of iterations = " << cmp << endl;

	return cost;
}

long ls_MEmax(int** D, int ** F, vector<int> * sol) {
	long cost = calculate_cost(D,F,(*sol));

	vector<long> tmprank;

	int cmp = 0;
	long ref_cost = cost;
	pair<int,int> tmp_pair = make_pair(0,0);

	vector<long> fcosts;
	vector<pair<int,int> > possibilities;
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
		if (tmprank.size() > 0) tmprank.clear();
		cout << "iteration " << cmp << " cost is = " << cost << " (ME large max)"<< endl;
		if (cost < ref_cost) ref_cost = cost;
		iter.push_back(cost);
		if (fcosts.size() < 5) fcosts.push_back(cost);
		else {
			//remove first
			fcosts.erase(fcosts.begin());
			fcosts.push_back(cost);
		}


		long max = fcosts[0];

		for (int i = 1; i < fcosts.size(); i++) {
			if (fcosts[i] > max) max = fcosts[i];
		}
		//cout << "iteration " << cmp << " cost is = " << cost << " (ME climber)"<< endl;
		for (int i = 0; i < possibilities.size(); i++) {
			long tmpcost = cost;

			iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
			tmpcost = calculate_cost(D,F,(*sol));

			if (tmpcost < max) {
				better[i] = betterSols(D, F, (*sol),possibilities, max);
				tmprank.push_back(tmpcost);
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
		pair<int,int> rn = make_pair(ran(tmprank, cost), tmprank.size());
		//cout << "-----" << rn.first << " " << rn.second << endl;
	//	vrank.push_back(rn);
		cmp++;
	}
	/////


	int best_it = -1;
	int bestcost = cost;
	long tmpcost;
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
	iter.push_back(cost);

	//cout << "-------- number of iterations = " << cmp << endl;

	return cost;
}

long ls_best(int** D, int ** F, vector<int> * sol) {
	long cost = calculate_cost(D,F,(*sol));
	//long ref_cost = cost;

	bool modif;

	int cmp = 0;
	pair<int,int> tmp_pair = make_pair(0,0);

	vector<pair<int,int> > possibilities;
	for (int i = 0; i < (*sol).size() - 1; i++) {
		for (int j = i + 1; j < (*sol).size(); j++) {
			if (i != j) {
				possibilities.push_back(make_pair(i,j));
			}
		}
	}

	vector<int> best_its;
	vector<long> fcosts;

	while(true) {
		iter.push_back(cost);
		cout << "iteration " << cmp << " cost is = " << cost << " (large_best)"<< endl;
	//	if (cost < ref_cost) ref_cost = cost;
		if (fcosts.size() < 5) fcosts.push_back(cost);
		else {
			//remove first
			fcosts.erase(fcosts.begin());
			fcosts.push_back(cost);
		}


		long max = fcosts[0];

		int best_it = -1;
		long bestcost = cost;
		long tmpcost;
		long newCost = cost;
		best_its.clear();
		best_its.push_back(-1);
		for (int i = 0; i < possibilities.size(); i++) {

			// init into loop
			if (tmp_pair != possibilities[i]) {
				tmpcost = cost;
				
				// check neigh
				iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
				tmpcost = calculate_cost(D,F,(*sol));
				if (tmpcost < max)
					{	//	if (tmpcost == bestcost && tmpcost < ref_cost) {
							if (tmpcost == bestcost && tmpcost < cost) {
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
						//int indCheck = checkBetter(D, F, (*sol), possibilities, &bestcost, tmpcost, ref_cost, &modif);
						int indCheck = checkBetter(D, F, (*sol), possibilities, &bestcost, tmpcost, cost, &modif);
		
						if(indCheck != -1) {
							if (modif) best_its.clear();
							best_its.push_back(i);
							newCost = tmpcost;
						}
					}
				//restore
				iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
			}			
		}

		//cout << "size = " << best_its.size() << endl;

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
	//cout << "-------- number of iterations (large_best) = " << cmp << endl;

	return cost;
}


long ls_worst(int** D, int ** F, vector<int> * sol) {
	long cost = calculate_cost(D,F,(*sol));
	//long ref_cost = cost;

	vector<long> fcosts;

	cout << "first cost = " << endl;

	bool modif;

	int cmp = 0;
	pair<int,int> tmp_pair = make_pair(0,0);

	vector<pair<int,int> > possibilities;
	for (int i = 0; i < (*sol).size() - 1; i++) {
		for (int j = i + 1; j < (*sol).size(); j++) {
			if (i != j) {
				possibilities.push_back(make_pair(i,j));
			}
		}
	}

	vector<int> best_its;

	while(true) {
		iter.push_back(cost);
		cout << "iteration " << cmp << " cost is = " << cost << " (large_worst)"<< endl;
	//	if (cost < ref_cost) ref_cost = cost;
		int best_it = -1;
		long bestcost = -1;
		long tmpcost;
		best_its.clear();
		best_its.push_back(-1);

		if (fcosts.size() < 5) fcosts.push_back(cost);
		else {
			//remove first
			fcosts.erase(fcosts.begin());
			fcosts.push_back(cost);
		}

		long max = fcosts[0];
		for (int i = 1; i < fcosts.size(); i++) {
			if (fcosts[i] > max) max = fcosts[i];
		}

		for (int i = 0; i < possibilities.size(); i++) {

			// init into loop
			if (tmp_pair != possibilities[i]) {
				tmpcost = cost;
				
				// check neigh
				iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
				tmpcost = calculate_cost(D,F,(*sol));

				if (tmpcost < max){
					
				//	if (tmpcost == bestcost && tmpcost < ref_cost) {
					if (tmpcost == bestcost && tmpcost < cost) {
						best_its.push_back(i);
					}
					//else if (tmpcost > bestcost && tmpcost < ref_cost) {
					else if (tmpcost > bestcost && tmpcost < cost) {
						best_its.clear();
						bestcost = tmpcost;
						best_its.push_back(i);
					}
	
					modif = false;
				//	int indCheck = checkWorst(D, F, (*sol), possibilities, &bestcost, tmpcost, ref_cost, &modif);
					int indCheck = checkWorst(D, F, (*sol), possibilities, &bestcost, tmpcost,cost, &modif);
	
					if(indCheck != -1) {
						if (modif)  best_its.clear();
						best_its.push_back(i);
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
		cost = calculate_cost(D,F,(*sol));
		cmp++;
		//if (cmp > MAX_ITER) break;
	}
	//cout << "-------- number of iterations (large_worst) = " << cmp << endl;

	return cost;
}
