#include "methods.h"

extern vector<long> me;
extern vector<pair<int,int> > vrank;

void init_sol(vector<int> *sol, int n) {
	int val = rand() % n;
	while((*sol).size() < n) {
		if(!isIntoVect((*sol),val)) 
			(*sol).push_back(val);
		else 
			val = rand() % n;
	}
}

long calculate_cost(int ** D, int ** F, vector<int> sol ) {
	long cost = 0;
	for (int i = 0; i < sol.size(); i++) {
		for (int j = 0; j < sol.size(); j++) {
			cost += D[i][j] * F[sol[i]][sol[j]];
		}
	}
	return cost;
}


int ran(vector<long> v, long c) {
	int nb = 0;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] < c) nb++;
	}
	return nb + 1;
}

bool isIntoVect(vector<int> v, int val) {
	for (int i = 0; i < v.size(); i++) {
		if (v[i] == val) return true;
	}
	return false;
}

// used in max expand


int betterSols(int** D, int ** F, vector<int> sol, vector<pair<int,int> > possibilities, long comparative_cost) {
	long solCost = calculate_cost(D,F,sol);
	//long tmpcost;
	long secondcost = solCost;
	int nb = 0;
	for (int i = 0; i < possibilities.size(); i++) {
	//	tmpcost = comparative_cost;

		long scost = solCost;

		iter_swap(sol.begin() + possibilities[i].first, sol.begin() + possibilities[i].second);

		scost = calculate_cost(D,F,sol);

	//	secondcost = calculate_cost(D,F,sol);

	///	if (secondcost != scost) cout << "problem" << endl;

		//tmpcost = calculate_cost(D,F,sol);

		if (scost < comparative_cost) nb++;
		//if(secondcost != tmpcost) cout << "not ok " << endl;
		iter_swap(sol.begin() + possibilities[i].first, sol.begin() + possibilities[i].second);
	}
	return nb;
}

int betterSols_neutral(int** D, int ** F, vector<int> sol, vector<pair<int,int> > possibilities, long comparative_cost) {
	long solCost = calculate_cost(D,F,sol);
	//long tmpcost;
	long secondcost = solCost;
	int nb = 0;
	for (int i = 0; i < possibilities.size(); i++) {
	//	tmpcost = comparative_cost;

		long scost = solCost;

		iter_swap(sol.begin() + possibilities[i].first, sol.begin() + possibilities[i].second);

		scost = calculate_cost(D,F,sol);

	//	secondcost = calculate_cost(D,F,sol);

	///	if (secondcost != scost) cout << "problem" << endl;

		//tmpcost = calculate_cost(D,F,sol);

		if (scost <= comparative_cost) nb++;
		//if(secondcost != tmpcost) cout << "not ok " << endl;
		iter_swap(sol.begin() + possibilities[i].first, sol.begin() + possibilities[i].second);
	}
	return nb;
}



