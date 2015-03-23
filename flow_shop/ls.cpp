#include "ls.h"


float first(int ** d, int jobs, int machs, vector<int> * sol) {
	float cost = tft(d, jobs, machs, *sol);
	cout << "init cost = " << cost << endl;

	float tmpcost = 0;

	vector<pair<int, int> > poss;
	// i is the current location into sol, j corresponds to the new one
	for (int i = 0; i < jobs; i++) {
		for (int j = 0; j < jobs ; j++) {
			if (i!=j) poss.push_back(make_pair(i,j));
		}
	}
	int totalSize = poss.size();
	int move = 0;
	pair<int,int> tmp_pair;

	int cmp = 0;

	while(totalSize > 0) {
		cout << cmp <<" : cost = " << cost << endl;
		totalSize = poss.size();
		bool ok = false;
		while(!ok){
			move = rand() % totalSize;
			tmp_pair = poss[move];

			//move
			int toMove = (*sol)[tmp_pair.first];

			(*sol).erase((*sol).begin()+ tmp_pair.first);
			(*sol).insert((*sol).begin() + tmp_pair.second, toMove );
			tmpcost = tft(d, jobs, machs, *sol);



			//restore
			if (tmpcost >= cost) {
				//restore
				(*sol).erase((*sol).begin()+ tmp_pair.second);
				(*sol).insert((*sol).begin() + tmp_pair.first, toMove );
				poss.erase(poss.begin()+move);
				poss.push_back(tmp_pair);
				totalSize--;
			}
			else {
				cost = tmpcost;
				ok = true;
			}
			if (totalSize == 0) break;
		}
		cmp++;
	}
	cout << "final cost = " << cost << endl;
	return cost;
}

float best(int ** d, int jobs, int machs, vector<int> * sol) {
	float cost = tft(d, jobs, machs, *sol);
	cout << "init cost = " << cost << endl;

	float tmpcost = 0;
	float bestCost = 0;
	bool ok = true;
	vector<pair<int,int> > validMoves;
	int toMove;
	int cmp = 0;

	while(ok) {
		tmpcost = cost;
		bestCost = cost;
		validMoves.clear();

		cout << cmp << " : cost = " << cost << endl;

		for (int i = 0; i < jobs; i++) {
			for (int j = 0; j < jobs; j++) {
				if (i != j) {
				//	cout << i << " and " << j << " bestCost = " << bestCost << endl;
					toMove = (*sol)[i];
					(*sol).erase((*sol).begin()+i);
					(*sol).insert((*sol).begin() + j, toMove);
					tmpcost = tft(d, jobs, machs, *sol);

					if(tmpcost < bestCost) {
						bestCost = tmpcost;
						validMoves.clear();
						validMoves.push_back(make_pair(i,j));
					}
					else if (tmpcost == bestCost && bestCost < cost) {
						validMoves.push_back(make_pair(i,j));
					}

					(*sol).erase((*sol).begin()+ j);
					(*sol).insert((*sol).begin() + i, toMove );
				}
			}
		}
		if (validMoves.size() == 0) break;
		else {
			int tmp = rand() % validMoves.size();
			toMove = (*sol)[validMoves[tmp].first];
			(*sol).erase((*sol).begin()+ validMoves[tmp].first);
			(*sol).insert((*sol).begin() + validMoves[tmp].second, toMove);
			cost = bestCost;
			//apply move
		}
		cmp++;
	}


	return cost;
}