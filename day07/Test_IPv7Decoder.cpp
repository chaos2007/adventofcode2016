#include<gtest/gtest.h>
#include "IPv7Decoder.h"

TEST(Decoder, example_1)
{
    IPv7Decoder decoder("abba[mnop]qrst");
    EXPECT_TRUE(decoder.contains_abba());
}

TEST(Decoder, example_2)
{
    IPv7Decoder decoder("abcd[bddb]xyyx");
    EXPECT_FALSE(decoder.contains_abba());
}

TEST(Decoder, example_3)
{
    IPv7Decoder decoder("aaaa[qwer]tyui");
    EXPECT_FALSE(decoder.contains_abba());
}

TEST(Decoder, example_4)
{
    IPv7Decoder decoder("ioxxoj[asdfgh]zxcvbn");
    EXPECT_TRUE(decoder.contains_abba());
}

TEST(Decoder, example_5)
{
    EXPECT_EQ(2, IPv7Decoder::count_valid_abbas("example_1.txt"));
}

TEST(Decoder, example_6)
{
    IPv7Decoder decoder("aba[bab]xyz");
    EXPECT_TRUE(decoder.contains_bab());
}

TEST(Decoder, example_7)
{
    IPv7Decoder decoder("xyx[xyx]xyx");
    EXPECT_FALSE(decoder.contains_bab());
}

TEST(Decoder, example_8)
{
    IPv7Decoder decoder("aaa[kek]eke");
    EXPECT_TRUE(decoder.contains_bab());
}

TEST(Decoder, example_9)
{
    IPv7Decoder decoder("zazbz[bzb]cdb");
    EXPECT_TRUE(decoder.contains_bab());
}

TEST(Decoder, example_10)
{
    EXPECT_EQ(3, IPv7Decoder::count_valid_babs("example_2.txt"));
}

TEST(Decoder, problem_1)
{
    EXPECT_EQ(118, IPv7Decoder::count_valid_abbas("prob_1.txt"));
}

TEST(Decoder, problem_2)
{
    EXPECT_EQ(260, IPv7Decoder::count_valid_babs("prob_1.txt"));
}