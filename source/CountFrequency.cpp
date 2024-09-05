#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct CountFrequency {

    static unordered_map<char, long> count_frequency(string &str) {

        // 1. Read the Dataset (Replace with your actual data loading)
        // std::string dataset = "CCCTCGGCAATTACTACTCACTTGGAGGGGGCAAGAGCCTGTAGATGCGTCTCCTAAATGGGCGGCGACAGGTTATATCCACATTGTGCACAACATCGGGCGGCGAGTAGAATTATCGCGCGAGAGCGCTAACTTACTAGCCCCTTTCACGCTCAAGAGTGATGTCTACTCCCTTCAGCGCTGTCACCGAAGGGCTATATGCCCATTAAGACTATGCAACATGTCTACGGCATCGTGTCGCAGCGAAGGCTACAATATGAGGCGCCGGGATTTTGACCGTCTTCCTCTAAACCGCCGTTGGGTGCGCGTAGACATGTATGTTTAAAGCGAGCTGTTTTAGCCAGGGAACAGTGCTTGAGGGGCCGGTTGAGGCAGAAACACAGCCCTTTCTCGCGGGTCTGTTTCGTCCGGACAGCGCGAACTCTGCCGAATCACTGTGCCGCAGCCCGGCAGGTTAAGCTTGTAATTGCAGTGCATATCGTAGTTCACCCTGCGTAGTCTATACGCCAATCCGCAGCACCTTTACGATGGGTCCAAAACCAAGCTGCGATATTGGGGTGCAAGGGTCACGACCAAAGAACTTTACTCTCAGTTTCAGAGCGACAGGCACGATTGCCATCGCTCCGTCCAAATGGACCGCTGTATTAGGAGCTGATTGTGCCTTAGAACTCAATCTCCGGATATTCGAGATAACGCACGGGTTTTCAGCCTGCACGGCTGTGGCTAAGAAAGGTAAGCAGCAGTGAGAGCTATGATAGATCAGGCATGTGCACATCTCGGATTCTAGATATATATGGTTTGTCTACCGCAGCGAGGCAACTTGTCGCGCCTGTATGATCGTATGGCGGCAGCGATCACCGCTCGTAATTAGATTCAGCTCTCAGCTGAGGGGGCATAAGCCGCCCTTTCTACAAGTATAAGGGACACTCTGTCACGGATGACTCTTCCGACTACTATTCCCGTTCGCAGAACCGGACTGCGCTATCCGTGCGGTGCTTTA"; 

        // Read from the text file
        std::unordered_map<char, long> frequencyMap;

        // 2. Count Character Frequencies            
        for (char c : str) {
            frequencyMap[c]++;
        }

        // 3. Sort Characters by Frequency (Descending Order)
        std::vector<std::pair<char, long>> sortedFrequencies(frequencyMap.begin(), frequencyMap.end());
        std::sort(sortedFrequencies.begin(), sortedFrequencies.end(), 
                [](const auto& a, const auto& b) { return a.second > b.second; });

        // 4. Assign Numeric Values Based on Frequency Rank
        std::unordered_map<char, long> charToValueMap;
        long numericValue = sortedFrequencies.size(); // Start with the highest value
        for (const auto& pair : sortedFrequencies) {
            charToValueMap[pair.first] = numericValue--;
        }

        // 5. Output the Mapping
        // std::cout << "Character to Numeric Value Mapping:\n";
        // for (const auto& pair : charToValueMap) {
        //     std::cout << pair.first << ": " << pair.second << std::endl;
        // }

        return charToValueMap;
    }
};

// int main() {
//     CountFrequency::count_frequency("../data/dna.txt");
//     return 0;
// }