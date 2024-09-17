#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

struct CountFrequency {

    static unordered_map<char, long> count_frequency(string &str) {

        std::unordered_map<char, long> frequencyMap;

        // Count Character Frequencies            
        for (char c : str) {
            frequencyMap[c]++;
        }

        // Sort Characters by Frequency (Descending Order)
        std::vector<std::pair<char, long>> sortedFrequencies(frequencyMap.begin(), frequencyMap.end());
        std::sort(sortedFrequencies.begin(), sortedFrequencies.end(), 
                [](const auto& a, const auto& b) { return a.second > b.second; });

        // Assign Numeric Values Based on Frequency Rank
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


    static unordered_map<char, long> count_frequency(string &str1, string &str2) {

        std::unordered_map<char, long> frequencyMap;

        // Count Character Frequencies            
        for (char c : str1) {
            frequencyMap[c]++;
        }

        for (char c : str2) {
            frequencyMap[c]++;
        }

        // Sort Characters by Frequency (Descending Order)
        std::vector<std::pair<char, long>> sortedFrequencies(frequencyMap.begin(), frequencyMap.end());
        std::sort(sortedFrequencies.begin(), sortedFrequencies.end(), 
                [](const auto& a, const auto& b) { return a.second > b.second; });

        // Assign Numeric Values Based on Frequency Rank
        std::unordered_map<char, long> charToValueMap;
        long numericValue = sortedFrequencies.size(); // Start with the highest value
        for (const auto& pair : sortedFrequencies) {
            charToValueMap[pair.first] = numericValue--;
        }

        return charToValueMap;
    }
};