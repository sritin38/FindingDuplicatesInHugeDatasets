#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Minimizer structure
struct Minimizer {
    size_t kmerHash;
    string value;
    int offset;
};

// Simple hash function for demonstration (replace with a robust one if needed)
// param: k size string sequence
// return: hash value of string
std::size_t hashKmer(const std::string& kmer) {
    std::hash<std::string> hasher;
    // hceck for libraries
    // Google 
    return hasher(kmer);
}

// Extract minimizer from a window
// param: string sequence, k-mer
// return: Minimizer object
Minimizer extractMinimizerHash(std::string& sequence, int kmer) {
    
    Minimizer minimizer;
    // Initialize to max possible value
    std::size_t minHash = -1;
    int minPos = sequence.length() +1;

    for (int i=0; i <= sequence.length() - kmer; i++) {

        std::size_t kmerHash = hashKmer(sequence.substr(i, kmer));
        if (kmerHash < minHash) {
            minHash = kmerHash;
            minPos = i;
        }
    }

    minimizer.kmerHash = minHash;
    minimizer.offset = minPos;
    return minimizer;
}

// Window string sequence and get minimizers
// param: string sequence, k-mer size, window size
// return: list of minimizers.
std::vector<Minimizer> windowStringSequence(std::string& sequence, int kmerSize, int windowSize) {
    
    std::vector<Minimizer> minimizersList;
    std::size_t index = 0;
    
    // ABCA
    // CAN BE DONE USING MULTI THREADING/PROCESSING.
    while (index <= sequence.length() - windowSize) {
        std::string windowSequence;
        if (index+windowSize < sequence.length()) {
            windowSequence = sequence.substr(index, windowSize);
        }
        else {
            windowSequence = sequence.substr(index, sequence.length()-1);
        }

        Minimizer minimizer = extractMinimizerHash(windowSequence, kmerSize);
        minimizer.offset = minimizer.offset + index; 
        minimizersList.push_back(minimizer);
        index = index + windowSize;
    }
    std::cout << "Minimizers count: " <<minimizersList.size();
    return minimizersList;
}

int main() {
    int kmer = 4;
    int window = 10;
    std::cout << "Testing Hashing\n";
    std::string sequence = "ABAAABBAACBAAAAABBAABABAA";
    std::vector<Minimizer> minimizers = windowStringSequence(sequence, kmer, window);
    
    for (int i=0; i<minimizers.size(); i++) {

        std::cout << "\nSequence: " << sequence.substr(minimizers.at(i).offset, kmer) << "\tHash: " << minimizers.at(i).kmerHash;
    }
    // Minimizer min = extractMinimizerHash(sequence, kmer);
    // std::cout << "hash kmer: " << min.kmerHash;
    // std::cout << "\nkmer: " << sequence.substr(min.offset, kmer);
    
    std::string seq2 = "ABAAABAACBAABBABAAAAABBAB";
    // Minimizer min2 = extractMinimizerHash(seq2, kmer);
    // std::cout << "\nhash kmer: " << min2.kmerHash;
    // std::cout << "\nkmer: " << seq2.substr(min2.offset, kmer);

    std::vector<Minimizer> minimizers2 = windowStringSequence(seq2, kmer, window);
    for (int i=0; i<minimizers2.size(); i++) {

        std::cout << "\nSequence: " << sequence.substr(minimizers2.at(i).offset, kmer) << "\tHash: " << minimizers2.at(i).kmerHash;
    }
    return 0;
}