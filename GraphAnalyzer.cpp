#include "GraphHelper.h"
#include "FeatureGraph.h"
#include "GraphAnalyzer.h"
#include <algorithm>
#include <utility>
#include <iterator>
#include <cmath>
#include <unordered_set>
#include <queue>
#include <vector>

using namespace std;

// helper sort method
bool sortBackwards(const pair<float,int> &one,
           const pair<float,int> &two)
{
  return (one.first > two.first);
}

// helper heapify method
bool operator < (const Triangle &one, const Triangle &other) {
  return (((one.edgeA).weight + (one.edgeB).weight + (one.edgeC).weight) <
      ((other.edgeA).weight + (other.edgeB).weight + (other.edgeC).weight));
}

GraphAnalyzer::GraphAnalyzer(FeatureGraph& G) {
    this->G = G;
    G.initializeTriangles();
    openTrianglesMaxHeap = priority_queue<Triangle>();
    vector<Triangle> temp = G.getOpenTriangles();
    for(Triangle x : temp) openTrianglesMaxHeap.push(x);
}

void GraphAnalyzer::insert(Node n) {
  G.insert(n);
  // TODO Adjust calculations for ratio of open triangles and topKtriangles
    
  // RELOADS all the triangles appropriately
  G.initializeTriangles();
  openTrianglesMaxHeap = priority_queue<Triangle>();
  vector<Triangle> temp = G.getOpenTriangles();
  for(Triangle x : temp) openTrianglesMaxHeap.push(x);
};

void GraphAnalyzer::insert(Edge e) {
  G.insert(e);
  // TODO Adjust calculations for ratio of open triangles and topKtriangles
    
  // RELOADS all the triangles appropriately
  G.initializeTriangles();
  openTrianglesMaxHeap = priority_queue<Triangle>();
  vector<Triangle> temp = G.getOpenTriangles();
  for(Triangle x : temp) openTrianglesMaxHeap.push(x);
};

int GraphAnalyzer::diameter() {
    return G.diameter();
};


float GraphAnalyzer::openClosedTriangleRatio() {
    int open = G.numOpenTriangles();
    int closed = G.numClosedTriangles();
    if(closed == 0) return -1;
    return (open * 1.0) / closed;
};

string GraphAnalyzer::topKOpenTriangles(int k) {
    vector<Triangle> temp;
    string result = "";
    int loop;
    if(openTrianglesMaxHeap.size() > k) loop = k;
    else loop = openTrianglesMaxHeap.size();
    for(int i = 0; i < loop; i++){
        Triangle t = openTrianglesMaxHeap.top();
        temp.push_back(t);
        result += t.getID();
        if(i != loop - 1) result += ";";
        openTrianglesMaxHeap.pop();
    }
    for(Triangle x : temp) openTrianglesMaxHeap.push(x);
    return result;
};


vector<int> GraphAnalyzer::topKNeighbors(int nodeID, int k,  vector<float> w) {
  vector<pair<float,int>> dots(0);
  vector<int> result(0);
  vector<int> neighborIDs = G.getNeighbors(nodeID);
  vector<float> feats;
  float sum(0);
  
  for(unsigned int i = 0; i < neighborIDs.size(); i++){
    feats.resize(0);
    feats = G.getFeatures(neighborIDs[i]);
    for(unsigned int j = 0; j < w.size(); j++){
      sum += (feats[j] * w[j]);
    }
    dots.push_back(pair<float,int>(sum,neighborIDs[i]));
    sum = 0;
  }
  sort(dots.begin(), dots.end(), sortBackwards);
  
  int loop;
  if(dots.size() > k) loop = k;
  else loop = dots.size();
  
  for(int i = 0; i < loop; i++){
    result.push_back(dots[i].second);
  }
  return result;
};


int GraphAnalyzer::topNonNeighbor(int nodeID, vector<float> w) {
  return G.topNonNeighbor(nodeID, w);
};


float GraphAnalyzer::jacardIndexOfTopKNeighborhoods(int nodeAID, int nodeBID, int k, vector<float> w) {
  vector<int> nodeA = topKNeighbors(nodeAID, k, w);
  vector<int> nodeB = topKNeighbors(nodeBID, k, w);
  int shared(0);
  unordered_set <int> total;
  for(unsigned int i = 0; i < nodeA.size(); i++) total.insert(nodeA[i]);
  for(unsigned int i = 0; i < nodeB.size(); i++) total.insert(nodeB[i]);
  if(total.size() == 0) return 0;
  if(nodeA.size() > nodeB.size()){
    for(unsigned int i = 0; i < nodeA.size(); i++){
      std::vector<int>::iterator it = std::find(nodeB.begin(), nodeB.end(), nodeA[i]);
      if(it != nodeB.end()) shared++;
    }
  }
  else{
    for(unsigned int i = 0; i < nodeB.size(); i++){
      std::vector<int>::iterator it = std::find(nodeA.begin(), nodeA.end(), nodeB[i]);
      if(it != nodeA.end()) shared++;
    }
  }
  return (shared * 1.0) / total.size();
};
