#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "CountFrequency.cpp"
#include "NumberFormation.cpp"
#include "Heap.cpp"

#include "Date.cpp"
#include "Hash.cpp"
#include "Minimizer.cpp"
#include "../include/rabinkarphash.h"

using namespace std;

std::vector<Minimizer> get_minimizers(string sequence, KarpRabinHash<> hasher, int string_window, int kmer_size) {

    std::vector<Minimizer> minimizers_list;
    Hash hash = Hash("", kmer_size);
    std::size_t index = 0;

    while (index <= sequence.length() - string_window) {

        std::string windowSequence;
        if (index+string_window < sequence.length()) {
            windowSequence = sequence.substr(index, string_window);
        }
        else {
            windowSequence = sequence.substr(index, sequence.length()-1);
        }

        hash.update_string_value(windowSequence);
        Minimizer minimizer = hash.get_min_hash(hasher);

        minimizer.offset = minimizer.offset + index;
        minimizers_list.push_back(minimizer);
        index = index + string_window;
    }

    return minimizers_list;
}

void display_minimizers(std::vector<Minimizer> minimizer_list) {

    for(int i=0; i<minimizer_list.size(); i++) {

        std::cout << "String minimizer no " << i << " " << minimizer_list[i].value << " " << minimizer_list[i].hash << " " << minimizer_list[i].offset << endl;
    }
}

void start() {

    // Sample string values
    string str1 = "CCCTCGGCAATTACTACTCACTTGGAGGGGGCAAGAGCCTGTAGATGCGT";
    string str2 = "CCCTCGGCAATTACTACTCACTTGGAGGGGGCAAGAGCCTGTAGATGCGT";

    // Counting character frequency of the string
    unordered_map<char, int> str1_freq = CountFrequency::count_frequency(str1);
    unordered_map<char, int> str2_freq = CountFrequency::count_frequency(str2);

    // Display character frequency
    // cout << "String 1 frequency pairs: " << endl;
    // for (const auto& pair : str1_freq) {
    //     cout << pair.first << ": " << pair.second << endl;
    // }

    // cout << "String 2 frequency pairs: " << endl;
    // for (const auto& pair : str2_freq) {
    //     cout << pair.first << ": " << pair.second << endl;
    // }

    // Window size, that will slide accross the string
    int window_size = 6;
    // Kmer size, that could be a potential minimizer
    int kmer_size = 3;

    // Get list of minimizers of string 1.
    cout << "List of Minimizers of string 1." << endl;
    vector<Minimiser> minimizers1 = Minimiser::get_minimisers(str1_freq, str1, kmer_size, window_size);
    for (auto& k: minimizers1) {

        auto val1 = str1.substr(k.offset, kmer_size);
        auto val2 = k.kmer;
        cout << str1.substr(k.offset, kmer_size) << " : " << k.kmer << endl;
    }

    // Get list of minimizers of string 2.
    cout << "List of Minimizers of string 1." << endl;
    vector<Minimiser> minimizers2 = Minimiser::get_minimisers(str2_freq, str2, kmer_size, window_size);
    for (auto& k: minimizers2) {
        auto val1 = str1.substr(k.offset, kmer_size);
        auto val2 = k.kmer;
        cout << str2.substr(k.offset, kmer_size) << " : " << k.kmer << endl;
    }

    // Create heap for string 1.
    cout << "Heap for string 1." << endl;
    MaxHeap str1_heap = MaxHeap(minimizers1.size());
    str1_heap.buildHeap(minimizers1);
    str1_heap.print();

    // Create heap for string 2
    cout << "Heap for string 2." << endl;
    MaxHeap str2_heap = MaxHeap(minimizers2.size());
    str2_heap.buildHeap(minimizers2);
    str2_heap.print();

    // Search minimizers of string 1 in heap of string 2.
    while (str1_heap.size != -1) {

        Minimiser str1_top_kmer = str1_heap.pop();
        Minimiser match_substr = str2_heap.search(str1_top_kmer.kmer);
        cout << "Minimizers of string 1 and 2 matched: " << match_substr.kmer << " " << str1.substr(match_substr.offset, kmer_size) << endl;
    }
    cout << "Heap size of string 1: " << str1_heap.size << endl;
    cout << "Heap size of string 2: " << str2_heap.size << endl;
}

int main() {

    start();

    // Date birthDay = Date();
    // birthDay.display();
    // Date deathDay(4, 4, 2030);
    // deathDay.display();

    // int substring_window = 5;
    // int hash_bits = 32;
    // KarpRabinHash<> hasher(substring_window, hash_bits); // Create a KarpRabinHash object

    // for (int i=0; i<10; i++) {
    //     hasher.eat(i);
    //     std::cout << "Hash of '" << i << "' is: " << hasher.hashvalue << std::endl;
    // }
    // std::cout << "Hash of '" << 1 << "' is: " << hasher.hashvalue << std::endl;

    // // string str1 = "ABAAABBAACBAAAAABBAABABAA";
    // // string str2 = "ABAAABAACBAABBABAAAAABBAB";

    // // int string_window = 12;
    // // int kmer_size = 5;
    
    // // Hash hash = Hash("", kmer_size);

    // // std::vector<Minimizer> minimizers_list_str1 = get_minimizers(str1, hasher, string_window, kmer_size);
    // // std::vector<Minimizer> minimizers_list_str2 = get_minimizers(str2, hasher, string_window, kmer_size);

    // // // size_t val1 = hash.get_min_hash(hasher);
    // // display_minimizers(minimizers_list_str1);
    // // std::cout << endl;
    // // display_minimizers(minimizers_list_str2);

    // //

    // // hash.update_string_value("ABAAABAACBAABBABAAAAABBAB");
    // // size_t val2 = hash.get_min_hash(hasher);

    // // std::cout << "The hash1 is " << val1 << std::endl;
    // // std::cout << "The hash2 is " << val2 << std::endl;
}