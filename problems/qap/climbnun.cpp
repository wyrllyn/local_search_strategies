#include "climbnun.h"

extern vector<long> iter;
extern vector<pair<int,int> > vrank;



long nun_first(int ** D, int ** F, vector<int> * sol) {
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

	while(true) {
		swaps.clear();
		iter.push_back(cost);
		//cout << cmp << " : cost = " << cost << endl;
		long tmpcost = cost;
		for (int i = 0; i < poss1.size(); i++) {
			iter_swap((*sol).begin() + poss1[i].first, (*sol).begin() + poss1[i].second);
			tmpcost = calculate_cost(D,F,(*sol));
			if (tmpcost < cost) {
				swaps.push_back(poss1[i]);
				for (int j = 0; j < poss2.size(); j++) {

					int tmpcost2 = tmpcost;
					iter_swap((*sol).begin() + poss2[j].first, (*sol).begin() + poss2[j].second);
					tmpcost2 = calculate_cost(D,F,(*sol));

					iter_swap((*sol).begin() + poss2[j].first, (*sol).begin() + poss2[j].second);

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

	//cout << "final cost = " << cost << endl;
	return cost;
}



long nun_best(int** D, int ** F, vector<int> * sol) {
	long cost = calculate_cost(D,F,(*sol));
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
		cout << "iteration " << cmp << " cost is = " << cost << " (large_best_no_deter)"<< endl;
		int best_it = -1;
		long bestcost = cost;
		long tmpcost;
		//long newCost = cost;
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
	//cout << "-------- number of iterations (large_best) = " << cmp << endl;

	return cost;

}

long nun_ME(int** D, int ** F, vector<int> * sol) {
	long cost = calculate_cost(D,F,(*sol));

	vector<long> tmprank;

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
	while(true) {
		if (tmprank.size() > 0) tmprank.clear();
		iter.push_back(cost);
		cout << "iteration " << cmp << " cost is = " << cost << " (ME climber)"<< endl;
		for (int i = 0; i < possibilities.size(); i++) {
			long tmpcost = cost;

			iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
			tmpcost = calculate_cost(D,F,(*sol));

			if (tmpcost < cost) {
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
		vrank.push_back(rn);
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

long stoch_ME(int** D, int ** F, vector<int> * sol) {
	long cost = calculate_cost(D,F,(*sol));

	vector<long> tmprank;

	int cmp = 0;
	//pair<int,int> tmp_pair = make_pair(0,0);

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
	int cmp_neutral = 0;
	vector<pair<int,long> > swaps;

	while(true) {
		if (tmprank.size() > 0) tmprank.clear();
		swaps.clear();
		iter.push_back(cost);
		cout << "------------ iteration " << cmp << " cost is = " << cost << " (ME climber)"<< endl;
		for (int i = 0; i < possibilities.size(); i++) {
			long tmpcost = cost;

			iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
			tmpcost = calculate_cost(D,F,(*sol));

			// add neutrality
			if (tmpcost < cost) {
				better[i] = betterSols(D, F, (*sol),possibilities, tmpcost);
				tmprank.push_back(tmpcost);
			}
			else better[i] = 0;

			if (tmpcost <= cost) swaps.push_back(make_pair(i, tmpcost));
			//else better[i] = 0;

			iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
		}


		int index = indexOfMaxValue2(better);
		//tmp_pair = make_pair(possibilities[index].first, possibilities[index].second);
		
		// end of LS
		//if (index == -1) break;
		//cout << "swap size = " <<  swaps.size() << endl;

		// todo: modif
		if (swaps.size() == 0) break;


		int it_swap = rand() % swaps.size();
		//cout << "it swap = " << it_swap << endl;
		//cout << " 1 : " << index << endl;
		if (swaps[it_swap].second == cost) {
			cout << "neutral" << endl;
			index = swaps[it_swap].first;

		}
		else if (index == -1) {
			//cout << "other" << endl;
			//index = indexOfMaxValue2(better);
			index = swaps[it_swap].first;
		}
		//if (index == -1) break;
	//	cout << "swap size = " <<  swaps.size() << endl;
	//	if (index == -1) break;
		//cout << " 2 : " << index << endl;
	/*	else if (best_its[0] > -1 ) {
			//cout << "best (" << bestcost << ")" << endl;
			if(best_its.size() > 1) {
			int it = rand() % best_its.size();
			best_it = best_its[it];
			}
			else best_it = best_its[0];
		}*/

		iter_swap((*sol).begin() + possibilities[index].first, (*sol).begin() + possibilities[index].second);
		long oldcost = cost;

		cost = calculate_cost(D,F,(*sol));
		pair<int,int> rn = make_pair(ran(tmprank, cost), tmprank.size());
		//cout << "-----" << rn.first << " " << rn.second << endl;
		vrank.push_back(rn);
		
		if (oldcost == cost) cmp_neutral++;
		else cmp_neutral = 0;
		//cout << cmp_neutral << endl;
		if (cmp_neutral >= (*sol).size()* 100) break;

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

	cout << "final cost = " << cost << endl;

	return cost;
}