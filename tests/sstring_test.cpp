#include <iostream>
#include <gtest/gtest.h>
#include "../src/sstring.h"

//
// -----------------------------------------------------------------
// Test constructors, assignments
TEST(SStringTestSuite, cpconst) {
    sstring::String s("mytest");
    sstring::String s2(s);
    ASSERT_EQ(s, s2);
}

TEST(SStringTestSuite, mvconst) {
    sstring::String s2("mmyteste");
    sstring::String s(s2(1, 7));
    ASSERT_EQ(s, "mytest");
}

TEST(SStringTestSuite, cpassign) {
    sstring::String s("mytest");
    sstring::String s2 = s;
    ASSERT_EQ(s, s2);
}

TEST(SStringTestSuite, mvassing) {
    sstring::String s("mytest");
    sstring::String s2 = std::move(s);
    ASSERT_EQ(s2, "mytest");
}
// -----------------------------------------------------------------
// Test extension
TEST(SStringTestSuite, extend_string) {
    sstring::String s("mytest");
    sstring::String s2("δsuper");
    s += s2;
    ASSERT_EQ(s, "mytestδsuper");
    ASSERT_EQ(s[8], "u");
}

TEST(SStringTestSuite, extend_std_string) {
    sstring::String s("mytest");
    std::string s2("δsuper");
    s += s2;
    ASSERT_EQ(s, "mytestδsuper");
    ASSERT_EQ(s[8], "u");
}

TEST(SStringTestSuite, extend_const_char) {
    sstring::String s("mytest");
    s += "δsuper";
    ASSERT_EQ(s, "mytestδsuper");
    ASSERT_EQ(s[8], "u");
}

TEST(SStringTestSuite, extend_move) {
    sstring::String s("mytest");
    s += sstring::String("δsuper");
    ASSERT_EQ(s, "mytestδsuper");
    ASSERT_EQ(s[8], "u");
}


// -----------------------------------------------------------------
// Test length
TEST(SStringTestSuite, slen) {
    sstring::String s{"mytest"};
    ASSERT_EQ(s.slen(), 6);
}

TEST(SStringTestSuite, sbytesize) {
    sstring::String s{"mytest"};
    ASSERT_EQ(s.size(), 6);
}

TEST(SStringTestSuite, slenutf8) {
    sstring::String s{"Το καλό το τεστ just check είναι αυτό"};
    ASSERT_EQ(s.slen(), 37);
}

TEST(SStringTestSuite, sbytesizeutf8) {
    sstring::String s{"just τεστ"};
    ASSERT_EQ(s.size(), 13);
}

TEST(SStringTestSuite, slen_emoji) {
    sstring::String s{"my 🐼 test"};
    ASSERT_EQ(s.slen(), 9);
}

TEST(SStringTestSuite, sbytesize_emoji) {
    sstring::String s{"my 🐼 test"};
    ASSERT_EQ(s.size(), 12);
}

// -----------------------------------------------------------------
// Test substring

TEST(SStringTestSuite, substr_onegrapheme) {
    sstring::String s("mytest");
    auto ss = s(1,2);
    sstring::String tval{"y"};
    ASSERT_EQ(ss, tval);
}


TEST(SStringTestSuite, substr) {
    sstring::String s("mytest");
    auto ss = s(1,4);
    sstring::String tval{"yte"};
    ASSERT_EQ(ss, tval);

}

TEST(SStringTestSuite, substr_lft) {
    sstring::String s("mytest");
    auto ss = s(3);
    sstring::String tval{"est"};
    ASSERT_EQ(ss, tval);
}

TEST(SStringTestSuite, substr_lft_larger) {
    sstring::String s("mytest");
    auto ss = s(10);
    sstring::String tval{""};
    ASSERT_EQ(ss, tval);
}

TEST(SStringTestSuite, substr_negative_lft_one) {
    sstring::String s("mytest");
    auto ss = s(-1);
    sstring::String tval{"t"};
    ASSERT_EQ(ss, tval);
}

TEST(SStringTestSuite, substr_negative_lft_larger) {
    sstring::String s("mytest");
    auto ss = s(-10);
    sstring::String tval{"mytest"};
    ASSERT_EQ(ss, tval);
}

TEST(SStringTestSuite, substr_negative_lft) {
    sstring::String s("mytest");
    auto ss = s(-4, -2);
    sstring::String tval{"te"};
    ASSERT_EQ(ss, tval);
}

TEST(SStringTestSuite, larger_rgt) {
    sstring::String s("mytest");
    auto ss = s(2, 29);
    ASSERT_EQ(ss, sstring::String{"test"});
}

