#include <iostream>
#include <string>
#include <vector>
#include "../include/Hash.h"
#include "../include/Minimizer.h"
#include "../include/rabinkarphash.h"

using namespace std;

// Hash construtor
Hash::Hash(string hash_value, int substring_window, int hash_bits) {

    this->hash_string = hash_value;
    this->substring_window = substring_window;
    this->hash_bits = hash_bits;

    KarpRabinHash<> hasher(substring_window, hash_bits); // Create a KarpRabinHash object
}

// Get min hash value from the string
Minimizer Hash::get_min_hash(KarpRabinHash<> hasher) {

    hasher.reset();

    // Calculate initial hash for the first substring
    for (int i = 0; i < substring_window; i++) {

        hasher.eat(hash_string[i]);
    }

    std::cout << "Hash of '" << hash_string.substr(0, substring_window) << "' is: " << hasher.hashvalue << std::endl;
    size_t min_hash = hasher.hashvalue;
    size_t min_index = 0;
    string sequence = hash_string.substr(0, substring_window);

    // Slide the window and update the hash for subsequent substrings
    for (int i = 1; i <= hash_string.length() - substring_window; i++) {

        hasher.update(hash_string[i - 1], hash_string[i + substring_window - 1]); // Update the hash
        std::cout << "Hash of '" << hash_string.substr(i, substring_window) << "' is: " << hasher.hashvalue << std::endl;

        if (min_hash < hasher.hashvalue) {

            min_hash = hasher.hashvalue;
            min_index = i;
            sequence = hash_string.substr(i, substring_window);
        }
    }

    Minimizer minimizer = Minimizer(min_hash, sequence, min_index);

    return minimizer;
}

void Hash::update_string_value(string str) {

    hash_string = str;
}