#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> splitLine(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

std::vector<int> splitPart(const std::string &str, char d)
{
    std::vector<int> vPart;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        vPart.push_back(std::stoi(str.substr(start, stop - start)));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }
    vPart.push_back(std::stoi(str.substr(start)));

    return vPart;
}

void print_ip(const std::vector<int>& ip) 
{
    for (size_t i = 0; i < ip.size(); ++i) 
    {
        if (i != 0) std::cout << ".";
        std::cout << ip[i];
    }
    std::cout << std::endl;
}

void filter(const std::vector<std::vector<int>>& ip_pool, int nByte1=-1 , int nByte2=-1)
{
    for (const auto& ip : ip_pool)
    {
        if (nByte1 != -1)
        {
            if (nByte1 != ip[0]) continue;
            if (nByte2 != -1 && nByte2 != ip[1]) continue;
        }
        print_ip(ip);
    }
}

void filter_any(const std::vector<std::vector<int>>& ip_pool, int nAnyByte)
{
    for (const auto& ip : ip_pool)
    {
        if (std::any_of(ip.begin(), ip.end(), [nAnyByte](int ip_part) { return ip_part == nAnyByte; }))
        {
            print_ip(ip);
        }
    }
}

int main(int argc, char const *argv[])
{
    try
    {
        //std::ifstream file("..//ip_filter.tsv"); 
        //std::ifstream file("..//output.txt"); 
        //if (!file.is_open()) 
       // {
        //    std::cerr << "Ошибка открытия файла!" << std::endl;
         //   return 1;
        //}

        std::vector<std::vector<int>> vIP;

        for(std::string line; std::getline(std::cin, line);)
        {
            auto vLine = splitLine(line, '\t');
            vIP.push_back(splitPart(vLine.at(0), '.'));
        }

        std::sort(vIP.begin(), vIP.end(), std::greater<std::vector<int>>());

        // TODO reverse lexicographically sort
        filter(vIP);
        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        filter(vIP, 1);

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        filter(vIP, 46, 70);

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        filter_any(vIP, 46);

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
    std::cin;
    return 0;
}
