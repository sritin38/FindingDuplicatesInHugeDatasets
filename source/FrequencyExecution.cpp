#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <chrono>
#include <sys/resource.h>

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
    string string_path_1 = "../data/proteins1.txt";
    string string_path_2 = "../data/proteins2.txt";
    // string string_path_1 = "../data/NoLCS/1.txt";
    // string string_path_2 = "../data/NoLCS/2.txt";
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

    // str1 = "CCCTCGGCCATTACTACTCACTTGGAGGGGGCAAGAGCCTGTAGATGCGT";
    // str2 = "CCCTCGGCAATTACTACTCACTTGGAGGGGGCAAGAGCCTGTAGATGCGT";
    // str2 = "GTGCTCTAGCGATAGTGCGATAAGTGATTAGTACTCACTTGGAGCATGAT";

    // Counting character frequency of the string
    unordered_map<char, long> str_freq = CountFrequency::count_frequency(str1, str2);

    // Display character frequency
    // cout << "String frequency assigned " << endl;
    // for (const auto& pair : str1_freq) {
    //     cout << pair.first << ": " << pair.second << endl;
    // }

    // Window size, that will slide accross the string
    int window_size = 100;
    // Kmer size, that could be a potential minimizer
    int kmer_size = 7;

    // Get list of minimizers of string 1.
    cout << "Minimizers for string 2 is generating..." << endl;

    // Old minimizer computation method
    // vector<Minimiser> minimizers1 = Minimiser::get_minimisers(str_freq, str1, kmer_size, window_size);

    // Old minimizer with jumping window method
    // vector<Minimiser> minimizers1 = Minimiser::get_minimisers_space(str_freq, str1, kmer_size, window_size);

    // New minimizer computation method
    vector<Minimiser> minimizers1 = Minimiser::get_minimisers_frequency(str_freq, str1, kmer_size, window_size);
    
    // New minimizer with jumping window method
    // vector<Minimiser> minimizers1 = Minimiser::get_minimisers_spaced_frequency(str_freq, str1, kmer_size, window_size);

    cout << "Minimizer list for string 1 is generated." << endl;
    
    // Display
    // for (auto& k: minimizers1) {

    //     auto val1 = str1.substr(k.offset, kmer_size);
    //     auto val2 = k.kmer;
    //     cout << str1.substr(k.offset, kmer_size) << " : " << k.kmer << " | " << k.offset << endl;
    // }

    // Get list of minimizers of string 2.
    cout << "Minimizers for string 2 is generating..." << endl;

    // Old minimizer computation method
    // vector<Minimiser> minimizers2 = Minimiser::get_minimisers(str_freq, str2, kmer_size, window_size);

    // Old minimizer with jumping window method
    // vector<Minimiser> minimizers2 = Minimiser::get_minimisers_space(str_freq, str2, kmer_size, window_size);

    // New minimizer computation method
    vector<Minimiser> minimizers2 = Minimiser::get_minimisers_frequency(str_freq, str2, kmer_size, window_size);

    // New minimizer with jumping window method
    // vector<Minimiser> minimizers2 = Minimiser::get_minimisers_spaced_frequency(str_freq, str2, kmer_size, window_size);

    cout << "Minimizer list for string 2 is generated." << endl;
    
    // Display minimizers
    // for (auto& k: minimizers2) {
    //     auto val1 = str2.substr(k.offset, kmer_size);
    //     auto val2 = k.kmer;
    //     cout << str2.substr(k.offset, kmer_size) << " : " << k.kmer << " | " << k.offset << endl;
    // }

    // Create heap for string 1.
    // cout << "Heap for string 1." << endl;
    // MaxHeap str1_heap = MaxHeap(minimizers1.size());
    // str1_heap.buildHeap(minimizers1);
    // str1_heap.print();

    // Create heap for string 2
    cout << "Heap created for minimizers of string 2." << endl;
    MaxHeap str2_heap = MaxHeap(minimizers2.size());
    str2_heap.buildHeap(minimizers2);
    // str2_heap.print();

    // Search minimizers of string 1 in heap of string 2.
    // while (str1_heap.size != -1) {

    //     Minimiser str1_top_kmer = str1_heap.pop();
    //     Minimiser match_substr = str2_heap.search(str1_top_kmer.kmer);
    //     if (match_substr.offset == -1 || match_substr.kmer == -1) {

    //         continue;
    //     }
    //     cout << "Minimizers of string 1 and 2 matched: " << match_substr.kmer << " " << str1.substr(match_substr.offset, kmer_size) << endl;

    //     // Forward search
    //     long lcs_suffix = 0;
    //     long str_offset = match_substr.offset + kmer_size;
    //     for (long i=str1_top_kmer.offset+kmer_size; 
    //         (str1[i] == str2[str_offset] && str1.length() > i && str2.length() > str_offset); 
    //         i++, str_offset++) {
    //         char val1 = str1[i];
    //         char val2 = str2[str_offset];
    //         lcs_suffix++;
    //     }

    //     long lcs_rev_suffix = 0;
    //     str_offset = match_substr.offset - 1;
    //     for (long i=str1_top_kmer.offset - 1; 
    //         (str1[i] == str2[str_offset] && i >= 0 && str_offset >= 0); 
    //         i--, str_offset--) {

    //         lcs_rev_suffix++;
    //     }

    //     long str_start = match_substr.offset - lcs_rev_suffix;
    //     long str_len = lcs_rev_suffix + kmer_size + lcs_suffix;
    //     cout << "String matching: " << str1.substr(str_start, str_len) << endl << "Length: " << str_len << endl;
    // }

    // cout << "Heap size of string 1: " << str1_heap.size << endl;
    // cout << "Heap size of string 2: " << str2_heap.size << endl;

    // Search minimizers of string 1 in heap of string 2.
    auto str2_heap_dup = str2_heap;
    size_t lcs_offset = 0;
    size_t lcs_length = 0;
    while (minimizers1.size() > 0) {

        Minimiser str1_top_kmer = minimizers1[0];
        minimizers1.erase(minimizers1.begin());
        str2_heap_dup = str2_heap;
        Minimiser match_substr = str2_heap_dup.search(str1_top_kmer.kmer);
        do {

            str2_heap_dup.deleteKey(str1_top_kmer.kmer);

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

                lcs_length = str_len;
                lcs_offset = str_start;
            }

            match_substr = str2_heap_dup.search(str1_top_kmer.kmer);
        } while (match_substr.kmer != -1);
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