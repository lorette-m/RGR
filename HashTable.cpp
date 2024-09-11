#include "HashTable.h"

uint32_t MurmurHash3(const void* key, int len, uint32_t seed) 
{
    const uint32_t m = 0xc6a4a793;
    const int r = 24;
    uint32_t h = seed ^ (len * m);

    const auto* data = static_cast<const uint8_t*>(key);
    const int nblocks = len / 4;

    for (int i = 0; i < nblocks; i++) 
    {
        uint32_t k = *reinterpret_cast<const uint32_t*>(data + i * 4);
        k *= m;
        k ^= k >> r;
        k *= m;
        h ^= k;
        h *= m;
    }

    const auto* tail = data + nblocks * 4;
    uint32_t k1 = 0;

    switch (len & 3) 
    {
    case 3: k1 ^= tail[2] << 16;
    case 2: k1 ^= tail[1] << 8;
    case 1: k1 ^= tail[0];
        k1 *= m;
        k1 ^= k1 >> r;
        k1 *= m;
        h ^= k1;
    };

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}

void search(std::unordered_map<std::string,
    std::unique_ptr<std::list<int>>, MurmurHash3Hash>& hashTable, std::string key, std::ostream& ost)
{
    if (hashTable.empty()) 
    {
        throw std::invalid_argument("Hash table is empty. Nothing to search");
    }
    else 
    {
        if (hashTable.find(key) == hashTable.end())
        {
            ost << "Key " << key << " not found in the hash table" << std::endl;
        }
        else
        {
            ost << "Key " << key << " found in the hash table. Values: ";
            for (const int& value : *(hashTable[key]))
            {
                ost << value << " ";
            }
        }
    }
}

void displayHashTable(std::unordered_map<std::string, 
    std::unique_ptr<std::list<int>>, MurmurHash3Hash>& hashTable, std::ostream& ost)
{
    if (hashTable.empty()) 
    {
        throw std::invalid_argument("Hash table is empty. Nothing to display");
    } 
    else 
    {
        for (const auto& pair : hashTable) 
        {
            std::cout << "Key: " << pair.first << " -> Values: ";
            for (const int& value : *(pair.second)) 
            {
                std::cout << value << " ";
            }
            std::cout << std::endl;
        }
    }
}