#include <iostream>
#include <optional>
#include <string>
#include <vector>

using std::ostream;
using std::string;
using std::vector;
using std::size_t;

enum class BucketType {
    Normal,
    ESS, // As explained in class--> Empty since start
    EAR //As explained in class--> Empty after remove
};

struct HashTableBucket {
    string key;
    size_t value;
    BucketType state;

    HashTableBucket() {
        state = BucketType::ESS;
        key = "";
        value = 0;
    }
};

//main Hashtable class
class HashTable {

public:

    HashTable(size_t initCapacity = 8); // 2^3 actually

    bool insert(string key, size_t value); //works-->True, duplicate-->False

    bool remove(string key);

    bool contains(const string& key) const;//check key is in table or not

    std::optional<size_t> get(const string& key) const;

    size_t& operator[](const string& key);

    //vector --> contain all the key
    vector<string> keys() const;

    double alpha() const;

    size_t capacity() const;
    size_t size() const;

    friend ostream& operator<<(ostream& os, const HashTable& hashTable);
    //help to see the private parts

private:

    vector<HashTableBucket> tableDate; //main storage

    size_t currentSize; //keep track-->key-value pair

    vector<size_t> offsets;

    size_t hash(const string& key) const;
};