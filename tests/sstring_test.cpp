/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2019  <copyright holder> <email>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

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

TEST(SStringTestSuite, substr_negative_lft_one) {
    sstring::String s("mytest");
    auto ss = s(-1);
    sstring::String tval{"t"};
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

TEST(SStringTestSuite, substr_bndr_lft) {
    sstring::String s("mytest");
    auto ss = s(0, 4);
    ASSERT_EQ(ss, "myte");
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
    std::vector<sstring::String> v = s.split(":");
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
    ss >> s;
    ss.clear();
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