TEST(SStringTestSuite, lft_lrg_right) {
    sstring::String s("mytest");
    auto ss = s(5, 2);
    ASSERT_EQ(ss, sstring::String{""});
}

TEST(SStringTestSuite, lft_lrg_right_neg) {
    sstring::String s("mytest");
    auto ss = s(-2, -4);
    ASSERT_EQ(ss, sstring::String{""});
}

TEST(SStringTestSuite, lrg_lft_neg_right_neg) {
    sstring::String s("This is a test");
    auto ss = s(-20, -4);
    ASSERT_EQ(ss, sstring::String{"This is a "});
}

TEST(SStringTestSuite, lrg_lft_neg_lrg_right_neg) {
    sstring::String s("This is a test");
    auto ss = s(-20, -19);
    ASSERT_EQ(ss, sstring::String{""});
}

TEST(SStringTestSuite, substr_bndr_lft) {
    sstring::String s("mytest");
    auto ss = s(0, 4);
    ASSERT_EQ(ss, "myte");
}

TEST(SStringTestSuite, substr_2char) {
    sstring::String s("my");
    auto ss = s(0, 1);
    ASSERT_EQ(ss, "m");
}

// -----------------------------------------------------------------
// Test grapheme at index
TEST(SStringTestSuite, grapheme_at_index) {
    sstring::String s("Test index Ω of grapheme");
    auto ss= s[11];
    ASSERT_EQ(ss, "Ω");
}

TEST(SStringTestSuite, grapheme_at_index_0) {
    sstring::String s("Test index Ω of grapheme");
    auto ss= s[0];
    ASSERT_EQ(ss, "T");
}

TEST(SStringTestSuite, grapheme_at_index_0_utf) {
    sstring::String s("🐼Test index Ω of grapheme");
    auto ss= s[0];
    ASSERT_EQ(ss, "🐼");
}

TEST(SStringTestSuite, grapheme_at_index_0_double_utf) {
    sstring::String s("🐼🐼Test index Ω of grapheme");
    auto ss= s[0];
    ASSERT_EQ(ss, "🐼");
}

TEST(SStringTestSuite, grapheme_at_index_end) {
    sstring::String s("Test index Ω of grapheme q");
    auto ss= s[25];
    ASSERT_EQ(ss, "q");
}

TEST(SStringTestSuite, grapheme_at_index_end_utf) {
    sstring::String s("Test index of grapheme 🐼");
    auto ss= s[23];
    ASSERT_EQ(ss, "🐼");
}

TEST(SStringTestSuite, grapheme_at_index_end_double_utf) {
    sstring::String s("Test index 🐼🐼🐼 of grapheme 🐼🐵");
    auto ss= s[28];
    ASSERT_EQ(ss, "🐵");
}

TEST(SStringTestSuite, grapheme_at_out_of_range) {
    sstring::String s("Test index 🐼🐼🐼 of grapheme 🐼🐵");
    EXPECT_THROW({
        try {
            auto ss= s[128];
        }
        catch (const std::out_of_range& e) {
            EXPECT_STREQ("Index out of bounds", e.what());
            throw;
        }
    }, std::out_of_range);
}

TEST(SStringTestSuite, grapheme_at_index_neg_edge) {
    sstring::String s("Test index 🐼🐼🐼 of grapheme 🐼🐵");
    auto ss = s[-1];
    ASSERT_EQ(ss, "🐵");
}

TEST(SStringTestSuite, grapheme_at_index_neg) {
    sstring::String s("Test index 🐼🐼🐼 of grapheme 🐼🐵");
    auto ss = s[-5];
    ASSERT_EQ(ss, "m");
}

// -----------------------------------------------------------------
// Test join
TEST(SStringTestSuite, join_str) {
    sstring::String s(",");
    std::vector<std::string> v = {"my", "test", "is", "ok"};
    sstring::String s2 = s.join(v);
    ASSERT_EQ(s2, "my,test,is,ok");
}

TEST(SStringTestSuite, join_str_utf8) {
    sstring::String s(",");
    std::vector<std::string> v = {"my", "τεστ", "is", "οκ"};
    sstring::String s2 = s.join(v);
    ASSERT_EQ(s2, "my,τεστ,is,οκ");
}

TEST(SStringTestSuite, join_str_emoji) {
    sstring::String s(",");
    std::vector<std::string> v = {"🐼", "🐵", "💿"};
    sstring::String s2 = s.join(v);
    ASSERT_EQ(s2, "🐼,🐵,💿");
}

