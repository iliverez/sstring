#ifndef SSTRING_SSTRING_H
#define SSTRING_SSTRING_H

#include <string>
#include <cstdint>
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
        String operator() (int64_t lft, int64_t rgt) const;

        // grapheme at index operator
        String operator[] (int64_t idx);

        // += (String extend) operator overloads
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
        [[nodiscard]] inline int64_t slen() const {return len;}
        void  clear();

        // join the elements of container (iterable) C with the value of this
        // String as a delimiter.
        //
        // If the length of the container is 1, the unique element of the container
        // is returned without the value of this String.
        //
        // If the length of the container is 0, an emtpty String is returned.
        //
        // If this string is empty, the elements of the container are concatenated.
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

        // split a String using the given delimiter.
        // Funcion overloads are available for any type of delimiter
        std::vector<String> split(const char &d, unsigned int cnt=0);
        std::vector<String> split(const char *d, unsigned int cnt=0);
        std::vector<String> split(const std::string &d, unsigned int cnt=0);
        std::vector<String> split(const String &d, unsigned int cnt=0);

        // rsplit: Split a String using a delimiter from starting from the right.
        // Return  
        std::vector<String> rsplit(const char &d, unsigned int cnt=0);
        std::vector<String> rsplit(const char *d, unsigned int cnt=0);
        std::vector<String> rsplit(const std::string &d, unsigned int cnt=0);
        std::vector<String> rsplit(const String &d, unsigned int cnt=0);


        // allignment methods.
        String rjust(int64_t width);
        String rjust(int64_t width, const char c);
        String rjust(int64_t width, const std::string &c);
        String rjust(int64_t width, const char *c);
        String rjust(int64_t width, const String &c);

        String ljust(int64_t width);
        String ljust(int64_t width, const char c);
        String ljust(int64_t width, const std::string &c);
        String ljust(int64_t width, const char *c);
        String ljust(int64_t width, const String &c);

        String center(int64_t width);
        String center(int64_t width, const char c);
        String center(int64_t width, const std::string &c);
        String center(int64_t width, const char *c);
        String center(int64_t width, const String &c);

        // zfill, pad a string, usully representing a number with zeros
        // at the leftin given space. Take care for point and decimal digits.

        String zfill(int64_t width);
        // substitute a given substring with a given new one and will return
        //  the result in a new string.
        //
        // Optionally, a count will be passed to denote how many occurrences 
        // to replace. Default value will be -1 which means all.
        //
        // Optionally, the reverse option can be given, to start replacing from
        // the end of the string. Default is to replace from the start.
        //
        // If the old substring is not found, the original string is returned in
        // a new object.
        // String replace(String ptrn, String s, int nm=-1, bool rvrs=false);

        String upper() const;
        String lower() const;

    protected:
        std::string str;
        int64_t len;
        std::vector<uint64_t> gpos;


    private:
        enum class Alignment {
            RIGHT,
            LEFT,
            CENTER
        };
        void rebuild();
        String just(int64_t width, const String &c, Alignment dir);
	   
        // Helper function to convert a Unicode character to lowercase
        char32_t to_lower(char32_t ch) const;

        // Helper function to convert a Unicode character to uppercase
        char32_t to_upper(char32_t ch) const;


	// helper string for i18n supporrt
	//std::string data;

    };


    // String contantenation. Various types are supported, both for copy
    // or move semantics
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

    // String equality. Notice that it refers to string content
    // equality and not to object (type) equality.
    bool operator==(const String &lhs, const String &rhs);
    bool operator==(const String &lhs, const char *rhs);
    bool operator==(const char *lhs, const String &rhs);

    // iostream support (input/output)
    std::ostream & operator << (std::ostream &out, const String &s);
    std::istream & operator >> (std::istream &is, String &s);

    // Return the max allowed size for String
    inline static size_t max_size();
}

#endif //SSTRING_SSTRING_H
