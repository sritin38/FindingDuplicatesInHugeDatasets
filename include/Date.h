#pragma once
#include <iostream>

using namespace std;

struct Date {
    private: 
    int day, month, year;
    
    public:
    Date(int month=1, int day=1, int year=1999);
    void display();
};