TEST(SStringTestSuite, join_string) {
    sstring::String s(",");
    std::vector<sstring::String> v = {
            sstring::String("my"),
            sstring::String("test"),
            sstring::String("is"),
            sstring::String("ok")
    };
    sstring::String s2 = s.join(v);
    ASSERT_EQ(s2, "my,test,is,ok");
}

TEST(SStringTestSuite, join_empty_str) {
    sstring::String s("");
    std::vector<std::string> v = {"my", "τεστ", "is", "🐼","οκ"};
    sstring::String s2 = s.join(v);
    ASSERT_EQ(s2, "myτεστis🐼οκ");
}

TEST(SStringTestSuite, join_empty_vec) {
    sstring::String s(",");
    std::vector<std::string> v;
    sstring::String s2 = s.join(v);
    ASSERT_EQ(s2, "");
}

TEST(SStringTestSuite, join_array_str) {
    sstring::String s(",");
    std::string v[] = {"my", "τεστ", "is", "🐼","οκ"};
    sstring::String s2 = s.join(v);
    ASSERT_EQ(s2, "my,τεστ,is,🐼,οκ");
}

TEST(SStringTestSuite, join_array_cchar) {
    sstring::String s(",");
    const char* v[] = {"my", "τεστ", "is", "🐼","οκ"};
    sstring::String s2 = s.join(v);
    ASSERT_EQ(s2, "my,τεστ,is,🐼,οκ");
}

// -----------------------------------------------------------------
// Test split
TEST(SStringTestSuite, split_const_char) {
    sstring::String s("my:test");
    std::vector<sstring::String> v = s.split(':');
    ASSERT_EQ(v[0], "my");
    ASSERT_EQ(v[1], "test");
    ASSERT_EQ(v.size(), 2);
}

TEST(SStringTestSuite, split_std_str) {
    sstring::String s("my:test");
    std::string delim(":");
    std::vector<sstring::String> v = s.split(delim);
    ASSERT_EQ(v[0], "my");
    ASSERT_EQ(v[1], "test");
    ASSERT_EQ(v.size(), 2);
}


TEST(SStringTestSuite, split_const_char_utf8) {
    sstring::String s("το:τεστ");
    std::vector<sstring::String> v = s.split(":");
    ASSERT_EQ(v[0], "το");
    ASSERT_EQ(v[1], "τεστ");
    ASSERT_EQ(v.size(), 2);
}

TEST(SStringTestSuite, split_const_char_emoji) {
    sstring::String s("το:🐼:τεστ");
    std::vector<sstring::String> v = s.split(":");
    ASSERT_EQ(v[0], "το");
    ASSERT_EQ(v[1], "🐼");
    ASSERT_EQ(v[2], "τεστ");
    ASSERT_EQ(v.size(), 3);
}

TEST(SStringTestSuite, split_const_char_right) {
    sstring::String s("το🐼τεστ");
    std::vector<sstring::String> v = s.split("στ");
    ASSERT_EQ(v[0], "το🐼τε");
    ASSERT_EQ(v[1], "");
    ASSERT_EQ(v.size(), 2);
}

TEST(SStringTestSuite, split_const_char_left) {
    sstring::String s("το🐼τεστ");
    std::vector<sstring::String> v = s.split("το");
    ASSERT_EQ(v[0], "");
    ASSERT_EQ(v[1], "🐼τεστ");
    ASSERT_EQ(v.size(), 2);
}

TEST(SStringTestSuite, split_empty_left) {
    sstring::String s(",my,test");
    std::vector<sstring::String> v = s.split(",");
    ASSERT_EQ(v[0], "");
    ASSERT_EQ(v[1], "my");
    ASSERT_EQ(v[2], "test");
}

TEST(SStringTestSuite, split_empty_right) {
    sstring::String s("my,test,");
    std::vector<sstring::String> v = s.split(",");
    ASSERT_EQ(v[0], "my");
    ASSERT_EQ(v[1], "test");
    ASSERT_EQ(v[2], "");
}

TEST(SStringTestSuite, split_consecutive_two_left) {
    sstring::String s(",,my,test");
    std::vector<sstring::String> v = s.split(",");
    ASSERT_EQ(v[0], "");
    ASSERT_EQ(v[1], "");
    ASSERT_EQ(v[2], "my");
    ASSERT_EQ(v[3], "test");
}

TEST(SStringTestSuite, split_consecutive_two_middle) {
    sstring::String s("my,,test");
    std::vector<sstring::String> v = s.split(",");
    ASSERT_EQ(v[0], "my");
    ASSERT_EQ(v[1], "");
    ASSERT_EQ(v[2], "test");
}

