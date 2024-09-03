#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>

#include "CountFrequency.cpp"
// #include "NumberFormation.cpp"
// #include "Heap.cpp"
// #include "Node.cpp"

// #include "Date.cpp"
// #include "Hash.cpp"

using namespace std;

void start() {

    // Sample string values
    
    string string_path = "../data/dna.txt";
    string str1 = "CCCTCGGCCATTACTACTCACTTGGAGGGGGCAAGAGCCTGTAGATGCGT";
    string str2 = "CCCTCGGCAATTACTACTCACTTGGAGGGGGCAAGAGCCTGTAGATGCGT";

    // Counting character frequency of the string
    unordered_map<char, long> str1_freq; // = CountFrequency::count_frequency(string_path);
    // unordered_map<char, int> str2_freq = CountFrequency::count_frequency(str2);

    // Display character frequency
    cout << "String 1 frequency pairs: " << endl;
    for (const auto& pair : str1_freq) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // cout << "String 2 frequency pairs: " << endl;
    // for (const auto& pair : str2_freq) {
    //     cout << pair.first << ": " << pair.second << endl;
    // }

    // Window size, that will slide accross the string
    int window_size = 100;
    // Kmer size, that could be a potential minimizer
    int kmer_size = 25;

    // Get list of minimizers of string 1.
    // cout << "List of Minimizers of string 1." << endl;
    // vector<Minimiser> minimizers1 = Minimiser::get_minimisers(str1_freq, str1, kmer_size, window_size);
    // for (auto& k: minimizers1) {

    //     auto val1 = str1.substr(k.offset, kmer_size);
    //     auto val2 = k.kmer;
    //     cout << str1.substr(k.offset, kmer_size) << " : " << k.kmer << endl;
    // }

    // Get list of minimizers of string 2.
    // cout << "List of Minimizers of string 2." << endl;
    // vector<Minimiser> minimizers2 = Minimiser::get_minimisers(str1_freq, str2, kmer_size, window_size);
    // for (auto& k: minimizers2) {
    //     auto val1 = str2.substr(k.offset, kmer_size);
    //     auto val2 = k.kmer;
    //     cout << str2.substr(k.offset, kmer_size) << " : " << k.kmer << endl;
    // }

    // Create heap for string 1.
    // cout << "Heap for string 1." << endl;
    // MaxHeap str1_heap = MaxHeap(minimizers1.size());
    // str1_heap.buildHeap(minimizers1);
    // str1_heap.print();

    // Create heap for string 2
    // cout << "Heap for string 2." << endl;
    // MaxHeap str2_heap = MaxHeap(minimizers2.size());
    // str2_heap.buildHeap(minimizers2);
    // str2_heap.print();

    // Search minimizers of string 1 in heap of string 2.
    // while (str1_heap.size != -1) {

    //     Minimiser str1_top_kmer = str1_heap.pop();
    //     Minimiser match_substr = str2_heap.search(str1_top_kmer.kmer);
    //     cout << "Minimizers of string 1 and 2 matched: " << match_substr.kmer << " " << str1.substr(match_substr.offset, kmer_size) << endl;

        

    //     int str_start = match_substr.offset - lcs_rev_suffix;
    //     int str_len = lcs_rev_suffix + lcs_suffix;
    //     cout << "TOTAL TREE LCS: " << str1.substr(str_start, str_len) << endl << "Length: " << str_len << endl;
    // }

    // cout << "Heap size of string 1: " << str1_heap.size << endl;
    // cout << "Heap size of string 2: " << str2_heap.size << endl;
}

int main() {

    cout<<"Hello";
    start();
    return 0;
}