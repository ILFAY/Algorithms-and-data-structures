#ifndef UNTITLED4_RANDOMSTREAMGEN_H
#define UNTITLED4_RANDOMSTREAMGEN_H
#include <string>
#include <vector>
#include <random>
#include <cmath>
#include <cstdint>

class RandomStreamGen {
private:
    std::mt19937 gen_;
    size_t n_;
    std::string rand_string() {
        static const std::string A = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-";
        std::uniform_int_distribution<int> lenDist(1, 30);
        std::uniform_int_distribution<int> chDist(0, static_cast<int>(A.size() - 1));

        int L = lenDist(gen_);
        std::string s(L, '\0');
        for (int i = 0; i < L; ++i) s[i] = A[chDist(gen_)];
        return s;
    }
public:
    RandomStreamGen(size_t n, size_t seed =42) : gen_(seed), n_(n) {}
    std::vector<std::string> gen_stream() {
        std::vector<std::string> s;
        s.reserve(n_);
        for (size_t i = 0; i < n_; ++i) {s.push_back(rand_string());}
        return s;
    }

    std::vector<size_t> split_prefixes(double step) {
        std::vector<size_t> splt;

        for (double i = step; i < 1; i+=step) {
            splt.push_back(static_cast<size_t>(std::floor(i * n_)));
        }
        if (splt.empty() || splt.back() != n_) splt.push_back(n_);
        return splt;
    }
};
#endif