TEST(SStringTestSuite, split_consecutive_two_right) {
    sstring::String s("my,test,,");
    std::vector<sstring::String> v = s.split(",");
    ASSERT_EQ(v[0], "my");
    ASSERT_EQ(v[1], "test");
    ASSERT_EQ(v[2], "");
    ASSERT_EQ(v[3], "");
}

TEST(SStringTestSuite, split_consecutive_three_left) {
    sstring::String s(",,,my,test");
    std::vector<sstring::String> v = s.split(",");
    ASSERT_EQ(v[0], "");
    ASSERT_EQ(v[1], "");
    ASSERT_EQ(v[2], "");
    ASSERT_EQ(v[3], "my");
    ASSERT_EQ(v[4], "test");
}

TEST(SStringTestSuite, split_consecutive_three_middle) {
    sstring::String s("my,,,test");
    std::vector<sstring::String> v = s.split(",");
    ASSERT_EQ(v[0], "my");
    ASSERT_EQ(v[1], "");
    ASSERT_EQ(v[2], "");
    ASSERT_EQ(v[3], "test");
}

TEST(SStringTestSuite, split_consecutive_three_right) {
    sstring::String s("my,test,,,");
    std::vector<sstring::String> v = s.split(",");
    ASSERT_EQ(v[0], "my");
    ASSERT_EQ(v[1], "test");
    ASSERT_EQ(v[2], "");
    ASSERT_EQ(v[3], "");
    ASSERT_EQ(v[4], "");
}

TEST(SStringTestSuite, split_consecutive_four_left) {
    sstring::String s(",,,,my,test");
    std::vector<sstring::String> v = s.split(",");
    ASSERT_EQ(v[0], "");
    ASSERT_EQ(v[1], "");
    ASSERT_EQ(v[2], "");
    ASSERT_EQ(v[3], "");
    ASSERT_EQ(v[4], "my");
    ASSERT_EQ(v[5], "test");
}

TEST(SStringTestSuite, split_consecutive_four_middle) {
    sstring::String s("my,,,,test");
    std::vector<sstring::String> v = s.split(",");
    ASSERT_EQ(v[0], "my");
    ASSERT_EQ(v[1], "");
    ASSERT_EQ(v[2], "");
    ASSERT_EQ(v[3], "");
    ASSERT_EQ(v[4], "test");
}

TEST(SStringTestSuite, split_consecutive_four_right) {
    sstring::String s("my,test,,,,");
    std::vector<sstring::String> v = s.split(",");
    ASSERT_EQ(v[0], "my");
    ASSERT_EQ(v[1], "test");
    ASSERT_EQ(v[2], "");
    ASSERT_EQ(v[3], "");
    ASSERT_EQ(v[4], "");
    ASSERT_EQ(v[5], "");
}

TEST(SStringTestSuite, split_not_found) {
    sstring::String s("my:test");
    std::vector<sstring::String> v = s.split(",");
    ASSERT_EQ(v[0], "my:test");
    ASSERT_EQ(v.size(), 1);
}

// rsplit
TEST(SStringTestSuite, rsplit_sstring) {
    sstring::String s("my:test");
    sstring::String d(":");
    std::vector<sstring::String> v = s.rsplit(d);
    ASSERT_EQ(v[0], "test");
    ASSERT_EQ(v[1], "my");
    ASSERT_EQ(v.size(), 2);
}

TEST(SStringTestSuite, rsplit_const_char) {
    sstring::String s("my:test");
    std::vector<sstring::String> v = s.rsplit(':');
    ASSERT_EQ(v[0], "test");
    ASSERT_EQ(v[1], "my");
    ASSERT_EQ(v.size(), 2);
}

TEST(SStringTestSuite, rsplit_std_str) {
    sstring::String s("my:test");
    std::string delim(":");
    std::vector<sstring::String> v = s.rsplit(delim);
    ASSERT_EQ(v[0], "test");
    ASSERT_EQ(v[1], "my");
    ASSERT_EQ(v.size(), 2);
}


TEST(SStringTestSuite, rsplit_const_char_utf8) {
    sstring::String s("το:τεστ");
    std::vector<sstring::String> v = s.rsplit(":");
    ASSERT_EQ(v[0], "τεστ");
    ASSERT_EQ(v[1], "το");
    ASSERT_EQ(v.size(), 2);
}

TEST(SStringTestSuite, rsplit_const_char_emoji) {
    sstring::String s("το:🐼:τεστ");
    std::vector<sstring::String> v = s.rsplit(":");
    ASSERT_EQ(v[0], "τεστ");
    ASSERT_EQ(v[1], "🐼");
    ASSERT_EQ(v[2], "το");
    ASSERT_EQ(v.size(), 3);
}

