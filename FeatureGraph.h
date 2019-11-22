#ifndef FEATURE_H
#define FEATURE_H


#include <string>
#include <vector>
#include <map>
#include "GraphHelper.h"


using namespace std;



class FeatureGraph {

 private:
  map<int, Node> nodes;
  map<int, vector<int>> neighbors;
  vector<Edge> edges;
  int skillsize;
  int numnodes;
  int numedges;

 public:
    // TODO add necessary private fields


    // Constructor
    // 
    // N: The number of nodes
    // d: the sizee of the skill vectors of all nodes
    // nodes: vector of nodes to insert
    // edges: vector of edges to insert
    FeatureGraph(int N, int d, vector<Node> nodes, vector<Edge> edges);


    //Insert node with given ID and feature vectors
    void insert(Node node);

    // insert given edge
    // May assume nodes in edge are already present
    void insert(Edge edge);

    void print();

    vector<int> getNeighbors(int nodeID);

    vector<float> getFeatures(int nodeID);

};  

#endif
