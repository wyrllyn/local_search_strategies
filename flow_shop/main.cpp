#include "parser.h"
#include "methods.h"
#include "ls.h"

#include <sstream>


int main(int argc, char** argv) {
	int s = time(NULL)/* 100*/;
	int method = 9;
	string filename = "instances/20_15_01.txt";

	if (argc > 1) filename = argv[1];
	if (argc > 2) method = atoi(argv[2]);
	if (argc > 3) s = atoi(argv[3]);

	int ** d;
	int njobs;
	int nmach;

	vector<int> sol;

	srand(s);

	cout << "test" << endl;

	parse_fs(&d, &njobs, &nmach, filename);

	init(njobs, &sol);	

	switch(method) {
		case 1:
			cout << "final = " << first(d, njobs, nmach, &sol);
			break;
		case 2:
			cout << "final = " << best(d, njobs, nmach, &sol);
			break;
		case 3:
			cout << "final = " << worst(d, njobs, nmach, &sol);
			break;
		case 4:
			cout << "final = " << nun_first(d, njobs, nmach, &sol);
			break;
		case 5:
			cout << "final = " << nun_best(d, njobs, nmach, &sol);
			break;
		case 6:
			cout << "final = " << nun_me(d, njobs, nmach, &sol);
			break;
		case 7:
			cout << "final = " << large_first(d, njobs, nmach, &sol);
			break;
		case 8:
			cout << "final = " << large_best(d, njobs, nmach, &sol);
			break;
		case 9:
			cout << "final = " << large_worst(d, njobs, nmach, &sol);
			break;
		case 10:
			break;
		case 11:
			break;
		case 12:
			break;
		case 13:
			break;
	}


	

	cout << endl;
	for (int i = 0; i < sol.size(); i++) cout << sol[i] << " " ;
	cout << endl;






	for (int i = 0; i < njobs; i++) {
		free(d[i]);
	}
	free(d);



	return 0;
}