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

Minimiser extract_minimizer_lexicographical(std::string str, int kmer) {

    Minimiser minimizer;
    std::vector<string> strings = {};
    for (int i=0; i <= str.length()-kmer; i++) {
        strings.push_back(str.substr(i,kmer));
    }

    sort(strings.begin(), strings.end());
    int index = str.find(strings[0]);

    // how are you going to convert this string to its ACSII value so that it can then be inserted into a HEAP
    long value = 0;
    for(int i=0; i<strings[0].length(); i++) {

        value = value + ((int)strings[0][i] - 65);
    }
    minimizer.kmer = value;
    minimizer.offset = index;
    return minimizer;
}

vector<Minimiser> window_string_sequence(std::string& sequence, int kmer_size, int window_size) {
    
    vector<Minimiser> kmers = vector<Minimiser>();
    long potential_kmer = 0;

    for (long i=0; i<=sequence.length()-window_size; i++) {

        long condition = i + window_size - kmer_size;
        long position = 0;

        auto minimizer = extract_minimizer_lexicographical(sequence.substr(i, window_size), kmer_size);
        if (potential_kmer != minimizer.kmer) {

            potential_kmer = minimizer.kmer;
            minimizer.offset = minimizer.offset + i;
            kmers.push_back(minimizer);
        }
        
    }

    return kmers;
}

void start() {

    // dataset 1 file path
    // string string_path_1 = "../data/dna1.txt";
    // string string_path_2 = "../data/dna2.txt";
    string string_path_1 = "../data/large_datasets/dna1.txt";
    string string_path_2 = "../data/large_datasets/dna2.txt";
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

    // str1 = "CCCTCGGCCATTACTACTCACTT"; //GGAGGGGGCAAGAGCCTGTAGATGCGT";
    // str2 = "CCCTCGGCAATTACTACTCACTT"; //GGAGGGGGCAAGAGCCTGTAGATGCGT";

    // Window size, that will slide accross the string
    int window_size = 50;
    // Kmer size, that could be a potential minimizer
    int kmer_size = 15;

    // Get list of minimizers of string 1.
    cout << "List of Minimizers of string 1." << endl;
    vector<Minimiser> minimizers1 = window_string_sequence(str1, kmer_size, window_size);
    for (auto& k: minimizers1) {

        auto val1 = str1.substr(k.offset, kmer_size);
        auto val2 = k.kmer;
        cout << str1.substr(k.offset, kmer_size) << " : " << k.kmer << endl;
    }

    // Get list of minimizers of string 2.
    cout << "List of Minimizers of string 2." << endl;
    vector<Minimiser> minimizers2 = window_string_sequence(str2, kmer_size, window_size);
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
    while (str1_heap.size != -1) {

        Minimiser str1_top_kmer = str1_heap.pop();
        Minimiser match_substr = str2_heap.search(str1_top_kmer.kmer);
        if (match_substr.offset == -1 || match_substr.kmer == -1) {

            continue;
        }
        cout << "Minimizers of string 1 and 2 matched: " << match_substr.kmer << " " << str1.substr(match_substr.offset, kmer_size) << " | string1: " << str1_top_kmer.offset << " | string2: " << match_substr.offset << endl;

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
        cout << "String matching: " << str1.substr(str_start, str_len) << endl << "Length: " << str_len << endl;
    }
}

int main() {

    auto start_timer = high_resolution_clock::now();
    start();
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start_timer);
    cout << duration.count() << endl;
    return 0;
}