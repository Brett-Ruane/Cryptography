#pragma once

#include <iostream>
#include <string>
#include <bitset>
//#include <unordered_map>
#include <map>

typedef std::pair<char, char> charPair;
typedef std::map<char, charPair> myMap;

const std::string encrypt(const std::string m, const std::string k);
const std::string decrypt(const std::string c, const std::string k);
myMap makeASCIIMap();
