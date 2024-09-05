#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct Minimiser {

    size_t offset;
    long kmer = -1;

    static vector<Minimiser> get_minimisers(unordered_map<char, long> str_map, string str, int kmer_size, int window_size) {

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

        // for (int num: kmers) {
        //     cout << num << endl;
        // }

        return kmers;
    }   
};