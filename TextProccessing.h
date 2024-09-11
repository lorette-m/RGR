#ifndef TEXT_PROCCESSING_H
#define TEXT_PROCCESSING_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <list>
#include <memory>
#include <string>

#include "HashTable.h"

int textProcessing(std::string& fileName, 
	std::unordered_map<std::string, std::unique_ptr<std::list<int>>, MurmurHash3Hash>& hashTable);

#endif