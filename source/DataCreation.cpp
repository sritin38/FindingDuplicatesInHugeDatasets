#include <iostream>
#include <random>
#include <string>

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3); // For DNA (0-3 for A, C, G, T)

    int sequenceLength = 1000; // Adjust as needed
    std::string sequence;

    for (int i = 0; i < sequenceLength; ++i) {
        sequence += "ACGT"[dis(gen)]; 
    }

    std::cout << sequence << std::endl;
    return 0;
}