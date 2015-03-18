#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

void parse_fs(int*** d, int* nj, int * nm, string filename);

vector<string> tokenize(string toSplit, string token);

#endif