#include "climbn.h"

extern vector<long> iter;

//OK
long first(int ** D, int ** F, vector<int> * sol) {
	long cost = calculate_cost(D,F,(*sol));
	long tmpcost;
	bool ok = false;
	//cout << "INIT Cost = " << cost  << endl;

	//vector pair for each swap possibilities + size of reachable 
	// size for swap = size of the vector
	vector<pair<int,int> > possibilities;
	for (int i = 0; i < (*sol).size() - 1; i++) {
		for (int j = i + 1; j < (*sol).size(); j++) {
			if (i != j)	possibilities.push_back(make_pair(i,j));
		}
	}

	//cout << "possibilities SIZE = " << possibilities.size() << endl;

	int size_for_swap = possibilities.size();
	int cmp = 0;
	while(true) {
		int index;
		ok = false;
		iter.push_back(cost);
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

	//cout << "-------- number of iterations (ls_first) = " << cmp << endl;
	return cost;
}

// local search with best
long best(int** D, int ** F, vector<int> * sol) {
	long cost = calculate_cost(D,F,(*sol));

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
		cout << "iteration " << cmp << " cost is = " << cost << " (climber_best)"<< endl;
		int best_it = -1;
		best_its.clear();
		best_its.push_back(-1);

		long bestcost = cost;
		long tmpcost;

		for (int i = 0; i < possibilities.size(); i++) {
			//tmpcost = cost;
			iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
			tmpcost = calculate_cost(D,F,(*sol));

			if (tmpcost < bestcost) {
				bestcost = tmpcost;
				best_its.clear();
				best_its.push_back(i);
			}
			else if (tmpcost == bestcost && tmpcost < cost ) {
				best_its.push_back(i);
			}
			iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
		}

		if (best_its[0] == -1) break;

		if(best_its.size() > 1) {
			int it = rand() % best_its.size();
			best_it = best_its[it];
		}
		else best_it = best_its[0];

		iter_swap((*sol).begin() + possibilities[best_it].first, (*sol).begin() + possibilities[best_it].second);
		cost = bestcost;
		cmp++;
	}
	//cout << "-------- number of iterations (climber_best) = " << cmp << endl;

	
	return cost;
}


// local search with worst
long worst(int** D, int ** F, vector<int> * sol) {
	long cost = calculate_cost(D,F,(*sol));

	int cmp = 0;
	pair<int,int> tmp_pair = make_pair(0,0);

	vector<int> best_its;

	vector<pair<int,int> > possibilities;
	for (int i = 0; i < (*sol).size() - 1; i++) {
		for (int j = i + 1; j < (*sol).size(); j++) {
			if (i != j) {
				possibilities.push_back(make_pair(i,j));
			}
		}
	}

	while(true) {
		iter.push_back(cost);
		int best_it = -1;
		long wcost = -1;
		long tmpcost;
		best_its.clear();
		best_its.push_back(-1);
		cout << "iteration " << cmp << " cost is = " << cost << " (climber_worst)"<< endl;

		for (int i = 0; i < possibilities.size(); i++) {
			//tmpcost = cost;
			iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
			tmpcost = calculate_cost(D,F,(*sol));

			if (tmpcost > wcost && tmpcost < cost) {
				wcost = tmpcost;
				best_its.clear();
				best_its.push_back(i);
			}
			else if (tmpcost == wcost) {
				best_its.push_back(i);
			}

			iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
		}

		if (best_its[0] == -1) break;

		if(best_its.size() > 1) {
			int it = rand() % best_its.size();
			best_it = best_its[it];
		}
		else best_it = best_its[0];

		iter_swap((*sol).begin() + possibilities[best_it].first, (*sol).begin() + possibilities[best_it].second);
		cost = wcost;
		cmp++;
	}

	//cout << "-------- number of iterations (climber_worst) = " << cmp << endl;
	return cost;
}

