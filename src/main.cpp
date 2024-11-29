// Created by Erriana Thomas on 11/29/2024.
// #1 TO DO: Read and access data from weather.csv file
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "B-Tree.h"
using namespace std;


void readFile(const string& filename, BTree& tree) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    // skipping the header line
    getline(file, line);

    while (getline(file, line)) {
        stringstream ss(line);

        // declaring variables for all columns
        string precipitationStr, dateFull, dateMonth, dateWeek, dateYear;
        string city, stationCode, stationLocation, state;
        string avgTemp, maxTemp, minTemp, windDirection, windSpeedStr;

        // reading each value into corresponding variable
        getline(ss, precipitationStr, ',');
        getline(ss, dateFull, ',');
        getline(ss, dateMonth, ',');
        getline(ss, dateWeek, ',');
        getline(ss, dateYear, ',');
        getline(ss, city, ',');
        getline(ss, stationCode, ',');
        getline(ss, stationLocation, ',');
        getline(ss, state, ',');
        getline(ss, avgTemp, ',');
        getline(ss, maxTemp, ',');
        getline(ss, minTemp, ',');
        getline(ss, windDirection, ',');
        getline(ss, windSpeedStr, ',');

        // Try converting precipitation and windspeed to floats
        int precipitation = stoi(precipitationStr);
        int windSpeed = stoi(windSpeedStr);

        tree.insert(city, state, (float)precipitation, (float)windSpeed);
    }

    file.close();
}

int main() {
    BTree btree(3);

    try {
        readFile("../data/weather.csv", btree);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    btree.traverse();
    return 0;
}