int checkBetter(int** D, int ** F, vector<int> sol, vector<pair<int,int> > possibilities, long * bestCost, long currentCost, long xcost, bool * modif) {
	long tmpBestCost = (*bestCost);
	vector<int> index;
	index.push_back(-1);

	for (int i = 0; i < possibilities.size(); i++) {
		long tmpCost = currentCost;

		iter_swap(sol.begin() + possibilities[i].first, sol.begin() + possibilities[i].second);

		tmpCost = calculate_cost(D,F, sol);

		//tmpCost = calculate_cost(D,F,sol);

		if(tmpCost < tmpBestCost) {
			index.clear();
			index.push_back(i);
			tmpBestCost = tmpCost;
			(*modif) = true;
		}
		else if (tmpCost == tmpBestCost && tmpCost < xcost) {
			if (index[i] == -1) index.clear();
			index.push_back(i);
		}

		iter_swap(sol.begin() + possibilities[i].first, sol.begin() + possibilities[i].second);
	}

	if (*modif) {
		(*bestCost) = tmpBestCost;
		//cout << "#### next swap will be on " << possibilities[index].first << " and " << possibilities[index].second << endl;
	}
	return index[0];
}
int checkBetter2(int** D, int ** F, vector<int> sol, vector<pair<int,int> > possibilities, long * bestCost, long currentCost, long xcost, bool * modif) {
	long tmpBestCost = (*bestCost);
	vector<int> index;
	index.push_back(-1);

	for (int i = 0; i < possibilities.size(); i++) {
		long tmpCost = currentCost;

		iter_swap(sol.begin() + possibilities[i].first, sol.begin() + possibilities[i].second);

		tmpCost = calculate_cost(D,F,sol);
		//tmpCost = calculate_cost(D,F,sol);

		if(tmpCost < tmpBestCost) {
			index.clear();
			index.push_back(i);
			tmpBestCost = tmpCost;
			(*modif) = true;
		}
		else if (tmpCost == tmpBestCost && tmpCost < xcost) {
			if (index[i] == -1) index.clear();
			index.push_back(i);
		}

		iter_swap(sol.begin() + possibilities[i].first, sol.begin() + possibilities[i].second);
	}

	if (*modif) {
		(*bestCost) = tmpBestCost;
		//cout << "#### next swap will be on " << possibilities[index].first << " and " << possibilities[index].second << endl;
	}
	if (index.size() > 1) {
		//cout << "-------------- chkbet2 size = " << index.size() << endl;
		int t = rand() % index.size();
		return index[t];
	}
	return index[0];
}



int checkWorst(int** D, int ** F, vector<int> sol, vector<pair<int,int> > possibilities, long * bestCost, long currentCost, long xcost,  bool * modif) {
//	cout << " ###############################################" << endl;
	long tmpBestCost = (*bestCost);
	vector<int> index;
	index.push_back(-1);

	for (int i = 0; i < possibilities.size(); i++) {
		long tmpCost = currentCost;

		iter_swap(sol.begin() + possibilities[i].first, sol.begin() + possibilities[i].second);

		tmpCost = calculate_cost(D,F,sol);

	//	tmpCost = calculate_cost(D,F,sol);

		if(tmpCost > tmpBestCost && tmpCost < xcost) {
		//	cout << "tmpBestCost = " << tmpBestCost << " tmpCost = " << tmpCost << " xcost = " << xcost << endl;
		//	cout << "-------- modif" << endl;
			index.clear();
			index.push_back(i);
			tmpBestCost = tmpCost;
			*modif = true;
		}
		else if (tmpCost == tmpBestCost && tmpCost < xcost) {
		//	cout << "---------- equalty" << endl;
			if (index[i] == -1) index.clear();
			index.push_back(i);
		}

		iter_swap(sol.begin() + possibilities[i].first, sol.begin() + possibilities[i].second);
	}

	if (index[0] != -1) {
		(*bestCost) = tmpBestCost;
		//cout << "#### next swap will be on " << possibilities[index].first << " and " << possibilities[index].second << endl;
	}
	return index[0];
}

int checkWorst2(int** D, int ** F, vector<int> sol, vector<pair<int,int> > possibilities, long * bestCost, long currentCost, long xcost,  bool * modif) {
//	cout << " ###############################################" << endl;
	long tmpBestCost = (*bestCost);
	vector<int> index;
	index.push_back(-1);

	for (int i = 0; i < possibilities.size(); i++) {
		long tmpCost = currentCost;

		iter_swap(sol.begin() + possibilities[i].first, sol.begin() + possibilities[i].second);

		tmpCost = calculate_cost(D,F, sol)	;

		if(tmpCost > tmpBestCost && tmpCost < xcost) {
		//	cout << "---------- modif  " << (long)xcost << " " << (long)tmpCost << " " << (long)tmpBestCost << endl;
			index.clear();
			index.push_back(i);
			tmpBestCost = tmpCost;
			*modif = true;
		}
		else if (tmpCost == tmpBestCost && tmpCost < xcost) {
			//cout << "---------- equalty" << endl;
			if (index[i] == -1) index.clear();
			index.push_back(i);
		}

		iter_swap(sol.begin() + possibilities[i].first, sol.begin() + possibilities[i].second);
	}

	if (index[0] != -1) {
		(*bestCost) = tmpBestCost;
	}

	if (index.size() > 1) {
		//cout << "-------------- chkbet2 size = " << index.size() << endl;
		int t = rand() % index.size();
		return index[t];
	}	

	return index[0];
}


