#ifndef IPV7DECODER_H
#define IPV7DECODER_H

#include<string>
#include<cstdint>
#include<list>

class IPv7Decoder {
public:
    IPv7Decoder( const std::string & address);
    ~IPv7Decoder();

    bool contains_bab() { return bab; }
    bool contains_abba() { return abba; }

    static uint32_t count_valid_babs(const std::string &str);
    static uint32_t count_valid_abbas(const std::string &str);

private:
    std::list<std::string> supernet_list;
    std::list<std::string> hypernet_list;
    std::string address;
    bool abba;
    bool bab;

    static bool valid_abba_string(const std::string &str);
    static std::list<std::string> valid_bab_strings(const std::string &str);
    bool check_for_abba( );
    bool check_for_bab( );
    void split_supernet_and_hypernet( std::string address );
};

#endif