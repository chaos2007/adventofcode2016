#include<gtest/gtest.h>
#include<string>

class IPv7Decoder {

    public:
        IPv7Decoder() {};
        ~IPv7Decoder() {};

        bool valid_address(const std::string &str) {return false;};

    private:


};


TEST(Decoder, constructor) {
    IPv7Decoder decoder;
    IPv7Decoder *decoder2 = new IPv7Decoder;
    delete decoder2;
}

TEST(Decoder, example_1) {
    IPv7Decoder decoder;
    ASSERT_TRUE(decoder.valid_address("abba[mnop]qrst"));
}
/*
TEST(Decoder, example_2) {
    IPv7Decoder decoder;
    ASSERT_FALSE(decoder.valid_address("abcd[bddb]xyyx"));
}

TEST(Decoder, example_3) {
    IPv7Decoder decoder;
    ASSERT_FALSE(decoder.valid_address("aaaa[qwer]tyui"));
}

TEST(Decoder, example_4) {
    IPv7Decoder decoder;
    ASSERT_TRUE(decoder.valid_address("ioxxoj[asdfgh]zxcvbn"));
}

*/
