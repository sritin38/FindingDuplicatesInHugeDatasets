#pragma once
#include <iostream>
#include <string>
using namespace std;

struct Minimizer {

    size_t hash;
    string value;
    int offset;

    Minimizer(size_t hash, string value, int offset);
    Minimizer();
};