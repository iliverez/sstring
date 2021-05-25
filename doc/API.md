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

### operator() (int64_t lft);
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
