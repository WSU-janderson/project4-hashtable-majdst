/**
 * HashTable.cpp
 *  * Project 4 - Majid Dousti - CS5100
 **/

#include "HashTable.h"
#include <random>
#include <numeric>
#include <algorithm>

using namespace std;

HashTable::HashTable(size_t initCapacity) {
    currtSize = 0; //defult size -->0

    tableData.resize(initCapacity); //init ESS

    generateOffsets(initCapacity); //pseudo-random probe offset
}

/*
 * Helper function-->shuffled vector
 */
void HashTable::generateOffsets(size_t N) {
    offsets.resize(N-1);
    iota(offsets.begin(), offsets.end(), 1); //vector filling

    //Random Vector
    random_device rd;
    mt19937 g(rd());
    shuffle(offsets.begin(), offsets.end(), g);
}

size_t HashTable::hash(const string& key) const {
    size_t hashvalue = 0;
    for (char c: key) {
        hashValue = 37 * hashValue + c;
    }//just remember--> const mean no change in any class

    return hashValue % capacity();//fitting to table capacity
}

size_t HashTable::capacity() const {
    return tableData.size();
}

size_t HashTable::size() const {
    return currentSize;
}

double HashTable::alpha() const {

    return static_cast<double>(size())/static_cast<double>(capacity());
} //remember--> Static is for floating division -->prevent integer division
