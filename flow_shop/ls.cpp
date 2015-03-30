#include "ls.h"


long first(int ** d, int jobs, int machs, vector<int> * sol) {
	long cost = tft(d, jobs, machs, *sol);
	cout << "init cost = " << cost << endl;

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

long best(int ** d, int jobs, int machs, vector<int> * sol) {
	long cost = tft(d, jobs, machs, *sol);
	cout << "init cost = " << cost << endl;

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

long worst(int ** d, int jobs, int machs, vector<int> * sol) {
		long cost = tft(d, jobs, machs, *sol);
	cout << "init cost = " << cost << endl;

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

		cout << cmp << " : cost = " << cost << endl;

		for (int i = 0; i < jobs; i++) {
			for (int j = 0; j < jobs; j++) {
				if (i != j) {
				//	cout << i << " and " << j << " bestCost = " << bestCost << endl;
					toMove = (*sol)[i];
					(*sol).erase((*sol).begin()+i);
					(*sol).insert((*sol).begin() + j, toMove);
					tmpcost = tft(d, jobs, machs, *sol);

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
	cout << "nun first" << endl;
	long cost = tft(d, jobs, machs, *sol);
	cout << "init cost = " << cost << endl;

	long tmpcost = 0;
	bool ok = true;
	vector<pair<int,int> > validMoves;
	int toMove;
	int cmp = 0;

	while(ok) {
		tmpcost = cost;
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

					if(tmpcost < cost) {
						validMoves.push_back(make_pair(i,j));
						// test n2
						for (int k = 0; k < jobs; k++) {
							for (int l = 0; l < jobs; l++) {
								if (k != l) {
									int toMove2 = (*sol)[k];
									(*sol).erase((*sol).begin()+k);
									(*sol).insert((*sol).begin() + l, toMove2);

									long tmpcost2 = tft(d, jobs, machs, *sol);

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
			//cout << validMoves.size() << endl;
			int tmp = rand() % validMoves.size();
			toMove = (*sol)[validMoves[tmp].first];
			(*sol).erase((*sol).begin()+ validMoves[tmp].first);
			(*sol).insert((*sol).begin() + validMoves[tmp].second, toMove);
			cost = tft(d, jobs, machs, *sol);;
			//apply move
		}
		cmp++;
	}

	return cost;
}

long nun_best(int ** d, int jobs, int machs, vector<int> * sol) {
	long cost = tft(d, jobs, machs, *sol);
	cout << "init cost = " << cost << endl;

	long tmpcost = 0;
	bool ok = true;
	vector<pair<int,int> > validMoves;
	int toMove;
	long bestCost;
	int cmp = 0;

	while(ok) {
		tmpcost = cost;
		validMoves.clear();

		cout << cmp << " : cost = " << cost << endl;
		bestCost = cost;

		for (int i = 0; i < jobs; i++) {
			for (int j = 0; j < jobs; j++) {
				if (i != j) {
				//	cout << i << " and " << j << " bestCost = " << bestCost << endl;
					toMove = (*sol)[i];
					(*sol).erase((*sol).begin()+i);
					(*sol).insert((*sol).begin() + j, toMove);
					tmpcost = tft(d, jobs, machs, *sol);

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

									long tmpcost2 = tft(d, jobs, machs, *sol);

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
			//cout << validMoves.size() << endl;
			int tmp = rand() % validMoves.size();
			toMove = (*sol)[validMoves[tmp].first];
			(*sol).erase((*sol).begin()+ validMoves[tmp].first);
			(*sol).insert((*sol).begin() + validMoves[tmp].second, toMove);
			cost = tft(d, jobs, machs, *sol);;
			//apply move
		}
		cmp++;
	}

	return cost;
}

long nun_me(int ** d, int jobs, int machs, vector<int> * sol) {
		cout << "nun first" << endl;
	long cost = tft(d, jobs, machs, *sol);
	cout << "init cost = " << cost << endl;

	long tmpcost = 0;
	bool ok = true;
	vector<pair<int,int> > validMoves;
	int toMove;
	int cmp = 0;

	int nb_max = 0;

	while(ok) {
		nb_max = 0;
		tmpcost = cost;
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

					
					if(tmpcost < cost) {
						int nb = 0;
						// test n2
						for (int k = 0; k < jobs; k++) {
							for (int l = 0; l < jobs; l++) {
								if (k != l) {
									int toMove2 = (*sol)[k];
									(*sol).erase((*sol).begin()+k);
									(*sol).insert((*sol).begin() + l, toMove2);

									long tmpcost2 = tft(d, jobs, machs, *sol);

									if (tmpcost2 < cost) nb++;

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
			//cout << validMoves.size() << endl;
			int tmp = rand() % validMoves.size();
			toMove = (*sol)[validMoves[tmp].first];
			(*sol).erase((*sol).begin()+ validMoves[tmp].first);
			(*sol).insert((*sol).begin() + validMoves[tmp].second, toMove);
			cost = tft(d, jobs, machs, *sol);;
			//apply move
		}
		cmp++;
	}

	return cost;
}

long large_first(int ** d, int jobs, int machs, vector<int> * sol) {
	cout << "nun first" << endl;
	long cost = tft(d, jobs, machs, *sol);
	cout << "init cost = " << cost << endl;

	long tmpcost = 0;
	bool ok = true;
	vector<pair<pair<int,int>, pair<int,int> > > validMoves;
	int toMove;
	int cmp = 0;

	while(ok) {
		tmpcost = cost;
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

					if(tmpcost < cost) validMoves.push_back(make_pair(make_pair(i,j), make_pair(-1,-1)));
						
						// test n2
						for (int k = 0; k < jobs; k++) {
							for (int l = 0; l < jobs; l++) {
								if (k != l) {
									int toMove2 = (*sol)[k];
									(*sol).erase((*sol).begin()+k);
									(*sol).insert((*sol).begin() + l, toMove2);

									long tmpcost2 = tft(d, jobs, machs, *sol);

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
			//cout << validMoves.size() << endl;
			int tmp = rand() % validMoves.size();
			toMove = (*sol)[validMoves[tmp].first.first];
			(*sol).erase((*sol).begin()+ validMoves[tmp].first.first);
			(*sol).insert((*sol).begin() + validMoves[tmp].first.second, toMove);

			if (validMoves[tmp].second.first != -1) {
				toMove = (*sol)[validMoves[tmp].second.first];
				(*sol).erase((*sol).begin()+ validMoves[tmp].second.first);
				(*sol).insert((*sol).begin() + validMoves[tmp].second.second, toMove);
			}


			cost = tft(d, jobs, machs, *sol);;
			
		}
		cmp++;
	}

	return cost;
}

long large_best(int ** d, int jobs, int machs, vector<int> * sol) {
	long cost = tft(d, jobs, machs, *sol);
	cout << "init cost = " << cost << endl;

	long tmpcost = 0;
	bool ok = true;
	vector<pair<pair<int,int>, pair<int,int> > > validMoves;
	int toMove;
	long bestCost;
	int cmp = 0;

	while(ok) {
		tmpcost = cost;
		validMoves.clear();

		cout << cmp << " : cost = " << cost << endl;
		bestCost = cost;

		for (int i = 0; i < jobs; i++) {
			for (int j = 0; j < jobs; j++) {
				if (i != j) {
				//	cout << i << " and " << j << " bestCost = " << bestCost << endl;
					toMove = (*sol)[i];
					(*sol).erase((*sol).begin()+i);
					(*sol).insert((*sol).begin() + j, toMove);
					tmpcost = tft(d, jobs, machs, *sol);

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

								long tmpcost2 = tft(d, jobs, machs, *sol);

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
			//cout << validMoves.size() << endl;
			int tmp = rand() % validMoves.size();
			toMove = (*sol)[validMoves[tmp].first.first];
			(*sol).erase((*sol).begin()+ validMoves[tmp].first.first);
			(*sol).insert((*sol).begin() + validMoves[tmp].first.second, toMove);

			if (validMoves[tmp].second.first != -1) {
				toMove = (*sol)[validMoves[tmp].second.first];
				(*sol).erase((*sol).begin()+ validMoves[tmp].second.first);
				(*sol).insert((*sol).begin() + validMoves[tmp].second.second, toMove);
				//cout << "2 moves" << endl;
			}
			cost = tft(d, jobs, machs, *sol);;
			
		}
		cmp++;
	}

	return cost;
}

long large_worst(int ** d, int jobs, int machs, vector<int> * sol) {
	cout << "nun first" << endl;
	long cost = tft(d, jobs, machs, *sol);
	cout << "init cost = " << cost << endl;

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

		cout << cmp << " : cost = " << cost << endl;

		for (int i = 0; i < jobs; i++) {
			for (int j = 0; j < jobs; j++) {
				if (i != j) {
				//	cout << i << " and " << j << " bestCost = " << bestCost << endl;
					toMove = (*sol)[i];
					(*sol).erase((*sol).begin()+i);
					(*sol).insert((*sol).begin() + j, toMove);
					tmpcost = tft(d, jobs, machs, *sol);

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

								long tmpcost2 = tft(d, jobs, machs, *sol);

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
			//cout << validMoves.size() << endl;
			int tmp = rand() % validMoves.size();
			toMove = (*sol)[validMoves[tmp].first.first];
			(*sol).erase((*sol).begin()+ validMoves[tmp].first.first);
			(*sol).insert((*sol).begin() + validMoves[tmp].first.second, toMove);

			if (validMoves[tmp].second.first != -1) {
				toMove = (*sol)[validMoves[tmp].second.first];
				(*sol).erase((*sol).begin()+ validMoves[tmp].second.first);
				(*sol).insert((*sol).begin() + validMoves[tmp].second.second, toMove);
			}


			cost = tft(d, jobs, machs, *sol);;
			
		}
		cmp++;
	}

	return cost;
}