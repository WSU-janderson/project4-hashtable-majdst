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

//Hello Weekend :( -->after interview

void HashTable::resize() {
    vector<HashTableBucket> oldTable = tableData;
    size_t newCap = capacity()*2; //doubling the size

    tableData.clear();
    tableData.resize(newCap);

    //reseting the size
    currentSize = 0;

    for (const auto& bucket : oldTable::Normal) {

        if (bucket.state == BucketType::Normal) {

            insert(bucket.key, bucket.value);
        }
    }
}

bool HashTable::insert(string key, size_t value) {
    if (alpha() >= 0.5){resize();} // checking --> Need for resize

    size_t home = hash(key); //home bucket index

    std::optional<size_t> firstEAR;

    //HomeBucket First
    if (tableData[home].state == BucketType::NORMAL) {
        //checking the duplicate
        if (tableData[home].key == key) {
            return false;
        }
    } else if (tableData[home].state == BucketType::EAR) {
        //tombstone
        firstEAR = home;
    } else if (tableData[home].state == BucketType::ESS) {
        //perfect spot--> insert-->Done
        tableData[home].key = key;
        tableData[home].value = value;
        tableData[home].state = BucketType::NORMAL;
        currentSize++;
        return true;
    }

    for (size_t offset : offsets) {
        size_t probeIndex = (home + offset) % capacity();//just probing

        if (tableData[probeIndex].state == BucketType::NORMAL) {//checking for duplicate
            if (tableData[probeIndex].key == key) {
                return false; // Duplicate found!
            }
        }else if (tableData[probeIndex].state == BucketType::EAR) {
            if (!firstEAR.has_value()) {
                firstEAR = probeIndex;
            }
        }else if (tableData[probeIndex].state == BucketType::ESS) {
            size_t insertIndex = firstEAR.has_value() ? firstEAR.value() : probeIndex;

            tableData[insertIndex].key = key;
            tableData[insertIndex].value = value;
            tableData[insertIndex].state = BucketType::NORMAL;
            currentSize++;
            return true; // Success!
        }
    }
    if (firstEAR.has_value()) {
        size_t insertIndex = firstEAR.value();
        tableData[insertIndex].key = key;
        tableData[insertIndex].value = value;
        tableData[insertIndex].state = BucketType::NORMAL;
        currentSize++;
        return true; // Done
    }
    return false;
}
