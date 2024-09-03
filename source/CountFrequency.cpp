#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct CountFrequency {

    static unordered_map<char, long> count_frequency(string string_path) {

        // 1. Read the Dataset (Replace with your actual data loading)
        // std::string dataset = "CCCTCGGCAATTACTACTCACTTGGAGGGGGCAAGAGCCTGTAGATGCGTCTCCTAAATGGGCGGCGACAGGTTATATCCACATTGTGCACAACATCGGGCGGCGAGTAGAATTATCGCGCGAGAGCGCTAACTTACTAGCCCCTTTCACGCTCAAGAGTGATGTCTACTCCCTTCAGCGCTGTCACCGAAGGGCTATATGCCCATTAAGACTATGCAACATGTCTACGGCATCGTGTCGCAGCGAAGGCTACAATATGAGGCGCCGGGATTTTGACCGTCTTCCTCTAAACCGCCGTTGGGTGCGCGTAGACATGTATGTTTAAAGCGAGCTGTTTTAGCCAGGGAACAGTGCTTGAGGGGCCGGTTGAGGCAGAAACACAGCCCTTTCTCGCGGGTCTGTTTCGTCCGGACAGCGCGAACTCTGCCGAATCACTGTGCCGCAGCCCGGCAGGTTAAGCTTGTAATTGCAGTGCATATCGTAGTTCACCCTGCGTAGTCTATACGCCAATCCGCAGCACCTTTACGATGGGTCCAAAACCAAGCTGCGATATTGGGGTGCAAGGGTCACGACCAAAGAACTTTACTCTCAGTTTCAGAGCGACAGGCACGATTGCCATCGCTCCGTCCAAATGGACCGCTGTATTAGGAGCTGATTGTGCCTTAGAACTCAATCTCCGGATATTCGAGATAACGCACGGGTTTTCAGCCTGCACGGCTGTGGCTAAGAAAGGTAAGCAGCAGTGAGAGCTATGATAGATCAGGCATGTGCACATCTCGGATTCTAGATATATATGGTTTGTCTACCGCAGCGAGGCAACTTGTCGCGCCTGTATGATCGTATGGCGGCAGCGATCACCGCTCGTAATTAGATTCAGCTCTCAGCTGAGGGGGCATAAGCCGCCCTTTCTACAAGTATAAGGGACACTCTGTCACGGATGACTCTTCCGACTACTATTCCCGTTCGCAGAACCGGACTGCGCTATCCGTGCGGTGCTTTA"; 

        // Read from the text file
        ifstream input_file(string_path);
        string line;
        std::unordered_map<char, long> frequencyMap;

        // Check if the file is successfully opened 
        if (input_file.is_open()) {
            while (getline(input_file, line)) { 

                // 2. Count Character Frequencies            
                for (char c : line) {
                    frequencyMap[c]++;
                }
            }
        }

        // Close the file 
        input_file.close();

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