# sstring API

## Constructors and copy move operators

### String()
Empty constructor. Initializes an empty string

### ~String()
Default destructor

### explicit String(const std::string &s)
Create a String from an *std::string*

### explicit String(const char *s)
Create a String from a *const* *char* *

### String(const String &s)
Copy constructor

### String(String &&s) noexcept
Move constructor

### String operator=(const String &s)
Copy assignment

### String operator=(const char *s)
Assign a *const* *char* * to a String

### String operator=(const std::string &s)
Assign an *std::string* to a String

### String operator=(String &&s)
Move assignment

### String operator=(std::string &&s)
Creates a String object where the argument *std::string* is moved to it

## Substrings

### String operator() (int64_t lft)
Creates a substring starting from position lft.
This is equivalent to Python's [] substring like 
```python 
s[3:]
```

For example, to substring the String *"This is a test"* from position 5 to the end of it, would be:
```C++
sstring::String s("This is a test");
std::cout << s(5) << std::endl;
```
and would return `is a test`.
If lft is larger than the length of the String, an empty String wil be returned.

If a negative lft is given, the substring will begin from lft graphemes starting from the end of the string until its end:
```C++
sstring::String s("This is a test");
std::cout << s(-4) << std::endl;
```
will return `test`.
If the negative lft is larger than the length of the String, a copy of the whole initial String will be returned.

### operator() (int64_t lft, int64_t rgt)
Creates a substring starting from position lft until rgt. Grapheme at rgt is not included.
This is equivalent to Python's [] substring like 
```python 
s[1:4]
```

For example, to substring the String *"This is a test"* from position 1 to 4, it would be:
```C++
sstring::String s("This is a test");
std::cout << s(1,4) << std::endl;
```
and would return `his`.

If rgt is larger than the String length, the lengh of the String is used as rgt.
If both lft and rgt are larger than the length of String, an empty string is returned
If negative indices are used, counting starts from the end of String (but counts from 1, not 0). For example:

```C++
sstring::String s("This is a test");
std::cout << s(-4, -1) << std::endl;
```
will return ```tes```

If negative lft is larger than the length of String, but rgt is valid, lft is considered the start of the String.
If both negative indices are larger than length, an empty string is returned.

## Grapheme at index

### String operator[] (int64_t idx)
Return the grapheme at index idx. If the index is larger than the length of the String, it throws an std::out_of_range exception.
Negative index is also supported.


## Extend string

### String opearator+=(const String &s)
Extend current string with the content of sstring::String s. String s may be empty.

### String opearator+=(const char *s)
Extend current string with the contents of *const char *s*. *const char *s* may be empty.

### String opearator+=(const std::string &s)
Extend current string with the content of std::string s. String s may be empty.

### String operator+=(String && s)
Extend current string with the content of sstring::String s. String s may be empty. Uses move semantics.

### String operator+=(std::string &&s)
Extend current string with the content of std::string s. String s may be empty. Uses move semantics.

## Alignment
The String class offers alignment capability (left, center, right). The alignment space is filled by default with the space char. A string or another char can be used to fill the alignment.

The alignment methods return a new string with the aligned content or a copy of the initial String if the alignment space is smaller than the length of the String.

If a negative value is used for the alignment space, a copy of the initial string is returned.

If the length of the filling string is larger than the space to be filled, the first graphemes that fit will be used.

For center alignment only:

  * If the space cannot be equally divided, the extra space goes on the left side.
  * if the filling string does not fit in the alignment space on both sides, it will be trimmed on both sides so that the result string is still centered.

For example:
```C++
sstring::String s("test");
std::cout << ":" << s.ljust(10) << ":" << std::endl;
std::cout << ":" << s.ljust10, ".") << ":" << std::endl;
std::cout << ":" << s.ljust(10, ".+") << ":" << std::endl;
std::cout << ":" << s.ljust(11, ".+") << ":" << std::endl;
std::cout << ":" << s.center(10, '.') << ":" << std::endl;
std::cout << ":" << s.center(10, '.+') << ":" << std::endl;
std::cout << ":" << s.center(10, ".+-*") << ":" << std::endl;
std::cout << ":" << s.rjust(10, ".+") << ":" << std::endl;
```
will produce:

```bash
:test      :
:test......:
:test.+.+.+:
:test.+.+.+.:
:...test...:
:.+.test.+.:
:.+-test.+-:
:.+.+.+test:
```
### String ljust(int64_t width)
Align text on the left side of a space with given width. Space char is used as a filling char.

### String ljust(int64_t width, const char c)
Align text on the left side of a space with given width, using character c for filling the space.

### String ljust(int64_t width, const std::string &c)
Align text on the left side of a space with given width, using std::string c for filling the space.

### String ljust(int64_t width, const char *c)
Align text on the left side of a space with given width, using const char * c for filling the space.

### String ljust(int64_t width, const String &c)
Align text on the left side of a space with given width, using String c for filling the space.


### String center(int64_t width)
Align text on the left side of a space with given width. Space char is used as a filling char.

### String center(int64_t width, const char c)
Align text in the center of a space with given width, using character c for filling the space.

### String center(int64_t width, const std::string &c)
Align text in the center of a space with given width, using std::string c for filling the space.

### String center(int64_t width, const char *c)
Align text in the center of a space with given width, using const char * c for filling the space.

### String centerint64_t width, const String &c)
Align text in the center of a space with given width, using String c for filling the space.

### String rjust(int64_t width)
Align text on the right side of a space with given width. Space char is used as a filling char.

### String rjust(int64_t width, const char c)
Align text on the right side of a space with given width, using char c for filling the space.

### String rjust(int64_t width, const std::string &c)
Align text on the right side of a space with given width, std::string c for filling the space.

### String rjust(int64_t width, const char *c)
Align text on the right side of a space with given width, using const char *c for filling the space.

### String rjust(int64_t width, const String &c)
Align text on the right side of a space with given width, using char c for filling the space.


## Zero fill
Fill a String with leading zeros

### String zfill(int64_t width)
Fill the string with leading zeroes. If the string is larger than the width, the whole String will be returned in a new String.
