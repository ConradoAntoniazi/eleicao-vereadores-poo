#ifndef UTF_8_UTILS_HPP
#define UTF_8_UTILS_HPP

#include <string>

using namespace std;

class UTF8Utils{
public:
    static string iso_8859_1_to_utf8(string &str);
    static bool compare_pt_BR(const string &s1, const string &s2);
};

#endif // UTF_8_UTILS_HPP