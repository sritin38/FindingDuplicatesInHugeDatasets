#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include "RabinKarpRollingHash.cpp"

using namespace std;

struct Minimiser {

    size_t offset;
    long kmer = -1;

    Minimiser (size_t offset, long kmer) {

        this->offset = offset;
        this->kmer = kmer;
    }

    Minimiser() {}

    // Frequency
    static vector<Minimiser> get_minimisers(unordered_map<char, long> str_map, string &str, int kmer_size, int window_size) {

        vector<Minimiser> kmers = vector<Minimiser>();

        long potential_kmer = 0;
        for (long i=0; i<=str.length()-window_size; i++) {

            long condition = i + window_size - kmer_size;
            long new_kmer = 0;
            long position = 0;
            for (long j=i; j<=condition; j++) {

                string str_num;
                for (long k=0; k < kmer_size; k++) {

                    str_num = str_num + to_string(str_map[str.at(j+k)]);
                }
                
                long num = stol(str_num);
                if (j != i) {
                    if (new_kmer > num && new_kmer != num) {

                        new_kmer = num;
                        position = j;
                    }
                }
                else {
                    new_kmer = num;
                    position = j;
                }
            }

            if (potential_kmer != new_kmer) {

                Minimiser minimizer = Minimiser();
                minimizer.offset = position;
                potential_kmer = new_kmer;
                minimizer.kmer = potential_kmer;
                kmers.push_back(minimizer);
            }
        }

        return kmers;
    }

    // Frequency
    static vector<Minimiser> get_minimisers_space(unordered_map<char, long> str_map, string &str, int kmer_size, int window_size) {

        vector<Minimiser> kmers = vector<Minimiser>();

        long potential_kmer = 0;
        for (long i=0; i<=str.length()-window_size; i=i+window_size) {

            long condition = i + window_size - kmer_size;
            long new_kmer = 0;
            long position = 0;
            for (long j=i; j<=condition; j++) {

                string str_num;
                for (long k=0; k < kmer_size; k++) {

                    str_num = str_num + to_string(str_map[str.at(j+k)]);
                }
                
                long num = stol(str_num);
                if (j != i) {
                    if (new_kmer > num && new_kmer != num) {

                        new_kmer = num;
                        position = j;
                    }
                }
                else {
                    new_kmer = num;
                    position = j;
                }
            }

            if (potential_kmer != new_kmer) {

                Minimiser minimizer = Minimiser();
                minimizer.offset = position;
                potential_kmer = new_kmer;
                minimizer.kmer = potential_kmer;
                kmers.push_back(minimizer);
            }
        }

        return kmers;
    }

    // Frequency
    static vector<Minimiser> get_minimisers_frequency(unordered_map<char, long> str_map, string &str, int kmer_size, int window_size) {

        vector<Minimiser> minimizers = vector<Minimiser>();
        vector<Minimiser> kmers = vector<Minimiser>(); 
        long condition = window_size - kmer_size;

        string str_num;
        for (long k=0; k < kmer_size; k++) {

            str_num = str_num + to_string(str_map[str.at(k)]);
        }

        kmers.push_back(Minimiser(0, stol(str_num)));
        long index = 1;
        for (long i=kmer_size; i<str.length(); i++) {

            index = i - (kmer_size - 1);
            string next_substr = to_string(str_map[str.at(i)]);
            if (next_substr.length() == 2) {
                str_num = str_num.substr(2);
            } else {
                str_num = str_num.substr(1);
            }
            
            str_num = str_num + next_substr;
            kmers.push_back(Minimiser(index, stol(str_num)));

            if (kmers.size() > window_size-kmer_size) {
                
                auto compareNum = [](const Minimiser& a, const Minimiser& b) {
                    return a.kmer < b.kmer;
                };
                auto min = min_element(kmers.begin(), kmers.end(), compareNum);
                minimizers.push_back(min[0]);
                if (minimizers.size() > 1 && minimizers[minimizers.size()-2].offset == minimizers[minimizers.size()-1].offset) {
                    
                    minimizers.pop_back();
                }

                kmers.erase(kmers.begin());
            }
        }

        return minimizers;
    }

    // Frequency
    static vector<Minimiser> get_minimisers_spaced_frequency(unordered_map<char, long> str_map, string &str, int kmer_size, int window_size) {

        vector<Minimiser> minimizers = vector<Minimiser>();
        vector<Minimiser> kmers = vector<Minimiser>();
        long index = 0;
        for (long i=0; i<str.length()-window_size; i=i+window_size) {

            string str_num;
            for (long k=i; k < i+kmer_size; k++) {

                str_num = str_num + to_string(str_map[str.at(k)]);
            }

            kmers.push_back(Minimiser(i, stol(str_num)));
            for (long j=i+kmer_size; j<i+window_size; j++) {
            
                index = j - (kmer_size-1);
                str_num = str_num.substr(1);
                str_num = str_num + to_string(str_map[str.at(j)]);
                kmers.push_back(Minimiser(index, stol(str_num)));
            }

            auto compareNum = [](const Minimiser& a, const Minimiser& b) {
                return a.kmer < b.kmer;
            };
            auto min = min_element(kmers.begin(), kmers.end(), compareNum);
            minimizers.push_back(min[0]);
            kmers.clear();
        }

        return minimizers;
    }

    // Hash
    static vector<Minimiser> get_minimisers(string &str, int kmer_size, int window_size) {

        vector<Minimiser> kmers = vector<Minimiser>();
        rolling_hash hash;
        vector<Minimiser> hash_index = vector<Minimiser>(); 

        for (long k = 0; k < kmer_size; k++) {
                        
            hash.push_back(str[k]);
        }

        hash_index.push_back(Minimiser(0, hash.get()));
        long index = 1;
        for (long i=kmer_size; i<=str.length(); i++) {

            index = i - (kmer_size - 1);
            hash.pop_front();
            hash.push_back(str[i]);
            hash_index.push_back(Minimiser(index, hash.get()));

            if (hash_index.size() > window_size-kmer_size) {
                
                auto compareNum = [](const Minimiser& a, const Minimiser& b) {
                    return a.kmer < b.kmer;
                };
                auto min = min_element(hash_index.begin(), hash_index.end(), compareNum);
                kmers.push_back(min[0]);
                if (kmers.size() > 1 && kmers[kmers.size()-2].offset == kmers[kmers.size()-1].offset) {
                    
                    kmers.pop_back();
                }
                hash_index.erase(hash_index.begin());
            }
        }

        return kmers;
    }

    static vector<Minimiser> get_minimisers_spaced_hash(string &str, int kmer_size, int window_size) {

        vector<Minimiser> kmers = vector<Minimiser>();
        rolling_hash hash;
        vector<Minimiser> hash_index = vector<Minimiser>(); 
        long index = 0;
        for (long i=0; i < str.length()-window_size; i=i+window_size) {

            for (long k = i; k < i+kmer_size; k++) {
                            
                hash.push_back(str[k]);
            }

            hash_index.push_back(Minimiser(i, hash.get()));
            for (long j=i+kmer_size; j < i+window_size; j++) {

                index = j - (kmer_size - 1);
                hash.pop_front();
                hash.push_back(str[i]);
                hash_index.push_back(Minimiser(index, hash.get()));

                if (hash_index.size() > window_size-kmer_size) {
                    
                    auto compareNum = [](const Minimiser& a, const Minimiser& b) {
                        return a.kmer < b.kmer;
                    };

                    auto min = min_element(hash_index.begin(), hash_index.end(), compareNum);
                    kmers.push_back(min[0]);
                    hash_index.clear();
                }
            }
        }

        return kmers;
    }
};