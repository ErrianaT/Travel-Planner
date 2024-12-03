// Created by Erriana Thomas on 11/29/2024.
// #1 TO DO: Create B-Tree class/methods and store appropriate data in tree

#ifndef B_TREE_H
#define B_TREE_H
#include <vector>
#endif //B_TREE_H

#include <string>
using namespace std;

struct BTreeNode {
    vector<string> cities; // cities
    vector<string> states; // states corresponding to cities
    vector<int> temperatures; // temperature of the states
    vector<float> precipitations; // average precipitation in inches
    vector<float> windSpeed; // average windspeed in mph
    vector<BTreeNode*> children; // pointers to child nodes
    bool isLeaf; // true if node is a lead
    BTreeNode(bool leaf) {
        isLeaf = leaf;
    }
};

class BTree {
private:
    BTreeNode* root;
    int d; // Minimum degree of B-tree
    void insertNonFullNode(BTreeNode* node, const string& city, const string& state, float precipitation, float windSpeed, int temperature);
    void splitChild(BTreeNode* parent, int i, BTreeNode* child);
    void traverseHelper(BTreeNode* node);
    string searchByCity(BTreeNode* node, const string& city);

public:
    explicit BTree(int minDegree);
    void insert(const string& city, const string& state, float precipitation, float windSpeed, int temperature);
    void traverse();
    string searchCity(const string& city);
};
