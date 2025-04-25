#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::string current = in;
    std::set<std::string> results;
    combos(current, 0, in, floating, dict, results);
    return results;

}

// Define any helper functions here

// recursive backtracking helper function
void combos(string& current, int index, const std::string& in,
    const std::string& floating, const std::set<std::string>& dict,
    std::set<std::string> results)
{

    // this block is a base case for when we have a valid/invalid word with proper length
    if(current.length() == index) // current word is proper length
    {
        if(dict.find(current) != dict.end() && floating.empty()) // valid word is found
        {
            results.insert(current);
        }  
        return;
    }

    // skip current index's letter
    if(current[index] == '-')
    {
        combos(current, index + 1, in, floating, dict, results); // recursive call
    }
    else
    {
        // try all letters/chars
        for(char c = 'a'; c <= 'z'; c++)
        {
            current[index] = c;

            // check to see if char is in the string
            int position = floating.find(c);
            if(position != std::string::npos) // char in string
            {
                std::string newFloat = floating;
                newFloat.erase(position, 1);
                combos(current, index + 1, in, newFloat, dict, results); // recursive call
            }
            else
            {
                combos(current, index + 1, in, floating, dict, results); // recursive call
            }
            current[index] = '-'; // backtracking case
        }
    }

}
