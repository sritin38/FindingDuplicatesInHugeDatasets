#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <chrono>
#include <sys/resource.h>

// #include "NumberFormation.cpp"
// #include "Heap.cpp"
// #include "Node.cpp"

using namespace std;
using namespace std::chrono;

struct Minimiser {

    size_t offset;
    string kmer;

    Minimiser (size_t offset, string kmer) {

        this->offset = offset;
        this->kmer = kmer;
    }

    Minimiser() {}
};

class MaxHeap {

    public:
        vector<Minimiser> array;
        int size;
        long capacity;

        // Constructor
        MaxHeap(long capacity) {
            this->size = 0;
            this->capacity = capacity;
            this->array.resize(capacity);
        }

        // Heapify function, heapify the node at index 'i'
        void heapify(long i) {

            // initialize initial values
            long largest = i;
            long left = 2 * i + 1;
            long right = 2 * i + 2;

            // Compare root node with left node of subtree
            if (left < size && array[left].kmer > array[largest].kmer) {
                largest = left;
            }
            // Compare root node with right node of subtree
            if (right < size && array[right].kmer > array[largest].kmer) {
                largest = right;
            }
            // If root node is changed then swap the values and call heapify function on subtree
            if (i != largest) {
                swap(array[i], array[largest]);
                heapify(largest);
            }
        }

        // Build heap function
        void buildHeap(const vector<Minimiser>& arr) {

            capacity = arr.size();
            size = capacity;
            array = arr;

            for (long i= (size-1)/2; i>=0; i--) {
                heapify(i);
            }
        }

        // Insert new values into the heap
        void insert(Minimiser value) {

            // increase array capacity
            if (size == capacity) {
                capacity *= 2;
                array.resize(capacity);
            }

            size++;
            long i = size-1;
            array[i] = value;

            // Adjust the value in the heap
            while (i != 0 && array[(i-1)/2].kmer < array[i].kmer) {

                swap(array[i], array[(i - 1) / 2]);
                i = (i-1)/2;
            }
        }

        // Function to get the root node
        Minimiser top() {

            if (size < 0) {
                return Minimiser();
            }
            else {
                return array[0];
            }
        }

        // Remove and return the root-node/max-value of the heap
        Minimiser pop() {
            
            // If the heap is empty
            if (size < 0) {
                return Minimiser();
            }

            // If the heap is of size 1
            if (size == 1) {
                size--;
                return array[0];
            }

            // Store the max value and remove it
            // Place the last value in the heap to the root
            Minimiser max = array[0];
            array[0] = array[size-1];
            size--;
            
            // Call heapify function to adjust the structure
            heapify(0);
            return max;
        }

        // Delete a specific key from heap
        void deleteKey(string key) {

            long index = -1;
            for (long i=0; i<size; i++) {
                
                if (array[i].kmer == key) {
                    index = i;
                    break;
                }
            }

            if (index == size) {

                cout << "Key not found" << endl;
                return;
            }

            if (index == size-1) {
                
                size--;
                return;
            }

            array[index] = array[size-1];
            size--;

            heapify(index);
        }

        Minimiser search(string kmer) {
            for (long i = 0; i < size; ++i) {
                if (array[i].kmer == kmer) {
                    return array[i]; // Key found
                }
            }
            return Minimiser(); // Key not found
        }

        // Function to print the heap
        void print()  {
            cout << "Max Heap: ";
            for (long i = 0; i < size; ++i)
                cout << array[i].kmer << " ";
            cout << endl;
        }
};

Minimiser extract_minimizer_lexicographical(std::string str, int kmer) {

    Minimiser minimizer;
    std::vector<string> strings = {};
    for (int i=0; i <= str.length()-kmer; i++) {
        strings.push_back(str.substr(i,kmer));
    }

    sort(strings.begin(), strings.end());
    int index = str.find(strings[0]);
    minimizer.kmer = strings[0];
    minimizer.offset = index;
    return minimizer;
}

vector<Minimiser> window_string_sequence(std::string& sequence, int kmer_size, int window_size) {
    
    vector<Minimiser> kmers = vector<Minimiser>();
    string potential_kmer;

    for (long i=0; i<=sequence.length()-window_size; i=i+window_size) {

        auto minimizer = extract_minimizer_lexicographical(sequence.substr(i, window_size), kmer_size);
        if (potential_kmer != minimizer.kmer) {

            potential_kmer = minimizer.kmer;
            minimizer.offset = minimizer.offset + i;
            kmers.push_back(minimizer);
        }
    }

    return kmers;
}

vector<Minimiser> get_minimisers(string &str, int kmer_size, int window_size) {

    vector<Minimiser> minimizers = vector<Minimiser>();
    vector<Minimiser> kmers = vector<Minimiser>(); 
    long condition = window_size - kmer_size;

    for (long i=0; i<str.length(); i++) {

        kmers.push_back(Minimiser(i, str.substr(i, kmer_size)));
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

void start() {

    // dataset 1 file path
    // string string_path_1 = "../data/proteins1.txt";
    // string string_path_2 = "../data/proteins2.txt";
    string string_path_1 = "../data/NoLCS/1.txt";
    string string_path_2 = "../data/NoLCS/2.txt";
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

    // Window size, that will slide accross the string
    int window_size = 100;
    // Kmer size, that could be a potential minimizer
    int kmer_size = 1;

    // Get list of minimizers of string 1.
    cout << "Minimizers for string 1 is generating..." << endl;
    // vector<Minimiser> minimizers1 = window_string_sequence(str1, kmer_size, window_size);
    vector<Minimiser> minimizers1 = get_minimisers(str1, kmer_size, window_size);
    cout << "Minimizer list for string 1 is generated." << endl;

    // Display minimizers of string 1.
    // for (auto& k: minimizers1) {

    //     auto val1 = str1.substr(k.offset, kmer_size);
    //     auto val2 = k.kmer;
    //     cout << str1.substr(k.offset, kmer_size) << " : " << k.kmer << " | " << k.offset << endl;
    // }

    // Get list of minimizers of string 2.
    cout << "Minimizers for string 2 is generating..." << endl;
    // vector<Minimiser> minimizers2 = window_string_sequence(str2, kmer_size, window_size);
    vector<Minimiser> minimizers2 = get_minimisers(str2, kmer_size, window_size);
    cout << "Minimizer list for string 2 is generated." << endl;

    // Display minimzizers of string 2
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
    cout << "Heap created for string 2." << endl;
    MaxHeap str2_heap = MaxHeap(minimizers2.size());
    str2_heap.buildHeap(minimizers2);
    // str2_heap.print();

    // Search minimizers of string 1 in heap of string 2.
    size_t lcs_offset = 0;
    size_t lcs_length = 0;
    while (minimizers1.size() > 0) {

        // Minimiser str1_top_kmer = str1_heap.pop();
        Minimiser str1_top_kmer = minimizers1[0];
        minimizers1.erase(minimizers1.begin());
        Minimiser match_substr = str2_heap.search(str1_top_kmer.kmer);
        if (match_substr.offset == -1 || match_substr.kmer == "") {

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