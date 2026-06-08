#include "ip_filter.h"
#include <fstream>
#include <iostream>
#include <algorithm>

int main(int argc, char const *argv[])
{
    try
    {
        //std::ifstream file("..//ip_filter.tsv"); 
        //std::ifstream file("..//output.txt"); 
        //if (!file.is_open()) 
        //{
        //    std::cerr << "Ошибка открытия файла!" << std::endl;
        //    return 1;
        //}

        std::vector<std::vector<int>> vIP;

        for(std::string line; std::getline(std::cin, line);)
        {
            auto vLine = splitLine(line, '\t');
            vIP.push_back(splitPart(vLine.at(0), '.'));
        }

        std::sort(vIP.begin(), vIP.end(), std::greater<std::vector<int>>());

        filter(vIP, {});
        filter(vIP, { 1 });
        filter(vIP, { 46, 70 });
        filter_any(vIP, 46);
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    std::cin;
    return 0;
}
