#include "gtest/gtest.h"
#include "stringFunctions/StringFunctions.h"

TEST(StringFunctionsTest, StartSpaces) {
    std::string str = "Some str";
    std::string strWithSpaces = "   ";
    std::string result = strWithSpaces + str;
    StrFunc::clearStartSpaces(result);

    EXPECT_EQ(result, str);
}

TEST(StringFunctionsTest, StartSpacesEmpty) {
    std::string str = "";
    std::string strWithSpaces = "   ";
    std::string result = strWithSpaces + str;
    StrFunc::clearStartSpaces(result);

    EXPECT_EQ(result, str);
}

TEST(StringFunctionsTest, EndSpaces) {
    std::string str = "    Some str";
    std::string strWithSpaces = "   ";
    std::string result = str + strWithSpaces;
    StrFunc::clearEndSpaces(result);

    EXPECT_EQ(result, str);
}

TEST(StringFunctionsTest, EndSpacesEmpty) {
    std::string str = "";
    std::string strWithSpaces = "   ";
    std::string result = str + strWithSpaces;
    StrFunc::clearEndSpaces(result);

    EXPECT_EQ(result, str);
}

TEST(StringFunctionsTest, clearSpacesBoth) {
    std::string str = "Some str";
    std::string strWithSpaces = "   ";
    std::string result = strWithSpaces + str + strWithSpaces;
    StrFunc::clearSpacesBoth(result);

    EXPECT_EQ(result, str);
}

TEST(StringFunctionsTest, GetWordByPos) {
    std::string str = "  0 1  2  3  4   5 ";

    for (int i = 0; i < 6; i++) {
        std::string result = StrFunc::getWordByPos(str, i);
        std::string check = std::to_string(i);
        EXPECT_EQ(result, check);
    }

}

TEST(StringFunctionsTest, GetWordByPosWithQuotes) {
    std::string str = R"(  1  2 " 3  4   "  "5" 6 "7 8 9" 10)";
    EXPECT_EQ(StrFunc::getWordByPos(str, 0), "1");
    EXPECT_EQ(StrFunc::getWordByPos(str, 1), "2");
    EXPECT_EQ(StrFunc::getWordByPos(str, 2), "3  4");
    EXPECT_EQ(StrFunc::getWordByPos(str, 3), "5");
    EXPECT_EQ(StrFunc::getWordByPos(str, 4), "6");
    EXPECT_EQ(StrFunc::getWordByPos(str, 5), "7 8 9");
    EXPECT_EQ(StrFunc::getWordByPos(str, 6), "10");
}

TEST(StringFunctionsTest, GetWordWithDoubleQuotets) {
    std::string str = R"(   "some text"   )";
    EXPECT_EQ(StrFunc::getWordWithQuotes(str, '\"'), "some text");
}

TEST(StringFunctionsTest, GetWordWithDoubleQuotetsBad) {
    std::string str = R"(  "some text   )";
    EXPECT_EQ(StrFunc::getWordWithQuotes(str, '\"'), "");
    std::string str2 = R"(  some text"  )";
    EXPECT_EQ(StrFunc::getWordWithQuotes(str2, '\"'), "");
    std::string str3 = "  some text ";
    EXPECT_EQ(StrFunc::getWordWithQuotes(str3, '\"'), "");
}

TEST(StringFunctionsTest, GetWordWithQuotets) {
    std::string str = R"(   'some text'   )";
    EXPECT_EQ(StrFunc::getWordWithQuotes(str, '\''), "some text");
}

TEST(StringFunctionsTest, GetWordWithQuotetsBad) {
    std::string str = R"(  'some text   )";
    EXPECT_EQ(StrFunc::getWordWithQuotes(str, '\''), "");
    std::string str2 = R"(  some text'  )";
    EXPECT_EQ(StrFunc::getWordWithQuotes(str2, '\''), "");
    std::string str3 = "  some text ";
    EXPECT_EQ(StrFunc::getWordWithQuotes(str3, '\''), "");
}