/*
    COP3530: Graphs 2 - Andrewfied Dijkstra Algorithm

    Student: Erik Meurrens

*/
/*
    Quiz 10: Andrewfied Dijkstra algorithm

    A graph is provided as a vector of strings. Write a function with the following signature: 
    int dijkstra(vector<string>& graph) that takes in as input a graph and returns the shortest 
    path between vertices s and t. If no path exists between s and t, then return -1. The details
     of the graph as a vector of strings are as follows:
     
    1. The start position is represented by a 's' and will always be the first character of the first string.
    2. The end position is represented by a 't' and will always be the final character of the final string.
    3. a '.' character represents that you cannot visit this vertex in the graph
    4. all other characters will be numeric characters '1'-'9' which represents the cost of moving to that vertex.
    5. There is no cost in moving to the destination ('t') character.
    6. Adjacent characters are those immediately horizontal or vertical from the current character (diagonal moves are not allowed).

    Sample Input:
        s3153
        1.424
        22.3t
    
    Sample Output:
        13
        
    Explanation:
        The shortest path from 's' to 't' follows s -> 3 -> 1 -> 4 -> 2 -> 3 -> t, which totals 13
*/

#include <iostream>
#include <climits>
#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;

struct Node {
    char value;
    int weight;
    int src_dist;
    int X;
    int Y;

    Node* left;
    Node* right;
    Node* up;
    Node* down;

    Node* parent;

    Node() {
        left = nullptr;
        right = nullptr;
        up = nullptr;
        down = nullptr;
        parent = nullptr;
    }

    bool operator>(const Node& rhs) const {
        return this->src_dist > rhs.src_dist;
    }
};

int dijkstra(std::vector<std::string> & graph) 
{
    // Initialize visited set
    unordered_set<Node*> visited;
    // Initialize toVisit priority queue
    priority_queue <Node, vector<Node>, greater<Node>> toVisit;

    // Initialize Nodes 2D vector
    vector<vector<Node>> nodes(graph.size());
    if (graph.size() > 0) {
        for (int i = 0; i < graph.size(); i++) {
            nodes[i].resize(graph[0].size());
        }
    }
    else {
        return -1;
    }

    for (int i = 0; i < graph.size(); i++) {
        for (int j = 0; j < graph[0].size(); j++) {
            nodes[i][j].value = graph[i][j];
            nodes[i][j].X = i;
            nodes[i][j].Y = j;

            if (isdigit(graph[i][j])) {
                nodes[i][j].weight = graph[i][j] - '0';
            }
            else if (graph[i][j] == 's' || graph[i][j] == 't') {
                nodes[i][j].weight = 0;
            }
            else {
                nodes[i][j].weight = INT_MAX;
            }

            if (i > 0) 
                nodes[i][j].left = &nodes[i - 1][j];
            if (i < nodes.size() - 1)
                nodes[i][j].right = &nodes[i + 1][j];
            if (j > 0)
                nodes[i][j].down = &nodes[i][j - 1];
            if (j < nodes[0].size() - 1)
                nodes[i][j].up = &nodes[i][j + 1];

            if (graph[i][j] == 's') {
                nodes[i][j].src_dist = 0;
                toVisit.push(nodes[i][j]);
            }
            else {
                nodes[i][j].src_dist = INT_MAX;
            }
        }
    }

    // How to navigate with Dijkstra?
    // While toVisit is not empty
    while (!toVisit.empty()) {
        Node* currNode = &nodes[toVisit.top().X][toVisit.top().Y];
        // Check if node is visited, if so continue
        if (visited.find(currNode) != visited.end()) {
            toVisit.pop();
            continue;
        }
        // Else mark it as visited
        else {
            visited.emplace(currNode);
            toVisit.pop();
        }
        // For all, non-diagonal adjacent nodes
        for (int i = 0; i < 4; i++) {
            Node* adjacentNode = nullptr;;
            if (i == 0)
                adjacentNode = currNode->left;
            else if (i == 1)
                adjacentNode = currNode->right;
            else if (i == 2)
                adjacentNode = currNode->down;
            else if (i == 3)
                adjacentNode = currNode->up;

            // Check if X,Y are valid () && Check that weight != INT_MAX
            if (adjacentNode != nullptr && adjacentNode->weight != INT_MAX) {
                if (adjacentNode->src_dist > adjacentNode->weight + currNode->src_dist) {
                    adjacentNode->src_dist = adjacentNode->weight + currNode->src_dist;
                    adjacentNode->parent = currNode;
                }
                // If weight of node == 0 && visited.size() > 1, it is t, therefore assign parent to t and break to continue
                if (adjacentNode->value == 't')
                    return adjacentNode->src_dist;
                else {
                    toVisit.emplace(*adjacentNode);
                }
            }
            
        }   
    }
	return -1;
}
