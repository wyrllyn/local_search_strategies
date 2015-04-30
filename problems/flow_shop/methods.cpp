#include "methods.h"

extern int ** mat;

void init(int jobs, vector<int> * sol) {
	while((*sol).size() < jobs) {
		int tmp = rand() % jobs;
		if (!isInto(*sol, tmp)) (*sol).push_back(tmp);
	}
}

bool isInto(vector<int> s, int n) {
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == n) return true;
	}
	return false;
}

long tft(int **d, int jobs, int machs, vector<int> sol) {
	long toReturn = 0;
	//int ** mat = (int**)malloc(sizeof(int*) * jobs );
	int ** mat = new int*[jobs];
	//cout << "alloc done" << endl;
	for (int i = 0; i < jobs ; i++ ) {
	//	cout << i << "on " << jobs << endl;
		//mat[i] = (int*) malloc(sizeof(int) * machs);
		mat[i] = new int[machs];
	}


	//// compute /////

	for (int i = 0; i < sol.size(); i++) {
		for (int m = 0; m < machs; m++ )  {
			if (i == 0 && m == 0) mat[i][m] = d[sol[i]][m];
			else if (i == 0) mat[i][m] = d[sol[i]][m] + mat[i][m-1] ;
			else if (m == 0) mat[i][m] = d[sol[i]][m] + mat [i - 1][m] ;
			else mat[i][m] = d[sol[i]][m] + max(mat [i - 1][m] , mat[i][m-1]) ;			
		}
	//	if (mat[i][machs -1] > toReturn  ) toReturn = mat[i][machs -1];
	}
	toReturn = mat[jobs-1][machs -1];

	//cout << toReturn << " vs " << mat[jobs-1][machs -1] << endl;



	for (int  i =0; i < jobs; i++) {
		delete [] mat[i];
	}
	delete [] mat; 



	return toReturn;
}

long costf(int **d, int jobs, int machs, vector<int> sol) {
	long current = 0;
	vector<long> col;
	for (int i = 0; i < jobs; i++) col.push_back(0);

for (int m = 0; m < machs; m++ )  {
	current = 0;
	for (int i = 0; i < sol.size(); i++) {

		
			/*if (i == 0 && m == 0) {
				current = d[sol[i]][m];
				col[i] = d[sol[i]][m];
			}
			else if (i == 0)  {
				current = d[sol[i]][m] + col[i] ;
				col[i] = current;
			}
			else if (m == 0) {
				current = d[sol[i]][m] + current;
				col[i] = current;
			}
			else {
				current = d[sol[i]][m] + max(current, col[i]);
				col[i] = current;
			} 	*/
				current = d[sol[i]][m] + max(current, col[i]);
				col[i] = current;
		}

	//	if (mat[i][machs -1] > toReturn  ) toReturn = mat[i][machs -1];
	}
	return current;
}

long getMax(vector<long> v) {
	long max = v[0];
	for (int i = 1; i < v.size(); i++) {
		if(v[i] > max) max = v[i];
	}
	return max;
}

int ran(vector<long> v, long c) {
	int nb = 0;
	for (int i = 0; i < v.size(); i++) {
		if (v[i] < c) nb++;
	}
	return nb + 1;
}