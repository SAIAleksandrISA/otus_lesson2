#ifndef IP_FILTER_H
#define IP_FILTER_H

#include <string>
#include <vector>


std::vector<std::string> splitLine(const std::string& str, char d);
std::vector<int> splitPart(const std::string& str, char d);

void filter(const std::vector<std::vector<int>>& ip_pool, std::initializer_list<int> filters);
void filter_any(const std::vector<std::vector<int>>& ip_pool, int nAnyByte);

#endif // IP_FILTER_H