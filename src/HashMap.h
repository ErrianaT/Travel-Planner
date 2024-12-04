//implementing a map from scratch to store each cities average temp for every week
#include <iostream>
#include <vector>
#include <tuple>
#include <list>
using namespace std;

class HashMap{
private:
    //define a bucket as a list of key-value pairs
    vector<list<pair<string, vector<tuple<int,int,int>>>>> buckets;
    int size;
    int numElements;
    //gives each string key a unique numerical index for the list
    int hashFunction(const string& key) const{
        hash<string> hashFn;
        return hashFn(key) % size;
    }
    //resizes the hash table when there are too many elements
    void resize(){
        int newSize = size * 2;
        vector<list<pair<string, vector<tuple<int,int,int>>>>> newBuckets(newSize);
        for (auto bucket : buckets) {
            for (auto pair : bucket) {
                int newIndex = hash<string>()(pair.first) % newSize;
                newBuckets[newIndex].emplace_back(pair);
            }
        }
        buckets = newBuckets;
        size = newSize;
    }
public:
    //constructor for the hashmap
    HashMap (int bucketSize){
        size = bucketSize;
        buckets.resize(size);
    }
    //inserts or updates a key-value pair
    void insert(string key, vector<tuple<int, int, int>> value){
        //resizes the hashmap to maintain the load factor
        if(float(numElements) / size > 0.7){
            resize();
        }
        int index = hashFunction(key);
        auto& bucket = buckets[index];
        for(auto pair : bucket){
            if(pair.first == key){
                pair.second = value;
                return;
            }
        }
        bucket.emplace_back(key, value);
        numElements++;
    }
    //returns the vector of tuples associated with a certain city
    vector<tuple<int,int,int>> get(const string& key) const{
        int index = hashFunction(key);
        auto bucket = buckets[index];
        for(const auto& pair : bucket){
            if(pair.first == key){
                return pair.second;
            }
        }
    }

    vector<tuple<int,int,int>>& operator[](const string& key){
        int index = hashFunction(key);
        auto& bucket = buckets[index];
        for(auto& pair : bucket){
            if(pair.first == key){
                return pair.second;
            }
        }
        bucket.emplace_back(key, vector<tuple<int,int,int>>);
        numElements++;
        if((float)numElements / size > 0.7){
            resize();
            index = hashFunction(key);
            bucket = buckets[index];
        }
        return bucket.back().second;
    }


};
