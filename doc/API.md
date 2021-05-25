# sstring API

## Constructors and copy move operators

### String()
Empty constructor. Initializes an empty string

### ~String()
Default destructor

### String(const std::string &s)
Create a String from an *std::string*

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

