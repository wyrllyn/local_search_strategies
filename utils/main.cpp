#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

vector<string> tokenize(string toSplit, string token) {
    int pos;
    vector<string> result;
    while ((pos = toSplit.find(token)) != string::npos) {
        string nuString = toSplit.substr(0, pos);
    if (!nuString.empty()) {
        result.push_back(nuString);
    }
        toSplit = toSplit.substr(pos + 1);
    }
    result.push_back(toSplit);
    return result;
}

void parse(vector<float> * res, string filename) {
	ifstream file(filename.c_str(), ios::in); 

	if(file) {
		string line;
		vector<string> tempVect;
 		while(getline(file, line)) {
			//cout << line << endl;
 			tempVect = tokenize(line, " ");
 			(*res).push_back(atoi(tempVect[0].c_str()));
 		}
		file.close();
	}
	else {
		cout << "error : cannot open file " << filename << endl;
	}
}

float min(vector<float> res) {
	float tmp = res[0];
	for (int i = 1; i < res.size(); i++) {
		if (res[i] < tmp) tmp = res[i];
	}
	return tmp;

}

float max(vector<float> res) {
	float tmp = res[0];
	for (int i = 1; i < res.size(); i++) {
		if (res[i] > tmp) tmp = res[i];
	}
	return tmp;
}

float avg(vector<float> res) {
	float tmp = res[0];
	for (int i = 1; i < res.size(); i++) {
		tmp += res[i];
	}
	tmp = (float)(tmp / (float) res.size());
	return tmp;
}



int main(int argc, char** argv) {
	string filename = " ";

	if (argc > 1) filename = argv[1];
	vector<float> res;
	parse(&res, filename);

	cout << " size = " << res.size() << endl;

	cout << "avg = " <<  fixed << avg(res) << endl;

	//for (int i = 0; i < res.size() ; i++) cout << res[i] << endl;




}