TEST(SStringTestSuite, rsplit_const_char_right) {
    sstring::String s("το🐼τεστ");
    std::vector<sstring::String> v = s.rsplit("στ");
    ASSERT_EQ(v[0], "");
    ASSERT_EQ(v[1], "το🐼τε");
    ASSERT_EQ(v.size(), 2);
}

TEST(SStringTestSuite, rsplit_const_char_left) {
    sstring::String s("το🐼τεστ");
    std::vector<sstring::String> v = s.rsplit("το");
    ASSERT_EQ(v[0], "🐼τεστ");
    ASSERT_EQ(v[1], "");
    ASSERT_EQ(v.size(), 2);
}


TEST(SStringTestSuite, rsplit_sstring_many) {
    sstring::String s("new:test:number:six");
    sstring::String d(":");
    std::vector<sstring::String> v = s.rsplit(d);
    ASSERT_EQ(v[0], "six");
    ASSERT_EQ(v[1], "number");
    ASSERT_EQ(v[2], "test");
    ASSERT_EQ(v[3], "new");
    ASSERT_EQ(v.size(), 4);
}

TEST(SStringTestSuite, rsplit_consecutive) {
    sstring::String s("my::test");
    sstring::String d(":");
    std::vector<sstring::String> v = s.rsplit(d);
    ASSERT_EQ(v[0], "test");
    ASSERT_EQ(v[1], "");
    ASSERT_EQ(v[2], "my");
    ASSERT_EQ(v.size(), 3);
}

TEST(SStringTestSuite, rsplit_consecutive_end) {
    sstring::String s("my::test::");
    sstring::String d(":");
    std::vector<sstring::String> v = s.rsplit(d);
    ASSERT_EQ(v[0], "");
    ASSERT_EQ(v[1], "");
    ASSERT_EQ(v[2], "test");
    ASSERT_EQ(v[3], "");
    ASSERT_EQ(v[4], "my");
    ASSERT_EQ(v.size(), 5);
}

TEST(SStringTestSuite, rsplit_consecutive_start) {
    sstring::String s("::my::test");
    sstring::String d(":");
    std::vector<sstring::String> v = s.rsplit(d);
    ASSERT_EQ(v[0], "test");
    ASSERT_EQ(v[1], "");
    ASSERT_EQ(v[2], "my");
    ASSERT_EQ(v[3], "");
    ASSERT_EQ(v[4], "");
    ASSERT_EQ(v.size(), 5);
}

TEST(SStringTestSuite, rsplit_consecutive_empty) {
    sstring::String s(":::");
    sstring::String d(":");
    std::vector<sstring::String> v = s.rsplit(d);
    ASSERT_EQ(v[0], "");
    ASSERT_EQ(v[1], "");
    ASSERT_EQ(v[2], "");
    ASSERT_EQ(v[3], "");
    ASSERT_EQ(v.size(), 4);
}

TEST(SStringTestSuite, rsplit_empty_left) {
    sstring::String s(",my,test");
    std::vector<sstring::String> v = s.rsplit(",");
    ASSERT_EQ(v[0], "test");
    ASSERT_EQ(v[1], "my");
    ASSERT_EQ(v[2], "");
}

TEST(SStringTestSuite, rsplit_empty_right) {
    sstring::String s("my,test,");
    std::vector<sstring::String> v = s.rsplit(",");
    ASSERT_EQ(v[2], "my");
    ASSERT_EQ(v[1], "test");
    ASSERT_EQ(v[0], "");
}

TEST(SStringTestSuite, rsplit_consecutive_two_left) {
    sstring::String s(",,my,test");
    std::vector<sstring::String> v = s.rsplit(",");
    ASSERT_EQ(v[3], "");
    ASSERT_EQ(v[2], "");
    ASSERT_EQ(v[1], "my");
    ASSERT_EQ(v[0], "test");
}

TEST(SStringTestSuite, rsplit_consecutive_two_middle) {
    sstring::String s("my,,test");
    std::vector<sstring::String> v = s.rsplit(",");
    ASSERT_EQ(v[2], "my");
    ASSERT_EQ(v[1], "");
    ASSERT_EQ(v[0], "test");
}

TEST(SStringTestSuite, rsplit_consecutive_two_right) {
    sstring::String s("my,test,,");
    std::vector<sstring::String> v = s.rsplit(",");
    ASSERT_EQ(v[3], "my");
    ASSERT_EQ(v[2], "test");
    ASSERT_EQ(v[1], "");
    ASSERT_EQ(v[0], "");
}

