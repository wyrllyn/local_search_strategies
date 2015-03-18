#include "parser.h"

#include <sstream>


int main(int argc, char** argv) {
	int s = 100;
	int method = 1;
	string filename = "instances/20_5_01_ta001.txt";

	if (argc > 1) filename = argv[1];
	if (argc > 2) method = atoi(argv[2]);
	if (argc > 3) s = atoi(argv[3]);

	int ** d;
	int njobs;
	int nmach;

	parse_fs(&d, &njobs, &nmach, filename);

	for (int i = 0; i < njobs ; i++) {
		for (int j = 0; j < nmach; j++) {
			cout << d[i][j] << " ";
		}

		cout << endl;
	}

	for (int i = 0; i < njobs; i++) {
		free(d[i]);
	}
	free(d);



	return 0;
}