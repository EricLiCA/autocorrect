#ifndef TREE_H
#define TREE_H

#include "Levenshtein.h"
#include "Node.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>

class Tree {
private:
    Node *root_;
    Node *cursor_;

    std::vector<std::string> suggestions_;
    std::string typedCharacters_;
    std::vector<std::string> lexique_;
    std::vector<Node *> nonMinimized_;
    std::vector<Node *> minimized_;
    void initializeTree();
    void readLexique(std::string lexiqueName);
    void setRootNode();
    void createFinalStates();
    void addWord(std::string word);
    void addLexique(int lowIndex, int highIndex);
    Node *search(char letter);
    std::vector<std::string> updateAutocomplete(std::string searchWord);
    void addSuggestion(Node *current, std::string savedCharacters);

public:
    Tree(std::string lexiqueName);
    Tree(std::vector<std::string> lexique);

    Node* search(std::string searchWord);
    void autocomplete(std::string word);
    void getUserInput();
    std::vector<std::string> autocorrect(std::string input);
    std::vector<std::string> getLexique();
    std::vector<std::string> getSuggestions();

};

#endif // TREE_H
