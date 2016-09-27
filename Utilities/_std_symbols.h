#ifndef CPPREF__STD_SYMBOLS_H
#define CPPREF__STD_SYMBOLS_H

#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <type_traits>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

#include <stdint.h>
#include <functional>
#include <cstdint>
#include <climits>

typedef uint8_t u_int8_t;
typedef uint16_t u_int16_t;
typedef uint32_t u_int32_t;

#ifndef CPPREF__LEHR_THREADS
#define CPPREF__LEHR_THREADS
#endif //CPPREF__LEHR_THREADS

#else
#endif

using std::make_pair;

using std::true_type;
using std::false_type;

using std::integral_constant;

using std::is_same;
using std::enable_if;
using std::pair;
using std::size_t;

using std::vector;
using std::list;
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
