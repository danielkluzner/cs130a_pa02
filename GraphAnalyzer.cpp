#include "GraphHelper.h"
#include "FeatureGraph.h"
#include "GraphAnalyzer.h"
#include <algorithm>
#include <utility>
#include <iterator>
#include <cmath>
#include <bits/stdc++.h>

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