TEST(SStringTestSuite, rsplit_consecutive_three_left) {
    sstring::String s(",,,my,test");
    std::vector<sstring::String> v = s.rsplit(",");
    ASSERT_EQ(v[4], "");
    ASSERT_EQ(v[3], "");
    ASSERT_EQ(v[2], "");
    ASSERT_EQ(v[1], "my");
    ASSERT_EQ(v[0], "test");
}

TEST(SStringTestSuite, rsplit_consecutive_three_middle) {
    sstring::String s("my,,,test");
    std::vector<sstring::String> v = s.rsplit(",");
    ASSERT_EQ(v[3], "my");
    ASSERT_EQ(v[2], "");
    ASSERT_EQ(v[1], "");
    ASSERT_EQ(v[0], "test");
}

TEST(SStringTestSuite, rsplit_consecutive_three_right) {
    sstring::String s("my,test,,,");
    std::vector<sstring::String> v = s.rsplit(",");
    ASSERT_EQ(v[4], "my");
    ASSERT_EQ(v[3], "test");
    ASSERT_EQ(v[2], "");
    ASSERT_EQ(v[1], "");
    ASSERT_EQ(v[0], "");
}

TEST(SStringTestSuite, rsplit_consecutive_four_left) {
    sstring::String s(",,,,my,test");
    std::vector<sstring::String> v = s.rsplit(",");
    ASSERT_EQ(v[5], "");
    ASSERT_EQ(v[4], "");
    ASSERT_EQ(v[3], "");
    ASSERT_EQ(v[2], "");
    ASSERT_EQ(v[1], "my");
    ASSERT_EQ(v[0], "test");
}

TEST(SStringTestSuite, rsplit_consecutive_four_middle) {
    sstring::String s("my,,,,test");
    std::vector<sstring::String> v = s.rsplit(",");
    ASSERT_EQ(v[4], "my");
    ASSERT_EQ(v[3], "");
    ASSERT_EQ(v[2], "");
    ASSERT_EQ(v[1], "");
    ASSERT_EQ(v[0], "test");
}

TEST(SStringTestSuite, rsplit_consecutive_four_right) {
    sstring::String s("my,test,,,,");
    std::vector<sstring::String> v = s.rsplit(",");
    ASSERT_EQ(v[5], "my");
    ASSERT_EQ(v[4], "test");
    ASSERT_EQ(v[3], "");
    ASSERT_EQ(v[2], "");
    ASSERT_EQ(v[1], "");
    ASSERT_EQ(v[0], "");
}

TEST(SStringTestSuite, rsplit_not_found) {
    sstring::String s("my:test");
    std::vector<sstring::String> v = s.rsplit(",");
    ASSERT_EQ(v[0], "my:test");
    ASSERT_EQ(v.size(), 1);
}



// -----------------------------------------------------------------
// Test alignment methods
// Right
TEST(SStringTestSuite, rjust_string) {
    sstring::String s("test");
    auto s2 = s.rjust(10);
    ASSERT_EQ(s2, "      test");
    ASSERT_EQ(s2.slen(), 10);
}

TEST(SStringTestSuite, rjust_char) {
    sstring::String s("test");
    char c = '+';
    auto s2 = s.rjust(10, c);
    ASSERT_EQ(s2, "++++++test");
    ASSERT_EQ(s2.slen(), 10);
}

TEST(SStringTestSuite, rjust_string_utf) {
    sstring::String s("τεστ");
    auto s2 = s.rjust(10);
    ASSERT_EQ(s2, "      τεστ");
    ASSERT_EQ(s2.slen(), 10);
}

TEST(SStringTestSuite, rjust_string_fl_utf) {
    sstring::String s("τεστ");
    sstring::String fl(".");
    auto s2 = s.rjust(10, fl);
    ASSERT_EQ(s2, "......τεστ");
    ASSERT_EQ(s2.slen(), 10);
}


TEST(SStringTestSuite, rjust_string_multi_utf_fit) {
    sstring::String s("τεστ");
    sstring::String fl(".+");
    auto s2 = s.rjust(10, fl);
    ASSERT_EQ(s2, ".+.+.+τεστ");
    ASSERT_EQ(s2.slen(), 10);
}

TEST(SStringTestSuite, rjust_string_multi_utf_nfit) {
    sstring::String s("τεστ");
    sstring::String fl(".+");
    auto s2 = s.rjust(11, fl);
    ASSERT_EQ(s2, ".+.+.+.τεστ");
    ASSERT_EQ(s2.slen(), 11);
}



