#include "ls.h"
#include "parser.h"
#include <limits>

int main(int argc, char** argv) {
	int s = time(NULL);

	srand(s);
	cout << "s = " << s << endl;
	string filename = "qapdata/kra30b.dat";
	int ** D;
	int ** F;
	int n;
	vector<int> sol;
	vector<int> sol2;
	vector<int> sol3;
	vector<int> sol4;
	vector<int> sol5;
	vector<int> sol6;
	vector<int> sol7;
	vector<int> sol8;
	vector<int> sol_lbc;


	int64_t c1 = -1;
	int64_t c2 = -1;
	int64_t c3 = -1;
	int64_t c4 = -1;
	int64_t c5 = -1;
	int64_t c6 = -1;
	int64_t c7 = -1;
	int64_t c8 = -1;

	int64_t c_lbc = -1;

	if (argc > 1) filename = argv[1];

	parse_qap(&D, &F, &n, filename);

	init_sol(&sol, n);

	for (int i = 0; i < sol.size(); i++) {
		sol2.push_back(sol[i]);
		sol3.push_back(sol[i]);
		sol4.push_back(sol[i]);
		sol5.push_back(sol[i]);
		sol6.push_back(sol[i]);
		sol7.push_back(sol[i]);
		sol8.push_back(sol[i]);
		sol_lbc.push_back(sol[i]);
	}

	cout << "INIT COST = " << calculate_cost(D,F,sol) << endl;

	c1 = ls_first(D,F,&sol);
	c2 = climber_best(D,F,&sol2);
	c3 = climber_worst(D,F,&sol3);

	c4 = ls_ME_climber(D,F,&sol4);
	c_lbc = large_best_climber(D,F,&sol_lbc);


	c5 = ls_ME_large(D,F,&sol5);
	c6 = large_best(D, F, &sol6);

//	c7 = large_worst(D,F, &sol7);

//	c8 = large_first(D,F, &sol8);


	cout << "FINAL Cost with FIRST = " << c1  <<   endl;
	cout << "FINAL cost with climber_best = " << c2 << endl;
	cout << "FINAL cost with climber_worst = " << c3 << endl << endl;

	cout << "FINAL cost with climber_ME = " << c4 <<  endl;
	cout << "FINAL cost with large_best_climber = " << c_lbc <<  endl << endl;


	cout << "FINAL cost with large_ME = " << c5 << endl;
	cout << "FINAL cost with large_best = " << c6 <<   endl << endl;
	

//	cout << "FINAL cost with large_worst = " << c7 <<   endl;
//	cout << "FINAL cost with large_first = " << c8 <<   endl;


	cout << "seed was : " << s << endl;


	//write_res("costs.txt", c1, c2 );

	for (int i = 0; i < n; i++) {
		free(F[i]);
		free(D[i]);
	}

	free(D);
	free(F);




	// temp verification, hope it works
//	cout << "FINAL Cost with FIRST = " << calculate_cost(D,F,sol) << endl;
//	cout << "FINAL cost with MAX EXPAND = " << calculate_cost(D,F,sol2) << endl;

//	for (int i = 0; i < sol.size(); i++) cout << sol[i] << " ";
//	cout << endl;

	//int imax = std::numeric_limits<int>::max();
//	cout << "max value = " << imax << endl;


//	cout << "size of sol is " << sol.size() << endl;

/*	for (int i = 0; i < n; i++) {
		cout << sol[i] << " " ;
	}*/



	/*for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << " " << D[i][j];
		}
		cout << endl;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << " " << F[i][j];
		}
		cout << endl;
	}*/

	return 0;
}