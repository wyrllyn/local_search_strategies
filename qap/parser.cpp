#include "parser.h"

void parse_qap(int*** D, int*** F, int * size, string filename) {
	ifstream file(filename.c_str(), ios::in); 
	(*size) = 0;
	int t_i = 0;
	int t_j = 0;
	bool d_filled = false;
 
    if(file)
    {     
    	string line;
    	vector<string> tempVect;
        while(getline(file, line)) {
        	//cout << line << endl;
        	tempVect = tokenize(line, " ");
        	//cout << "size " << tempVect.size() << endl;
        	if ((*size) == 0) {
        		(*size) = atoi(tempVect[0].c_str());
        		if ((*size) > 0) {
        			//cout << "size = " << (*size) << endl;
        			(*D) = (int**) malloc(sizeof(int*) * (*size));
        			(*F) = (int**) malloc(sizeof(int*) * (*size));
        			for (int i = 0; i < (*size) ; i++) {
        				(*D)[i] = (int*) malloc(sizeof(int)* (*size));
        				(*F)[i] = (int*) malloc(sizeof(int)* (*size));
        			}
        		}
        	} 
        	else {
        		if(!d_filled) {
        			if(tempVect.size() > 1) {
        				for (int i = 0; i < tempVect.size(); i++) {
        					(*D)[t_i][t_j] = atoi(tempVect[i].c_str());
        					if (t_j == (*size) - 1) {
        						t_j = 0;
        						t_i ++;
        					}
        					else t_j++;
        				}
        			}
        			if(t_i > (*size) - 1) {
        				d_filled = true;
        				t_i = 0;
        				t_j = 0;
        			}
        		}
        		else {
					if(tempVect.size() > 1) {
        				for (int i = 0; i < tempVect.size(); i++) {
        					(*F)[t_i][t_j] = atoi(tempVect[i].c_str());
        					if (t_j == (*size) - 1) {
        						t_j = 0;
        						t_i ++;
        					}
        					else t_j++;
        				}
        			}
        			if (t_i > (*size) - 1) break;
        		}
        	}
        }    
        file.close();
    }
    else {
   		cerr << "Could not open file" << endl;
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

void write_res(string fileName, vector<float> iter) {

   // cout << "test" << endl;
  //  ofstream ofs;
    
 //   ofs.open(fileName, ios::out /*| ios::app*/);

    ofstream ofs(fileName.c_str(), ios::app); 

    if(ofs) {  
        for (int i = 0; i < iter.size(); i++)
          ofs << i << " " << (long)iter[i]<< " " << endl;
        ofs << endl;
        ofs.close();
    }
}

void write_res2(string fileName, vector<pair<int,int> > iter) {

   // ofstream ofs;
    ofstream ofs(fileName.c_str(), ios::app); 
    
  //  ofs.open(fileName, ios::out /*| ios::app*/);

    if(ofs) {  
        for (int i = 0; i < iter.size(); i++)
          ofs << i << " " << iter[i].first<< " " << iter[i].second << endl;
      ofs << endl;
        ofs.close();
    }
}