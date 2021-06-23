#include<iostream>
#include <sstream>
#include <climits>
#include "sstring.h"

uint64_t absl(int64_t n);

namespace sstring {

    String::String() : str{}, len{0} {}

    String::~String() = default;

    String::String(const char *s) : str(s), len{0} {
        rebuild();
    }

    String::String(const std::string &s) {
        str = s;
        len = 0;
        rebuild();
    }

    String::String(const String &s) {
        str = s.str;
        len = s.len;
        gpos = s.gpos;
    }

    String::String(String &&s) noexcept :
        str{std::move(s.str)}, len{s.len}, gpos{std::move(s.gpos)}
    {
        s.clear();
    }

    String & String::operator=(const String &s) {
        str = s.str;
        len = s.len;
        gpos = s.gpos;
        return *this;
    }

    String & String::operator=(const char *s) {
        str = std::string(s);
        len = 0;
        rebuild();
        return *this;
    }

    String & String::operator=(const std::string &s) {
        str = s;
        rebuild();
        return *this;
    }

    String & String::operator=(String &&s) noexcept {
        if (&s == this) {
            return *this;
        }
        str = std::move(s.str);
        len = s.len;
        gpos = std::move(s.gpos);
        s.clear();
        return *this;
    }

    String & String::operator=(std::string &&s) noexcept {
        str = std::move(s);
        rebuild();
        s.clear();
        return *this;
    }

    String
    String::operator()(int64_t lft) {
        int64_t rgt = len;
        return operator()(lft, rgt);
    }

    String
    String::operator()(int64_t lft, int64_t rgt) {

        int64_t s = -1;
        int64_t f = -1;

        if (lft >= 0 and rgt >= len) {
            rgt = len;
            f = str.size();
        }

        if (lft >= 0 and rgt >= 0 and lft > rgt) {
            return String();
        }

        if (lft < 0) {
            int64_t tmp = len + lft;
            s = tmp < 0 ? 0 : gpos[tmp];
        }

        if (rgt < 0) {
            int64_t tmp = len  + rgt;
            f = tmp < 0 ? 0 : gpos[tmp];
        }

        if (s < 0) {
            if (lft == len) {
                s = str.size();
            } else {
                s = gpos[lft];
            }
        }

        if (f < 0) {
            if (rgt == len) {
                f = str.size();
            } else {
                f = gpos[rgt];
            }
        }

        if (s > f) {
            return String();
        }
        return String(str.substr(s, f - s));
    }

    String String::operator[](int64_t idx) {
        if (absl(idx) > max_size() or absl(idx) >= len) {
            throw std::out_of_range("Index out of bounds");
        }
        if (idx >= 0) {
            return this->operator()(idx, idx+1);
        } else {
            if (idx == -1) {
                return this->operator()(idx);
            } else {
                return this->operator()(idx, idx+1);
            }
        }
    }

    String String::operator+=(const String &s) {
        str += s.str;
        for (auto e : s.gpos) {
            gpos.emplace_back(e + len);
        }
        len += s.len;
        return *this;
    }

    String String::operator+=(const char *s) {
        this->str += std::string(s);
        rebuild();
        return *this;
    }

    String String::operator+=(const std::string &s) {
        str += s;
        rebuild();
        return *this;
    }

    String String::operator+=(String &&s) {
        str += std::move(s.str);
        rebuild();
        s.clear();
        return *this;
    }

    String String::operator+=(std::string &&s) {
        str += s;
        rebuild();
        return *this;
    }

    void String::clear() {
        str.clear();
        len = 0;
        gpos.clear();
    }

    std::vector<String> String::split(const char &d, unsigned int cnt) {
        return split(String(std::to_string(d)), cnt);
    }

    std::vector<String> String::split(const char *d, unsigned int cnt) {
        return split(String(d), cnt);
    }
    
    std::vector<String> String::split(const std::string &d, unsigned int cnt) {
        return split(String(d), cnt);
    }

