#include "ls.h"
#include "parser.h"
#include <limits>

int main(int argc, char** argv) {
	int s = 1425497434;
	srand(s);
	cout << "s = " << s << endl;
	string filename = "qapdata/lipa50b.dat";
	int ** D;
	int ** F;
	int n;
	vector<int> sol;
	vector<int> sol2;
	int64_t c1;
	int64_t c2;

	if (argc > 1) filename = argv[1];

	parse_qap(&D, &F, &n, filename);

	init_sol(&sol, n);

	for (int i = 0; i < sol.size(); i++) {
		sol2.push_back(sol[i]);
	}

	c1 = ls_first(D,F,&sol);
	c2 = ls_ME(D,F,&sol2);

//seed = 1425497434 => pb with max expand ?


	cout << "FINAL Cost with FIRST = " << c1 << endl;
	cout << "FINAL cost with MAX EXPAND = " << c2 << endl;

	write_res("costs.txt", c1, c2 );

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