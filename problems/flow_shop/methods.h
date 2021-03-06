#ifndef METHODS_H
#define METHODS_H

#include <vector>
#include <iostream>
#include <cstdlib>

#include <algorithm>

using namespace std;

void init(int jobs, vector<int> * sol);

bool isInto(vector<int> s, int n);

long tft(int **d, int jobs, int machs, vector<int> sol);

long getMax(vector<long> v);

long costf(int **d, int jobs, int machs, vector<int> sol);

int ran(vector<long> v, long c);

#endif