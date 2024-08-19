#include <iostream>
#include <string>
#include "../include/rabinkarphash.h" // Include your header file

int main() {
    std::string inputString = "ABCABCD";
    int substringLength = 3; // Length of substrings (sliding window size)
    int hashBits = 32; // Desired number of bits in the hash value

    KarpRabinHash<> hasher(substringLength, hashBits); // Create a KarpRabinHash object

    // Calculate initial hash for the first substring
    for (int i = 0; i < substringLength; i++) {
        hasher.eat(inputString[i]);
    }
    std::cout << "Hash of '" << inputString.substr(0, substringLength) << "' is: " << hasher.hashvalue << std::endl;

    // Slide the window and update the hash for subsequent substrings
    for (int i = 1; i <= inputString.length() - substringLength; i++) {
        hasher.update(inputString[i - 1], inputString[i + substringLength - 1]); // Update the hash
        std::cout << "Hash of '" << inputString.substr(i, substringLength) << "' is: " << hasher.hashvalue << std::endl;
    }

    return 0;
}