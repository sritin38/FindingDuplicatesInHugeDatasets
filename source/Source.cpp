#include <iostream>
#include <string>
#include <vector>
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

int main() {
    Date birthDay = Date();
    birthDay.display();
    Date deathDay(4, 4, 2030);
    deathDay.display();

    int substring_window = 5;
    int hash_bits = 32;
    KarpRabinHash<> hasher(substring_window, hash_bits); // Create a KarpRabinHash object

    string str1 = "ABAAABBAACBAAAAABBAABABAA";
    string str2 = "ABAAABAACBAABBABAAAAABBAB";

    int string_window = 12;
    int kmer_size = 5;
    
    Hash hash = Hash("", kmer_size);

    std::vector<Minimizer> minimizers_list_str1 = get_minimizers(str1, hasher, string_window, kmer_size);
    std::vector<Minimizer> minimizers_list_str2 = get_minimizers(str2, hasher, string_window, kmer_size);

    // size_t val1 = hash.get_min_hash(hasher);
    display_minimizers(minimizers_list_str1);
    std::cout << endl;
    display_minimizers(minimizers_list_str2);

    // hash.update_string_value("ABAAABAACBAABBABAAAAABBAB");
    // size_t val2 = hash.get_min_hash(hasher);

    // std::cout << "The hash1 is " << val1 << std::endl;
    // std::cout << "The hash2 is " << val2 << std::endl;
}