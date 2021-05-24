#ifndef SSTRING_SSTRING_H
#define SSTRING_SSTRING_H

#include <string>
#include <vector>
#include <iterator>

namespace sstring {

    class String {
    public:
        String();
        explicit String(const std::string &s);
        explicit String(const char *s);
        String(const String &s);
        String(String &&s) noexcept;
        virtual ~String();

        String & operator=(const String &s);
        String & operator=(const char *s);
        String & operator=(const std::string &s);
        String & operator=(String &&s) noexcept;
        String & operator=(std::string &&s) noexcept;

        // substring operator
        String operator() (int64_t lft);
        String operator() (int64_t lft, int64_t rgt);

        // grapheme at index operator
        String operator[] (int64_t idx);


        // += operator overloads
        String operator+=(const String &s);

        String operator+=(const char *s);

        String operator+=(const std::string &s);
        String operator+=(String && s);
        String operator+=(std::string &&s);

        // return the std::string object of String
        [[nodiscard]] inline const std::string & stdstr() const {return str;}
 
        // Get the size (number of bytes) of the String
        [[nodiscard]] inline size_t size() const {return str.size();}

        // Get the length of the String as the number of graphemes in it
        [[nodiscard]] inline size_t slen() const {return len;}
        void  clear();


        template <typename C>
        String join(const C & cntr) {
            auto max = std::size(cntr);
            String r;
            size_t cnt = 0;

            for (auto i : cntr) {
                r += i;
                cnt++;

                if (cnt != max) {
                    r += str;
                }
            }
            return r;
        }

        std::vector<String> split(const char &d, unsigned int cnt=0);
        std::vector<String> split(const char *d, unsigned int cnt=0);
        std::vector<String> split(const std::string &d, unsigned int cnt=0);
        std::vector<String> split(const String &d, unsigned int cnt=0);


    protected:
        std::string str;
        size_t len;
        std::vector<uint64_t> gpos;


    private:
        void rebuild();

    };

    String operator+(const String &lhs, const String &rhs);
    String operator+(String &&lhs, String &&rhs);
    String operator+(String &&lhs, const String &rhs);
    String operator+(const String &lhs, String &&rhs);
    String operator+(String lhs, const String &rhs);
    String operator+(String lhs, String &&rhs);
    String operator+(const String &lhs, const char *rhs);
    String operator+(const String &lhs, const std::string &rhs);
    String operator+(String &&lhs, const std::string &rhs);
    String operator+(const String &lhs, std::string &&rhs);

    String operator+(const std::string &lhs, const std::string &rhs);
    String operator+(const std::string &lhs, const String &rhs);
    String operator+(const std::string &lhs, String &&rhs);
    String operator+(const std::string &lhs, std::string &&rhs);

    String operator+(const std::string &lhs, const char *rhs);
    String operator+(const char *lhs, const String &rhs);


    String operator+(const char *lhs, const std::string &rhs);

    bool operator==(const String &lhs, const String &rhs);
    bool operator==(const String &lhs, const char *rhs);
    bool operator==(const char *lhs, const String &rhs);

    std::ostream & operator << (std::ostream &out, const String &s);
    std::istream & operator >> (std::istream &is, String &s);

    inline static size_t max_size();
}

#endif //SSTRING_SSTRING_H
