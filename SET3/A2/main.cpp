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
#include<chrono>

void MergeSort(std::vector<int>& mass, int l, int r) {
    int m = (l+r)/2;
    if (r-l <= 1) return;
    MergeSort(mass, l, m);
    MergeSort(mass, m, r);
    std::vector<int> temp;
    int lp = l, rp = m;
    while (lp < m && rp < r) {
        if (mass[lp] < mass[rp]) {
            temp.push_back(mass[lp++]);
        }
        else {
            temp.push_back(mass[rp++]);
        }
    }
    while (lp < m) {
        temp.push_back(mass[lp++]);
    }
    while (rp < r) {
        temp.push_back(mass[rp++]);
    }
    for (int i = l; i < r; ++i) {
        mass[i] = temp[i - l];
    }
}
void InsertionSort(std::vector<int>& mass, int l, int r) {
    for (int i = l+1; i < r; ++i) {
        int k = i;
        while (k>l && mass[k-1] > mass[k]) {
            std::swap(mass[k], mass[k-1]);
            --k;
        }
    }
}
void CombinedSort(std::vector<int>& mass, int l, int r, int barrier) {
    int m = (l+r)/2;
    if (r-l <= barrier){
        InsertionSort(mass, l, r);

        return;
    }
    CombinedSort(mass, l, m, barrier);
    CombinedSort(mass, m, r, barrier);
    std::vector<int> temp;
    int lp = l, rp = m;
    while (lp < m && rp < r) {
        if (mass[lp] < mass[rp]) {
            temp.push_back(mass[lp++]);
        }
        else {
            temp.push_back(mass[rp++]);
        }
    }
    while (lp < m) {
        temp.push_back(mass[lp++]);
    }
    while (rp < r) {
        temp.push_back(mass[rp++]);
    }
    for (int i = l; i < r; ++i) {
        mass[i] = temp[i - l];
    }
}


class ArrayGenerator {
    std::random_device rand_dev;
    std::mt19937 generator;
    std::uniform_int_distribution<> gen;
public:
    ArrayGenerator(int min, int max) : generator(rand_dev()), gen(min, max) {}

    std::vector<int> GetRandomVector(int n) {
        std::vector<int> result;
        result.reserve(n);
        for (int i = 0; i < n; ++i) {
            result.push_back(gen(generator));
        }
        return result;
    }

    std::vector<int> GetBackVector(int n) {
        std::vector<int> result;
        result.reserve(n);
        for (int i = 0; i < n; ++i) {
            result.push_back(n - i);
        }
        return result;
    }
    std::vector<int> GetAlmostVector(int n) {
        std::vector<int> result;
        result.reserve(n);
        for (int i = 0; i < n; ++i) {
            result.push_back(i);
        }
        int sw = std::min(n/50 + 1, 50);
        for (int i = 0; i < sw; ++i) {
            int n1 = gen(generator) % n;
            int n2 = gen(generator) % n;
            std::swap(result[n1], result[n2]);
        }
        return result;
    }

};

struct SortTester {

    long  TestMerge(std::vector<int> A) {
        auto start = std::chrono::high_resolution_clock::now();
        MergeSort(A, 0, A.size());
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long msec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        return msec;
    }
    long long  TestCombined(std::vector<int> A, int b) {
        auto start = std::chrono::high_resolution_clock::now();
        CombinedSort(A, 0, A.size(), b);
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long msec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        return msec;
    }

};

int main() {
    std::ofstream fout1("..\\merge_results_unordered1.txt");
    std::ofstream fout2("..\\merge_results_back_ordered1.txt");
    std::ofstream fout3("..\\merge_results_almost_ordered1.txt");
    std::ofstream fout4("..\\combined5_results_unordered1.txt");
    std::ofstream fout5("..\\combined5_results_back_ordered1.txt");
    std::ofstream fout6("..\\combined5_results_almost_ordered1.txt");
    std::ofstream fout7("..\\combined10_results_unordered1.txt");
    std::ofstream fout8("..\\combined10_results_back_ordered1.txt");
    std::ofstream fout9("..\\combined10_results_almost_ordered1.txt");
    std::ofstream fout10("..\\combined20_results_unordered1.txt");
    std::ofstream fout11("..\\combined20_results_back_ordered1.txt");
    std::ofstream fout12("..\\combined20_results_almost_ordered1.txt");
    std::ofstream fout13("..\\combined30_results_unordered1.txt");
    std::ofstream fout14("..\\combined30_results_back_ordered1.txt");
    std::ofstream fout15("..\\combined30_results_almost_ordered1.txt");
    std::ofstream fout16("..\\combined50_results_unordered1.txt");
    std::ofstream fout17("..\\combined50_results_back_ordered1.txt");
    std::ofstream fout18("..\\combined50_results_almost_ordered1.txt");
    SortTester T;
    ArrayGenerator Genos(0, 6000);
    for (int i = 500; i <=100000; i+=100) {
        auto A = Genos.GetRandomVector(i);
        fout1 << i << " " << T.TestMerge(A) << '\n';
        fout4 << i << " " << T.TestCombined(A, 5) << '\n';
        fout7 << i << " " << T.TestCombined(A, 10) << '\n';
        fout10 << i << " " << T.TestCombined(A, 20) << '\n';
        fout13 << i << " " << T.TestCombined(A, 30) << '\n';
        fout16 << i << " " << T.TestCombined(A, 50) << '\n';
        A = Genos.GetBackVector(i);
        fout2 << i << " " << T.TestMerge(A) << '\n';
        fout5 << i << " " << T.TestCombined(A, 5) << '\n';
        fout8 << i << " " << T.TestCombined(A, 10) << '\n';
        fout11 << i << " " << T.TestCombined(A, 20) << '\n';
        fout14 << i << " " << T.TestCombined(A, 30) << '\n';
        fout17 << i << " " << T.TestCombined(A, 50) << '\n';
        A = Genos.GetAlmostVector(i);
        fout3 << i << " " << T.TestMerge(A) << '\n';
        fout6 << i << " " << T.TestCombined(A, 5) << '\n';
        fout9 << i << " " << T.TestCombined(A, 10) << '\n';
        fout12 << i << " " << T.TestCombined(A, 20) << '\n';
        fout15 << i << " " << T.TestCombined(A, 30) << '\n';
        fout18 << i << " " << T.TestCombined(A, 50) << '\n';
        if (i % 5000 == 0) std::cout << i << '\n';
    }
    fout1.close();
    fout2.close();
    fout3.close();
    fout4.close();
    fout5.close();
    fout6.close();
    fout7.close();
    fout8.close();
    fout9.close();
    fout10.close();
    fout11.close();
    fout12.close();
    fout13.close();
    fout14.close();
    fout15.close();
    fout16.close();
    fout17.close();
    fout18.close();



}