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

void QuickSort(std::vector<int>& mass, int l, int r) {
    if (r - l <= 1) return;

    int pivot = mass[(r + l) / 2];
    int i = l, j = r - 1;

    while (i <= j) {
        while (mass[i] < pivot) ++i;
        while (mass[j] > pivot) --j;

        if (i <= j) {
            std::swap(mass[i++], mass[j--]);
        }
    }

    if (l < j + 1) QuickSort(mass, l, j + 1);
    if (i < r) QuickSort(mass, i, r);
}

void heapify(std::vector<int> &arr, int index, int l, int r) {
    int left = l + 2 * (index - l) + 1;
    int right = l + 2 * (index - l) + 2;
    int largest = index;
    if (left < r && arr[left] > arr[largest]) largest = left;
    if (right < r && arr[right] > arr[largest]) largest = right;
    if (largest != index) {
        std::swap(arr[index], arr[largest]);
        heapify(arr, largest, l, r);
    }
}

void build_heap(std::vector<int> &arr, int l, int r) {
    for (int i = l + (r - l) / 2 - 1; i >= l; --i)
        heapify(arr, i, l, r);
}

void heapSort(std::vector<int> &arr, int l, int r) {
    build_heap(arr, l, r);
    for (int i = r - 1; i > l; --i) {
        std::swap(arr[l], arr[i]);
        heapify(arr, l, l, i);
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

void IntroSort(std::vector<int>& mass, int l, int r, int depth=0) {
    if (r - l <= 16) {
        InsertionSort(mass, l, r);
        return;
    }
    if (depth >= 2 * std::log2(mass.size())) {
        heapSort(mass, l, r);
        return;
    }

    int pivot = mass[(r + l) / 2];
    int i = l, j = r - 1;

    while (i <= j) {
        while (mass[i] < pivot) ++i;
        while (mass[j] > pivot) --j;

        if (i <= j) {
            std::swap(mass[i++], mass[j--]);
        }
    }

    if (l < j + 1) IntroSort(mass, l, j + 1, depth+1);
    if (i < r) IntroSort(mass, i, r, depth+1);
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

    long  TestQuick(std::vector<int> A) {
        auto start = std::chrono::high_resolution_clock::now();
        QuickSort(A, 0, A.size());
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long msec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        return msec;
    }
    long long  TestIntro(std::vector<int> A) {
        auto start = std::chrono::high_resolution_clock::now();
        IntroSort(A, 0, A.size());
        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        long long msec = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        return msec;
    }

};

int main() {
    // Отключить синхронизацию между iostream и stdio.
    std::ios::sync_with_stdio(false);

    // Отключить синхронизацию между std::cin и std::cout.
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> a;
    for (int i =0; i < n; ++i) {
        int k;
        std::cin >> k;
        a.push_back(k);
    }
    IntroSort(a,0, a.size(), 15);
    for (int i =0; i < n; ++i) {
        std::cout << a[i] << " ";
    }



}