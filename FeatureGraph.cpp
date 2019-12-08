#include <string>
#include <vector>
#include "FeatureGraph.h"
#include "GraphHelper.h"
#include <map>
#include <iterator>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <utility>
#include <climits>
#include <set>

using namespace std;

// helper sort method
bool sortBackwards2(const pair<float,int> &one,
           const pair<float,int> &two)
{
  return (one.first > two.first);
}

//helper sort method
bool sortDist(const pair<int,int> &one,
            const pair<int,int> &two)
{
  return (one.second < two.second);
}

FeatureGraph::FeatureGraph(int N, int d, vector<Node> nodes, vector<Edge> edges) {
  for(int i = 0; i < N; i++){
    insert(nodes[i]);
  }
  skillsize = d;
  numnodes = N;
  for(int i = 0; i < edges.size(); i++){
    insert(edges[i]);
  }
  numedges = edges.size();
  initializeTriangles();
};

void FeatureGraph::insert(Node node){
  nodes.insert(pair<int, Node>(node.id, Node(node)));
  numnodes++;
  vector<int> empty(0);
  neighbors.insert(pair<int, vector<int>>(node.id, empty));
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

int FeatureGraph::getWeight(int n1, int n2)
{
  for(unsigned int i = 0; i < edges.size(); i++)
    {
      if((edges[i].IdA == n1 && edges[i].IdB == n2) || (edges[i].IdA == n2 && edges[i].IdB == n1))
          return edges[i].weight;
    }
  return INT_MAX;
}

int FeatureGraph::diameter(){
  int max = -1;
  map<int, Node>::iterator itr;
  for(itr = nodes.begin(); itr != nodes.end(); itr++)
    {
      int d = maxDistance(itr->first);
      if(d > max) max = d;
    }
  return max;
}

int FeatureGraph::maxDistance(int nodeID){
  int curr = nodeID;
  vector<int> currNeighs;
  if(nodes.size() == 0 || nodes.size() == 1) return 0;
  set<int> Q;
  map<int, int> dist; // pair<id, dist>
  
  // initialize all the distance to infinity
  // insert all elements into "queue"
  map<int, Node>::iterator itr;
  for(itr = nodes.begin(); itr != nodes.end(); itr++)
    {
        Q.insert(itr->first);
        dist.insert(pair<int, int>(itr->first, INT_MAX));
    }
  dist[nodeID] = 0;
  
  // fill dist
  while(!Q.empty()){
      Q.erase(curr);
      currNeighs.resize(0);
      currNeighs = getNeighbors(curr);
      for(unsigned int x = 0; x < currNeighs.size(); x++){
          if((getWeight(currNeighs[x], curr) + dist[curr]) < dist[currNeighs[x]])
              dist[currNeighs[x]] = getWeight(currNeighs[x], curr) + dist[curr];
      }
      
      vector<pair<int, int>> temp;
      map<int, int>::iterator it;
      for(it = dist.begin(); it != dist.end(); it++)
      {
          temp.push_back(*it);
      }
      sort(temp.begin(), temp.end(), sortDist);
      
      for(unsigned int i = 0; i < temp.size(); i++)
      {
          if(Q.find(temp[i].first) != Q.end()){
              curr = temp[i].first;
              break;
          }
      }
  }
  
  vector<pair<int, int>> temp2;
  map<int, int>::iterator it2;
  for(it2 = dist.begin(); it2 != dist.end(); it2++)
  {
      temp2.push_back(*it2);
  }
  sort(temp2.begin(), temp2.end(), sortDist);
  
  int result = temp2[temp2.size() - 1].second;
  if(result == 0) return INT_MAX;
  return result;
}

int FeatureGraph::numOpenTriangles(){
    return open.size();
}

int FeatureGraph::numClosedTriangles(){
    return closed.size();
}

vector<Triangle> FeatureGraph::getOpenTriangles(){
    vector<Triangle> t;
    map<string, Triangle>::iterator itr;
    for(itr = open.begin(); itr != open.end(); itr++){
        t.push_back(itr->second);
    }
    return t;
}

int FeatureGraph::topNonNeighbor(int nodeID, vector<float> w) {
  vector<pair<float,int>> dots(0);
  vector<int> neighborIDs = getNeighbors(nodeID);
  vector<float> feats;
  float sum(0);
  
  map<int, Node>::iterator itr;
  for(itr = nodes.begin(); itr != nodes.end(); itr++){
    std::vector<int>::iterator it = std::find(neighborIDs.begin(), neighborIDs.end(), itr->first);
    if(it == neighborIDs.end() && itr->first != nodeID){
      feats.resize(0);
      feats = (itr->second).features;
      for(unsigned int j = 0; j < w.size(); j++){
	sum += (feats[j] * w[j]);
      }
      dots.push_back(pair<float,int>(sum, itr->first));
      sum = 0;
    }
  }
  
  if(dots.size() == 0) return -1;
  sort(dots.begin(), dots.end(), sortBackwards2);
  return dots[0].second;
}

void FeatureGraph::initializeTriangles() {
  open.clear();
  closed.clear();
  map<int, Node>::iterator itr;
  int id1, id2, id3;
  vector<int> neighbors1, neighbors2, neighbors3;
  for(itr = nodes.begin(); itr != nodes.end(); itr++){
    id1 = itr->first;
    neighbors1.resize(0);
    neighbors1 = getNeighbors(id1);
    for(unsigned int i = 0; i < neighbors1.size(); i++){
      id2 = neighbors1[i];
      neighbors2.resize(0);
      neighbors2 = getNeighbors(id2);
      for(unsigned int j = 0; j < neighbors2.size(); j++){
	if(neighbors2[j] != id1){
	  id3 = neighbors2[j];
	  neighbors3.resize(0);
	  neighbors3 = getNeighbors(id3);
	  
	  vector<int> ids {id1, id2, id3};
	  sort(ids.begin(), ids.end());
	  string insertid = to_string(ids[0]) + "," + to_string(ids[1]) + "," + to_string(ids[2]);
	  map<string, Triangle>::iterator c = closed.find(insertid);
	  map<string, Triangle>::iterator o = open.find(insertid);
	  vector<int>::iterator exists = find(neighbors3.begin(), neighbors3.end(), id1);

	  if(c == closed.end() && o == open.end()){

	    vector<Edge> e;
	    for(unsigned int k = 0; k < edges.size(); k++){
	      if((edges[k].IdA == id1 || edges[k].IdB == id1) && (edges[k].IdA == id2 || edges[k].IdB == id2)){
		e.push_back(edges[k]);
	      }
	      if((edges[k].IdA == id1 || edges[k].IdB == id1) && (edges[k].IdA == id3 || edges[k].IdB == id3)){
		e.push_back(edges[k]);
	      }
	      if((edges[k].IdA == id2 || edges[k].IdB == id2) && (edges[k].IdA == id3 || edges[k].IdB == id3)){
		e.push_back(edges[k]);
	      }
	    }
	    
	    if(exists == neighbors3.end()){
	      // open
	      open.insert(pair<string, Triangle>(insertid, Triangle(insertid, nodes.lower_bound(id1)->second, nodes.lower_bound(id2)->second, nodes.lower_bound(id3)->second, e[0], e[1], Edge(-1, -1, 0))));
	    }
	    else{
	      // closed
	      closed.insert(pair<string, Triangle>(insertid, Triangle(insertid, nodes.lower_bound(id1)->second, nodes.lower_bound(id2)->second, nodes.lower_bound(id3)->second, e[0], e[1], e[2])));
	    }
	  } // if triangle DNE
	} // if not itself
      } // neighbors2
    } // neighbors1
  } // nodes
} // function
