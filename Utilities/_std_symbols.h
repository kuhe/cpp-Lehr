#ifndef CPPREF__STD_SYMBOLS_H
#define CPPREF__STD_SYMBOLS_H

#include <vector>
#include <string>
#include <iostream>
#include <type_traits>

#if defined(_WIN32)

#include <stdint.h>
#include <functional>

typedef uint8_t u_int8_t;
typedef uint16_t u_int16_t;
typedef uint32_t u_int32_t;

#endif

using std::true_type;
using std::false_type;

using std::integral_constant;

using std::is_same;
using std::enable_if;
using std::pair;
using std::size_t;

using std::vector;
using std::string;
using std::to_string;
using std::stoi;
using std::ifstream;
using std::cout;
using std::endl;
using std::cin;

using std::move;
using std::function;
using std::forward;
using std::remove_const;

#endif //CPPREF__STD_SYMBOLS_H
