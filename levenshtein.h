#ifndef LEVENSHTEIN_H
#define LEVENSHTEIN_H


#include <vector>
#include <string>
#include <iostream>
#include <set>

class Levenshtein {
private:
    std::string word_;
    std::vector<std::string> wordPermutations_;

public:
    Levenshtein(std::string word);

    void updatePermutations();

    void replaceLetter();

    void insertLetter();

    void removeLetter();

    void swapLetters();

    void updateWord(std::string word);

    void printPermutations();

    std::vector<std::string> permutations();
};


#endif // LEVENSHTEIN_H
