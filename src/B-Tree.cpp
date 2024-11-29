// Created by Erriana Thomas on 11/29/2024.
// #1 TO DO: Create B-Tree class/methods and store appropriate data in tree


#include "B-Tree.h"
#include <iostream>
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

void BTree::splitChild(BTreeNode* parent, int i, BTreeNode *child) {
    // creating a new node to store d-1 keys of the full child
    BTreeNode* newNode = new BTreeNode(child->isLeaf);
    for (int j = 0; j < d - 1; ++j) {
        newNode->cities.push_back(child->cities[d+j]);
        newNode->states.push_back(child->states[d+j]);
        newNode->precipitations.push_back(child->precipitations[d+j]);
        newNode->windSpeed.push_back(child->windSpeed[d+j]);
    }

    if (!child->isLeaf) {
        // moving other half of children to new node
        for (int j = 0; j < d; ++j) {
            newNode->cities.push_back(child->cities[d+j]);
        }
        child->children.resize(d);
    }

    // reducing size of the full child node
    child->cities.resize(d-1);
    child->states.resize(d-1);
    child->precipitations.resize(d-1);
    child->windSpeed.resize(d-1);

    // inserting a new child into parent
    parent->children.insert(parent->children.begin() + i + 1, newNode);

    // moving middle key up to parent node
    parent->cities.insert(parent->cities.begin() + i, child->cities[d - 1]);
    parent->states.insert(parent->states.begin() + i, child->states[d - 1]);
    parent->precipitations.insert(parent->precipitations.begin() + i, child->precipitations[d - 1]);
    parent->windSpeed.insert(parent->windSpeed.begin() + i, child->windSpeed[d - 1]);
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
        cout << "City: " << node->cities[i] << ", State: " << node->states[i] << ", Precipitation: " <<
            node->precipitations[i] << ", WindSpeed: " << node->windSpeed[i] << endl;
    }
    if(!node->isLeaf) { traverseHelper(node->children[node->cities.size()]); }
}

BTree::BTree(int minDegree) {
    root = nullptr;
    d = minDegree;
}

void BTree::insert(const string &city, const string &state, float precipitation, float windSpeed) {
    if(root == nullptr) {
        root = new BTreeNode(true);
        root->cities.push_back(city);
        root->states.push_back(state);
        root->precipitations.push_back(precipitation);
        root->windSpeed.push_back(windSpeed);
    } else {
        if (root->cities.size() == 2 * d - 1) {
            BTreeNode* newRoot = new BTreeNode(false);
            newRoot->children.push_back(root);
            splitChild(newRoot, 0, root);
            root = newRoot;
        }
        insertNonFullNode(root, city, state, precipitation, windSpeed);
    }
}



