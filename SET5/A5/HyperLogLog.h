
#ifndef UNTITLED4_HYPERLOGLOG_H
#define UNTITLED4_HYPERLOGLOG_H

#include <vector>
#include <cstdint>
#include <cmath>
#include <algorithm>

class HyperLogLog {
private:
    int B_;
    uint32_t m_;
    std::vector<uint8_t> M_;

    static uint8_t rho(uint32_t tail, int tailBits) {
        if (tail == 0) return static_cast<uint8_t>(tailBits + 1);
        uint8_t cnt = 1;
        for (int i = tailBits - 1; i >= 0; --i) {
            if ((tail >> i) & 1u) break;
            cnt++;
        }
        return cnt;
    }

    double alpha() const {
        return 0.7213 / (1.0 + 1.079 / static_cast<double>(m_));
    }

public:
    HyperLogLog(int B) : B_(B), m_(1u << B), M_(m_, 0) {}

    void add(uint32_t h) {
        uint32_t j = h >> (32 - B_);
        int tailBits = 32 - B_;
        uint32_t tailMask = (tailBits == 32) ? 0xFFFFFFFFu : ((1u << tailBits) - 1u);
        uint32_t tail = h & tailMask;

        uint8_t r = rho(tail, tailBits);
        if (r > M_[j]) M_[j] = r;
    }

    double estimate() const {
        double Z = 0.0;
        double V = 0;

        for (uint8_t v : M_) {
            Z += std::ldexp(1.0, -v);
            if (v == 0) V++;
        }

        double E = alpha() * static_cast<double>(m_) * static_cast<double>(m_) / Z;

        if (E <= 2.5 * static_cast<double>(m_) && V > 0) {
            E = (static_cast<double>(m_) * std::log(static_cast<double>(m_) / V));
        }
        return E;
    }
};


#endif //UNTITLED4_HYPERLOGLOG_H