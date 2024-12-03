#include <iostream>
#include <vector>
#include <tuple>
#include "HashMap.h"
using namespace std;

class TempsMap{
private:
    //map with locations (strings) as keys and tuples storing day, month, and average temp for that week(all ints) as values
    HashMap temperatures;

public:
    int searchByCityAndDay(string city, int month, int day){
        for (auto data : temperatures[city]){
            //checks if the city data corresponds to the correct month and if the day inputted
            //is in the week corresponding to the data
            if(get<1>(data) == month && (day >= get<0>(data) && day <= get<0>(data)+7)){
                return get<2>(data);
            }
        }
    }
};
