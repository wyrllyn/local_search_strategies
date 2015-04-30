#include "ls.h"
#include "climbn.h"
#include "climbnun.h"
#include "climblarge.h"
#include "parser.h"
#include <sstream>
#include <limits>

vector<long> iter;
vector<long> me;
vector<pair<int,int> > vrank;

int main(int argc, char** argv) {
	int s = 100;
	int method = 16;
	string filename = "instances/bur26a.dat";
	vector<string> fl;
	

	int ** D;
	int ** F;
	int n;

	vector<int> sol;
	long cost = -1;

	if (argc > 1) filename = argv[1];
	if (argc > 2) method = atoi(argv[2]);
	if (argc > 3) s = atoi(argv[3]);

	fl = tokenize(filename, "/");

	srand(s);

	//cout << "file is " << filename << endl;

	parse_qap(&D, &F, &n, filename);
	init_sol(&sol, n);



//////////////////////
	///////////////////////////////////
	std::stringstream ssr;
	ssr << "res/" << fl[1] << "-m" << method <<"-s" << s << "-iter.txt";
	string res = ssr.str();

	std::stringstream ssm;
	ssm << "res/" << fl[1] << "-m" << method <<"-s" << s <<  "-me.txt";
	string res_me = ssm.str();

	std::stringstream ssra;
	ssra<< "res/" << fl[1] << "-m" << method <<"-s" << s <<  "-rank.txt";
	string res_rank = ssra.str();
////////////////////////////////
	///////////////////////////////////

	cout << res << endl;


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
		case 14: // this one was used not 13 or 15
			cost = ls_ME2(D,F, &sol);
			break;
		case 15: 
			cost = ls_MEmax(D,F, &sol);
			break;
		case 16:
			cost = stoch_first(D,F, &sol);
			break;
		case 17:
			cost = stoch_best(D,F, &sol);
			break;
		case 18:
			cost = stoch_worst(D,F, &sol);
			break;
		case 19:
			cost = stoch_ME(D,F, &sol);
			break;

	}

	

	//cout << "FINAL Cost = " << cost  << " = " << calculate_cost(D,F,sol) <<   endl;

	write_res(res, iter);
	if (me.size() > 0) write_res(res_me, me);
	if (vrank.size() > 0) write_res2(res_rank, vrank);

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