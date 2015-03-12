#include "ls.h"
#include "climbn.h"
#include "climbnun.h"
#include "climblarge.h"
#include "parser.h"
#include <limits>

int main(int argc, char** argv) {
	int s = 1000;
	int method = 12;
	string filename = "qapdata/nug30.dat";

	int ** D;
	int ** F;
	int n;

	vector<int> sol;
	int64_t cost = -1;

	if (argc > 1) filename = argv[1];
	if (argc > 2) method = atoi(argv[2]);
	if (argc > 3) s = atoi(argv[3]);

	srand(s);

	parse_qap(&D, &F, &n, filename);
	init_sol(&sol, n);
	cout << "INIT COST = " << calculate_cost(D,F,sol) << endl;

	switch(method) {
		case 1:
			cost = first(D,F,&sol);
			break;
		case 2:
			cost = best(D,F,&sol);
			break;
		case 3:
			cost = worst(D,F,&sol);
			break;
		case 4:
			cost = nun_first(D,F,&sol);
			break;
		case 5:
			cost = nun_best(D,F,&sol);
			break;
		case 6:
			cost = nun_ME(D,F, &sol);
			break;
		case 7:
			cost = large_first(D,F, &sol);
			break;
		case 8:
			cost = large_best(D,F, &sol);
			break;
		case 9:
			cost = large_worst(D,F, &sol);
			break;
		case 10:
			cost = ls_first(D,F, &sol);
			break;
		case 11:
			cost = ls_best(D,F, &sol);
			break;
		case 12:
			cost = ls_worst(D,F, &sol);
			break;
		case 13:
			cost = ls_ME(D,F, &sol);
			break;
	}

	

	cout << "FINAL Cost = " << cost  << " = " << calculate_cost(D,F,sol) <<   endl;

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