#include <iostream>
#include <string>
#include <vector>

struct Node {

    std::string sub;   // a substring of the input string
    std::vector<int> ch;

    Node() {    }
    Node(const std::string& sub, std::initializer_list<int> children) : sub(sub) {

        ch.insert(ch.end(), children);
    }
};