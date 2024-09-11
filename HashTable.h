#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <iostream>
#include <unordered_map>
#include <list>
#include <string>
#include <algorithm>

uint32_t MurmurHash3(const void* key, int len, uint32_t seed);

struct MurmurHash3Hash {
    size_t operator()(const std::string& key) const {
        return MurmurHash3(key.c_str(), key.size(), 0); // Используем seed = 0
    }
};

void search(std::unordered_map<std::string,
	std::unique_ptr<std::list<int>>, MurmurHash3Hash>& hashTable, std::string key, std::ostream& ost);

void displayHashTable(std::unordered_map<std::string, 
	std::unique_ptr<std::list<int>>, MurmurHash3Hash>& hashTable, std::ostream& ost);

#endif