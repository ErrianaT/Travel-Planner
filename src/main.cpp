#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "B-Tree.h"
#include <algorithm>  // For std::remove and std::erase
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
        string avgTemp, maxTemp, minTemp, windDirection, temp, windSpeedStr;

        // reading each value into corresponding variable
        getline(ss, precipitationStr, ',');  // Data.Precipitation
        getline(ss, dateFull, ',');          // Date.Full
        getline(ss, dateMonth, ',');         // Date.Month
        getline(ss, dateWeek, ',');          // Date.Week of
        getline(ss, dateYear, ',');          // Date.Year
        getline(ss, city, ',');              // Station.City
        getline(ss, stationCode, ',');       // Station.Code
        getline(ss, stationLocation, ',');   // Station.Location
        getline(ss, state, ',');             // Station.State
        getline(ss, avgTemp, ',');           // Data.Temperature.Avg Temp
        getline(ss, maxTemp, ',');           // Data.Temperature.Max Temp
        getline(ss, minTemp, ',');           // Data.Temperature.Min Temp
        getline(ss, windDirection, ',');     // Data.Wind.Direction
        getline(ss, temp, ',');               // placeholder
        getline(ss, windSpeedStr, ',');      // Data.Wind.Speed

        // removing quotation marks
        precipitationStr.erase(remove(precipitationStr.begin(), precipitationStr.end(), '"'), precipitationStr.end());
        windSpeedStr.erase(remove(windSpeedStr.begin(), windSpeedStr.end(), '"'), windSpeedStr.end());

        // converting precipitation and windspeed to floats
        float precipitation = (stof(precipitationStr));
        float windSpeed = (stof(windSpeedStr));

        // inserting into B tree
        tree.insert(city, state, precipitation, windSpeed);
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
