/*  COP3530
    Student: Erik Meurrens

    Quiz 8: Sets, Maps, Hash Tables (Find Digits)

*/
/*
    Find the Digits: Difference between Shuffled Digits

    You are given two numbers x and y represented as strings. y is generated by random shuffling x 
    and then adding 0 to n more digits at any random positions.

    Create a function that takes in these two numbers (x and y) as string inputs 
    and returns the newly inserted digit(s) that was/were added to y 
    in the form of a concatenated string of all the newly added digit(s) in an ascending order.
    You must use a set or map data structure from STL to solve the problem.

    Note: A single digit can be added more than once in the new number.

    Example 1:
    Input: x = "1234", y = "12345"
    Output: "5"
    Explanation: "5" is the digit that was added.
    
    Example 2:
    Input: x = "8", y = "56981234"
    Output: "1234569"
    
    Constraints:
    "x" and "y" > 0
    0 < x.length, y.length <= 10^8
    y.length >= x.length
*/

#include <iostream>
#include <set>
#include <string>
using namespace std;

std::string findTheDigits(std::string x, std::string y) {
    set<char> s;
    string newString = "";

    for (char i : y) {
        s.insert(i);
    }
    for (char i : x) {
        s.erase(i);
    }
    for (char i : s) {
        newString.append(1, i);
    }

    return newString;
}