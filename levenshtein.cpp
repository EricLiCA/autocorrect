#include "levenshtein.h"

Levenshtein::Levenshtein(std::string word) {
    word_ = word;
    updatePermutations();
}

void Levenshtein::updatePermutations() {
    wordPermutations_.clear();
    wordPermutations_.push_back(word_);
    replaceLetter();
    swapLetters();

}

void Levenshtein::replaceLetter() {
    char alphabet = 'a';
    for (int i = 0; i < word_.size(); ++i) {
        for (int j = 0; j < 26; ++j) {
            char replacementCharacter = alphabet + j;
            if (replacementCharacter != word_[i]) {
                std::string copyWord = word_;
                copyWord[i] = replacementCharacter;
                wordPermutations_.push_back(copyWord);
            }
        }
    }
}

void Levenshtein::insertLetter() {
    char alphabet = 'a';
    for (int i = 0; i < word_.size() + 1; ++i) {
        for (int j = 0; j < 26; ++j) {
            char characterToInsert = alphabet + j;
            std::string copyWord = word_;
            copyWord.insert(i, 1, characterToInsert);
            wordPermutations_.push_back(copyWord);
        }
    }
}

void Levenshtein::removeLetter() {
    for (int i = 0; i < word_.size(); ++i) {
        std::string copyWord = word_;
        copyWord.erase(i, 1);
        wordPermutations_.push_back(copyWord);
    }
}

void Levenshtein::swapLetters() {
    for (int i = 0; i < word_.size() - 1; ++i) {
        std::string copyWord = word_;
        std::swap(copyWord[i], copyWord[i + 1]);
        wordPermutations_.push_back(copyWord);
    }
}

void Levenshtein::updateWord(std::string word) {
    word_ = word;
}

void Levenshtein::printPermutations() {
    for (int i = 0; i < wordPermutations_.size(); ++i) {
        std::cout << wordPermutations_[i] << std::endl;
    }
    std::cout << "Permutations: " << wordPermutations_.size() << std::endl;
}

std::vector<std::string> Levenshtein::permutations() {
    return wordPermutations_;
}
