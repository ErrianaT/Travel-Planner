#include <iostream>
#include <vector>
#include <tuple>
#include "HashMap.cpp"
using namespace std;

class TempsMap{
private:
    //map with locations (strings) as keys and tuples storing day, month, and average temp for that week(all ints) as values
    HashMap temperatures;

public:
    //initialize w 72 buckets because there are 122 cities and the load size is 0.7 (122/0.7)
    TempsMap(){
        temperatures = HashMap(172);
    }
    int searchByCityAndDay(string city, int month, int day){
        for (auto data : temperatures[city]){
            //checks if the city data corresponds to the correct month and if the day inputted
            //is in the week corresponding to the data
            if(get<1>(data) == month && (day >= get<0>(data) && day <= get<0>(data)+7)){
                return get<2>(data);
            }
        }
    }
    void insert(string key, tuple<int,int,int>value){
        temperatures[key].push_back(value);
    }

    vector<tuple<int,int,int>>& operator[](const string& key){
        return temperatures[key];
    }
};