TEST(SStringTestSuite, rjust_string_char_utf) {
    sstring::String s("τεστ");
    auto s2 = s.rjust(10, '+');
    ASSERT_EQ(s2, "++++++τεστ");
    ASSERT_EQ(s2.slen(), 10);
}

TEST(SStringTestSuite, rjust_stdstr) {
    sstring::String s("test");
    std::string fl = ".";
    auto s2 = s.rjust(10, fl);
    ASSERT_EQ(s2, "......test");
    ASSERT_EQ(s2.slen(), 10);
}

TEST(SStringTestSuite, rjust_stdstr_utf) {
    sstring::String s("τεστ");
    std::string fl = "+";
    auto s2 = s.rjust(10, fl);
    ASSERT_EQ(s2, "++++++τεστ");
    ASSERT_EQ(s2.slen(), 10);
}

TEST(SStringTestSuite, rjust_string_utf_large) {
    sstring::String s("τεστ");
    std::string fl = "+.-*";
    auto s2 = s.rjust(7, fl);
    ASSERT_EQ(s2, "+.-τεστ");
    ASSERT_EQ(s2.slen(), 7);
}


// Left
TEST(SStringTestSuite, ljust_string) {
    sstring::String s("test");
    auto s2 = s.ljust(10);
    ASSERT_EQ(s2, "test      ");
    ASSERT_EQ(s2.slen(), 10);
}

TEST(SStringTestSuite, ljust_char) {
    sstring::String s("test");
    char c = '+';
    auto s2 = s.ljust(10, c);
    ASSERT_EQ(s2, "test++++++");
    ASSERT_EQ(s2.slen(), 10);
}

TEST(SStringTestSuite, ljust_string_utf) {
    sstring::String s("τεστ");
    auto s2 = s.ljust(10);
    ASSERT_EQ(s2, "τεστ      ");
    ASSERT_EQ(s2.slen(), 10);
}

TEST(SStringTestSuite, ljust_string_fl_utf) {
    sstring::String s("τεστ");
    sstring::String fl(".");
    auto s2 = s.ljust(10, fl);
    ASSERT_EQ(s2, "τεστ......");
    ASSERT_EQ(s2.slen(), 10);
}


TEST(SStringTestSuite, ljust_string_multi_utf_fit) {
    sstring::String s("τεστ");
    sstring::String fl(".+");
    auto s2 = s.ljust(10, fl);
    ASSERT_EQ(s2, "τεστ.+.+.+");
    ASSERT_EQ(s2.slen(), 10);
}

TEST(SStringTestSuite, ljust_string_multi_utf_nfit) {
    sstring::String s("τεστ");
    sstring::String fl(".+");
    auto s2 = s.ljust(11, fl);
    ASSERT_EQ(s2, "τεστ.+.+.+.");
    ASSERT_EQ(s2.slen(), 11);
}



TEST(SStringTestSuite, ljust_string_char_utf) {
    sstring::String s("τεστ");
    auto s2 = s.ljust(10, '+');
    ASSERT_EQ(s2, "τεστ++++++");
    ASSERT_EQ(s2.slen(), 10);
}

TEST(SStringTestSuite, ljust_stdstr) {
    sstring::String s("test");
    std::string fl = ".";
    auto s2 = s.ljust(10, fl);
    ASSERT_EQ(s2, "test......");
    ASSERT_EQ(s2.slen(), 10);
}

TEST(SStringTestSuite, ljust_stdstr_utf) {
    sstring::String s("τεστ");
    std::string fl = "+";
    auto s2 = s.ljust(10, fl);
    ASSERT_EQ(s2, "τεστ++++++");
    ASSERT_EQ(s2.slen(), 10);
}

TEST(SStringTestSuite, ljust_string_utf_large) {
    sstring::String s("τεστ");
    std::string fl = "+.-*";
    auto s2 = s.ljust(7, fl);
    ASSERT_EQ(s2, "τεστ+.-");
    ASSERT_EQ(s2.slen(), 7);
}


// Center
TEST(SStringTestSuite, center_string) {
    sstring::String s("test");
    auto s2 = s.center(10);
    ASSERT_EQ(s2, "   test   ");
    ASSERT_EQ(s2.slen(), 10);
}

TEST(SStringTestSuite, center_char) {
    sstring::String s("test");
    char c = '+';
    auto s2 = s.center(10, c);
    ASSERT_EQ(s2, "+++test+++");
    ASSERT_EQ(s2.slen(), 10);
}

TEST(SStringTestSuite, center_string_utf) {
    sstring::String s("τεστ");
    auto s2 = s.center(10);
    ASSERT_EQ(s2, "   τεστ   ");
    ASSERT_EQ(s2.slen(), 10);
}

