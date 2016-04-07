#ifndef CPPREF__STD_SYMBOLS_H
#define CPPREF__STD_SYMBOLS_H

#include <vector>
#include <string>
#include <iostream>

#if defined(_WIN32)

#include <stdint.h>

typedef uint8_t u_int8_t;
typedef uint16_t u_int16_t;
typedef uint32_t u_int32_t;

#endif

using std::vector;
using std::string;
using std::to_string;
using std::stoi;
using std::ifstream;
using std::cout;
using std::endl;
using std::cin;

#endif //CPPREF__STD_SYMBOLS_H