    std::vector<String> String::split(const String &d, unsigned int cnt) {
        std::vector<String> v;
        int n = 0;
        size_t ofs = 0;
        size_t pos = 0;

        while (true) {
            pos = str.find(d.str, ofs);
            if (pos == std::string::npos) {
                if (v.empty()) {
                    v.emplace_back(*this);
                    return v;
                }
                break;
            }
            v.emplace_back(String(str.substr(ofs, pos - ofs)));
            ofs = pos + d.str.size();
            if (cnt > 0 and ++n == cnt) return v;
        }
        if (str.size() - ofs >= 0) {
            v.emplace_back(String(str.substr(ofs, pos - ofs)));
        }
        return v;
    }

    // ------------------------------------------------------------------------
    // private methods
    void String::rebuild() {
        char *p = (char *) str.c_str();
        char *o = p;
        char seq = 0;
        len = 0;
        gpos.clear();

        // detect utf-8 char sequences and keep a map of grapheme index to
        // byte index in gpos
        while ((p - o) < str.size()) {
            if (((unsigned char)*p & (unsigned char)0x80) == 0x80) {
                if (seq == 0) {
                    len++;
                    gpos.emplace_back(p - o);
                    seq = 1;
                } else {
                    if (((unsigned  char) *p & (unsigned char) 0x40) == 0x40) {
                        len++;
                        gpos.emplace_back(p - o);
                    }
                }
            }
            else {
                gpos.emplace_back(p - o);
                len++;
                seq = 0;
            }
            p++;
        }
    }

    String operator+(const String &lhs, const String &rhs) {
        String r = lhs;
        r += rhs;
        return r;
    }

    String operator+(String &&lhs, String &&rhs) {
        String r = std::move(lhs);
        String n = std::move(rhs);
        return (r+=n);
    }

    String operator+(const String &lhs, String &&rhs) {
        String r = lhs;
        r += rhs;
        return r;
    }

    String operator+(String &&lhs, const String &rhs) {
        String r = std::move(lhs);
        r += rhs;
        return r;
    }

    String operator+(String lhs, const String &rhs) {
        return lhs+=rhs;
    }

    String operator+(String lhs, String &&rhs) {
        String r = std::move(rhs);
        return lhs+=r;
    }

    String operator+(const String &lhs, const char *rhs) {
        String r(lhs);
        return r+=rhs;
    }

    String operator+(const String &lhs, const std::string &rhs) {
        String r(lhs);
        return r+=rhs;
    }

    String operator+(String &&lhs, const std::string &rhs) {
        String r = std::move(lhs);
        return r+=rhs;
    }

    String operator+(const String &lhs, std::string &&rhs) {
        String r = lhs;
        return r+=std::move(rhs);
    }

    String operator+(const std::string &lhs, const std::string &rhs) {
        String r{lhs};
        return (r += rhs);
    }

    String operator+(const std::string &lhs, const String &rhs) {
        String r{lhs};
        return (r += rhs);
    }

    String operator+(const std::string &lhs, String &&rhs) {
        String r(lhs);
        String k = std::move(rhs);
        return r+=k;
    }

    String operator+(const std::string &lhs, std::string &&rhs) {
        String r{lhs};
        return (r += rhs);
    }

    String operator+(const std::string &lhs, const char *rhs) {
        String r{lhs};
        return r+=rhs;
    }

    String operator+(const char *lhs, const String &rhs) {
        String r(lhs);
        return r+=rhs;
    }

    String operator+(const char *lhs, const std::string &rhs) {
       String r(lhs);
       return r+=rhs;
    }


    bool operator ==(const String &lhs, const String &rhs) {
        return lhs.stdstr() == rhs.stdstr() and lhs.size() == rhs.size();
    }

    bool operator ==(const String &lhs, const char * rhs) {
        return lhs.stdstr() == std::string(rhs);
    }

    bool operator ==(const char * lhs, const String &rhs) {
        return std::string(lhs) == rhs.stdstr();
    }

    std::ostream & operator << (std::ostream &out, const String &s)
    {
        out << std::string(s.stdstr());
        return out;
    }

    std::istream & operator >> (std::istream &is, String &s)
    {
        std::string tmp;
        is >> tmp;
        s += tmp;
        return is;
    }

    inline static size_t max_size() {
        return LONG_MAX;
    }

}

uint64_t absl(int64_t n) {
    uint64_t r;
    n < 0 ? r = static_cast<uint64_t>((-1) * n) : r = static_cast<uint64_t>(n);
    return r;
}

