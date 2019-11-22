#include "GraphHelper.h"
#include "FeatureGraph.h"
#include "GraphAnalyzer.h"
#include <algorithm>

using namespace std;


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
  vector<int> dots;
  vector<int> result;
  vector<int> neighborIDs = G.getNeighbors(nodeID);
  vector<float> feats;
  for(int i = 0; i < neighborIDs.size(); i++){
    feats.resize(0);
    feats = G.getFeatures(nodeID);
    for(int j = 0; j < w.size(); j++){
      dots.push_back(feats[j] * w[j]);
    }
  }
  make_heap(dots.begin(), dots.end());
  for(int i = 0; i < k; i++){
    result.push_back(dots.front());
    pop_heap(dots.begin(), dots.end());
    make_heap(dots.begin(), dots.end());
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



