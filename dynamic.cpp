#include <iostream>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <climits>
#include "dynamic.h"
using namespace std;

int minTests(int cars, int speed, vector<vector<int>>& memArray, vector<vector<int>>& speedChoice, vector<vector<bool>>& isSuccess) {
    // Base cases
    if (speed == 0) {
        return 0;
    }
    if (speed == 5) {
        return 1;
    }
    if (cars == 1) {
        return speed / 5;  
    }

    //GRADING: REUSE
    if (memArray[cars][speed] != -1) {
        return memArray[cars][speed];
    }

    int bestTests = INT_MAX;
    int bestSpeed = 5;
    bool bestChoice = true;

    // Try each possible test speed
    for (int testSpeed = 5; testSpeed <= speed; testSpeed += 5) {
        int successCase = minTests(cars, speed - testSpeed, memArray, speedChoice, isSuccess);
        int failCase = minTests(cars - 1, testSpeed - 5, memArray, speedChoice, isSuccess);
        int maxTests = 1 + max(successCase, failCase);

        // Update if it is better than the best so far
        if (maxTests < bestTests) {
            bestTests = maxTests;
            bestSpeed = testSpeed;
            bestChoice = (successCase >= failCase);
        }
    }

    //GRADING: UPDATE
    speedChoice[cars][speed] = bestSpeed;
    isSuccess[cars][speed] = bestChoice;
    memArray[cars][speed] = bestTests;
    return bestTests;
}

void printTests(int cars, int speed, vector<vector<int>>& speedChoice, vector<vector<bool>>& isSuccess) {
    int test = 1;
    int remainingSpeed = speed;
    int remainingCars = cars;

    while (remainingSpeed > 0 && remainingCars > 0) {
        // Handle base cases
        if (remainingSpeed == 5 || remainingCars == 1) {
            while (remainingSpeed >= 5) {
                cout << test << ": " << remainingCars << " SUCCEED at test speed 5 (" << remainingSpeed << ")" << endl;
                remainingSpeed -= 5;
                test++;
            }
            break;
        }

        // Handle normal case
        int testSpeed = speedChoice[remainingCars][remainingSpeed];
        bool succeed = isSuccess[remainingCars][remainingSpeed];

        if (succeed) {
            cout << test << ": " << remainingCars << " SUCCEED at test speed " << testSpeed << " (" << remainingSpeed << ")" << endl;
            remainingSpeed -= testSpeed;
        }
        else {
            cout << test << ": " << remainingCars << " FAIL at test speed " << testSpeed << " (" << remainingSpeed << ")" << endl;
            remainingCars--;
            remainingSpeed = testSpeed - 5;
        }
        test++;
    }
}

int main(int argc, char* argv[]) {
    if (argc == 3) {
        int cars = atoi(argv[1]);
        int maxSpeed = atoi(argv[2]);

        vector<vector<int>> memArray(cars + 1, vector<int>(maxSpeed + 1, -1));
        vector<vector<int>> speedChoice(cars + 1, vector<int>(maxSpeed + 1, 0));
        vector<vector<bool>> isSuccess(cars + 1, vector<bool>(maxSpeed + 1, true));

        int totalTests = minTests(cars, maxSpeed, memArray, speedChoice, isSuccess);

        cout << "Total tests: " << totalTests << endl;

        printTests(cars, maxSpeed, speedChoice, isSuccess);

        return 0;
    }
    else if (argc == 2 && string(argv[1]) == "t") {
        // Number of cars (constant)
        int cars = 3;
        // Test Speeds 
        int maxTestSpeedIncrement = 25;
        int maxTestSpeedCount = 20;

        ofstream file("timing_analysis_results.csv");
        file << "Timing Analysis: Cars: " << cars << "\n";
        file << "Speed, Time(ms)" << "\n";

        for (int testSpeed = 0; maxTestSpeedCount >= 0; testSpeed += maxTestSpeedIncrement) {
            vector<vector<int>> memArray(cars + 1, vector<int>(testSpeed + 1, -1));
            vector<vector<int>> speedChoice(cars + 1, vector<int>(testSpeed + 1, 0));
            vector<vector<bool>> isSuccess(cars + 1, vector<bool>(testSpeed + 1, true));

            auto start_time = chrono::high_resolution_clock::now();

            int totalTests = minTests(cars, testSpeed, memArray, speedChoice, isSuccess);

            auto end_time = chrono::high_resolution_clock::now();

            chrono::duration<double, milli> time_elapsed = end_time - start_time;

            file << testSpeed << "," << time_elapsed.count() << "\n";

            maxTestSpeedCount -= 1;
        }

        return 0;
    }
    else {
        cerr << "Usage: <Number_of_Cars> <Max_Speed> OR t" << endl;
        return 1;
    }
}