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
