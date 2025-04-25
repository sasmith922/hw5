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
    //std::cout << "before combos" << std::endl;
    combos(current, 0, in, floating, dict, results);
    //std::cout << "after combos, returning results" << std::endl;
    return results;

}

// Define any helper functions here

// recursive backtracking helper function
void combos(std::string& current, size_t index, const std::string& in,
    const std::string& floating, const std::set<std::string>& dict,
    std::set<std::string>& results)
{
    // this block is a base case for when we have a valid/invalid word with proper length
    if(current.length() == index) // current word is proper length
    {
        if(dict.find(current) != dict.end() && floating.empty()) // valid word is found
        {
            // // check to see if every index of float is empty, this prunes lots of paths
            // std::string temp = current; // use a temp string of current
            // for(char c : floating)
            // {
            //     size_t position = temp.find(c);
            //     if(position == std::string::npos)
            //     {
            //         return; // pruning by returning early
            //     }
            //     temp.erase(position, 1);
            // }
            results.insert(current);
        }  
        return;
    }

    // skip current index's letter
    if(in[index] != '-')
    {
        current[index] = in[index]; // copy the index's char, current is mutable, in is const
        combos(current, index + 1, in, floating, dict, results); // recursive call
        return;
    }
    else
    {
        // want to see how many dashes are left in current word
        size_t dashes = 0;
        for(size_t i = index; i < in.size(); i++)
        {
            if(in[i] == '-')
            {
                dashes++;
            }
        }
        if(floating.size() > dashes) // floating has more chars than there are dashes left
        {
            return; // end early
        }


        // try all floating letters
        for(int i = 0; i < floating.size(); i++)
        {
            char c = floating[i];
            current[index] = c;
            std::string newFloat = floating;
            newFloat.erase(i, 1);
            combos(current, index + 1, in, newFloat, dict, results); // recursive call
        }

        // try all letters/chars
        if(floating.size() < dashes) // more dashes than floating letters, so we have to try manually
        {
            for(char c = 'a'; c <= 'z'; c++)
            {
                current[index] = c;
                // check to see if char is in the string
                size_t position = floating.find(c);
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

}
