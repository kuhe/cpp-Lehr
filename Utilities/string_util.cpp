#include "string_util.h"

#ifndef _CPPREF_STRING_UTIL_CPP_
#define _CPPREF_STRING_UTIL_CPP_

// http://stackoverflow.com/questions/236129/split-a-string-in-c

std::vector<std::string> &string_util::split(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> string_util::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

std::string string_util::join(std::vector<std::string> v, std::string delim) {
    std::stringstream ss;
    for(size_t i = 0; i < v.size(); ++i) {
        if(i != 0)
            ss << delim;
        ss << v[i];
    }
    std::string s = ss.str();
    return s;
}

// http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring


std::string string_util::trim(const std::string& s) {
    return trimRight(trimLeft(s));
}

std::string string_util::trimLeft(const std::string& s) {
    size_t startpos = s.find_first_not_of(string_util::WHITESPACE);
    return (startpos == std::string::npos) ? "" : s.substr(startpos);
}

std::string string_util::trimRight(const std::string& s) {
    size_t endpos = s.find_last_not_of(string_util::WHITESPACE);
    return (endpos == std::string::npos) ? "" : s.substr(0, endpos+1);
}

#endif //_CPPREF_STRING_UTIL_CPP_