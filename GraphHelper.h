#ifndef HELPER_H
#define HELPER_H

#include <vector>
#include <iostream>
#include <string>
using namespace std;

struct Node {
    // NOTE: Do not edit node struct
    int id;
    vector<float> features;
    
    Node(int id, vector<float> features): id(id), features(features) {}
    Node(const Node &n2) { id = n2.id; features=n2.features;}
};


struct Edge {
    // NOTE: Do not edit Edge struct
    int IdA, IdB, weight;
    
    Edge(int IdA, int IdB, int weight): IdA(IdA), IdB(IdB), weight(weight) {}
};

class Triangle {
    // TODO make a Triangle class with appropriate fields and methods
    
private:
  string tID;
  Node nodeA, nodeB, nodeC;
  
public:
    
    // needed to be public in order for heap helper
    // method to access them
    Edge edgeA, edgeB, edgeC;
    
    // TODO make appropriate constuctor
    Triangle(string tID, Node nodeA, Node nodeB, Node nodeC, Edge edgeA, Edge edgeB, Edge edgeC):
    tID(tID), nodeA(nodeA), nodeB(nodeB), nodeC(nodeC), edgeA(edgeA), edgeB(edgeB), edgeC(edgeC) { }
    
    // Operator overloading for storage in priority queue
    // returns true iff t2 is greater than t1. 
    //
    // Note: Must be transitive
    //      This means if t1<t2 and t2<t3 than t1< t3
    bool operator < (Triangle const &other) {
      return (((this->edgeA).weight + (this->edgeB).weight + (this->edgeC).weight) < 
	      ((other.edgeA).weight + (other.edgeB).weight + (other.edgeC).weight));
    }
    
    const string getID() { return tID; }
    
    
};


#endif

    




    
