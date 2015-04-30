#include "parser.h"

void parse_fs(int*** d, int* nj, int * nm, string filename) {
	ifstream file(filename.c_str(), ios::in); 
	int i_job = 0;
	int curser = 0;

	*nj = -1;
	*nm = -1;

	bool alloc = false;

    int cmp = 0;
	if(file) {
		string line;
    	vector<string> tempVect;
        while(getline(file, line)) {
            cmp++;
           // cout << cmp << endl;
        	tempVect = tokenize(line, " ");
        	if (*nj == -1 && *nm == -1) {
        		*nj = atoi(tempVect[0].c_str());
        	}
        	else if (*nm == -1) {
        		*nm = atoi(tempVect[0].c_str());
        	}
        	else {

        		//cout << "nj = " << *nj << " nm = " << *nm << endl;
        		if (!alloc) {
        			(*d) = (int**)malloc(sizeof(int*) * (*nj));
                  //  cout << "here" << endl;
        			for (int i = 0; i < (*nj); i++) {
                       // cout << "here + " << i << endl;
        				(*d)[i] = (int*) malloc(sizeof(int) * (*nm));
        			}
        			alloc = true;
        		}
        		if (atoi(tempVect[0].c_str()) == i_job) {
        			curser++;
        			continue;
        		}
        		if (curser == 1) {
        			curser++;
        			continue;
        		}
        		if (curser == 2) {
        			for(int i = 0; i < tempVect.size(); i++) {
                         
        				if (i < (*nm)) {
                            //cout << i_job << " " << i << endl;
                            (*d)[i_job][i] = atoi(tempVect[i].c_str());
                        } 
        			}

        			curser = 0;
        			i_job ++;
        		}


        	}
        }
        file.close();

	}
	else {
		cerr << "Could not open file : " << filename << endl;
	}

}

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


void write_res(string fileName, vector<long> iter) {
    ofstream ofs(fileName.c_str(), ios::app); 

    if(ofs) {  
        for (int i = 0; i < iter.size(); i++)
          ofs << i << " " << (long)iter[i]<< " " << endl;
        ofs << endl;
        ofs.close();
    }
}

void write_res2(string fileName, vector<pair<int,int> > iter) {

    ofstream ofs(fileName.c_str(), ios::app); 

    if(ofs) {  
        for (int i = 0; i < iter.size(); i++)
          ofs << i << " " << iter[i].first<< " " << iter[i].second << endl;
      ofs << endl;
        ofs.close();
    }
}