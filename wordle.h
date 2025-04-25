#ifndef WORDLE_H
#define WORDLE_H

#ifndef RECCHECK
#include <set>
#include <string>
#endif

/**
 * @brief Returns the list of all legal words in the provided dictionary
 *        that meet the criteria provided in the `in` and `floating`
 *        inputs.
 * 
 * @param [in] in - string of fixed, correct characters and `-`s to indicate
 *                  the length of string and locations that must be filled in
 * @param [in] floating  - Characters that must be used somewhere in the word
 * @param [in] dict - Dictionary of strings of legal words
 * @return std::set<std::string> - Set of all words that meet the criteria
 */
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict);

/**
 * @param [in] in, floating, dict all come from wordle() call
 * @param [in] index is the current index we are operating on
 * @param [in] current is the current word state we are operating on
 * @param [in] results is the set of resulting words which we pass by 
 *             reference and operate on, this is what will be returned by wordle()
 */
void combos(std::string& current, size_t index, const std::string& in,
    const std::string& floating, const std::set<std::string>& dict,
    std::set<std::string>& results);

#endif