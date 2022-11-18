/*
    Quiz 1: Suffix counts

    In this problem, you will write a function that returns the count of a string’s suffix in a given string, S. 
    A suffix is a combination of one or more symbols appended at the end of the string. 
    You will be given the length, L of the suffix as a parameter to the function

    Sample Input:
        et tu, brute
        1
    
    Sample Output:
        2 
*/

#include <iostream>
#include <string>

int suffixCount(std::string S, int L) {
    std::string suffix = S.substr(S.size() - L);
    int count = 0;
    unsigned int nextIndex = S.find(suffix);

    while (nextIndex != std::string::npos) {
        count++;
        nextIndex = S.find(suffix, nextIndex + suffix.size());
    }

    return count;
}
