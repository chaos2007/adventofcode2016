#include<gtest/gtest.h>
#include<string>
#include<cstdint>
#include<iostream>
#include<fstream>

class IPv7Decoder {
public:
    IPv7Decoder() {};
    ~IPv7Decoder() {};

    bool contains_bab(const std::string &str ) {
        bool inside_hypernet = false;
        bool abba = false;
        for( int x = 0; x < str.length() - 2; x++ ) {
            if( str[x] == '[' ) {
                inside_hypernet = true;
            }
            if( str[x] == ']' ) {
                inside_hypernet = false;
            }
            if( !inside_hypernet ) {
                if( check_for_bab((uint8_t *)&(str.c_str()[x])) ) {
                    auto y = (str.substr(x, 1) + str.substr(x+1, 1) + str.substr(x+2,1));
                    if( str.find(y)  != std::string::npos ) {
                        return true;
                    }
                }
            }
        }
        return abba;
    }

    bool contains_abba(const std::string &str) {
        bool inside_hypernet = false;
        bool abba = false;
        for( int x = 0; x < str.length() - 3; x++ ) {
            if( str[x] == '[' ) {
                inside_hypernet = true;
            }
            if( str[x] == ']' ) {
                inside_hypernet = false;
            }
            if( check_for_abba((uint8_t *)&(str.c_str()[x]))) {
                if( inside_hypernet ) {
                    return false;
                } else {
                    abba = true;
                }
            }
        }
        return abba;
    }

    uint32_t count_valid_babs(const std::string &str) {
        std::string line;
        std::ifstream myfile(str.c_str());
        uint32_t count = 0;
        if( myfile.is_open() ) {
            while( getline( myfile, line ) ) {
                if( contains_bab(line) ) count++;
            }
        }
        return count;
    }

    uint32_t count_valid_abbas(const std::string &str) {
        std::string line;
        std::ifstream myfile(str.c_str());
        uint32_t count = 0;
        if( myfile.is_open() ) {
            while( getline( myfile, line ) ) {
                if( contains_abba(line) ) count++;
            }
        }
        return count;
    }

private:
    bool check_for_abba(const uint8_t* addr) {
        return (addr[0] == addr[3] &&
                addr[1] == addr[2] &&
                addr[0] != addr[1]);
    }

    bool check_for_bab(const uint8_t* addr) {
        return (addr[0] == addr[2] &&
                addr[0] != addr[1] );
    }
};


TEST(Decoder, constructor) {
    IPv7Decoder decoder;
    IPv7Decoder *decoder2 = new IPv7Decoder;
    delete decoder2;
}

TEST(Decoder, example_1) {
    IPv7Decoder decoder;
    EXPECT_TRUE(decoder.contains_abba("abba[mnop]qrst"));
    EXPECT_FALSE(decoder.contains_abba("abcd[bddb]xyyx"));
    EXPECT_FALSE(decoder.contains_abba("aaaa[qwer]tyui"));
    EXPECT_TRUE(decoder.contains_abba("ioxxoj[asdfgh]zxcvbn"));
    EXPECT_EQ(2, decoder.count_valid_abbas("example_1.txt"));
}

TEST(Decoder, example_2) {
    IPv7Decoder decoder;
    EXPECT_TRUE(decoder.contains_bab("aba[bab]xyz"));
    EXPECT_FALSE(decoder.contains_bab("xyx[xyx]xyx"));
    EXPECT_TRUE(decoder.contains_bab("aaa[kek]eke"));
    EXPECT_TRUE(decoder.contains_bab("zazbz[bzb]cdb"));
    EXPECT_EQ(3, decoder.count_valid_babs("example_2.txt"));
}

TEST(Decoder, problem_1) {
    IPv7Decoder decoder;
    EXPECT_EQ(118, decoder.count_valid_abbas("prob_1.txt"));
}