// uses rand if equalties 
int indexOfMaxValue2(vector<int> v) {
	int maxval = 0;
	vector<int> index;
	index.push_back(-1);
	for (int i = 0; i < v.size(); i++) {
		if (v[i] > maxval) {
			index.clear();
			index.push_back(i);
			maxval = v[i];
		}
		else if (v[i] == maxval && maxval > 0) {
			index.push_back(i);
		}
	}
	//cout << "------------------------ best ME value is " << maxval << endl;
	me.push_back(maxval);
	cout << "------------------------------------------------------------" << maxval << endl;
	//cout << index[0] << " ------------ " << index.size() << endl;
	if (index.size() == 1) return index[0];
	else {
		int t = rand() % index.size();
		return index[t];
	}
}



long updateCost(int **D, int** F, vector<int> sol, int ti, int tj) {
	long sum = 0;
	for (int i = 0; i < sol.size(); i++) {
		sum += D[i][ti]*F[sol[i]][sol[ti]];
		sum += D[i][tj]*F[sol[i]][sol[tj]];
		if (ti != i) sum += D[ti][i]*F[sol[ti]][sol[i]];
		if (tj != i) sum += D[tj][i]*F[sol[tj]][sol[i]];
	}
	return sum;
}

/*int betterSols(int** D, int ** F, vector<int> sol, vector<pair<int,int> > possibilities, long comparative_cost) {
	long solCost = calculate_cost(D,F,sol);
	//long tmpcost;
	long secondcost = solCost;
	int nb = 0;
	for (int i = 0; i < possibilities.size(); i++) {
	//	tmpcost = comparative_cost;

		secondcost = solCost;

	//	secondcost -= updateCost(D,F,sol, possibilities[i].first,possibilities[i].second );

		iter_swap(sol.begin() + possibilities[i].first, sol.begin() + possibilities[i].second);

	//	secondcost += updateCost(D,F,sol, possibilities[i].first,possibilities[i].second );

		secondcost = calculate_cost(D,F,sol);

		//tmpcost = calculate_cost(D,F,sol);

		if (secondcost < comparative_cost) nb++;
		//if(secondcost != tmpcost) cout << "not ok " << endl;
		iter_swap(sol.begin() + possibilities[i].first, sol.begin() + possibilities[i].second);
	}
	return nb;
}*/

/*int checkBetter(int** D, int ** F, vector<int> sol, vector<pair<int,int> > possibilities, long * bestCost, long currentCost, long xcost, bool * modif) {
	long tmpBestCost = (*bestCost);
	vector<int> index;
	index.push_back(-1);

	for (int i = 0; i < possibilities.size(); i++) {
		long tmpCost = currentCost;

	//	tmpCost -= updateCost(D,F,sol, possibilities[i].first,possibilities[i].second );

		iter_swap(sol.begin() + possibilities[i].first, sol.begin() + possibilities[i].second);

	//	tmpCost += updateCost(D,F,sol, possibilities[i].first,possibilities[i].second );

		tmpCost = calculate_cost(D,F,sol);

		if(tmpCost < tmpBestCost) {
			index.clear();
			index.push_back(i);
			tmpBestCost = tmpCost;
			(*modif) = true;
		}
		else if (tmpCost == tmpBestCost && tmpCost < xcost) {
			if (index[i] == -1) index.clear();
			index.push_back(i);
		}

		iter_swap(sol.begin() + possibilities[i].first, sol.begin() + possibilities[i].second);
	}

	if (*modif) {
		(*bestCost) = tmpBestCost;
		//cout << "#### next swap will be on " << possibilities[index].first << " and " << possibilities[index].second << endl;
	}
	return index[0];
}*/

