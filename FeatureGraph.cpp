#include <string>
#include <vector>
#include "FeatureGraph.h"
#include "GraphHelper.h"
#include <map>
#include <iterator>
#include <iostream>
#include <cmath>

using namespace std;

FeatureGraph::FeatureGraph(int N, int d, vector<Node> nodes, vector<Edge> edges) {
  this->edges = edges;
  for(int i = 0; i < N; i++){
    (this->nodes).insert(pair<int, Node>((nodes[i]).id, Node(nodes[i].id, nodes[i].features)));
  }
  skillsize = d;
  numnodes = N;
  numedges = edges.size();
  map<int, Node>::iterator itr;
  vector<int> empty(0);
  for(itr = this->nodes.begin(); itr != this->nodes.end(); itr++){
    neighbors.insert(pair<int, vector<int>>(itr->first, empty));
  }
  for(int i = 0; i < numedges; i++){
    neighbors[(edges[i]).IdA].push_back((edges[i]).IdB);
    neighbors[(edges[i]).IdB].push_back((edges[i]).IdA);
  }
};

void FeatureGraph::insert(Node node){
  nodes.insert(pair<int, Node>(node.id, Node(node.id, node.features)));
  numnodes++;
  vector<int> empty(0);
  neighbors[node.id] = empty;
};
    
void FeatureGraph::insert(Edge edge){
  edges.push_back(edge);
  numedges++;
  neighbors[edge.IdA].push_back(edge.IdB);
  neighbors[edge.IdB].push_back(edge.IdA);
};

void FeatureGraph::print(){
  cout << "Edges\n-------\n";
  for(unsigned int i = 0; i < edges.size(); i++){
    cout << "(" << (edges[i]).IdA << ", " << (edges[i]).IdB << ") ";
  }
  cout << endl << endl;
  map<int, vector<int>>::iterator itr;
  cout << "Nodes\n-------\n";
  cout << "nodeID\t\tneighbors\n";
  for(itr = neighbors.begin(); itr != neighbors.end(); itr++){
    cout << itr->first << "\t\t";
    for(unsigned int i = 0; i < (itr->second).size(); i++){
      cout << (itr->second)[i] << " ";
    }
    cout << endl;
  }
  cout << endl;
};

vector<int> FeatureGraph::getNeighbors(int nodeID){
  return neighbors[nodeID];
};

vector<float> FeatureGraph::getFeatures(int nodeID){
  Node n = nodes.lower_bound(nodeID)->second;
  return n.features;
};

int FeatureGraph::diameter(){
  return 0; // STUB
}

int FeatureGraph::maxDistance(int nodeID){
  return 0; // STUB
}

int FeatureGraph::distance(int nodeIdA, int nodeIdB){
  return 0; // STUB
}

