#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

void parse_qap(int*** D, int*** F, int * size, string filename);

vector<string> tokenize(string toSplit, string token);


#endif