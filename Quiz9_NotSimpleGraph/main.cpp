/*
	To check output:
		g++ -o main test-io/main.cpp && ./main < test-io/input-files/1.txt > test-io/output-files/1.txt && diff -w test-io/expected-output-files/1.txt test-io/output-files/1.txt
*/

#include "graph.h"

int main()
{
    //DO NOT CHANGE THIS FUNCTION. CHANGE YOUR IMPLEMENTATION CODE TO MAKE IT WORK
    
    int noOfLines, operation, vertex, to, fro, weight, source;
    std::vector<int> arr;
    Graph g;
    
    std::cin >> noOfLines;
    for(int i = 0; i < noOfLines; i++)
    {
        std::cin >> operation;
        switch(operation)
        {
            case 1: 
                std::cin >> fro >> to >> weight;
                g.insertEdge(fro, to, weight);
                break;
                
            case 2: 
                std::cin >> fro >> to;
                std::cout << g.isEdge(fro, to) << "\n";
                break;
                
            case 3: 
                std::cin >> fro >> to;
                std::cout << g.sumEdge(fro, to)<<"\n";
                break;
                
            case 4: 
                std::cin >> fro >> to;
                arr = g.getWeight(fro, to);
                for (int element : arr)
                    std::cout << element << " ";
                std::cout << "\n";
                break;
                
            case 5: 
                std::cin >> vertex;
                arr = g.getAdjacent(vertex);
                for (int element : arr)
                    std::cout << element << " ";
                std::cout << "\n";
                break;
        }
    }
}

 