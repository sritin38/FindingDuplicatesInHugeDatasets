#include <iostream>
#include <string>
#include <vector>
#include "../include/Minimizer.h"
using namespace std;

Minimizer::Minimizer(size_t hash, string value, int offset) {

    this->hash = hash;
    this->value = value;
    this->offset = offset;
}

Minimizer::Minimizer() {

    this->hash = 0;
    this->value = "";
    this->offset = 0;
}