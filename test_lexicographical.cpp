#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
// #include <bits/stdc++.h>

// Minimizer structure
struct Minimizer {
    std::string kmer;
    int offset;
};

Minimizer extractMinimizerLexicographical(std::string& str, int kmer) {

    Minimizer minimizer;
    std::vector<std::string> strings = {};
    for (int i=0; i <= str.length()-kmer; i++) {
        strings.push_back(str.substr(i,kmer));
    }

    std::sort(strings.begin(), strings.end());
    int index = str.find(strings[0]);

    minimizer.kmer = strings[0];
    minimizer.offset = index;
    return minimizer;
}

std::vector<Minimizer> windowStringSequence(std::string& sequence, int kmerSize, int windowSize) {
    
    std::vector<Minimizer> minimizersList;
    std::size_t index = 0;
    
    // CAN BE DONE USING MULTI THREADING/PROCESSING.
    while (index <= sequence.length() - windowSize) {
        std::string windowSequence;
        if (index+windowSize < sequence.length()) {
            windowSequence = sequence.substr(index, windowSize);
        }
        else {
            windowSequence = sequence.substr(index, sequence.length()-1);
        }

        Minimizer minimizer = extractMinimizerLexicographical(windowSequence, kmerSize);
        minimizer.offset = minimizer.offset + index; 
        minimizersList.push_back(minimizer);
        index = index + windowSize;
    }
    std::cout << "Minimizers count: " <<minimizersList.size();
    return minimizersList;
}

int main() {
    int kmer = 3;
    int window = 5;
    std::cout << "Testing Lexicographical\n";
    std::string sequence = "ABAAABBAACBAAAAABBAABABAA";
    std::vector<Minimizer> minimizers = windowStringSequence(sequence, kmer, window);
    
    for (int i=0; i<minimizers.size(); i++) {

        std::cout << "\nSequence: " << sequence.substr(minimizers.at(i).offset, kmer) << "\t IndexOffset: " << minimizers.at(i).offset;
    }

    return 0;
}