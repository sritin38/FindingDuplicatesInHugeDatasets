#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

// Function to generate all k-mers and their frequencies
std::unordered_map<std::string, int> generateKmerFrequencies(const std::string& str, int k) {

    std::unordered_map<std::string, int> kmerFrequencies;
    for (size_t i = 0; i <= str.size() - k; ++i) {
        std::string kmer = str.substr(i, k);
        kmerFrequencies[kmer]++;
    }
    return kmerFrequencies;
}

// Function to find minimizers based on frequency
std::vector<std::string> findMinimizers(const std::string& str, int k, int windowSize) {

    std::unordered_map<std::string, int> kmerFrequencies = generateKmerFrequencies(str, k);
    std::vector<std::string> minimizers;

    for (size_t i = 0; i <= str.size() - windowSize; ++i) {
        std::string minimizer = str.substr(i, k);
        int minFrequency = kmerFrequencies[minimizer];

        for (size_t j = 1; j < windowSize - k + 1; ++j) {
            std::string kmer = str.substr(i + j, k);
            int frequency = kmerFrequencies[kmer];
            if (frequency < minFrequency) {
                minimizer = kmer;
                minFrequency = frequency;
            }
        }
        minimizers.push_back(minimizer);
    }
    return minimizers;
}

int main() {

    std::string str = "ABAAABBAACBAAAAABBAABABAA";
    int k = 3;  // Length of k-mers
    int windowSize = 5;  // Size of the window to select minimizers

    // Find minimizers
    std::vector<std::string> minimizers = findMinimizers(str, k, windowSize);
    std::cout << "Minimizers:" << std::endl;
    for (const auto& minimizer : minimizers) {
        std::cout << minimizer << " ";
    }
    std::cout << std::endl;

    return 0;
}
