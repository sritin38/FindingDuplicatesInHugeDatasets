#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <chrono>

#include "CountFrequency.cpp"
#include "NumberFormation.cpp"
#include "Heap.cpp"
#include "Node.cpp"

// #include "Date.cpp"
// #include "Hash.cpp"

using namespace std;
using namespace std::chrono;

void start() {

    // dataset 1 file path
    string string_path_1 = "../data/dna1.txt";
    string string_path_2 = "../data/dna2.txt";
    string str1;
    string str2;
    
    // Read from the text file
    ifstream input_file1(string_path_1);
    string line;

    // Check if the file is successfully opened 
    if (input_file1.is_open()) {
        while (getline(input_file1, line)) { 

            str1 = str1.append(line);
        }
    }
    // Close the file 
    input_file1.close();

    // Read from the text file
    ifstream input_file2(string_path_2);
    line = "";

    // Check if the file is successfully opened 
    if (input_file2.is_open()) {
        while (getline(input_file2, line)) { 

            str2 = str2.append(line);
        }
    }
    // Close the file 
    input_file2.close();

    str1 = "CCCTCGGCCATTACTACTCACTT"; //GGAGGGGGCAAGAGCCTGTAGATGCGT";
    str2 = "CCCTCGGCAATTACTACTCACTT"; //GGAGGGGGCAAGAGCCTGTAGATGCGT";

    // Counting character frequency of the string
    unordered_map<char, long> str1_freq = CountFrequency::count_frequency(str1);
    unordered_map<char, long> str2_freq = CountFrequency::count_frequency(str2);

    // Display character frequency
    cout << "String 1 frequency value assignment: " << endl;
    for (const auto& pair : str1_freq) {
        cout << pair.first << ": " << pair.second << endl;
    }

    cout << "String 2 frequency pairs: " << endl;
    for (const auto& pair : str2_freq) {
        cout << pair.first << ": " << pair.second << endl;
    }

    // Window size, that will slide accross the string
    int window_size = 5; //50;
    // Kmer size, that could be a potential minimizer
    int kmer_size = 3; //15;

    // Get list of minimizers of string 1.
    cout << "List of Minimizers of string 1." << endl;
    vector<Minimiser> minimizers1 = Minimiser::get_minimisers(str1_freq, str1, kmer_size, window_size);
    // vector<Minimiser> minimizers1 = Minimiser::get_minimisers_space(str1_freq, str1, kmer_size, window_size);
    for (auto& k: minimizers1) {

        auto val1 = str1.substr(k.offset, kmer_size);
        auto val2 = k.kmer;
        cout << str1.substr(k.offset, kmer_size) << " : " << k.kmer << endl;
    }

    // Get list of minimizers of string 2.
    cout << "List of Minimizers of string 2." << endl;
    vector<Minimiser> minimizers2 = Minimiser::get_minimisers(str1_freq, str2, kmer_size, window_size);
    // vector<Minimiser> minimizers2 = Minimiser::get_minimisers_space(str1_freq, str2, kmer_size, window_size);
    for (auto& k: minimizers2) {
        auto val1 = str2.substr(k.offset, kmer_size);
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
    

    // cout << "Heap size of string 1: " << str1_heap.size << endl;
    // cout << "Heap size of string 2: " << str2_heap.size << endl;
}

int main() {

    auto start_timer = high_resolution_clock::now();
    start();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start_timer);
    cout << duration.count() << endl;
    return 0;
}