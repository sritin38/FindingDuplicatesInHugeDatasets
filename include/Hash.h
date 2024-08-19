#pragma once
#include <iostream>
#include <string>
#include "../include/rabinkarphash.h"
using namespace std;

struct Hash {

    string hash_string;
    size_t hash_value;
    int substring_window;
    int hash_bits;


    Hash(string hash_value, int substring_window, int hash_bits=32);
    size_t get_min_hash(KarpRabinHash<> hasher);
    void update_string_value(string str);
};