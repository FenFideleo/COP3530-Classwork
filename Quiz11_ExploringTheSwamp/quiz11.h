/*
*   COP3530
* 
*   Student: Erik Meurrens
* 
*   Notes:
*    1. S - - - - - - -
*       - - - - - - - -
*       - - - - - - - -
*       - - - - - - - -
*       - - - - - - - -
*       - - - - - - - E
* 
*    2. Only can move right or down
*/
/*
    Quiz 13: Exploring the swamp

Problem Statement:

Explorer Alberto, a coffee bean aficionado, is passing through a swamp while simultaneously trying to pick up as
many coffee beans as possible. The swamp is represented by a m x n integer array, swamp, where swamp[i]
[j] represents the number of coffee beans located at row i, column j of the swamp.

Alberto always enters the swamp at row 0, column 0, and always exits the swamp at row m, column n. At each 
step, he moves either one unit to the right (across one column) or one unit down (across one row).

When Alberto visits swamp[i][j], he collects all the coffee beans at that location. Write a function that returns 
the maximum number of coffee beans that Alberto can collect as he traverses through the swamp. Implement 
your solution using dynamic programming.

Example input:
3 3
5 3 4
8 6 9
1 3 2

Example output:
30

Explanation:
 - Input consists of m+1 lines
    - Line 1 of input denotes two integers m representing number of rows and n representing number of columns.
    - m lines follow in the input, each line repesenting a row in the grid and containing n integers each representing the number of coffee beans.
 -Output is the global optimal.
    - In the example input, it is calculated as 5 + 8 + 6 + 9 + 2 = 30 which is the maximum number of coffee beans that Alberto can pick up.
 
*/

#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

int swampExplorer(std::vector<std::vector<int>> &swamp_maze)
{
    // swamp_maze is the 2D grid of the swamp with coffee beans at each location
    // return the max beans that Alberto can collect
    vector<vector<int>> bestCombos(swamp_maze.size());
    for (int i = 0; i < bestCombos.size(); i++) {
        bestCombos[i].resize(swamp_maze[i].size());
    }
    for (int i = 0; i < bestCombos.size(); i++) {
        for (int j = 0; j < bestCombos[i].size(); j++) {
            if (i == 0) {
                if (j == 0)
                    bestCombos[i][j] = swamp_maze[i][j];
                else
                    bestCombos[i][j] = swamp_maze[i][j] + bestCombos[i][j - 1];
            }
            else if (j == 0) {
                bestCombos[i][j] = swamp_maze[i][j] + bestCombos[i - 1][j];
            }
            else {
                int fromTop = swamp_maze[i][j] + bestCombos[i - 1][j];
                int fromLeft = swamp_maze[i][j] + bestCombos[i][j - 1];

                if (fromTop > fromLeft)
                    bestCombos[i][j] = fromTop;
                else
                    bestCombos[i][j] = fromLeft;
            }
        }
    }
    
    return bestCombos[bestCombos.size() - 1][bestCombos[0].size() - 1];
}
