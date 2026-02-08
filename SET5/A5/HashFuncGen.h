#ifndef UNTITLED4_HASHFUNCGEN_H
#define UNTITLED4_HASHFUNCGEN_H
#include <string>
#include <vector>
#include <random>
#include <cmath>
#include <cstdint>
class HashFuncGen {
public:

    static uint64_t fnv(const std::string& str)
    {
        uint64_t hash = 1469598103934665603ULL; //константы я загуглил
        const uint64_t prime = 1099511628211ULL;
        for (char c : str) {
            hash ^= static_cast<uint64_t>(c);
            hash *= prime;
        }
        return hash;
    }

    static uint64_t mixing(uint64_t x) { // перемешка, чтобы убрать локальные зависимости, чиселки тоже подсмотрел
        x += 0x9e3779b97f4a7c15ULL;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
        x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
        return x;

    }

    static uint32_t hash32(const std::string& s) {
        uint64_t h64 = mixing(fnv(s));
        return static_cast<uint32_t>(h64 >> 32);
    }
};

#endif