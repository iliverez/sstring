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

### operator=(const String &s)
Copy assignment

### operator=(const char *s)
Assign a *const* *char* * to a String

### operator=(const std::string &s)
Assign an *std::string* to a String

### operator=(String &&s)
Move assignment

### operator=(std::string &&s)
Creates a String object where the argument *std::string* is moved to it

## Substrings

### operator() (int64_t lft)
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

### operator[] (int64_t idx)
Return the grapheme at index idx. If the index is larger than the length of the String, it throws an std::out_of_range exception.
Negative index is also supported.


## Extend string

### opearator+=(const String &s)
Extend current string with the content of sstring::String s. String s may be empty.

### opearator+=(const char *s)
Extend current string with the contents of *const char *s*. *const char *s* may be empty.

### opearator+=(const String &s)
Extend current string with the content of sstring::String s. String s may be empty.