long clone_first(int ** D, int ** F, vector<int> * sol) {
	long cost = calculate_cost(D,F,(*sol));
	long tmpcost;
	bool ok = false;
	//cout << "INIT Cost = " << cost  << endl;

	//vector pair for each swap possibilities + size of reachable 
	// size for swap = size of the vector
	vector<pair<int,int> > possibilities;
	for (int i = 0; i < (*sol).size() - 1; i++) {
		for (int j = i + 1; j < (*sol).size(); j++) {
			if (i != j)	possibilities.push_back(make_pair(i,j));
		}
	}

	//cout << "possibilities SIZE = " << possibilities.size() << endl;

	int size_for_swap = possibilities.size();
	int cmp = 0;
	while(true) {
		int index;
		ok = false;
		while(!ok) {
			long tmpcost2 = cost;
			index = rand() % size_for_swap;

			//tmpcost2 -= updateCost(D, F, *sol, possibilities[index].first, possibilities[index].second);

			iter_swap((*sol).begin() + possibilities[index].first, (*sol).begin() + possibilities[index].second);

			//tmpcost2 += updateCost(D, F, *sol, possibilities[index].first, possibilities[index].second);

			tmpcost = calculate_cost(D,F,(*sol));

			//if (tmpcost2 != tmpcost) cout << "problem with swaps : " << possibilities[index].first << " and " << possibilities[index].second << endl;
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

	//cout << "-------- number of iterations (ls_first) = " << cmp << endl;
	return cost;
}

long stoch_first(int ** D, int ** F, vector<int> * sol) {
	long cost = calculate_cost(D,F,(*sol));
	long tmpcost;
	//cout << "INIT Cost = " << cost  << endl;

	//vector pair for each swap possibilities + size of reachable 
	// size for swap = size of the vector
	vector<pair<int,int> > possibilities;
	for (int i = 0; i < (*sol).size() - 1; i++) {
		for (int j = i + 1; j < (*sol).size(); j++) {
			if (i != j)	possibilities.push_back(make_pair(i,j));
		}
	}

	//cout << "possibilities SIZE = " << possibilities.size() << endl;

	int size_for_swap = possibilities.size();
	int cmp = 0;
	pair<int,int> save;
	save.first = -1;
	save.second = -1;

	int cmp_neutral = 0;
	vector<pair<int,int> > swaps;

	while(true) {
		swaps.clear();
		int index;
		//ok = false;
		iter.push_back(cost);
		cout << "iteration " << cmp << " cost is = " << cost << " (stoch first)"<< endl;
		cout << cmp_neutral << endl;

		for (int i = 0; i < possibilities.size(); i++) {
			//if (save.first != possibilities[i].first || save.second != possibilities[i].second) {
				iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
				tmpcost = calculate_cost(D,F,(*sol));
				if (tmpcost <= cost) {
					swaps.push_back(possibilities[i]);
				}
				iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
			//}
		}
		if (swaps.size() == 0) break;
		int ind = rand() % swaps.size();

		iter_swap((*sol).begin() + swaps[ind].first, (*sol).begin() + swaps[ind].second );
		//save.first = swaps[ind].first;
		//save.second = swaps[ind].second;
		long oldcost = cost;
		cost = calculate_cost(D,F,(*sol));

		if (oldcost == cost) cmp_neutral++;
		else cmp_neutral = 0;

		if (cmp_neutral >= (*sol).size()* 100) break;


		cmp++;
	}

	//cout << "-------- number of iterations (ls_first) = " << cmp << endl;
	return cost;
}

long stoch_best(int ** D, int ** F, vector<int> * sol) {
	long cost = calculate_cost(D,F,(*sol));

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
	int cmp_neutral = 0;
	// place and cost
	vector<pair<int,long> > swaps;

	while(true) {
		iter.push_back(cost);
		swaps.clear();
		cout << "iteration " << cmp << " cost is = " << cost << " (stoch_best)"<< endl;
		int best_it = -1;
		best_its.clear();
		best_its.push_back(-1);

		long bestcost = cost;
		long tmpcost;

		for (int i = 0; i < possibilities.size(); i++) {
			//tmpcost = cost;
			iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
			tmpcost = calculate_cost(D,F,(*sol));

			if (tmpcost <= cost) {
				swaps.push_back(make_pair(i, tmpcost));
			}

			if (tmpcost < bestcost) {
				bestcost = tmpcost;
				best_its.clear();
				best_its.push_back(i);
			}
			else if (tmpcost == bestcost && tmpcost < cost ) {
				best_its.push_back(i);
			}

			iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
		}

		if (swaps.size() == 0) break;

		//////////////////////////////////////////////

		int it_swap = rand() % swaps.size();
		if (swaps[it_swap].second == cost) {
			//cout << "neutral" << endl;
			best_it = swaps[it_swap].first;

		}
		else if (best_its[0] > -1 ) {
			//cout << "best (" << bestcost << ")" << endl;
			if(best_its.size() > 1) {
			int it = rand() % best_its.size();
			best_it = best_its[it];
			}
			else best_it = best_its[0];
		}


		/////////////////////////////////////////////////

		

		iter_swap((*sol).begin() + possibilities[best_it].first, (*sol).begin() + possibilities[best_it].second);

		long oldcost = cost;
		cost = calculate_cost(D,F,(*sol));

		if (oldcost == cost) cmp_neutral++;
		else cmp_neutral = 0;
		//cout << cmp_neutral << endl;
		if (cmp_neutral >= (*sol).size()* 100) break;

		cmp++;
	}

	
	return cost;
}

long stoch_worst(int ** D, int ** F, vector<int> * sol) {
	long cost = calculate_cost(D,F,(*sol));

	int cmp = 0;
	pair<int,int> tmp_pair = make_pair(0,0);

	vector<int> best_its;

	vector<pair<int,int> > possibilities;
	for (int i = 0; i < (*sol).size() - 1; i++) {
		for (int j = i + 1; j < (*sol).size(); j++) {
			if (i != j) {
				possibilities.push_back(make_pair(i,j));
			}
		}
	}

	int cmp_neutral = 0;
	// place and cost
	vector<pair<int,long> > swaps;

	while(true) {
		swaps.clear();
		iter.push_back(cost);
		int best_it = -1;
		long wcost = -1;
		long tmpcost;
		best_its.clear();
		best_its.push_back(-1);
		cout << "iteration " << cmp << " cost is = " << cost << " (stoch_worst)"<< endl;

		for (int i = 0; i < possibilities.size(); i++) {
			//tmpcost = cost;
			iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
			tmpcost = calculate_cost(D,F,(*sol));

			if (tmpcost <= cost) {
				swaps.push_back(make_pair(i, tmpcost));
			}

			if (tmpcost > wcost && tmpcost < cost) {
				wcost = tmpcost;
				best_its.clear();
				best_its.push_back(i);
			}
			else if (tmpcost == wcost) {
				best_its.push_back(i);
			}

			iter_swap((*sol).begin() + possibilities[i].first, (*sol).begin() + possibilities[i].second);
		}

		if (swaps.size() == 0) break;

		int it_swap = rand() % swaps.size();
		if (swaps[it_swap].second == cost) {
			//cout << "neutral" << endl;
			best_it = swaps[it_swap].first;

		}
		else if (best_its[0] > -1) {
			int it = rand() % best_its.size();
			best_it = best_its[it];
		}

		long oldcost = cost;

		iter_swap((*sol).begin() + possibilities[best_it].first, (*sol).begin() + possibilities[best_it].second);
		cost = calculate_cost(D,F,(*sol));

		if (oldcost == cost) cmp_neutral++;
		else cmp_neutral = 0;
		//cout << cmp_neutral << endl;
		if (cmp_neutral >= (*sol).size()* 100) break;

		cmp++;
	}

	//cout << "-------- number of iterations (climber_worst) = " << cmp << endl;
	return cost;
}
