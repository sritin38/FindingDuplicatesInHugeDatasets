#include <iostream>
#include <string>
#include "Date.cpp"
#include "Hash.cpp"
#include "../include/rabinkarphash.h"

using namespace std;

int main() {
    Date birthDay = Date();
    birthDay.display();
    Date deathDay(4, 4, 2030);
    deathDay.display();

    int substring_window = 5;
    int hash_bits = 32;
    KarpRabinHash<> hasher(substring_window, hash_bits); // Create a KarpRabinHash object

    Hash hash = Hash("ABAAABBAACBAAAAABBAABABAA", 5);
    size_t val1 = hash.get_min_hash(hasher);

    std::cout << endl;

    hash.update_string_value("ABAAABAACBAABBABAAAAABBAB");
    size_t val2 = hash.get_min_hash(hasher);

    std::cout << "The hash1 is " << val1 << std::endl;
    std::cout << "The hash2 is " << val2 << std::endl;
}