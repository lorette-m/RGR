#include "TextProccessing.h"

int textProcessing(std::string& fileName, 
	std::unordered_map<std::string, std::unique_ptr<std::list<int>>, MurmurHash3Hash>& hashTable)
{
	if (!(hashTable.empty()))
	{
		throw std::invalid_argument("Hash table is not empty");
		return 1;
	}
	std::ifstream in(fileName);
	if (in.fail() || in.bad())
	{
		throw std::invalid_argument("Unable to open/read the file");
		return 1;
	}

	std::string line = "";
	int lineCounter = 0;
	std::string word = "";

	if (in.is_open())
	{
		while (std::getline(in, line))
		{
			std::cout << ++lineCounter << " " << line << std::endl;

			std::stringstream ss(line);
			while (ss >> word)
			{
				std::string fixWord = "";
				for (int i = 0; i < (word.size()); i++)
				{
					if ((char(word[i]) >= 'À' && char(word[i]) <= 'ÿ') 
					|| (char(word[i]) >= 'A' && char(word[i]) <= 'z'))
					{
						fixWord += tolower(word[i]);
					}
				}
				if (fixWord != "" && fixWord != " ")
				{
					if (hashTable.find(fixWord) != hashTable.end())
					{
						auto& lineCounterList = *hashTable[fixWord];
						if (std::find(lineCounterList.begin(), lineCounterList.end(), lineCounter) == lineCounterList.end())
						{
							hashTable[fixWord]->push_back(lineCounter);
						}
					}
					else
					{
						hashTable.emplace(fixWord, std::make_unique<std::list<int>>());
						hashTable[fixWord]->push_back(lineCounter);
					}
				}
				
			}
		}
	}

	if (lineCounter == 0)
	{
		throw std::invalid_argument("Empty file");
	}

	in.close();

	return 0;
}