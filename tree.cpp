#include "tree.h"

Tree::Tree(std::string lexiqueName) {
    readLexique(lexiqueName);
    initializeTree();
}

Tree::Tree(std::vector<std::string> lexique) {
    lexique_ = lexique;
    initializeTree();
}



void Tree::initializeTree() {
    createFinalStates();
    setRootNode();
    cursor_ = root_;
    addLexique(0, lexique_.size() - 1);
}

void Tree::getUserInput() {

}

void Tree::readLexique(std::string lexiqueName) {
    std::ifstream infile(lexiqueName);
    for (std::string line; getline(infile, line);) lexique_.push_back(line);
    infile.close();
}

void Tree::setRootNode() {
    std::string rootWord = lexique_[(lexique_.size() - 1) / 2];
    root_ = new Node(rootWord[0]);
    root_->setState(start);
}

void Tree::createFinalStates() {
    char alphabet = 'a';
    for (int i = 0; i < 26; ++i) {
        Node *finalState = new Node(alphabet + i);
        finalState->setState(final);
        minimized_.push_back(finalState);
    }
}

void Tree::addWord(std::string word) {
    Node *currentNode = root_;
    int charIndex = 0;

    while (charIndex < word.size()) {
        if (currentNode->Value() == word[charIndex]) {
            charIndex++;
            if (charIndex == word.size()) {
                currentNode->setState(endOfWord);
            }
            if (currentNode->Middle() == nullptr) {
                if (charIndex < word.size()) {
                    currentNode->setMiddle(new Node(word[charIndex]));
                }
            }
            currentNode = currentNode->Middle();
        } else {
            if (word[charIndex] < currentNode->Value()) {
                if (currentNode->Left() == nullptr) {
                    currentNode->setLeft(new Node(word[charIndex]));
                }
                currentNode = currentNode->Left();
            } else {
                if (currentNode->Right() == nullptr) {
                    currentNode->setRight(new Node(word[charIndex]));
                }
                currentNode = currentNode->Right();
            }
            if (charIndex == 0) currentNode->setState(start);
        }
    }
}

void Tree::addLexique(int lowIndex, int highIndex) {
    if (lowIndex <= highIndex) {
        int midIndex = (highIndex - lowIndex) / 2 + lowIndex; //prevent overflow
        std::string midWord = lexique_[midIndex];
        addWord(midWord); // add word to tree
        // recursive call
        addLexique(lowIndex, midIndex - 1);
        addLexique(midIndex + 1, highIndex);
    }
}

void Tree::autocomplete(std::string word) {
    typedCharacters_ = word;
    updateAutocomplete(typedCharacters_);
}

Node *Tree::search(char letter) {
    Node *scoutCursor_ = cursor_;
    while (scoutCursor_) {
        if (letter == scoutCursor_->Value()) {
            cursor_ = scoutCursor_->Middle();
            return scoutCursor_;
        } else if (letter < scoutCursor_->Value()) {
            scoutCursor_ = scoutCursor_->Left();
        } else {
            scoutCursor_ = scoutCursor_->Right();
        }
    }
    return nullptr;
}

Node* Tree::search(std::string searchWord) {
    cursor_ = root_;
    Node* found = root_;
    for (int i = 0; i < searchWord.size() && found != nullptr; i++) {
        found = search(searchWord[i]);
    }
    return found;
}


std::vector<std::string> Tree::updateAutocomplete(std::string searchWord) {
    suggestions_.clear();
    Node *searchNode = search(searchWord); // find node with current search word
    if (searchNode != nullptr) {
        if (searchNode->currentState() == endOfWord) {
            suggestions_.push_back(searchWord); // add suggestion to vector
        }
        if (searchNode->Middle() != nullptr) {
            addSuggestion(searchNode->Middle(), "");
        }
    }
    return suggestions_;
}

void Tree::addSuggestion(Node *current, std::string savedCharacters) {
    // Traverse left branch
    if (current->Left()) addSuggestion(current->Left(), savedCharacters);

    // Add word to suggestions if it's end of word
    if (current->currentState() == endOfWord)
        suggestions_.push_back(typedCharacters_ + savedCharacters + current->Value());

    // Traverse downwards the middle branch
    if (current->Middle()) addSuggestion(current->Middle(), savedCharacters + current->Value());

    // Traverse right branch
    if (current->Right()) addSuggestion(current->Right(), savedCharacters);
}

std::vector<std::string> Tree::autocorrect(std::string input) {
    Node* correct = search(input);
    std::vector<std::string> corrections;

    if(correct && correct->currentState() == endOfWord) // if input has no mistake (no need to correct)
        return corrections;

    Levenshtein generator(input);
    for (std::string permutation: generator.permutations()) {
        Node *result = search(permutation);
        if (result && result->currentState() == endOfWord) corrections.push_back(permutation);
    }

    std::sort(corrections.begin(), corrections.end());  // sort corrections by alphabetical order
    corrections.erase(std::unique(corrections.begin(), corrections.end()), corrections.end());

    return corrections;

}

std::vector<std::string> Tree::getSuggestions(){
    return suggestions_;
}

std::vector<std::string> Tree::getLexique(){
    return lexique_;
}
