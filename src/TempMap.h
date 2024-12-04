#ifndef TEMPMAP_H
#define TEMPMAP_H
#include <iostream>
#include <vector>
#include <tuple>
#include <list>
#include <functional>
#include <stdexcept>
using namespace std;

class TempsMap {
private:
    //define a bucket as a list of key-value pairs
    vector<list<pair<string, vector<tuple<int, int, int>>>>> buckets;
    int size;
    int numElements;

    //hash function to generate a hash index for the given key (city)
    int hashFunction(const string& key) const {
        hash<string> hashFn;
        return hashFn(key) % size;
    }

    //resize the hash table when there are too many elements
    void resize() {
        int newSize = size * 2;
        vector<list<pair<string, vector<tuple<int, int, int>>>>> newBuckets(newSize);
        for (const auto& bucket : buckets) {
            for (const auto& pair : bucket) {
                int newIndex = hash<string>()(pair.first) % newSize;
                newBuckets[newIndex].emplace_back(pair);
            }
        }
        buckets = move(newBuckets);
        size = newSize;
    }

public:
    //constructor for the hash map
    TempsMap(int bucketSize = 10) : size(bucketSize), numElements(0) {
        buckets.resize(size);
    }

    void insert(const string& key, const vector<tuple<int, int, int>>& value) {
        if ((float)numElements / size > 0.7) {
            resize();
        }

        int index = hashFunction(key);
        auto& bucket = buckets[index];
        for (auto& pair : bucket) {
            if (pair.first == key) {
                pair.second = value; //updating the value if the key exists
                return;
            }
        }
        bucket.emplace_back(key, value); //insert a new pair
        numElements++;
    }

    const vector<tuple<int, int, int>>& get(const string& key) const {
        int index = hashFunction(key);
        const auto& bucket = buckets[index];
        for (const auto& pair : bucket) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        throw runtime_error("Key not found: " + key);
    }

    //overloaded [] operator to access city data directly and add it if not present
    vector<tuple<int, int, int>>& operator[](const string& key) {
        int index = hashFunction(key);
        auto& bucket = buckets[index];
        for (auto& pair : bucket) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        // If the key doesn't exist, return an empty vector
        bucket.emplace_back(key, vector<tuple<int, int, int>>{});
        numElements++;
        if ((float)numElements / size > 0.7) {
            resize();
            index = hashFunction(key);
        }
        return bucket.back().second;
    }

    // Function to search by city and day and return the temperature
    int searchByCityAndDay(const string& city, int day) {
        // Retrieve the vector of tuples for the specified city
        vector<tuple<int, int, int>> cityData;
        try {
            cityData = get(city);
        } catch (const out_of_range& e) {
            cout << "City not found: " << city << endl;
            return -1;
        }

        // Iterate through the vector of tuples and check if the day is within the range of the week
        for (const auto& data : cityData) {
            int startDay = std::get<0>(data);
            int endDay = startDay + 7;  
            if (day >= startDay && day <= endDay) {
                return std::get<2>(data);  //returning the temperature
            }
        }

        // If no matching data is found
        cout << "No data found for the specified day." << endl;
        return -1;
    }

};

#endif // TEMPMAP_H
