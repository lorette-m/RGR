#define NOMINMAX

#include <unordered_map>
#include <map>
#include <list>
#include <Windows.h>

#include "TextProccessing.h"
#include "HashTable.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::unordered_map<std::string, std::unique_ptr<std::list<int>>, MurmurHash3Hash> hashTable;
    std::string fileName1 = "text1.txt";
    std::string fileName2 = "text2.txt";

    std::string cmd;

    while (!std::cin.eof())
    {
        try
        {
            std::cin >> cmd;

            if (std::cin.eof())
            {
                break;
            }
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
            }
            if (cmd == "LOAD")
            {
                std::cout << "Please select the file number (1 or 2): ";
                int textNum = 0;
                std::cin >> textNum;
                if (textNum == 1)
                {
                    textProcessing(fileName1, hashTable);
                }
                else if (textNum == 2)
                {
                    textProcessing(fileName2, hashTable);
                }
                else
                {
                    throw std::invalid_argument("Invalid file number");
                }
            }
            else if (cmd == "DISPLAY")
            {
                displayHashTable(hashTable, std::cout);
            }
            else if (cmd == "CLEAR")
            {
                hashTable.clear();
            }
            else if (cmd == "SEARCH")
            {
                std::cout << "Enter the word to search: ";
                std::string word;
                std::cin >> word;
                search(hashTable, word, std::cout);
            }
            else
            {
                throw std::invalid_argument("INVALID COMMAND");
            }
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
        }
    }

    return 0;
}