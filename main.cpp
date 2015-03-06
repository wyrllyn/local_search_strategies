#include "ls.h"
#include "parser.h"
#include <limits>

int main(int argc, char** argv) {
	int s = time(NULL);
	srand(s);
	cout << "s = " << s << endl;
	string filename = "qapdata/tai50a.dat";
	int ** D;
	int ** F;
	int n;
	vector<int> sol;
	vector<int> sol2;
	vector<int> sol3;
	vector<int> sol4;
	vector<int> sol5;
	int64_t c1;
	int64_t c2;
	int64_t c3;
	int64_t c4;
	int64_t c5;

	if (argc > 1) filename = argv[1];

	parse_qap(&D, &F, &n, filename);

	init_sol(&sol, n);

	for (int i = 0; i < sol.size(); i++) {
		sol2.push_back(sol[i]);
		sol3.push_back(sol[i]);
		sol4.push_back(sol[i]);
		sol5.push_back(sol[i]);
	}

	c1 = ls_first(D,F,&sol);
	//c2 = ls_MEv2(D,F,&sol2);
	c2 = climber_best(D,F,&sol2);

	c3 = climber_worst(D,F,&sol3);

	c5 = ls_ME_climber(D,F,&sol5);

	c4 = ls_ME_large(D,F,&sol4);

//seed = 1425497434 => pb with max expand ?


	cout << "FINAL Cost with FIRST = " << c1  << "  = " << calculate_cost(D,F,sol) << endl;
	//cout << "FINAL cost with MAX EXPAND = " << c2 << endl;
	cout << "FINAL cost with climber_best = " << c2 << "  = " << calculate_cost(D,F,sol2) << endl;
	cout << "FINAL cost with climber_worst = " << c3 << "  = " << calculate_cost(D,F,sol3) << endl;
	cout << "FINAL cost with climber_ME = " << c5 << "  = " << calculate_cost(D,F,sol5) << endl;
	cout << "FINAL cost with large_ME = " << c4 << "  = " << calculate_cost(D,F,sol4) << endl;


	cout << "s = " << s << endl;


	//write_res("costs.txt", c1, c2 );




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