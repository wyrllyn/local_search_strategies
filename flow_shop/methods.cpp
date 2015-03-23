#include "methods.h"

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

float tft(int **d, int jobs, int machs, vector<int> sol) {
	float toReturn = 0;
	int ** mat = (int**)malloc(sizeof(int*) * jobs );
	for (int i = 0; i < jobs ; i++ ) {
		mat[i] = (int*) malloc(sizeof(int) * machs);
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
		free(mat[i]);
	}
	free(mat);

	return toReturn;
}