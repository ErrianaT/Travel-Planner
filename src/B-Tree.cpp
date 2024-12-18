// Created by Erriana Thomas on 11/29/2024.
// #1 TO DO: Create B-Tree class/methods and store appropriate data in tree


#include "B-Tree.h"
#include <sstream>
#include <iostream>
using namespace std;

void BTree::insertNonFullNode(BTreeNode *node, const string &city, const string &state, float precipitation, float windSpeed, int temperature) {
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
        node->temperatures.insert(node->temperatures.begin() + i, temperature);
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
        insertNonFullNode(node->children[i], city, state,  precipitation, windSpeed, temperature);
    }
}

void BTree::splitChild(BTreeNode* parent, int i, BTreeNode *child) {
    BTreeNode* newNode = new BTreeNode(child->isLeaf);

    // moving second half to new node
    for (int j = d; j < 2 * d - 1; ++j) {
        newNode->cities.push_back(child->cities[j]);
        newNode->states.push_back(child->states[j]);
        newNode->precipitations.push_back(child->precipitations[j]);
        newNode->windSpeed.push_back(child->windSpeed[j]);
        newNode->temperatures.push_back(child->temperatures[j]);
    }

    // moving children pointers if node is not a leaf
    if (!child->isLeaf) {
        for (int j = d; j < 2 * d; ++j) {
            newNode->children.push_back(child->children[j]);
        }
    }

    // resizing
    child->cities.resize(d - 1);
    child->states.resize(d - 1);
    child->precipitations.resize(d - 1);
    child->windSpeed.resize(d - 1);
    child->children.resize(d);  // Only resize if the child is not a leaf

    // inserting new node into parent
    parent->children.insert(parent->children.begin() + i + 1, newNode);

    // moving middle key of child to parent node
    parent->cities.insert(parent->cities.begin() + i, child->cities[d - 1]);
    parent->states.insert(parent->states.begin() + i, child->states[d - 1]);
    parent->precipitations.insert(parent->precipitations.begin() + i, child->precipitations[d - 1]);
    parent->windSpeed.insert(parent->windSpeed.begin() + i, child->windSpeed[d - 1]);
    parent->temperatures.insert(parent->temperatures.begin() + i, child->temperatures[d - 1]);
}


void BTree::traverse() {
    traverseHelper(root);
}

void BTree::traverseHelper(BTreeNode *node) {
    if(node == nullptr) {
        return;
    }

    for (size_t i = 0; i < node->cities.size(); ++i) {
        if (!node->isLeaf) {
            traverseHelper(node->children[i]);
        }
        cout << node->cities[i] << ", " << node->states[i] << ", " << node->precipitations[i] << " inches, " <<
            node->windSpeed[i] << " mph" << node->temperatures[i] << " F"<< endl;
    }
    if(!node->isLeaf) { traverseHelper(node->children[node->cities.size()]); }
}

BTree::BTree(int minDegree) {
    root = nullptr;
    d = minDegree;
}

void BTree::insert(const string &city, const string &state, float precipitation, float windSpeed, int temperature) {
    if(root == nullptr) {
        root = new BTreeNode(true);
        root->cities.push_back(city);
        root->states.push_back(state);
        root->precipitations.push_back(precipitation);
        root->windSpeed.push_back(windSpeed);
        root->temperatures.push_back(temperature);
    } else {
        if (root->cities.size() == 2 * d - 1) {
            BTreeNode* newRoot = new BTreeNode(false);
            newRoot->children.push_back(root);
            splitChild(newRoot, 0, root);
            root = newRoot;
        }
        insertNonFullNode(root, city, state, precipitation, windSpeed, temperature);
    }
}

string BTree::searchByCity(BTreeNode* node, const string& city) {
    int i = 0;

    // Traversing the cities in the current node
    while (i < node->cities.size() && city > node->cities[i]) {
        ++i;
    }

    // If we find the city at the current index
    if (i < node->cities.size() && city == node->cities[i]) {
        ostringstream result;
        result << "City: " << city << "\n"
               << "State: " << node->states[i] << "\n"
               << "Precipitation: " << node->precipitations[i] << " inches\n"
               << "WindSpeed: " << node->windSpeed[i] << " mph\n"
               << "Average Temperature: " << node->temperatures[i] << " F"<< endl;
        return result.str();
    }


    // If it's a leaf node, the city is not found
    if (node->isLeaf) {
        return ""; 
    }

    return searchByCity(node->children[i], city);
}

string BTree::searchCity(const string& city) {
    string result = searchByCity(root, city);

    if (!result.empty()) {
        return result;
    }

    return "Location is not available.";
}
