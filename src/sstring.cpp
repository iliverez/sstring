#include<iostream>
#include <sstream>
#include <climits>
#include <locale>
#include <codecvt>

#include "i18n.h"
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

    String String::operator()(int64_t lft, int64_t rgt) const {
        return (*this)(lft,rgt);
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
        std::string td = "";
        td += d;
        return split(String(td), cnt);
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

    // rsplit functions
    std::vector<String> String::rsplit(const char &d, unsigned int cnt) {
        std::string td = "";
        td += d;
        return rsplit(String(td), cnt);
    }

    std::vector<String> String::rsplit(const char *d, unsigned int cnt) {
        return rsplit(String(d), cnt);
    }

    std::vector<String> String::rsplit(const std::string &d, unsigned int cnt) {
        return rsplit(String(d), cnt);
    }

    std::vector<String> String::rsplit(const String &d, unsigned int cnt) {
        std::vector<String> v;
        int n = 0;
        size_t ofs = str.size();
        size_t pos = str.size();
        std::string st;
        size_t t = 0;

        while (true) {
            pos = str.substr(0, pos+1).rfind(d.str);
            if (pos == std::string::npos) {
                if (v.empty()) {
                    v.emplace_back(*this);
                    return v;
                }
                break;
            }
            t = ofs - pos;
            v.emplace_back(String(str.substr(pos + d.size(), ofs - pos)));
            pos = pos - 1;
            ofs = pos;
            if (cnt > 0 and ++n == cnt) return v;
        }
        if (str.size() - ofs  - pos -1 >= 0) {
            v.emplace_back(String(str.substr(0, ofs + 1)));
        }
        return v;
    }


    // ------------------------------------------------------------------------
    // String alignment methods

    String String::just(int64_t width, const String &c, Alignment dir) {

        if (width <= len)
            return String(*this);

        auto fl = c;
        String r;
        int64_t le = (width-len) / fl.slen();
        int64_t sp = (width-len) % fl.slen();

        if (dir == Alignment::CENTER) {
            r += just( ((len+width)/2) + ((len+width) % 2), fl, Alignment::RIGHT);
            le = ((width - len) / 2) / fl.slen();
            sp = ((width - len) / 2) % fl.slen();
        }

        if (dir == Alignment::LEFT)
            r += str;

        for (auto i=0; i < le; i++)
            r += fl;
        if (sp > 0)
            r += fl(0, sp);

        if (dir == Alignment::RIGHT)
            r += str;

        return r;
    }

    // Align right
    String String::rjust(int64_t width, const String &c) {
        return just(width, c, Alignment::RIGHT);
    }

    String String::rjust(int64_t width) {
        return just(width, String(" "), Alignment::RIGHT);
    }

    String String::rjust(int64_t width, const char c) {
        return just(width, String(std::string(1,c)), Alignment::RIGHT);
    }

    String String::rjust(int64_t width, const char *c) {
        return just(width, String(c), Alignment::RIGHT);
    }

    String String::rjust(int64_t width, const std::string &c) {
        return just(width, String(c), Alignment::RIGHT);
    }

    // Align left
    String String::ljust(int64_t width, const String &c) {
        return just(width, c, Alignment::LEFT);
    }

    String String::ljust(int64_t width) {
        return just(width, String(" "), Alignment::LEFT);
    }

    String String::ljust(int64_t width, const char c) {
        return just(width, String(std::string(1,c)), Alignment::LEFT);
    }

    String String::ljust(int64_t width, const char *c) {
        return just(width, String(c), Alignment::LEFT);
    }

    String String::ljust(int64_t width, const std::string &c) {
        return just(width, String(c), Alignment::LEFT);
    }

    // Align center
    String String::center(int64_t width, const String &c) {
        return just(width, c, Alignment::CENTER);
    }

    String String::center(int64_t width) {
        return just(width, String(" "), Alignment::CENTER);
    }

    String String::center(int64_t width, const char c) {
        return just(width, String(std::string(1,c)), Alignment::CENTER);
    }

    String String::center(int64_t width, const char *c) {
        return just(width, String(c), Alignment::CENTER);
    }

    String String::center(int64_t width, const std::string &c) {
        return just(width, String(c), Alignment::CENTER);
    }


    // ------------------------------------------------------------------------
    String String::zfill(int64_t width) {
        return just(width, String("0"), Alignment::RIGHT);
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

    // ------------------------------------------------------------------------
    //  Operators
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
        s = tmp;
        return is;
    }

    inline static size_t max_size() {
        return LONG_MAX;
    }

    String String::lower() const {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
        std::u32string u32str = convert.from_bytes(str);

        for (size_t i = 0; i < u32str.size(); ++i) {
            u32str[i] = to_lower(u32str[i]);
        }
        return String(convert.to_bytes(u32str));
    }

    String String::upper() const {
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> convert;
        std::u32string u32str = convert.from_bytes(str);

        for (size_t i = 0; i < u32str.size(); ++i) {
            u32str[i] = to_upper(u32str[i]);
        }
        return String(convert.to_bytes(u32str));
    }

    char32_t String::to_lower(char32_t ch) const {
        auto it = LOWER_TABLE.find(ch);
        return (it != LOWER_TABLE.end()) ? it->second : ch;
    }

    char32_t String::to_upper(char32_t ch) const {
        auto it = UPPER_TABLE.find(ch);
        return (it != UPPER_TABLE.end()) ? it->second : ch;
    }



}

uint64_t absl(int64_t n) {
    uint64_t r;
    n < 0 ? r = static_cast<uint64_t>((-1) * n) : r = static_cast<uint64_t>(n);
    return r;
}

