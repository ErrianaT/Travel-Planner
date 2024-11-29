// Created by Erriana Thomas on 11/29/2024.
// #2 TO DO: Create B-Tree class/methods and store appropriate data in tree

// #1 TO DO: Read and access data from weather.csv file
#include "B-Tree.h"
using namespace std;

void BTree::insertNonFullNode(BTreeNode *node, const string &city, const string &state, float precipitation, float windSpeed) {
    int i = node->cities.size() - 1;

    if (node->isLeaf) {
        while(i >= 0 && city < node->cities[i]) { // insert key in sorted order into leaf node
            --i;
        }
        ++i;
        node->cities.insert(node->cities.begin() + i, city);
        node->states.insert(node->states.begin() + i, state);
        node->precipitations.insert(node->precipitations.begin() + i, precipitation);
        node->windSpeed.insert(node->windSpeed.begin() + i, windSpeed);
    } else { // finding child that will take new key
        while (i >= 0 && city < node->cities[i]) {
            --i;
        }
        ++i;
        if(node->children[i]->cities.size() == 2 * d - 1) { // splitting child if full
            splitChild(node, i, node->children[i]);
            if(city > node->cities[i]) { // deciding which child to go into
                ++i;
            }
        }
        insertNonFullNode(node->children[i], city, state,  precipitation, windSpeed);
    }
}




