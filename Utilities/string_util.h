#include <sstream>
#include <vector>

#ifndef _CPPREF_STRING_UTIL_H_
#define _CPPREF_STRING_UTIL_H_

namespace string_util {
    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
    std::vector<std::string> split(const std::string &s, char delim);
    std::string join(std::vector<std::string> v, std::string delim = "");
    const std::string WHITESPACE = " \n\r\t";
    std::string trim(const std::string& s);
    std::string trimLeft(const std::string& s);
    std::string trimRight(const std::string& s);
}

#endif //_CPPREF_STRING_UTIL_H_
