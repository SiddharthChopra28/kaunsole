#pragma once

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define MIN(a,b) ((a) < (b) ? (a) : (b))

#define DEBUG

#ifdef DEBUG
#define LOG(fmt, ...) fprintf(stderr, fmt"\n", ##__VA_ARGS__)
#else 
#define LOG(...)
#endif

