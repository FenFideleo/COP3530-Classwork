/*  COP3530
    Student: Erik Meurrens

    Quiz 9: Graphs 1 (Not So Simple Graph)

*/
/*
    Quiz 9: Not so simple Graph

    Write C++ code for implementing a Graph data structure that supports a directed graph with 
    self-loops and parallel edges. You are expected to implement the following methods and a main
    method is already built for you:

        void *insertEdge*(int from, int to, int weight);   // 1
        bool *isEdge*(int from, int to);                   // 2
        int *sumEdge*(int from, int to);                   // 3
        vector<int> *getWeight*(int from, int to);         // 4
        vector<int> *getAdjacent*(int vertex);             // 5


    Sample Input:
        7    
        1 0 0 10  
        1 0 1 20 
        1 0 2 30
        2 0 0  
        3 0 2 
        4 0 1
        5 0
    
    Sample Output:
        1  
        30
        20 
        0 1 2
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

class Graph
{
    private:
        // TODO: Graph structure that supports parallel edges and self-loops
        map<int, vector<vector<int>>> edges;


    public:
      void insertEdge(int from, int to, int weight);  
      bool isEdge(int from, int to);  
      int sumEdge(int from, int to); 
      std::vector<int> getWeight(int from, int to); 
      std::vector<int> getAdjacent(int vertex); 
};

void Graph::insertEdge(int from, int to, int weight) 
{
   /*
        TODO: insertEdge() adds a new edge between the from 
        and to vertex.
   */
    if ((edges[from].size()) <= to) {
        for (int i = edges[from].size(); i <= to; i++) {
            edges[from].push_back({/*empty vector*/});
        }
    }

    edges[from][to].push_back(weight);
}
        
bool Graph::isEdge(int from, int to) 
{
    /*
        TODO: isEdge() returns a boolean indicating true 
        if there is an edge between the from and to vertex
    */
    return (edges[from][to].size() > 0);
}

int Graph::sumEdge(int from, int to)
{
    /*
        TODO: sumEdge() returns the sum of weights of all edges 
        connecting the from and to vertex. Returns 0 if no edges 
        connect the two vertices.
    */
    int sum = 0;
    if ((edges[from].size()) > to) {
        for (int i = 0; i < edges[from][to].size(); i++) {
            sum += edges[from][to][i];
        }
    }
    
    return sum;
}

std::vector<int> Graph::getWeight(int from, int to)
{
    /*
        TODO: getWeight() returns a sorted vector containing all 
        weights of the edges connecting the from and to vertex
    */
    vector<int> weights;

    if ((edges[from].size()) > to) {
        for (int i = 0; i < edges[from][to].size(); i++) {
            weights.push_back(edges[from][to][i]);
        }
    }
    
    return weights;
}

std::vector<int> Graph::getAdjacent(int vertex) 
{
    /*
        TODO: getAdjacent() returns a sorted vector of all vertices
        that are connected to a vertex
    */
    vector<int> adjacents;

    for (int i = 0; i < edges[vertex].size(); i++) {
        for (int j = 0; j < edges[vertex][i].size(); j++) {
            adjacents.push_back(i);
        }
    }
    return adjacents;
}