/*	int checkWorst(int** D, int ** F, vector<int> sol, vector<pair<int,int> > possibilities, long * bestCost, long currentCost, long xcost,  bool * modif) {
//	cout << " ###############################################" << endl;
	long tmpBestCost = (*bestCost);
	vector<int> index;
	index.push_back(-1);

	for (int i = 0; i < possibilities.size(); i++) {
		long tmpCost = currentCost;

	//	tmpCost -= updateCost(D,F,sol, possibilities[i].first,possibilities[i].second );

		iter_swap(sol.begin() + possibilities[i].first, sol.begin() + possibilities[i].second);

	//	tmpCost += updateCost(D,F,sol, possibilities[i].first,possibilities[i].second );

		tmpCost = calculate_cost(D,F,sol);

		

		if(tmpCost > tmpBestCost && tmpCost < xcost) {
		//	cout << "tmpBestCost = " << tmpBestCost << " tmpCost = " << tmpCost << " xcost = " << xcost << endl;
		//	cout << "-------- modif" << endl;
			index.clear();
			index.push_back(i);
			tmpBestCost = tmpCost;
			*modif = true;
		}
		else if (tmpCost == tmpBestCost && tmpCost < xcost) {
		//	cout << "---------- equalty" << endl;
			if (index[i] == -1) index.clear();
			index.push_back(i);
		}

		iter_swap(sol.begin() + possibilities[i].first, sol.begin() + possibilities[i].second);
	}

	if (index[0] != -1) {
		(*bestCost) = tmpBestCost;
		//cout << "#### next swap will be on " << possibilities[index].first << " and " << possibilities[index].second << endl;
	}
	return index[0];
}

int checkBetter2(int** D, int ** F, vector<int> sol, vector<pair<int,int> > possibilities, long * bestCost, long currentCost, long xcost, bool * modif) {
	long tmpBestCost = (*bestCost);
	vector<int> index;
	index.push_back(-1);

	for (int i = 0; i < possibilities.size(); i++) {
		long tmpCost = currentCost;

	//	tmpCost -= updateCost(D,F,sol, possibilities[i].first,possibilities[i].second );

		iter_swap(sol.begin() + possibilities[i].first, sol.begin() + possibilities[i].second);

	//	tmpCost += updateCost(D,F,sol, possibilities[i].first,possibilities[i].second );

		tmpCost = calculate_cost(D,F,sol);

		if(tmpCost < tmpBestCost) {
			index.clear();
			index.push_back(i);
			tmpBestCost = tmpCost;
			(*modif) = true;
		}
		else if (tmpCost == tmpBestCost && tmpCost < xcost) {
			if (index[i] == -1) index.clear();
			index.push_back(i);
		}

		iter_swap(sol.begin() + possibilities[i].first, sol.begin() + possibilities[i].second);
	}

	if (*modif) {
		(*bestCost) = tmpBestCost;
		//cout << "#### next swap will be on " << possibilities[index].first << " and " << possibilities[index].second << endl;
	}
	if (index.size() > 1) {
		//cout << "-------------- chkbet2 size = " << index.size() << endl;
		int t = rand() % index.size();
		return index[t];
	}
	return index[0];
}

int checkWorst2(int** D, int ** F, vector<int> sol, vector<pair<int,int> > possibilities, long * bestCost, long currentCost, long xcost,  bool * modif) {
//	cout << " ###############################################" << endl;
	long tmpBestCost = (*bestCost);
	vector<int> index;
	index.push_back(-1);

	for (int i = 0; i < possibilities.size(); i++) {
		long tmpCost = currentCost;

		iter_swap(sol.begin() + possibilities[i].first, sol.begin() + possibilities[i].second);

		tmpCost = calculate_cost(D,F,sol);		

		if(tmpCost > tmpBestCost && tmpCost < xcost) {
			index.clear();
			index.push_back(i);
			tmpBestCost = tmpCost;
			*modif = true;
		}
		else if (tmpCost == tmpBestCost && tmpCost < xcost) {
		//	cout << "---------- equalty" << endl;
			if (index[i] == -1) index.clear();
			index.push_back(i);
		}

		iter_swap(sol.begin() + possibilities[i].first, sol.begin() + possibilities[i].second);
	}

	if (index[0] != -1) {
		(*bestCost) = tmpBestCost;
	}

	if (index.size() > 1) {
		//cout << "-------------- chkbet2 size = " << index.size() << endl;
		int t = rand() % index.size();
		return index[t];
	}	

	return index[0];
}




*/