TEST(SStringTestSuite, center_string_fl_utf) {
    sstring::String s("τεστ");
    sstring::String fl(".");
    auto s2 = s.center(10, fl);
    ASSERT_EQ(s2, "...τεστ...");
    ASSERT_EQ(s2.slen(), 10);
}

TEST(SStringTestSuite, center_string_multi_utf_fit) {
    sstring::String s("τεστ");
    sstring::String fl(".+");
    auto s2 = s.center(10, fl);
    ASSERT_EQ(s2, ".+.τεστ.+.");
    ASSERT_EQ(s2.slen(), 10);
}

TEST(SStringTestSuite, center_string_multi_utf_nfit) {
    sstring::String s("τεστ");
    sstring::String fl(".+");
    auto s2 = s.center(11, fl);
    ASSERT_EQ(s2, ".+.+τεστ.+.");
    ASSERT_EQ(s2.slen(), 11);
}

TEST(SStringTestSuite, center_string_char_utf) {
    sstring::String s("τεστ");
    auto s2 = s.center(10, '+');
    ASSERT_EQ(s2, "+++τεστ+++");
    ASSERT_EQ(s2.slen(), 10);
}

TEST(SStringTestSuite, center_stdstr) {
    sstring::String s("test");
    std::string fl = ".";
    auto s2 = s.center(10, fl);
    ASSERT_EQ(s2, "...test...");
    ASSERT_EQ(s2.slen(), 10);
}

TEST(SStringTestSuite, center_stdstr_utf) {
    sstring::String s("τεστ");
    std::string fl = "+";
    auto s2 = s.center(10, fl);
    ASSERT_EQ(s2, "+++τεστ+++");
    ASSERT_EQ(s2.slen(), 10);
}

TEST(SStringTestSuite, center_string_utf_large) {
    sstring::String s("τεστ");
    std::string fl = "+.-*";
    auto s2 = s.center(10, fl);
    ASSERT_EQ(s2, "+.-τεστ+.-");
    ASSERT_EQ(s2.slen(), 10);
}


// -----------------------------------------------------------------
// Zero fill
TEST(SStringTestSuite, zfill_int) {
    sstring::String s("34");
    auto s2 = s.zfill(4);
    ASSERT_EQ(s2, "0034");
}

TEST(SStringTestSuite, zfill_int_large) {
    sstring::String s("34567");
    auto s2 = s.zfill(4);
    ASSERT_EQ(s2, "34567");
}

TEST(SStringTestSuite, zfill_float) {
    sstring::String s("34.567");
    auto s2 = s.zfill(7);
    ASSERT_EQ(s2, "034.567");
}


// -----------------------------------------------------------------
// Test concatenation operators
TEST(SStringTestSuite, stdstr_concat) {
    std::string tmp1("mytest");
    sstring::String s("Here is ");
    s+= tmp1;
    ASSERT_EQ(s, "Here is mytest");
}

// -----------------------------------------------------------------
// Test stream operators

// Test istream iterator
TEST(SStringTestSuite, ssistream) {
    std::string tmp1("mytest");
    std::string tmp2("extended");

    sstring::String s;
    std::stringstream ss;
    ss << tmp1;
    ss << tmp2;
    ss >> s;
    ASSERT_EQ(s, sstring::String("mytestextended"));
}

// Test ostream operator
TEST(SStringTestSuite, ssostream) {
    sstring::String s("mytest");
    std::stringstream ss;
    ss << s;
    std::string s2;
    ss >> s2;
    ASSERT_EQ(s2, "mytest");
}


// -----------------------------------------------------------------
// Test i18n upper/lower
TEST(SStringTestSuite, strUpper) {
     sstring::String s("γαϊδούρι");
     sstring::String u = s.upper();
     ASSERT_EQ(u, "ΓΑΪΔΟΎΡΙ");
}

TEST(SStringTestSuite, strLower) {
     sstring::String s("ΓΑΪΔΟΎΡΙ");
     sstring::String u = s.lower();
     ASSERT_EQ(u, "γαϊδούρι");
}


// Test i18n upper/lower sequence

TEST(SStringTestSuite, strUpperSeq) {
     sstring::String s("ΐ");
     auto u = s.upper();
     ASSERT_EQ(u, "Ϊ́");
}

TEST(SStringTestSuite, strLowerSeq) {
     sstring::String s("Ϊ́");
     auto u = s.lower();
     ASSERT_EQ(u, "ΐ");
}

TEST(SStringTestSuite, strUpperSeq2) {
     sstring::String s("ΐ");
     auto u = s.upper();
     ASSERT_EQ(u, "Ϊ");
}



