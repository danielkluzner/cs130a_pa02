#include "GraphHelper.h"
#include "FeatureGraph.h"
#include "GraphAnalyzer.h"
#include <map>
#include <iostream>
#include <utility>
#include <algorithm>
using namespace std;

int main() {
    
    vector<Node> nodes  {
       Node(1, vector<float> { 10, 10}),
       Node(2, vector<float> { 20, 20}),
       Node(3, vector<float> { 30, 30}),
       Node(4, vector<float> { 40, 40}) };
    
    vector<Edge> edges {Edge(1,2, 10), Edge(2, 3, 9), Edge(3, 4, 1), Edge(1, 3, 5)};
  
    int d = 2;
    
    int open, closed;

    FeatureGraph graph = FeatureGraph(4, d, nodes, edges);
    graph.print();
    cout << endl;
    open = graph.numOpenTriangles();
    closed = graph.numClosedTriangles();
    cout << "open: " << open << ", closed: " << closed << ", open to closed ratio: " << (open * 1.0) / closed << endl << endl;

    graph.insert(Node(6, vector<float>{60,60}));
    graph.insert(Node(5, vector<float>{50,50}));
    graph.print();
    open = graph.numOpenTriangles();
    closed = graph.numClosedTriangles();
    cout << "open: " << open << ", closed: " << closed << ", open to closed ratio: " << (open * 1.0) / closed << endl << endl;
    cout << endl;
    graph.insert(Edge(4, 6, 7));
    graph.insert(Edge(5, 6, 8));
    graph.print();
    cout << endl;
    open = graph.numOpenTriangles();
    closed = graph.numClosedTriangles();
    cout << "open: " << open << ", closed: " << closed << ", open to closed ratio: " << (open * 1.0) / closed << endl << endl;
    graph.insert(Edge(2, 4, 5));
    graph.print();
    cout << endl;
    graph.initializeTriangles();
    open = graph.numOpenTriangles();
    closed = graph.numClosedTriangles();
    cout << "open: " << open << ", closed: " << closed << ", open to closed ratio: " << (open * 1.0) / closed << endl << endl;
    
    /*Node n1 = Node(1, vector<float> { 10, 10});
    Node n2 = Node(2, vector<float> { 20, 20});
    Node n3 = Node(3, vector<float> { 30, 30});
    Triangle t1 = Triangle(n1, n2, n3,
			  Edge(1,2, 10),
			  Edge(2, 3, 9),
			  Edge(1, 3, 5)
			  );
    Triangle t2 = Triangle(n1, n2, n3,
			  Edge(1,2, 20),
			  Edge(2, 3, 8),
			  Edge(1, 3, 17)
			  );
    cout << (t1 < t2) << endl;*/
    
    GraphAnalyzer analyzer = GraphAnalyzer(graph);
    cout << analyzer.topKOpenTriangles(4) << endl;
    analyzer.insert(Node(7, vector<float>{4, 2}));
    cout << analyzer.topKOpenTriangles(2) << endl;
    cout << analyzer.openClosedTriangleRatio() << endl;
    analyzer.insert(Edge(2, 7, 7));
    cout << analyzer.topKOpenTriangles(2) << endl;
    cout << analyzer.openClosedTriangleRatio() << endl;
    analyzer.insert(Node(8, vector<float>{7, 6}));
    cout << analyzer.topKOpenTriangles(2) << endl;
    
    analyzer.G.print();
    
    
    /*cout << analyzer.diameter() << "\n";

    cout << analyzer.openClosedTriangleRatio() << "\n";

    cout << analyzer.topKOpenTriangles(2) << "\n";

    
    int newNodeID = 5;
    vector<float> newFeatures {3, 3};
    Node newNode = Node(newNodeID, newFeatures);

    analyzer.insert(newNode);
    analyzer.insert(Edge(4, 5, 32));
    
    
    vector<float> weights{.5, .5};
    vector<int> neighbors = analyzer.topKNeighbors(2, 3, weights);
    
    for(auto i = neighbors.begin(); i != neighbors.end(); ++i)
        cout << *i << ",";
    cout << "\n";

    cout << analyzer.topNonNeighbor(2, weights) << "\n";

    cout << analyzer.jacardIndexOfTopKNeighborhoods(1, 2, 2, weights);*/
    return 0;
}
