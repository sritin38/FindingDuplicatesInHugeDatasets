#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

struct CountFrequency {

    static unordered_map<char, int> count_frequency(string dataset) {

        // 1. Read the Dataset (Replace with your actual data loading)
        // std::string dataset = "CCCTCGGCAATTACTACTCACTTGGAGGGGGCAAGAGCCTGTAGATGCGTCTCCTAAATGGGCGGCGACAGGTTATATCCACATTGTGCACAACATCGGGCGGCGAGTAGAATTATCGCGCGAGAGCGCTAACTTACTAGCCCCTTTCACGCTCAAGAGTGATGTCTACTCCCTTCAGCGCTGTCACCGAAGGGCTATATGCCCATTAAGACTATGCAACATGTCTACGGCATCGTGTCGCAGCGAAGGCTACAATATGAGGCGCCGGGATTTTGACCGTCTTCCTCTAAACCGCCGTTGGGTGCGCGTAGACATGTATGTTTAAAGCGAGCTGTTTTAGCCAGGGAACAGTGCTTGAGGGGCCGGTTGAGGCAGAAACACAGCCCTTTCTCGCGGGTCTGTTTCGTCCGGACAGCGCGAACTCTGCCGAATCACTGTGCCGCAGCCCGGCAGGTTAAGCTTGTAATTGCAGTGCATATCGTAGTTCACCCTGCGTAGTCTATACGCCAATCCGCAGCACCTTTACGATGGGTCCAAAACCAAGCTGCGATATTGGGGTGCAAGGGTCACGACCAAAGAACTTTACTCTCAGTTTCAGAGCGACAGGCACGATTGCCATCGCTCCGTCCAAATGGACCGCTGTATTAGGAGCTGATTGTGCCTTAGAACTCAATCTCCGGATATTCGAGATAACGCACGGGTTTTCAGCCTGCACGGCTGTGGCTAAGAAAGGTAAGCAGCAGTGAGAGCTATGATAGATCAGGCATGTGCACATCTCGGATTCTAGATATATATGGTTTGTCTACCGCAGCGAGGCAACTTGTCGCGCCTGTATGATCGTATGGCGGCAGCGATCACCGCTCGTAATTAGATTCAGCTCTCAGCTGAGGGGGCATAAGCCGCCCTTTCTACAAGTATAAGGGACACTCTGTCACGGATGACTCTTCCGACTACTATTCCCGTTCGCAGAACCGGACTGCGCTATCCGTGCGGTGCTTTA"; 

        // 2. Count Character Frequencies
        std::unordered_map<char, int> frequencyMap;
        for (char c : dataset) {
            frequencyMap[c]++;
        }

        // 3. Sort Characters by Frequency (Descending Order)
        std::vector<std::pair<char, int>> sortedFrequencies(frequencyMap.begin(), frequencyMap.end());
        std::sort(sortedFrequencies.begin(), sortedFrequencies.end(), 
                [](const auto& a, const auto& b) { return a.second > b.second; });

        // 4. Assign Numeric Values Based on Frequency Rank
        std::unordered_map<char, int> charToValueMap;
        int numericValue = sortedFrequencies.size(); // Start with the highest value
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