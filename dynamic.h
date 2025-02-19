#ifndef DYNAMIC_H
#define DYNAMIC_H

#include <vector>
using namespace std;

// Function declarations
int minTests(int cars, int speed, vector<vector<int>>& memArray, vector<vector<int>>& speedChoice, vector<vector<bool>>& isSuccess);
void printTests(int cars, int speed, vector<vector<int>>& speedChoice, vector<vector<bool>>& isSuccess);

#endif