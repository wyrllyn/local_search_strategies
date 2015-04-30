#include "parser.h"
#include "methods.h"
#include "ls.h"

#include <sstream>

vector<long> iter;
vector<long> me;
vector<pair<int,int> > vrank;

int main(int argc, char** argv) {
	int s = 100;
	int method = 1;
	string filename = "instances_50/20_10_01_ta011.txt";

	if (argc > 1) filename = argv[1];
	if (argc > 2) method = atoi(argv[2]);
	if (argc > 3) s = atoi(argv[3]);

	vector<string> fl = tokenize(filename, "/");

	int ** d;
	int njobs = 5;
	int nmach = 5;	

	vector<int> sol;

	srand(s);

	parse_fs(&d, &njobs, &nmach, filename);

	init(njobs, &sol);

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
			cout << "final = " << first_stoch(d, njobs, nmach, &sol);
			break;
		case 11:
			cout << "final = " << best_stoch(d, njobs, nmach, &sol);
			break;
		case 12:
			cout << "final = " << worst_stoch(d, njobs, nmach, &sol);
			break;
		case 13:
			cout << "final = " << me_stoch(d, njobs, nmach, &sol);
			break;
	}



	write_res(res, iter);
	if (me.size() > 0) write_res(res_me, me);
	if (vrank.size() > 0) write_res2(res_rank, vrank);
	

	cout << endl;
	for (int i = 0; i < sol.size(); i++) cout << sol[i] << " " ;
	cout << endl;


	for (int i = 0; i < njobs; i++) {
		free(d[i]);
	}
	free(d);


	return 0;
}