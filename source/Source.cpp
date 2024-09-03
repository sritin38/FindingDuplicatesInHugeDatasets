#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "CountFrequency.cpp"
#include "NumberFormation.cpp"
#include "Heap.cpp"
#include "Node.cpp"
#include "SuffixTree.cpp"
#include "ReverseSuffixTree.cpp"

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

int tree_traverse(string str2, Minimiser match_substr, vector<Node> str_suffix_tree) {

    size_t str_offset = 0;
    size_t i = 0;
    size_t lcs_length = 0;
    size_t node_counter = 0;
    bool iterate = true;
    string str2_substr = str2.substr(match_substr.offset, str2.length());
    while (iterate) {

        int node = 0;
        if (str_suffix_tree[i].ch.size() != 0) {

            node = str_suffix_tree[i].ch[node_counter];
            i = node;
        }
        // leaf node
        if (str_suffix_tree[i].ch.size() == 0) {

            int ch=0;
            for (;ch < str_suffix_tree[i].sub.length(); ch++) {
                char ch_dis = str_suffix_tree[i].sub[ch];
                char val = str2_substr[str_offset];
                if (str_suffix_tree[i].sub[ch] == str2_substr[str_offset]) {

                    lcs_length++;
                    str_offset++;
                }
                else {
                    iterate = false;
                    break; // break from loop
                }
            }

            if (ch == str_suffix_tree[i].sub.length()) {
                iterate = false;
            }
        }
        else {
            int node_sub_length = str_suffix_tree[node].sub.length();
            for (int ch=0; ch < str_suffix_tree[node].sub.length(); ch++) {
                char str2_substr_char = str2_substr[str_offset];
                char tree_suffix = str_suffix_tree[node].sub[ch];
                if (str2_substr[str_offset] == str_suffix_tree[node].sub[ch]) {

                    lcs_length++;
                    str_offset++;

                    if ((ch+1) == str_suffix_tree[node].sub.length()) {

                        node_counter = 0;
                        i = node;
                        break;
                    }
                }
            }
        }
    }

    return lcs_length;
}

int reverse_tree_traverse(string str2, Minimiser match_substr, vector<Node> str_suffix_tree) {

    size_t str_offset = match_substr.offset-1;
    size_t i = 0;
    size_t lcs_length = 0;
    size_t node_counter = 0;
    bool iterate = true;
    string str2_substr = str2.substr(0, match_substr.offset);
    while (iterate) {

        int node = 0;
        if (str_suffix_tree[i].ch.size() != 0) {

            node = str_suffix_tree[i].ch[node_counter];
            i = node;
        }
        // leaf node
        if (str_suffix_tree[i].ch.size() == 0) {

            int ch=0;
            for (;ch < str_suffix_tree[i].sub.length(); ch++) {
                char ch_dis = str_suffix_tree[i].sub[ch];
                char val = str2_substr[str_offset];
                if (str_suffix_tree[i].sub[ch] == str2_substr[str_offset]) {

                    lcs_length++;
                    str_offset--;
                }
                else {
                    iterate = false;
                    break; // break from loop
                }
            }

            if (ch == str_suffix_tree[i].sub.length()) {
                iterate = false;
            }
        }
        else {
            int node_sub_length = str_suffix_tree[node].sub.length();
            for (int ch=0; ch < str_suffix_tree[node].sub.length(); ch++) {
                char str2_substr_char = str2_substr[str_offset];
                char tree_suffix = str_suffix_tree[node].sub[ch];
                if (str2_substr[str_offset] == str_suffix_tree[node].sub[ch]) {

                    lcs_length++;
                    str_offset--;

                    if ((ch+1) == str_suffix_tree[node].sub.length()) {

                        node_counter = 0;
                        i = node;
                        break;
                    }
                }
            }
        }
    }

    return lcs_length;
}

void start() {

    // Sample string values
    string str1 = "CCCTCGGCCATTACTACTCACTTGGAGGGGGCAAGAGCCTGTAGATGCGT";
    string str2 = "CCCTCGGCAATTACTACTCACTTGGAGGGGGCAAGAGCCTGTAGATGCGT";

    // Counting character frequency of the string
    unordered_map<char, long> str1_freq = CountFrequency::count_frequency(str1);
    unordered_map<char, long> str2_freq = CountFrequency::count_frequency(str2);

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
    cout << "List of Minimizers of string 2." << endl;
    vector<Minimiser> minimizers2 = Minimiser::get_minimisers(str1_freq, str2, kmer_size, window_size);
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
        cout << "Minimizers of string 1 and 2 matched: " << match_substr.kmer << " " << str1.substr(match_substr.offset, kmer_size) << endl;

        SuffixTree suffix_tree = SuffixTree(str1.substr(str1_top_kmer.offset, str1.length()));
        suffix_tree.visualize();
        vector<Node> str_suffix_tree = suffix_tree.get_nodes();

        int lcs_suffix = tree_traverse(str2, match_substr, str_suffix_tree);
        cout << "LCS: " << lcs_suffix << endl;
        
        cout << endl;
        int lcs_rev_suffix = 0;
        if (match_substr.offset > 0) {
             
            ReverseSuffixTree rev_suffix_tree = ReverseSuffixTree(str1.substr(0, str1_top_kmer.offset));
            rev_suffix_tree.visualize();
            vector<Node> str_rev_suffix_tree = rev_suffix_tree.get_nodes();
            lcs_rev_suffix = reverse_tree_traverse(str2, match_substr, str_rev_suffix_tree);
            cout << "LCS Reverse: " << lcs_rev_suffix << endl;
        }

        int str_start = match_substr.offset - lcs_rev_suffix;
        int str_len = lcs_rev_suffix + lcs_suffix;
        cout << "TOTAL TREE LCS: " << str1.substr(str_start, str_len) << endl << "Length: " << str_len << endl;
    }

    cout << "Heap size of string 1: " << str1_heap.size << endl;
    cout << "Heap size of string 2: " << str2_heap.size << endl;

    // Implementing Sparse Suffix Tree and Reverse Sparse Suffix Tree
    // how to compare the 2 strings 
    // get the offset of 1 string and extract the substring from dataset
    // create the suffix tree of the other string

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