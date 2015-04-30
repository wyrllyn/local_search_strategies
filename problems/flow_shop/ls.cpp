#include "ls.h"

extern vector<long> iter;
extern vector<long> me;
extern vector<pair<int,int> > vrank;


long first(int ** d, int jobs, int machs, vector<int> * sol) {
	long cost = costf(d, jobs, machs, *sol);
	//cout << "init cost = " << cost << endl;

	long tmpcost = 0;

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
		//cout << cmp <<" : cost = " << cost << endl;
		iter.push_back(cost);
		totalSize = poss.size();
		bool ok = false;
		while(!ok){
			move = rand() % totalSize;
			tmp_pair = poss[move];

			//move
			int toMove = (*sol)[tmp_pair.first];

			(*sol).erase((*sol).begin()+ tmp_pair.first);
			(*sol).insert((*sol).begin() + tmp_pair.second, toMove );
			tmpcost = costf(d, jobs, machs, *sol);



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
	//cout << "final cost = " << cost << endl;
	return cost;
}

long best(int ** d, int jobs, int machs, vector<int> * sol) {
	long cost =  costf(d, jobs, machs, *sol);
	//cout << "init cost = " << cost << endl;

	long tmpcost = 0;
	long bestCost = 0;
	bool ok = true;
	vector<pair<int,int> > validMoves;
	int toMove;
	int cmp = 0;

	while(ok) {
		tmpcost = cost;
		bestCost = cost;
		validMoves.clear();

		//cout << cmp << " : cost = " << cost << endl;
		iter.push_back(cost);

		for (int i = 0; i < jobs; i++) {
			for (int j = 0; j < jobs; j++) {
				if (i != j) {
				//	//cout << i << " and " << j << " bestCost = " << bestCost << endl;
					toMove = (*sol)[i];
					(*sol).erase((*sol).begin()+i);
					(*sol).insert((*sol).begin() + j, toMove);
					tmpcost = costf(d, jobs, machs, *sol); //costf(d, jobs, machs, *sol);
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

long worst(int ** d, int jobs, int machs, vector<int> * sol) {
	long cost = costf(d, jobs, machs, *sol);

	long tmpcost = 0;
	long bestCost = 0;
	bool ok = true;
	vector<pair<int,int> > validMoves;
	int toMove;
	int cmp = 0;

	while(ok) {
		tmpcost = cost;
		bestCost = -1;
		validMoves.clear();

		//cout << cmp << " : cost = " << cost << endl;
		iter.push_back(cost);

		for (int i = 0; i < jobs; i++) {
			for (int j = 0; j < jobs; j++) {
				if (i != j) {
				//	//cout << i << " and " << j << " bestCost = " << bestCost << endl;
					toMove = (*sol)[i];
					(*sol).erase((*sol).begin()+i);
					(*sol).insert((*sol).begin() + j, toMove);
					tmpcost = costf(d, jobs, machs, *sol);

					if(tmpcost > bestCost && tmpcost < cost) {
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

long nun_first(int ** d, int jobs, int machs, vector<int> * sol) {
	//cout << "nun first" << endl;
	long cost = costf(d, jobs, machs, *sol);
	//cout << "init cost = " << cost << endl;

	long tmpcost = 0;
	bool ok = true;
	vector<pair<int,int> > validMoves;
	int toMove;
	int cmp = 0;

	while(ok) {
		tmpcost = cost;
		validMoves.clear();

		//cout << cmp << " : cost = " << cost << endl;
		iter.push_back(cost);

		for (int i = 0; i < jobs; i++) {
			for (int j = 0; j < jobs; j++) {
				if (i != j) {
				//	//cout << i << " and " << j << " bestCost = " << bestCost << endl;
					toMove = (*sol)[i];
					(*sol).erase((*sol).begin()+i);
					(*sol).insert((*sol).begin() + j, toMove);
					tmpcost = costf(d, jobs, machs, *sol);

					if(tmpcost < cost) {
						validMoves.push_back(make_pair(i,j));
						// test n2
						for (int k = 0; k < jobs; k++) {
							for (int l = 0; l < jobs; l++) {
								if (k != l) {
									int toMove2 = (*sol)[k];
									(*sol).erase((*sol).begin()+k);
									(*sol).insert((*sol).begin() + l, toMove2);

									long tmpcost2 = costf(d, jobs, machs, *sol);

									if (tmpcost2 < cost) validMoves.push_back(make_pair(i,j));

									(*sol).erase((*sol).begin()+l);
									(*sol).insert((*sol).begin() + k, toMove2);
								}
							}
						}
					}

					(*sol).erase((*sol).begin()+ j);
					(*sol).insert((*sol).begin() + i, toMove );
				}
			}
		}
		if (validMoves.size() == 0) break;
		else {
			////cout << validMoves.size() << endl;
			int tmp = rand() % validMoves.size();
			toMove = (*sol)[validMoves[tmp].first];
			(*sol).erase((*sol).begin()+ validMoves[tmp].first);
			(*sol).insert((*sol).begin() + validMoves[tmp].second, toMove);
			cost = costf(d, jobs, machs, *sol);;
			//apply move
		}
		cmp++;
	}

	return cost;
}

long nun_best(int ** d, int jobs, int machs, vector<int> * sol) {
	long cost = costf(d, jobs, machs, *sol);
	//cout << "init cost = " << cost << endl;

	long tmpcost = 0;
	bool ok = true;
	vector<pair<int,int> > validMoves;
	int toMove;
	long bestCost;
	int cmp = 0;

	while(ok) {
		tmpcost = cost;
		validMoves.clear();

		//cout << cmp << " : cost = " << cost << endl;
		iter.push_back(cost);
		bestCost = cost;

		for (int i = 0; i < jobs; i++) {
			for (int j = 0; j < jobs; j++) {
				if (i != j) {
				//	//cout << i << " and " << j << " bestCost = " << bestCost << endl;
					toMove = (*sol)[i];
					(*sol).erase((*sol).begin()+i);
					(*sol).insert((*sol).begin() + j, toMove);
					tmpcost = costf(d, jobs, machs, *sol);

					if(tmpcost < cost) {
						if (tmpcost < bestCost) {
							validMoves.clear();
							bestCost = tmpcost;
							validMoves.push_back(make_pair(i,j));
						}
						else if (tmpcost == bestCost && bestCost < cost) {
							validMoves.push_back(make_pair(i,j));
						}
						// test n2
						for (int k = 0; k < jobs; k++) {
							for (int l = 0; l < jobs; l++) {
								if (k != l) {
									int toMove2 = (*sol)[k];
									(*sol).erase((*sol).begin()+k);
									(*sol).insert((*sol).begin() + l, toMove2);

									long tmpcost2 = costf(d, jobs, machs, *sol);

									if (tmpcost2 < cost && tmpcost2 == bestCost) validMoves.push_back(make_pair(i,j));
									else if (tmpcost2 < bestCost) {
										validMoves.clear();
										bestCost = tmpcost2;
										validMoves.push_back(make_pair(i,j));
									}

									(*sol).erase((*sol).begin()+l);
									(*sol).insert((*sol).begin() + k, toMove2);
								}
							}
						}
					}

					(*sol).erase((*sol).begin()+ j);
					(*sol).insert((*sol).begin() + i, toMove );
				}
			}
		}
		if (validMoves.size() == 0) break;
		else {
			////cout << validMoves.size() << endl;
			int tmp = rand() % validMoves.size();
			toMove = (*sol)[validMoves[tmp].first];
			(*sol).erase((*sol).begin()+ validMoves[tmp].first);
			(*sol).insert((*sol).begin() + validMoves[tmp].second, toMove);
			cost = costf(d, jobs, machs, *sol);;
			//apply move
		}
		cmp++;
	}

	return cost;
}

long nun_me(int ** d, int jobs, int machs, vector<int> * sol) {
	long cost = costf(d, jobs, machs, *sol);
	//cout << "init cost = " << cost << endl;

	long tmpcost = 0;
	bool ok = true;
	vector<pair<int,int> > validMoves;
	int toMove;
	int cmp = 0;

	int nb_max = 0;

	vector<long> tmprank;

	while(ok) {
		nb_max = 0;
		tmpcost = cost;
		validMoves.clear();
		tmprank.clear();

		//cout << cmp << " : cost = " << cost << endl;
		iter.push_back(cost);

		for (int i = 0; i < jobs; i++) {
			for (int j = 0; j < jobs; j++) {
				if (i != j) {
				//	//cout << i << " and " << j << " bestCost = " << bestCost << endl;
					toMove = (*sol)[i];
					(*sol).erase((*sol).begin()+i);
					(*sol).insert((*sol).begin() + j, toMove);
					tmpcost = costf(d, jobs, machs, *sol);

					
					if(tmpcost < cost) {
						tmprank.push_back(tmpcost);
						int nb = 0;
						// test n2
						for (int k = 0; k < jobs; k++) {
							for (int l = 0; l < jobs; l++) {
								if (k != l) {
									int toMove2 = (*sol)[k];
									(*sol).erase((*sol).begin()+k);
									(*sol).insert((*sol).begin() + l, toMove2);

									long tmpcost2 = costf(d, jobs, machs, *sol);

									if (tmpcost2 < tmpcost) nb++;

									(*sol).erase((*sol).begin()+l);
									(*sol).insert((*sol).begin() + k, toMove2);
								}
							}
						}
						if (nb > nb_max) {
							nb_max = nb;
							validMoves.clear();
							validMoves.push_back(make_pair(i,j));
						}
						else if (nb == nb_max && nb_max > 0) {
							validMoves.push_back(make_pair(i,j));
						}
					}

					(*sol).erase((*sol).begin()+ j);
					(*sol).insert((*sol).begin() + i, toMove );
				}
			}
		}
		if (validMoves.size() == 0) break;
		else {
			////cout << validMoves.size() << endl;
			me.push_back(nb_max);
			int tmp = rand() % validMoves.size();
			toMove = (*sol)[validMoves[tmp].first];
			(*sol).erase((*sol).begin()+ validMoves[tmp].first);
			(*sol).insert((*sol).begin() + validMoves[tmp].second, toMove);
			cost = costf(d, jobs, machs, *sol);
			

			pair<int,int> rn = make_pair(ran(tmprank, cost), tmprank.size());
			vrank.push_back(rn);
		}
		cmp++;
	}

	// return best one
	long bcost = cost;
	for (int i = 0; i < jobs; i++) {
		for (int j = 0; j < jobs; j++) {
			if (i!=j) {
				toMove = (*sol)[i];
				(*sol).erase((*sol).begin()+i);
				(*sol).insert((*sol).begin() + j, toMove);
				tmpcost = costf(d, jobs, machs, *sol);
				if (tmpcost < bcost) {
					bcost = tmpcost;
					validMoves.push_back(make_pair(i,j));
				}
				(*sol).erase((*sol).begin()+ j);
				(*sol).insert((*sol).begin() + i, toMove );

			}
		}
	}

	if (validMoves.size() > 0) {
			int tmp = rand() % validMoves.size();
			toMove = (*sol)[validMoves[tmp].first];
			(*sol).erase((*sol).begin()+ validMoves[tmp].first);
			(*sol).insert((*sol).begin() + validMoves[tmp].second, toMove);
			cost = costf(d, jobs, machs, *sol);
			iter.push_back(cost);
	}


	return cost;
}

long large_first(int ** d, int jobs, int machs, vector<int> * sol) {
	//cout << "nun first" << endl;
	long cost = costf(d, jobs, machs, *sol);
	//cout << "init cost = " << cost << endl;

	long tmpcost = 0;
	bool ok = true;
	vector<pair<pair<int,int>, pair<int,int> > > validMoves;
	int toMove;
	int cmp = 0;

	while(ok) {
		tmpcost = cost;
		validMoves.clear();

		//cout << cmp << " : cost = " << cost << endl;
		iter.push_back(cost);

		for (int i = 0; i < jobs; i++) {
			for (int j = 0; j < jobs; j++) {
				if (i != j) {
				//	//cout << i << " and " << j << " bestCost = " << bestCost << endl;
					toMove = (*sol)[i];
					(*sol).erase((*sol).begin()+i);
					(*sol).insert((*sol).begin() + j, toMove);
					tmpcost = costf(d, jobs, machs, *sol);

					if(tmpcost < cost) validMoves.push_back(make_pair(make_pair(i,j), make_pair(-1,-1)));
						
						// test n2
						for (int k = 0; k < jobs; k++) {
							for (int l = 0; l < jobs; l++) {
								if (k != l) {
									int toMove2 = (*sol)[k];
									(*sol).erase((*sol).begin()+k);
									(*sol).insert((*sol).begin() + l, toMove2);

									long tmpcost2 = costf(d, jobs, machs, *sol);

									if (tmpcost2 < cost) validMoves.push_back(make_pair(make_pair(i,j), make_pair(k,l)));

									(*sol).erase((*sol).begin()+l);
									(*sol).insert((*sol).begin() + k, toMove2);
								}
							}
						}
					

					(*sol).erase((*sol).begin()+ j);
					(*sol).insert((*sol).begin() + i, toMove );
				}
			}
		}
		if (validMoves.size() == 0) break;

		else {
			////cout << validMoves.size() << endl;
			int tmp = rand() % validMoves.size();
			toMove = (*sol)[validMoves[tmp].first.first];
			(*sol).erase((*sol).begin()+ validMoves[tmp].first.first);
			(*sol).insert((*sol).begin() + validMoves[tmp].first.second, toMove);

			if (validMoves[tmp].second.first != -1) {
				toMove = (*sol)[validMoves[tmp].second.first];
				(*sol).erase((*sol).begin()+ validMoves[tmp].second.first);
				(*sol).insert((*sol).begin() + validMoves[tmp].second.second, toMove);
			}


			cost = costf(d, jobs, machs, *sol);;
			
		}
		cmp++;
	}

	return cost;
}

long large_best(int ** d, int jobs, int machs, vector<int> * sol) {
	long cost = costf(d, jobs, machs, *sol);
	//cout << "init cost = " << cost << endl;

	long tmpcost = 0;
	bool ok = true;
	vector<pair<pair<int,int>, pair<int,int> > > validMoves;
	int toMove;
	long bestCost;
	int cmp = 0;

	while(ok) {
		tmpcost = cost;
		validMoves.clear();

		//cout << cmp << " : cost = " << cost << endl;
		iter.push_back(cost);
		bestCost = cost;

		for (int i = 0; i < jobs; i++) {
			for (int j = 0; j < jobs; j++) {
				if (i != j) {
				//	//cout << i << " and " << j << " bestCost = " << bestCost << endl;
					toMove = (*sol)[i];
					(*sol).erase((*sol).begin()+i);
					(*sol).insert((*sol).begin() + j, toMove);
					tmpcost = costf(d, jobs, machs, *sol);

				//	if(tmpcost < cost) {
					if (tmpcost < bestCost) {
						validMoves.clear();
						bestCost = tmpcost;
						validMoves.push_back(make_pair(make_pair(i,j), make_pair(-1,-1)));
					}
					else if (tmpcost == bestCost && bestCost < cost) {
						validMoves.push_back(make_pair(make_pair(i,j), make_pair(-1,-1)));
					}
					// test n2
					for (int k = 0; k < jobs; k++) {
						for (int l = 0; l < jobs; l++) {
							if (k != l) {
								int toMove2 = (*sol)[k];
								(*sol).erase((*sol).begin()+k);
								(*sol).insert((*sol).begin() + l, toMove2);

								long tmpcost2 = costf(d, jobs, machs, *sol);

								if (tmpcost2 < cost && tmpcost2 == bestCost) validMoves.push_back(make_pair(make_pair(i,j), make_pair(k,l)));
								else if (tmpcost2 < bestCost) {
									validMoves.clear();
									bestCost = tmpcost2;
									validMoves.push_back(make_pair(make_pair(i,j), make_pair(k,l)));
								}

								(*sol).erase((*sol).begin()+l);
								(*sol).insert((*sol).begin() + k, toMove2);
							}
						}
					}
					//}

					(*sol).erase((*sol).begin()+ j);
					(*sol).insert((*sol).begin() + i, toMove );
				}
			}
		}
		if (validMoves.size() == 0) break;
		else {
			////cout << validMoves.size() << endl;
			int tmp = rand() % validMoves.size();
			toMove = (*sol)[validMoves[tmp].first.first];
			(*sol).erase((*sol).begin()+ validMoves[tmp].first.first);
			(*sol).insert((*sol).begin() + validMoves[tmp].first.second, toMove);

			if (validMoves[tmp].second.first != -1) {
				toMove = (*sol)[validMoves[tmp].second.first];
				(*sol).erase((*sol).begin()+ validMoves[tmp].second.first);
				(*sol).insert((*sol).begin() + validMoves[tmp].second.second, toMove);
				////cout << "2 moves" << endl;
			}
			cost = costf(d, jobs, machs, *sol);;
			
		}
		cmp++;
	}

	return cost;
}

long large_worst(int ** d, int jobs, int machs, vector<int> * sol) {
	//cout << "nun first" << endl;
	long cost = costf(d, jobs, machs, *sol);
	//cout << "init cost = " << cost << endl;

	long tmpcost = 0;
	bool ok = true;
	vector<pair<pair<int,int>, pair<int,int> > > validMoves;
	int toMove;
	int cmp = 0;
	long wcost;

	while(ok) {
		tmpcost = cost;
		validMoves.clear();

		wcost = 0;

		//cout << cmp << " : cost = " << cost << endl;
		iter.push_back(cost);

		for (int i = 0; i < jobs; i++) {
			for (int j = 0; j < jobs; j++) {
				if (i != j) {
				//	//cout << i << " and " << j << " bestCost = " << bestCost << endl;
					toMove = (*sol)[i];
					(*sol).erase((*sol).begin()+i);
					(*sol).insert((*sol).begin() + j, toMove);
					tmpcost = costf(d, jobs, machs, *sol);

					if(tmpcost == wcost && wcost != 0) validMoves.push_back(make_pair(make_pair(i,j), make_pair(-1,-1)));
					else if (tmpcost < cost && tmpcost > wcost) {
						validMoves.clear();
						validMoves.push_back(make_pair(make_pair(i,j), make_pair(-1,-1)));
						wcost = tmpcost;
					}
						
					// test n2
					for (int k = 0; k < jobs; k++) {
						for (int l = 0; l < jobs; l++) {
							if (k != l) {
								int toMove2 = (*sol)[k];
								(*sol).erase((*sol).begin()+k);
								(*sol).insert((*sol).begin() + l, toMove2);

								long tmpcost2 = costf(d, jobs, machs, *sol);

								if (tmpcost2 == wcost && wcost != 0) validMoves.push_back(make_pair(make_pair(i,j), make_pair(k,l)));
								else if (tmpcost2 < cost && tmpcost2 > wcost) {
									validMoves.clear();
									validMoves.push_back(make_pair(make_pair(i,j), make_pair(k,l)));
									wcost = tmpcost2;
								}

								(*sol).erase((*sol).begin()+l);
								(*sol).insert((*sol).begin() + k, toMove2);
							}
						}
					}
					

					(*sol).erase((*sol).begin()+ j);
					(*sol).insert((*sol).begin() + i, toMove );
				}
			}
		}
		if (validMoves.size() == 0) break;

		else {
			////cout << validMoves.size() << endl;
			int tmp = rand() % validMoves.size();
			toMove = (*sol)[validMoves[tmp].first.first];
			(*sol).erase((*sol).begin()+ validMoves[tmp].first.first);
			(*sol).insert((*sol).begin() + validMoves[tmp].first.second, toMove);

			if (validMoves[tmp].second.first != -1) {
				toMove = (*sol)[validMoves[tmp].second.first];
				(*sol).erase((*sol).begin()+ validMoves[tmp].second.first);
				(*sol).insert((*sol).begin() + validMoves[tmp].second.second, toMove);
			}


			cost = costf(d, jobs, machs, *sol);;
			
		}
		cmp++;
	}

	return cost;
}

///////////////////////////////////////////

long first_stoch(int ** d, int jobs, int machs, vector<int> * sol) {
	long cost = costf(d, jobs, machs, *sol);
	//cout << "init cost = " << cost << endl;

	long tmpcost = 0;

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

	int neutral_cmp = 0;

	while(totalSize > 0) {
		cout << cmp <<" : cost = " << cost << endl;
		iter.push_back(cost);
		totalSize = poss.size();
		bool ok = false;
		while(!ok){
			move = rand() % totalSize;
			tmp_pair = poss[move];

			//move
			int toMove = (*sol)[tmp_pair.first];

			(*sol).erase((*sol).begin()+ tmp_pair.first);
			(*sol).insert((*sol).begin() + tmp_pair.second, toMove );
			tmpcost = costf(d, jobs, machs, *sol);



			//restore
			if (tmpcost > cost) {
				//restore
				(*sol).erase((*sol).begin()+ tmp_pair.second);
				(*sol).insert((*sol).begin() + tmp_pair.first, toMove );
				poss.erase(poss.begin()+move);
				poss.push_back(tmp_pair);
				totalSize--;
			}
			else {
				if (cost == tmpcost) neutral_cmp++;
				else neutral_cmp = 0;

				cost = tmpcost;
				ok = true;

				//cout << "neutral_cmp = " << neutral_cmp  << " under " << 100 * jobs<< endl;
				if (neutral_cmp > 100 * jobs) break;
				
			}
			//cout << "totalSize " << totalSize << endl;
			if (totalSize == 0) break;
			
		}
		if (neutral_cmp > 100 * jobs) break;
		cmp++;
	}
	cout << "final cost = " << cost << endl;
	return cost;

}

// change value of neutral_cmp
// get each <= into vect
//

long best_stoch(int ** d, int jobs, int machs, vector<int> * sol) {
	long cost =  costf(d, jobs, machs, *sol);
	//cout << "init cost = " << cost << endl;

	long tmpcost = 0;
	long bestCost = 0;
	bool ok = true;
	vector<pair<int,int> > validMoves;
	int toMove;
	int cmp = 0;

	int neutral_cmp = 0;
	vector <pair<pair<int, int>, long> > all;

	while(ok) {
		tmpcost = cost;
		bestCost = cost;
		validMoves.clear();

		cout << cmp << " : cost = " << cost << endl;
		iter.push_back(cost);
		all.clear();

		for (int i = 0; i < jobs; i++) {
			for (int j = 0; j < jobs; j++) {
				if (i != j) {
				//	//cout << i << " and " << j << " bestCost = " << bestCost << endl;
					toMove = (*sol)[i];
					(*sol).erase((*sol).begin()+i);
					(*sol).insert((*sol).begin() + j, toMove);
					tmpcost = costf(d, jobs, machs, *sol); //costf(d, jobs, machs, *sol);
					if(tmpcost < bestCost) {
						bestCost = tmpcost;
						validMoves.clear();
						validMoves.push_back(make_pair(i,j));
					}
					else if (tmpcost == bestCost && bestCost < cost) {
						validMoves.push_back(make_pair(i,j));
					}

					if (tmpcost <= cost) {
						all.push_back(make_pair(make_pair(i,j), tmpcost));
					}

					(*sol).erase((*sol).begin()+ j);
					(*sol).insert((*sol).begin() + i, toMove );
				}
			}
		}
		if (all.size() == 0) break;
		else {
			int tmp = rand() % all.size();
			if(all[tmp].second == cost) {
				toMove = (*sol)[all[tmp].first.first];
				(*sol).erase((*sol).begin()+ all[tmp].first.first);
				(*sol).insert((*sol).begin() + all[tmp].first.second, toMove);
				neutral_cmp++;
			}
			else {
				int tmp = rand() % validMoves.size();
				toMove = (*sol)[validMoves[tmp].first];
				(*sol).erase((*sol).begin()+ validMoves[tmp].first);
				(*sol).insert((*sol).begin() + validMoves[tmp].second, toMove);
				cost = bestCost;
				neutral_cmp = 0;
			}

		}
		if (neutral_cmp > 100 * jobs) break;
		cmp++;
	}


	return cost;

}

long worst_stoch(int ** d, int jobs, int machs, vector<int> * sol) {
	long cost = costf(d, jobs, machs, *sol);

	long tmpcost = 0;
	long bestCost = 0;
	bool ok = true;
	vector<pair<int,int> > validMoves;
	int toMove;
	int cmp = 0;

	int neutral_cmp = 0;
	vector <pair<pair<int, int>, long> > all;

	while(ok) {
		tmpcost = cost;
		bestCost = -1;
		validMoves.clear();

		all.clear();

		cout << cmp << " : cost = " << cost << endl;
		iter.push_back(cost);

		for (int i = 0; i < jobs; i++) {
			for (int j = 0; j < jobs; j++) {
				if (i != j) {
				//	//cout << i << " and " << j << " bestCost = " << bestCost << endl;
					toMove = (*sol)[i];
					(*sol).erase((*sol).begin()+i);
					(*sol).insert((*sol).begin() + j, toMove);
					tmpcost = costf(d, jobs, machs, *sol);

					if(tmpcost > bestCost && tmpcost < cost) {
						bestCost = tmpcost;
						validMoves.clear();
						validMoves.push_back(make_pair(i,j));
					}
					else if (tmpcost == bestCost && bestCost < cost) {
						validMoves.push_back(make_pair(i,j));
					}

					if (tmpcost <= cost) {
						all.push_back(make_pair(make_pair(i,j), tmpcost));
					}

					(*sol).erase((*sol).begin()+ j);
					(*sol).insert((*sol).begin() + i, toMove );
				}
			}
		}
		if (all.size() == 0) break;
		else {
			int tmp = rand() % all.size();
			if(all[tmp].second == cost) {
				toMove = (*sol)[all[tmp].first.first];
				(*sol).erase((*sol).begin()+ all[tmp].first.first);
				(*sol).insert((*sol).begin() + all[tmp].first.second, toMove);
				neutral_cmp++;
			}
			else {
				int tmp = rand() % validMoves.size();
				toMove = (*sol)[validMoves[tmp].first];
				(*sol).erase((*sol).begin()+ validMoves[tmp].first);
				(*sol).insert((*sol).begin() + validMoves[tmp].second, toMove);
				cost = bestCost;
				neutral_cmp = 0;
			}
			//apply move
		}
		if (neutral_cmp > 100 * jobs) break;
		cmp++;
	}
	return cost;
}
long me_stoch(int ** d, int jobs, int machs, vector<int> * sol) {
		long cost = costf(d, jobs, machs, *sol);
	//cout << "init cost = " << cost << endl;

	long tmpcost = 0;
	bool ok = true;
	vector<pair<int,int> > validMoves;
	int toMove;
	int cmp = 0;

	int nb_max = 0;

	int neutral_cmp = 0;
	vector <pair<pair<int, int>, long> > all;

	while(ok) {
		nb_max = 0;
		tmpcost = cost;
		validMoves.clear();

		all.clear();

		cout << cmp << " : cost = " << cost << endl;
		iter.push_back(cost);

		for (int i = 0; i < jobs; i++) {
			for (int j = 0; j < jobs; j++) {
				if (i != j) {
					toMove = (*sol)[i];
					(*sol).erase((*sol).begin()+i);
					(*sol).insert((*sol).begin() + j, toMove);
					tmpcost = costf(d, jobs, machs, *sol);

					if (tmpcost <= cost) {
						all.push_back(make_pair(make_pair(i,j), tmpcost));
						//cout << "yay" << endl;
					}
					
					if(tmpcost < cost) {
						int nb = 0;
						// test n2
						for (int k = 0; k < jobs; k++) {
							for (int l = 0; l < jobs; l++) {
								if (k != l) {
									int toMove2 = (*sol)[k];
									(*sol).erase((*sol).begin()+k);
									(*sol).insert((*sol).begin() + l, toMove2);

									long tmpcost2 = costf(d, jobs, machs, *sol);

									if (tmpcost2 < tmpcost) nb++;

									(*sol).erase((*sol).begin()+l);
									(*sol).insert((*sol).begin() + k, toMove2);
								}
							}
						}
						if (nb > nb_max) {
							nb_max = nb;
							validMoves.clear();
							validMoves.push_back(make_pair(i,j));
						}
						else if (nb == nb_max && nb_max > 0) {
							validMoves.push_back(make_pair(i,j));
						}
					}

					(*sol).erase((*sol).begin()+ j);
					(*sol).insert((*sol).begin() + i, toMove );
				}
			}
		}
		//cout << all.size() << endl;
		//cout << validMoves.size() << endl;
		if (all.size() == 0) break;
		else {
			int tmp = rand() % all.size();
			//cout << "tmpcost = " << all[tmp].second << endl;
			if(all[tmp].second == cost) {
			//	cout << "here1" << endl;
				toMove = (*sol)[all[tmp].first.first];
				(*sol).erase((*sol).begin()+ all[tmp].first.first);
				(*sol).insert((*sol).begin() + all[tmp].first.second, toMove);
				neutral_cmp++;
			}
			else if (validMoves.size() > 0) {
				//cout << "here2" << endl;
				int tmp = rand() % validMoves.size();
				toMove = (*sol)[validMoves[tmp].first];
				(*sol).erase((*sol).begin()+ validMoves[tmp].first);
				(*sol).insert((*sol).begin() + validMoves[tmp].second, toMove);
				cost = costf(d, jobs, machs, *sol);
				neutral_cmp = 0;
			}
			
		}
		if (neutral_cmp > 100 * jobs) break;
		cmp++;
	}

	// return best one
	long bcost = cost;
	for (int i = 0; i < jobs; i++) {
		for (int j = 0; j < jobs; j++) {
			if (i!=j) {
				toMove = (*sol)[i];
				(*sol).erase((*sol).begin()+i);
				(*sol).insert((*sol).begin() + j, toMove);
				tmpcost = costf(d, jobs, machs, *sol);
				if (tmpcost < bcost) {
					bcost = tmpcost;
					validMoves.push_back(make_pair(i,j));
				}
				(*sol).erase((*sol).begin()+ j);
				(*sol).insert((*sol).begin() + i, toMove );

			}
		}
	}

	if (validMoves.size() > 0) {
			int tmp = rand() % validMoves.size();
			toMove = (*sol)[validMoves[tmp].first];
			(*sol).erase((*sol).begin()+ validMoves[tmp].first);
			(*sol).insert((*sol).begin() + validMoves[tmp].second, toMove);
			cost = costf(d, jobs, machs, *sol);
			iter.push_back(cost);
	}


	return cost;
}




////////////////////////////////////////////////////////


/*
long ls_first(int ** d, int jobs, int machs, vector<int> * sol) {
	//cout << "nun first" << endl;
	long cost = costf(d, jobs, machs, *sol);
	//cout << "init cost = " << cost << endl;

	long tmpcost = 0;

	long xcost = cost;
	vector<long> previous;

	bool ok = true;
	vector<pair<int,int> > validMoves;
	int toMove;
	int cmp = 0;

	while(ok) {
		tmpcost = cost;
		validMoves.clear();

		//cout << cmp << " : cost = " << cost << endl;
		iter.push_back(cost);

		if (cost < xcost) xcost = cost;
		if(previous.size() < 5) previous.push_back(cost);
		else {
			previous.erase(previous.begin()+0);
			previous.push_back(cost);
		}
		long max = getMax(previous);

		for (int i = 0; i < jobs; i++) {
			for (int j = 0; j < jobs; j++) {
				if (i != j) {
				//	//cout << i << " and " << j << " bestCost = " << bestCost << endl;
					toMove = (*sol)[i];
					(*sol).erase((*sol).begin()+i);
					(*sol).insert((*sol).begin() + j, toMove);
					tmpcost = costf(d, jobs, machs, *sol);

					if(tmpcost < xcost) validMoves.push_back(make_pair(i,j));
						// test n2
					for (int k = 0; k < jobs; k++) {
						for (int l = 0; l < jobs; l++) {
							if (k != l) {
								int toMove2 = (*sol)[k];
								(*sol).erase((*sol).begin()+k);
								(*sol).insert((*sol).begin() + l, toMove2);

								long tmpcost2 = costf(d, jobs, machs, *sol);

								if (tmpcost2 < xcost && tmpcost < max) validMoves.push_back(make_pair(i,j));

								(*sol).erase((*sol).begin()+l);
								(*sol).insert((*sol).begin() + k, toMove2);
							}
						}
					}
					

					(*sol).erase((*sol).begin()+ j);
					(*sol).insert((*sol).begin() + i, toMove );
				}
			}
		}
		if (validMoves.size() == 0) break;
		else {
			////cout << validMoves.size() << endl;
			int tmp = rand() % validMoves.size();
			toMove = (*sol)[validMoves[tmp].first];
			(*sol).erase((*sol).begin()+ validMoves[tmp].first);
			(*sol).insert((*sol).begin() + validMoves[tmp].second, toMove);
			cost = costf(d, jobs, machs, *sol);;
			//apply move
		}
		cmp++;
	}

	return cost;
}

long ls_best(int ** d, int jobs, int machs, vector<int> * sol) {
	long cost = costf(d, jobs, machs, *sol);
	//cout << "init cost = " << cost << endl;

	long tmpcost = 0;
	bool ok = true;
	vector<pair<int,int> > validMoves;
	int toMove;
	long bestCost;
	int cmp = 0;

	long xcost = cost;
	vector<long> previous;

	while(ok) {
		tmpcost = cost;
		validMoves.clear();

		//cout << cmp << " : cost = " << cost << endl;
		bestCost = cost;

		if (cost < xcost) xcost = cost;
		if(previous.size() < 5) previous.push_back(cost);
		else {
			previous.erase(previous.begin()+0);
			previous.push_back(cost);
		}
		long max = getMax(previous);

		for (int i = 0; i < jobs; i++) {
			for (int j = 0; j < jobs; j++) {
				if (i != j) {
				//	//cout << i << " and " << j << " bestCost = " << bestCost << endl;
					toMove = (*sol)[i];
					(*sol).erase((*sol).begin()+i);
					(*sol).insert((*sol).begin() + j, toMove);
					tmpcost = costf(d, jobs, machs, *sol);

					if(tmpcost < max) {
						if (tmpcost < bestCost) {
							validMoves.clear();
							bestCost = tmpcost;
							validMoves.push_back(make_pair(i,j));
						}
						else if (tmpcost == bestCost && bestCost < cost) {
							validMoves.push_back(make_pair(i,j));
						}
						// test n2
						for (int k = 0; k < jobs; k++) {
							for (int l = 0; l < jobs; l++) {
								if (k != l) {
									int toMove2 = (*sol)[k];
									(*sol).erase((*sol).begin()+k);
									(*sol).insert((*sol).begin() + l, toMove2);

									long tmpcost2 = costf(d, jobs, machs, *sol);

									if (tmpcost2 < cost && tmpcost2 == bestCost) validMoves.push_back(make_pair(i,j));
									else if (tmpcost2 < bestCost) {
										validMoves.clear();
										bestCost = tmpcost2;
										validMoves.push_back(make_pair(i,j));
									}

									(*sol).erase((*sol).begin()+l);
									(*sol).insert((*sol).begin() + k, toMove2);
								}
							}
						}
					}

					(*sol).erase((*sol).begin()+ j);
					(*sol).insert((*sol).begin() + i, toMove );
				}
			}
		}
		if (validMoves.size() == 0) break;
		else {
			////cout << validMoves.size() << endl;
			int tmp = rand() % validMoves.size();
			toMove = (*sol)[validMoves[tmp].first];
			(*sol).erase((*sol).begin()+ validMoves[tmp].first);
			(*sol).insert((*sol).begin() + validMoves[tmp].second, toMove);
			cost = costf(d, jobs, machs, *sol);;
			//apply move
		}
		cmp++;
	}

	return cost;
}

long ls_worst(int ** d, int jobs, int machs, vector<int> * sol) {
		long cost = costf(d, jobs, machs, *sol);
	//cout << "init cost = " << cost << endl;

	long tmpcost = 0;
	long bestCost = 0;
	bool ok = true;
	vector<pair<int,int> > validMoves;
	int toMove;
	int cmp = 0;

	long xcost = cost;
	vector<long> previous;

	while(ok) {
		tmpcost = cost;
		bestCost = -1;
		validMoves.clear();

		//cout << cmp << " : cost = " << cost << endl;

		if (cost < xcost) xcost = cost;
		if(previous.size() < 5) previous.push_back(cost);
		else {
			previous.erase(previous.begin()+0);
			previous.push_back(cost);
		}
		long max = getMax(previous);

		for (int i = 0; i < jobs; i++) {
			for (int j = 0; j < jobs; j++) {
				if (i != j) {
				//	//cout << i << " and " << j << " bestCost = " << bestCost << endl;
					toMove = (*sol)[i];
					(*sol).erase((*sol).begin()+i);
					(*sol).insert((*sol).begin() + j, toMove);
					tmpcost = costf(d, jobs, machs, *sol);

					if(tmpcost > bestCost && tmpcost < xcost) {
						bestCost = tmpcost;
						validMoves.clear();
						validMoves.push_back(make_pair(i,j));
					}
					else if (tmpcost == bestCost && bestCost < xcost) {
						validMoves.push_back(make_pair(i,j));
					}

					if(tmpcost < max) {
						for (int k = 0; k < jobs; k++) {
							for (int l = 0; l < jobs; l++) {
								if (k != l) {
									int toMove2 = (*sol)[k];
									(*sol).erase((*sol).begin()+k);
									(*sol).insert((*sol).begin() + l, toMove2);

									long tmpcost2 = costf(d, jobs, machs, *sol);

									if (tmpcost2 < xcost && tmpcost2 == bestCost) validMoves.push_back(make_pair(i,j));
									else if (tmpcost2 > bestCost && tmpcost2 < xcost) {
										validMoves.clear();
										bestCost = tmpcost2;
										validMoves.push_back(make_pair(i,j));
									}

									(*sol).erase((*sol).begin()+l);
									(*sol).insert((*sol).begin() + k, toMove2);
								}
							}
						}

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

long ls_me(int ** d, int jobs, int machs, vector<int> * sol) {
		//cout << "nun first" << endl;
	long cost = costf(d, jobs, machs, *sol);
	//cout << "init cost = " << cost << endl;

	long tmpcost = 0;
	bool ok = true;
	vector<pair<int,int> > validMoves;
	int toMove;
	int cmp = 0;

	int nb_max = 0;

	long xcost = cost;
	vector<long> previous;

	while(ok) {
		nb_max = 0;
		tmpcost = cost;
		validMoves.clear();

		//cout << cmp << " : cost = " << cost << endl;

		if (cost < xcost) xcost = cost;
		if(previous.size() < 5) previous.push_back(cost);
		else {
			previous.erase(previous.begin()+0);
			previous.push_back(cost);
		}
		long max = getMax(previous);

		for (int i = 0; i < jobs; i++) {
			for (int j = 0; j < jobs; j++) {
				if (i != j) {
				//	//cout << i << " and " << j << " bestCost = " << bestCost << endl;
					toMove = (*sol)[i];
					(*sol).erase((*sol).begin()+i);
					(*sol).insert((*sol).begin() + j, toMove);
					tmpcost = costf(d, jobs, machs, *sol);

					
					if(tmpcost < max) {
						int nb = 0;
						// test n2
						for (int k = 0; k < jobs; k++) {
							for (int l = 0; l < jobs; l++) {
								if (k != l) {
									int toMove2 = (*sol)[k];
									(*sol).erase((*sol).begin()+k);
									(*sol).insert((*sol).begin() + l, toMove2);

									long tmpcost2 = costf(d, jobs, machs, *sol);

									if (tmpcost2 < xcost) nb++;

									(*sol).erase((*sol).begin()+l);
									(*sol).insert((*sol).begin() + k, toMove2);
								}
							}
						}
						if (nb > nb_max) {
							nb_max = nb;
							validMoves.clear();
							validMoves.push_back(make_pair(i,j));
						}
						else if (nb == nb_max && nb_max > 0) {
							validMoves.push_back(make_pair(i,j));
						}
					}

					(*sol).erase((*sol).begin()+ j);
					(*sol).insert((*sol).begin() + i, toMove );
				}
			}
		}
		if (validMoves.size() == 0) break;
		else {
			////cout << validMoves.size() << endl;
			int tmp = rand() % validMoves.size();
			toMove = (*sol)[validMoves[tmp].first];
			(*sol).erase((*sol).begin()+ validMoves[tmp].first);
			(*sol).insert((*sol).begin() + validMoves[tmp].second, toMove);
			cost = costf(d, jobs, machs, *sol);;
			//apply move
		}
		cmp++;
	}

	return cost;
}

*/