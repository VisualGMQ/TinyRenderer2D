#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>

#define DEBUG

#ifdef DEBUG
#define Log(msg, ...) do { printf(msg "\n", ##__VA_ARGS__); fflush(stdout); }while(0)
#else
#define Log(msg, ...)
#endif

#endif
