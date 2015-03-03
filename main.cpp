#include "ls.h"
#include "parser.h"
#include <limits>

int main(int argc, char** argv) {
	int s = time(NULL);
	srand(s);
	cout << "s = " << s << endl;
	string filename = "qapdata/lipa50a.dat";
	int ** D;
	int ** F;
	int n;
	vector<int> sol;

	if (argc > 1) filename = argv[1];

	parse_qap(&D, &F, &n, filename);

	init_sol(&sol, n);

	for (int i = 0; i < sol.size(); i++) cout << sol[i] << " ";
	cout << endl;


	cout << "final cost = " << ls_first(D,F,&sol) << endl;

	for (int i = 0; i < sol.size(); i++) cout << sol[i] << " ";
	cout << endl;

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