#include "../include/Date.h"

using namespace std;

Date::Date(int month, int day, int year) {
    this->day = day;
    this->month = month;
    this->year = year;
}

void Date::display() {
    cout<< day <<"/" << month <<"/" << year << endl;
}