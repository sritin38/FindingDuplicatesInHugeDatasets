#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <chrono>

// #include "CountFrequency.cpp"
#include "NumberFormation.cpp"
#include "Heap.cpp"
#include "Node.cpp"

// #include "RabinKarpRollingHash.cpp"

// #include "Date.cpp"
// #include "Hash.cpp"

using namespace std;
using namespace std::chrono;

void start() {

    // dataset 1 file path
    string string_path_1 = "../data/proteins1.txt";
    string string_path_2 = "../data/proteins2.txt";
    // string string_path_1 = "../data/huge_datasets/dna1.txt";
    // string string_path_2 = "../data/huge_datasets/dna2.txt";
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

    // str1 = "CCCTCGGCCATTACTACTCACTTGATAGTGCGATGAGCCTGTAGATGCGT";
    // str2 = "CCCTCGGCAATTACTACTCACTTGGAGGGGGCAAGAGCCTGTAGATGCGT";
    // str2 = "GTGCTCTAGCGATAGTGCGATAAGTGATTAGTACTACGGGGGGGCATGAT";

    // Window size, that will slide accross the string
    int window_size = 1000;
    // Kmer size, that could be a potential minimizer
    int kmer_size = 50;

    // Get list of minimizers of string 1.
    cout << "Minimizers for string 1 is generating..." << endl;

    // Get minimizers 
    // vector<Minimiser> minimizers1 = Minimiser::get_minimisers(str1, kmer_size, window_size);

    // Get minimizers with jumping window
    vector<Minimiser> minimizers1 = Minimiser::get_minimisers_spaced_hash(str1, kmer_size, window_size);
    
    cout << "Minimizer list for string 1 is generated." << endl;
    
    // Display minimizer list of string 1.
    // for (auto& k: minimizers1) {

    //     auto val1 = str1.substr(k.offset, kmer_size);
    //     auto val2 = k.kmer;
    //     cout << str1.substr(k.offset, kmer_size) << " : " << k.kmer << endl;
    // }

    // Get list of minimizers of string 2.
    cout << "Minimizers for string 2 is generating..." << endl;

    // Get minimizers 
    // vector<Minimiser> minimizers2 = Minimiser::get_minimisers(str2, kmer_size, window_size);

    // Get minimizers with jumping window
    vector<Minimiser> minimizers2 = Minimiser::get_minimisers_spaced_hash(str2, kmer_size, window_size);

    cout << "Minimizer list for string 2 is generated." << endl;
    
    // Display minimizers list of string 2.
    // for (auto& k: minimizers2) {
    //     auto val1 = str2.substr(k.offset, kmer_size);
    //     auto val2 = k.kmer;
    //     cout << str2.substr(k.offset, kmer_size) << " : " << k.kmer << endl;
    // }

    // Create heap for string 2
    cout << "Heap created for string 2." << endl;
    MaxHeap str2_heap = MaxHeap(minimizers2.size());
    str2_heap.buildHeap(minimizers2);
    // str2_heap.print();

    // Search minimizers of string 1 in heap of string 2.
    size_t lcs_offset = 0;
    size_t lcs_length = 0;
    while (minimizers1.size() > 0) {

        Minimiser str1_top_kmer = minimizers1[0];
        minimizers1.erase(minimizers1.begin());
        Minimiser match_substr = str2_heap.search(str1_top_kmer.kmer);
        if (match_substr.offset == -1 || match_substr.kmer == -1) {

            continue;
        }
        // cout << "Minimizers of string 1 and 2 matched: " << match_substr.kmer << " " << str1.substr(match_substr.offset, kmer_size) << " | string1: " << str1_top_kmer.offset << " | string2: " << match_substr.offset << endl;

        // Forward search
        long lcs_suffix = 0;
        long str_offset = match_substr.offset + kmer_size;
        for (long i=str1_top_kmer.offset+kmer_size; 
            (str1[i] == str2[str_offset] && str1.length() > i && str2.length() > str_offset); 
            i++, str_offset++) {
            char val1 = str1[i];
            char val2 = str2[str_offset];
            lcs_suffix++;
        }

        long lcs_rev_suffix = 0;
        str_offset = match_substr.offset - 1;
        for (long i=str1_top_kmer.offset - 1; 
            (str1[i] == str2[str_offset] && i >= 0 && str_offset >= 0); 
            i--, str_offset--) {

            lcs_rev_suffix++;
        }

        long str_start = match_substr.offset - lcs_rev_suffix;
        long str_len = lcs_rev_suffix + kmer_size + lcs_suffix;
        if (str_len > lcs_length) {
            lcs_offset = str_start;
            lcs_length = str_len;
        }
    }

    cout << "String matching: " << str1.substr(lcs_offset, lcs_length) << endl << "Length: " << lcs_length << endl;
}

int main() {

    struct rusage usage;
    getrusage(RUSAGE_SELF, &usage);
    // long peakMemoryKB = usage.ru_maxrss;

    auto start_timer = high_resolution_clock::now();
    start();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start_timer);
    
    long peakMemoryKB = usage.ru_maxrss;
    cout << "Time duration: " << duration.count() << " | Memory usage: " << peakMemoryKB << endl;
    return 0;
}