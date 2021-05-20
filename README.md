# sstring
C++ Python-like strings with UTF support

## Highlights

sstring, aka smart string is a C++ library supporting UTF-8 strings (and in future UTF-16) and emoji seamlessly and offers string manipulation inspired by Python. Strings in this library can be used with **std::string** objects, or **const char * byte arrays**. IOstream is also supported. 

Additionally, some python strings functionality is offered like:
 * substrings with indices. Negative indices are supported too.
   ```C++
   auto s = sstring::String("My 🎃 test");
   std::cout << s(3) << std::endl;
   std::cout << s(1,6) << std::endl;
   
   // are equal to python's s[3:] and s[1:6] respectively and will result to:
   //  🎃 test
   //  y 🎃 t
   ```
 * Indexing a grapheme (could be a simple char, emoji or UTF-8 symbol)
   ```C++
   auto s = sstring::String("My 🎃 test");
   std::cout << s[3] << " Nice pumpkin!" << std::endl;
   
   // will result to:'m
   // 🎃 Nice pumpkin!
   ```
  * string join: Join a vector or array of strings,sstrings or const chars with a given string 
    ```C++
    sstring::String s(",");
    std::vector<std::string> v = {"🐼", "🐵", "💿"};
    sstring::String s2 = s.join(v);
    // will result to new sstring "🐼,🐵,💿";
    ```
  * split with a delimiter. The delimiter may be any of char, const char*, std::string or sstring::String
  ```C++
  sstring::String s("my:test");
  std::vector<sstring::String> v = s.split(":");
  // will return a vector with sstring:String elements "my" and "test"
  ```
  See doc/API.md for full documentation
        
## Build
To build sstring a c++17 compiler is required.

```bash
mkdir build
cd build && cmake ..
make
```
