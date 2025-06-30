#ifndef TRIE_H
#define TRIE_H
#include <vector>

class TrieNode{
public:
    TrieNode(char& letter){
        this->letter = letter;
    }
    std::vector<TrieNode> children;
    char letter;
};

class HeadTrieNode{
public:
    std::vector<TrieNode> children;
};

class Trie {
public:
    TrieNode head;
    void insert_phrase(std::string& phrase){
        for(auto& child : head.children){
            child.

        }
    }
    Trie();
    Trie(Trie &&) = default;
    Trie(const Trie &) = default;
    Trie &operator=(Trie &&) = default;
    Trie &operator=(const Trie &) = default;
    ~Trie();

private:
    
};

#endif TRIE_H
