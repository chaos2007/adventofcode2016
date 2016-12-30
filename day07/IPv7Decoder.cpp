#include "IPv7Decoder.h"
#include <string>
#include <cstdint>
#include <iostream>
#include <fstream>
#include <list>
#include <algorithm>

IPv7Decoder::IPv7Decoder(const std::string &address) : address(address)
{
    split_supernet_and_hypernet(address);
    bab = check_for_bab();
    abba = check_for_abba();
};

IPv7Decoder::~IPv7Decoder(){};

void IPv7Decoder::split_supernet_and_hypernet(std::string address)
{
    while (address.size())
    {
        std::size_t found = address.find_first_of("[");
        if (found != std::string::npos)
        {
            supernet_list.push_back(address.substr(0, found));
            address = address.substr(found + 1);
            found = address.find_first_of("]");
            hypernet_list.push_back(address.substr(0, found));
            address = address.substr(found + 1);
        }
        else
        {
            supernet_list.push_back(address);
            address = "";
        }
    }
}

bool IPv7Decoder::IPv7Decoder::check_for_bab()
{
    std::list<std::string> babs;
    std::for_each(supernet_list.begin(), supernet_list.end(), [&babs](std::string a) { babs.merge(IPv7Decoder::valid_bab_strings(a)); });
    for (auto iter = babs.begin(); iter != babs.end(); ++iter)
    {
        std::string opp = std::string("") + (*iter)[1] + (*iter)[0] + (*iter)[1];
        if (std::any_of(hypernet_list.begin(), hypernet_list.end(), [opp](std::string i) { return i.find(opp) != std::string::npos; }))
        {
            return true;
        }
    }
    return false;
}

bool IPv7Decoder::check_for_abba()
{
    bool supernet_abba = std::any_of(supernet_list.begin(), supernet_list.end(), IPv7Decoder::valid_abba_string);
    bool none_hypernet_abba = std::none_of(hypernet_list.begin(), hypernet_list.end(), IPv7Decoder::valid_abba_string);
    return supernet_abba && none_hypernet_abba;
}

uint32_t IPv7Decoder::count_valid_babs(const std::string &str)
{
    std::string line;
    std::ifstream myfile(str.c_str());
    uint32_t count = 0;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            IPv7Decoder decoder(line);
            if (decoder.contains_bab())
                count++;
        }
    }
    return count;
}

uint32_t IPv7Decoder::count_valid_abbas(const std::string &str)
{
    std::string line;
    std::ifstream myfile(str.c_str());
    uint32_t count = 0;
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            IPv7Decoder decoder(line);
            if (decoder.contains_abba())
                count++;
        }
    }
    return count;
}

bool IPv7Decoder::valid_abba_string(const std::string &str)
{
    for (int x = 0; x < str.length() - 3; x++)
    {
        uint8_t *addr = (uint8_t *)&(str.c_str()[x]);
        if (addr[0] == addr[3] && addr[1] == addr[2] && addr[0] != addr[1])
        {
            return true;
        }
    }
    return false;
}

std::list<std::string> IPv7Decoder::valid_bab_strings(const std::string &str)
{
    std::list<std::string> ret;
    for (int x = 0; x < str.length() - 2; x++)
    {
        uint8_t *addr = (uint8_t *)&(str.c_str()[x]);
        if (addr[0] == addr[2] && addr[0] != addr[1])
        {
            ret.push_back(str.substr(x, 3));
        }
    }
    return ret;
}
