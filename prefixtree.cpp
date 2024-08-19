#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <functional>

// Represents a node in the Prefix Tree (Trie)
struct TrieNode {
    std::unordered_map<char, TrieNode*> children; // Map to store child nodes for each character
    bool isEndOfWord = false; // Flag to indicate if this node marks the end of a word

    TrieNode() {}
};

class Trie {
private:
    TrieNode* root; // Root node of the Trie

public:
    Trie() {
        root = new TrieNode(); // Initialize the root node
    }

    // Insert a word into the Trie
    void insert(const std::string& word) {
        TrieNode* currentNode = root;
        for (char c : word) {
            if (currentNode->children.find(c) == currentNode->children.end()) {
                currentNode->children[c] = new TrieNode();
            }
            currentNode = currentNode->children[c];
        }
        currentNode->isEndOfWord = true; 
    }

    // Search for a word in the Trie
    bool search(const std::string& word) {
        TrieNode* currentNode = root;
        for (char c : word) {
            if (currentNode->children.find(c) == currentNode->children.end()) {
                return false; 
            }
            currentNode = currentNode->children[c];
        }
        return currentNode->isEndOfWord; 
    }

    // Check if a prefix exists in the Trie
    bool startsWith(const std::string& prefix) {
        TrieNode* currentNode = root;
        for (char c : prefix) {
            if (currentNode->children.find(c) == currentNode->children.end()) {
                return false; 
            }
            currentNode = currentNode->children[c];
        }
        return true; // If we reach the end of the prefix, it exists
    }

    // Visualize the Prefix Tree (Trie) structure - this can be complex, so I'll provide a basic version
    void visualize() {
        if (!root) {
            std::cout << "<empty>\n";
            return;
        }

        std::function<void(TrieNode*, const std::string)> recursiveVisualize;
        recursiveVisualize = [&](TrieNode* node, std::string prefix) {
            for (const auto& pair : node->children) {
                char c = pair.first;
                TrieNode* child = pair.second;
                std::cout << prefix << c;
                if (child->isEndOfWord) {
                    std::cout << "*"; // Mark end of word
                }
                std::cout << std::endl;
                recursiveVisualize(child, prefix + c); 
            }
        };

        recursiveVisualize(root, ""); 
    }
};

int main() {
    Trie trie;
    trie.insert("apple");
    trie.insert("app");
    trie.insert("banana");
    trie.insert("bat");

    std::cout << trie.search("apple") << std::endl;   // Output: 1 (true)
    std::cout << trie.search("app") << std::endl;      // Output: 1 (true)
    std::cout << trie.startsWith("appl") << std::endl; // Output: 1 (true)
    std::cout << trie.startsWith("bana") << std::endl; // Output: 1 (true)

    std::cout << "\nVisualization:\n";
    trie.visualize();

    return 0;
}
