#include "ip_filter.h"
#include <cassert>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <initializer_list>

bool isValidIpPart(int part) 
{
    return part >= 0 && part <= 255;
}

template <typename T, typename Converter>
std::vector<T> split(const std::string& str, char d, Converter conv)
{
    std::vector<T> result;
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos)
    {
        std::string part_str = str.substr(start, stop - start);
        if (part_str.empty())
        {
            throw std::invalid_argument("Invalid IP address format: empty part detected between delimiters.");
        }
        try
        {
            result.push_back(conv(part_str));
        }
        catch (const std::exception& e)
        {
            throw std::runtime_error("Failed to convert part '" + part_str + "' from string '" + str + "': " + e.what());
        }
        start = stop + 1;
        stop = str.find_first_of(d, start);
    }
    std::string last_part_str = str.substr(start);
    if (last_part_str.empty())
    {
        throw std::invalid_argument("Invalid IP address format: empty part detected at the end of string.");
    }
    try
    {
        result.push_back(conv(last_part_str));
    }
    catch (const std::exception& e)
    {
        throw std::runtime_error("Failed to convert last part '" + last_part_str + "' from string '" + str + "': " + e.what());
    }

    return result;
}

auto string_identity_converter = [](const std::string& s) -> std::string 
{
    return s;
};

auto ip_part_converter = [](const std::string& s) -> int 
{
    int part = std::stoi(s);
    if (!isValidIpPart(part))
    {
        throw std::out_of_range("IP part value out of range (0-255).");
    }
    return part;
};

std::vector<std::string> splitLine(const std::string &str, char d)
{
    return split<std::string>(str, d, string_identity_converter);
}

std::vector<int> splitPart(const std::string &str, char d)
{
    return split<int>(str, d, ip_part_converter);
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

void filter(const std::vector<std::vector<int>>& ip_pool, std::initializer_list<int> filters)
{
    if (ip_pool.empty()) 
        return;

    if (filters.size() == 0)
    {
         for(const auto& ip : ip_pool)
             print_ip(ip);
         return;
    }
    
    if (filters.size() > 4) 
        return; 

    std::vector<int> filter_prefix(filters);

    for (const auto& ip : ip_pool)
    {
        bool match = true;
        for (size_t i = 0; i < filter_prefix.size(); ++i)
        {
            if (i >= ip.size() || ip[i] != filter_prefix[i])
            {
                match = false;
                break;
            }
        }

        if (match)
        {
            print_ip(ip);
        }
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