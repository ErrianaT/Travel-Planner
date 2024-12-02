#include <iostream>
#include <map>
#include <vector>
#include <tuple>
using namespace std;

class TempsMap{
private:
    //map with locations (strings) as keys and tuples storing day, month, high, and low temp (all ints) as values
    unordered_map<string, vector<tuple<int, int, int, int>> temperatures;

public:
    void insert(string city, int month, int day, int high, int low){
        temperatures[city].push_back(make_tuple(month, day, high, low));
    }

    string findIdealCity(int month, int day, int high, int low){
        vector<string> result;
        for (auto city : temperatures){
            for (auto data : city.second){
                if(get<2>(data) <= high && get<3>(data) >= low && get<0>(data) == month && get<1>(data) == day){
                    result.push_back(city.first);
                }
            }
        }
    }
};
