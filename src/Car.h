#ifndef CAR_H
#define CAR_H
#include <iostream>
#include <iomanip>
using namespace std;

const int YEAR_MIN = 1990, YEAR_MAX = 2024;
const int XP_MIN = 1000, XP_MAX = 9999;
const int NR_MANUFACTURERS = 25;

class Car {
private:
    string make;
    int year;
    int transponder;
    string manufacturers[NR_MANUFACTURERS] = 
        {"Toyota", "Ford", "Volkswagen", "Honda", "Chevrolet", "Nissan", "BMW", 
         "Mercedes-Benz", "Audi", "Hyundai", "Kia", "Subaru", "Mazda", "Tesla", 
         "Jaguar", "Fiat", "Land Rover", "Mitsubishi", "Peugeot", "Renault", 
         "Porsche", "Lexus", "Volvo", "Skoda", "Infiniti"};
public:
    Car() {
        make = manufacturers[arc4random() % NR_MANUFACTURERS];
        year = arc4random() % (YEAR_MAX - YEAR_MIN + 1) + YEAR_MIN;
        transponder = arc4random() % (XP_MAX - XP_MIN + 1) + XP_MIN;
    }
    string getMake()          { return make; }
    int getYear()             { return year; }
    int getTransponder()      { return transponder; }
    void setMake(string mk)   { make = mk; }
    void setYear(int yr)      { year = yr; }
    void setTransponder(int t) { transponder = t; }

    void print() {
        cout << "[" << year << " " << make << " (" << transponder << ")]\n";
    }

};
#endif