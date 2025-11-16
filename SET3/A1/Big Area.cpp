#include <iostream>
#include <algorithm>
#include <string>
#include <map>
#include <vector>
#include <cmath>
#include <complex>
#include <cstdint>
#include <float.h>
#include <iomanip>
#include <queue>
#include <fstream>
#include<random>

int main() {
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    double x1 = 1, x2 = 1.5 , x3 = 2;
    double y1 = 1, y2 = 2, y3 = 1.5;
    double r1 = 1 , r2 = std::sqrt(5)/2, r3 = std::sqrt(5)/2;
    double x_min = std::min(std::min(x1 - r1, x2 - r2), x3 - r3);
    double x_max = std::max(std::max(x1 + r1, x2 + r2), x3 + r3);
    double y_min = std::min(std::min(y1 - r1, y2 - r2), y3 - r3);
    double y_max = std::max(std::max(y1 + r1, y2 + r2), y3 + r3);
    std::uniform_real_distribution<> X_gen(x_min, x_max);
    std::uniform_real_distribution<> Y_gen(y_min, y_max);
    int counter = 0;
    double r1_sq = r1*r1;
    double r2_sq = r2*r2;
    double r3_sq = r3*r3;

    std::ofstream fout("..\\results.txt");
    std::vector<double> results;
    for (int i = 0; i < 100001; ++i) {
        double x = X_gen(generator);
        double y = Y_gen(generator);
        double x1_dif = x1 - x;
        double x2_dif = x2 - x;
        double x3_dif = x3 - x;
        double y1_dif = y1 - y;
        double y2_dif = y2 - y;
        double y3_dif = y3 - y;
        if (((i-100) % 500) == 0) {
            results.push_back((counter * 1.0 / i * (x_max - x_min) * (y_max - y_min)));
            fout << i << " " << results[results.size() - 1] << "\n";
        }
        if (x1_dif * x1_dif +  y1_dif * y1_dif >= r1_sq) continue;
        if (x2_dif * x2_dif +  y2_dif * y2_dif >= r2_sq) continue;
        if (x3_dif * x3_dif +  y3_dif * y3_dif >= r3_sq) continue;
        ++counter;


    }
    fout.close();


}