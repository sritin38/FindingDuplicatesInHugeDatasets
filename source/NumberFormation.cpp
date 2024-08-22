#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct Minimiser {

    size_t offset;
    int kmer = -1;

    static vector<Minimiser> get_minimisers(unordered_map<char, int> str_map, string str, int kmer_size, int window_size) {

        vector<Minimiser> kmers = vector<Minimiser>();

        int potential_kmer = 0;
        for (int i=0; i<=str.length()-window_size; i++) {

            int condition = i + window_size - kmer_size;
            int new_kmer = 0;
            int position = 0;
            for (int j=i; j<=condition; j++) {

                int num = 0;
                num = num + (str_map[str.at(j)] * 100);
                num = num + (str_map[str.at(j+1)] * 10);
                num = num + str_map[str.at(j+2)];
                
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