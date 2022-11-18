/*
	Project 2: Simplified Page Rank Algorithm

	Student: Erik Meurrens

	Notes:
	- Consider webpage class
	- Consider graph/adjlist class
		- Need webpageList to sort pages in alpha order for printing (use normal, ordered map)

	- Rank formula: Rank(currNode) = Sum(Rank(i)/out+degree(i))
	- Rank of a Page, r(p) = M x r(p-1)

*/

#include <iostream>
#include <iomanip>
#include <map>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
using namespace std;

class WebGraph {
	// Webpage struct to store vertex info for the web graph
	struct Webpage {
		string name;
		double rank;
		int outdegree;
		unordered_map<string, Webpage*> linkedPages;

		Webpage(string name = "null") {
			this->name = name;
			rank = 0.0;
			outdegree = 0;
		}
	};
	// Uses adjacency list structure map<string, Webpage> -> Webpage.linkedPages returns adjacent pages
	map<string, Webpage> adjList;
	// Stores current power iterations in graph
	unsigned int pIterations;

	// Do power iterations
	void POWERFULLY_ITERATE(unsigned int p) {	// Please don't take points off for the fun function name
		for (int i = 0; i < p; i++) {
			auto iterTo = adjList.begin();
			// Multiply current website rank by outdegree factor of each site pointing to current website
			vector<double> oldRanks(adjList.size());
			int j = 0;
			while (iterTo != adjList.end()) {
				double newRank = 0.0;
				auto iterFrom = adjList.begin();
				int k = 0;
				while (iterFrom != adjList.end()) {
					// Look for all sites pointing to current site and add rank contribution
					if (iterFrom->second.linkedPages.find(iterTo->first) != iterFrom->second.linkedPages.end()) {
						double outdegreeFactor = 1.0 / iterFrom->second.outdegree;
						if (i == 0) {
							newRank = (1.0 / adjList.size());
						}
						else if (j > k) {
							newRank += (outdegreeFactor * oldRanks[k]);
						}
						else {
							newRank += (outdegreeFactor * iterFrom->second.rank);
						}

					}
					if (j == 0) {
						oldRanks[k] = iterFrom->second.rank;
					}
					iterFrom++;
					k++;
				}
				iterTo->second.rank = newRank;
				iterTo++;
				j++;
			}
		}
	}

public:
	WebGraph(int powerIterations = 0) {
		pIterations = powerIterations;
	}

	void insert(string from, string to) {
		// If "from" website does not exist, add it to graph
		if (adjList.find(from) == adjList.end()) {
			adjList[from] = Webpage(from);
		}
		// Check if "to" website does not exist in graph, if so add it
		if (adjList.find(to) == adjList.end()) {
			adjList[to] = Webpage(to);
		}
		// Add "to" to linkedPages of "from" website, supposing it does not already exist in linkedPages
		// If it does not exist, increment outdegree of "from" website, else do nothing
		if (adjList[from].linkedPages.find(to) == adjList[from].linkedPages.end()) {
			adjList[from].linkedPages[to] = &adjList[to];
			adjList[from].outdegree++;
		}
	}

	void print() {
		POWERFULLY_ITERATE(pIterations);
		for (auto v : adjList) {
			cout << v.second.name << " " << setprecision(2) << fixed << v.second.rank << endl;
		}
	}
};

int main() {
	// Read numLines and numPowerIterations
	int numLines = 0;
	int numPowerIterations = 0;
	cin >> numLines;
	cin >> numPowerIterations;

	WebGraph graph(numPowerIterations);
	string from_page;
	string to_page;

	// Read from_page to_page and insert into graph
	for (int i = 0; i < numLines; i++) {
		cin >> from_page;
		cin >> to_page;
		graph.insert(from_page, to_page);
	}
	
	// Print all pages in ascending alpha order, rounding rank of page to 2 decimal
	graph.print();

	return 0;
}