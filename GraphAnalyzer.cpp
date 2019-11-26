#include "GraphHelper.h"
#include "FeatureGraph.h"
#include "GraphAnalyzer.h"
#include <algorithm>
#include <utility>
#include <algorithm>

using namespace std;

bool sortBackwards(const pair<float,int> &one,  
		   const pair<float,int> &two) 
{ 
  return (one.first > two.first); 
} 

void GraphAnalyzer::insert(Node n) {
  G.insert(n);
  // TODO Adjust calculations for ratio of open triangles and topKtriangles
};

void GraphAnalyzer::insert(Edge e) {
  G.insert(e);
  // TODO Adjust calculations for ratio of open triangles and topKtriangles
};

int GraphAnalyzer::diameter() {
  //TODO
  return 2;
};


float GraphAnalyzer::openClosedTriangleRatio() {
  //TODO
  return .5;
};

string GraphAnalyzer::topKOpenTriangles(int k) {
  //TODO
  return "2,3,4";
};


vector<int> GraphAnalyzer::topKNeighbors(int nodeID, int k,  vector<float> w) {
  vector<pair<float,int>> dots;
  vector<int> result(k,0);
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
  for(int i = 0; i < k; i++){
    result[i] = dots[i].second;
  }
  return result;
};


int GraphAnalyzer::topNonNeighbor(int nodeID, vector<float> w) {
  //TODO
  return 1;
};


float GraphAnalyzer::jacardIndexOfTopKNeighborhoods(int nodeAID, int nodeBiID, int k, vector<float> w) {
  //TODO
  return 0;
};
