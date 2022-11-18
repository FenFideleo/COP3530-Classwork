#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <chrono>
#include "splay_tree.h"
using namespace std;
using namespace std::chrono;


class Graph {
    unordered_map<string, unsigned int> mappy;
public:
    void putIn(string category);
};

void Graph::putIn(string category) {
    if (mappy.count(category) > 0) {
        mappy[category]++;
    }
    else {
        mappy[category] = 1;
    }
}

void ReadFile(Graph unorderedMappy) {
    ifstream info("rows.csv");
    if (info.is_open()) {
        string liner;
        getline(info, liner);

        while (getline(info, liner)) {
            istringstream stream(liner);

            string date;
            getline(stream, date, ',');

            string category;
            getline(stream, category, ',');

            unorderedMappy.putIn(category);
        }
    }
    else {
        cout << "Go cry" << endl;
    }
}

void ReadFile(SplayTree<string> splay) {
    ifstream info("rows.csv");
    if (info.is_open()) {
        string liner;
        getline(info, liner);

        while (getline(info, liner)) {
            istringstream stream(liner);

            string date;
            getline(stream, date, ',');

            string category;
            getline(stream, category, ',');

            splay.insert(category);
        }
    }
    else {
        cout << "Couldn't open file stream" << endl;
    }
}



int main() {
    /*
     * runtime duration code from https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
     */
    auto start = high_resolution_clock::now();

    Graph unorderedMappy;
    ReadFile(unorderedMappy);

    cout << "Hello, World, from Mappy!" << endl;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Mappy Runtime:" << duration.count() << endl;

    // Testing Splay Tree
    start = high_resolution_clock::now();

    // Read file into Splay Tree
    SplayTree<string> splay;
    ReadFile(splay);

    cout << "Hello, World, from Splay" << endl;

    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Splay Tree Runtime:" << duration.count() << endl;

    return 0;
}
