#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "RandomStreamGen.h"
#include "HashFuncGen.h"
#include "HyperLogLog.h"

int main() {
    const size_t N = 1'000'000;
    const double step = 0.05;
    const int B = 20;
    const int R = 30;

    RandomStreamGen tmp(N, 1);
    auto ks = tmp.split_prefixes(step);

    std::ofstream out("../raw_B20.csv");
    out << "k,run,Nt\n";

    for (int r = 0; r < R; ++r) {
        RandomStreamGen gen(N, 1000 + r);
        auto stream = gen.gen_stream();

        HyperLogLog hll(B);

        size_t idx = 0;
        size_t next_k = ks[idx];

        for (size_t i = 0; i < stream.size(); ++i) {
            uint32_t h = HashFuncGen::hash32(stream[i]);
            hll.add(h);

            size_t processed = i + 1;
            if (processed == next_k) {
                out << processed << "," << r << "," << hll.estimate() << "\n";
                idx++;
                if (idx >= ks.size()) break;
                next_k = ks[idx];
            }
        }
    }

    return 0;
}
