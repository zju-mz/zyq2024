#include "HeapSort.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <random>

// 检查序列是否有序（升序）
template<typename T>
bool check(const std::vector<T>& vec) {
    for (size_t i = 1; i < vec.size(); ++i) {
        if (vec[i - 1] > vec[i]) {
            return false;
        }
    }
    return true;
}

// 生成随机序列
template<typename T>
std::vector<T> generateRandomVector(size_t size) {
    std::vector<T> vec(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> dis(0, 1000000);
    for (size_t i = 0; i < size; ++i) {
        vec[i] = dis(gen);
    }
    return vec;
}

// 生成有序序列
template<typename T>
std::vector<T> generateSortedVector(size_t size) {
    std::vector<T> vec(size);
    for (size_t i = 0; i < size; ++i) {
        vec[i] = static_cast<T>(i);
    }
    return vec;
}

// 生成逆序序列
template<typename T>
std::vector<T> generateReverseSortedVector(size_t size) {
    std::vector<T> vec(size);
    for (size_t i = 0; i < size; ++i) {
        vec[i] = static_cast<T>(size - i - 1);
    }
    return vec;
}

// 生成部分元素重复序列
template<typename T>
std::vector<T> generatePartiallyDuplicatedVector(size_t size) {
    std::vector<T> vec(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> dis(0, 100000);
    for (size_t i = 0; i < size; ++i) {
        vec[i] = dis(gen);
    }
    // 随机选择一些位置设置重复元素
    std::uniform_int_distribution<size_t> index_dis(0, size - 1);
    for (size_t i = 0; i < size / 10; ++i) {
        size_t index = index_dis(gen);
        vec[index] = vec[size - 1 - i];
    }
    return vec;
}

int main() {
    const size_t vectorSize = 1000000;

    // 测试随机序列
    std::vector<int> randomVec = generateRandomVector<int>(vectorSize);
    std::vector<int> randomVecCopy = randomVec;

    auto start = std::chrono::high_resolution_clock::now();
    heapsort(randomVec);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "自定义堆排序（随机序列）耗时: " << diff.count() << " 秒，排序结果: " << (check(randomVec)? "正确" : "错误") << std::endl;

    start = std::chrono::high_resolution_clock::now();
    std::make_heap(randomVecCopy.begin(), randomVecCopy.end());
    std::sort_heap(randomVecCopy.begin(), randomVecCopy.end());
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diffStl = end - start;
    std::cout << "std::sort_heap(随机序列)耗时: " << diffStl.count() << " 秒，排序结果: " << (check(randomVecCopy)? "正确" : "错误") << std::endl;

    // 测试有序序列
    std::vector<int> sortedVec = generateSortedVector<int>(vectorSize);
    std::vector<int> sortedVecCopy = sortedVec;

    start = std::chrono::high_resolution_clock::now();
    heapsort(sortedVec);
    end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    std::cout << "自定义堆排序（有序序列）耗时: " << diff.count() << " 秒，排序结果: " << (check(sortedVec)? "正确" : "错误") << std::endl;

    start = std::chrono::high_resolution_clock::now();
    std::make_heap(sortedVecCopy.begin(), sortedVecCopy.end());
    std::sort_heap(sortedVecCopy.begin(), sortedVecCopy.end());
    end = std::chrono::high_resolution_clock::now();
    diffStl = end - start;
    std::cout << "std::sort_heap(有序序列)耗时: " << diffStl.count() << " 秒，排序结果: " << (check(sortedVecCopy)? "正确" : "错误") << std::endl;

    // 测试逆序序列
    std::vector<int> reverseSortedVec = generateReverseSortedVector<int>(vectorSize);
    std::vector<int> reverseSortedVecCopy = reverseSortedVec;

    start = std::chrono::high_resolution_clock::now();
    heapsort(reverseSortedVec);
    end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    std::cout << "自定义堆排序（逆序序列）耗时: " << diff.count() << " 秒，排序结果: " << (check(reverseSortedVec)? "正确" : "错误") << std::endl;

    start = std::chrono::high_resolution_clock::now();
    std::make_heap(reverseSortedVecCopy.begin(), reverseSortedVecCopy.end());
    std::sort_heap(reverseSortedVecCopy.begin(), reverseSortedVecCopy.end());
    end = std::chrono::high_resolution_clock::now();
    diffStl = end - start;
    std::cout << "std::sort_heap(逆序序列)耗时: " << diffStl.count() << " 秒，排序结果: " << (check(reverseSortedVecCopy)? "正确" : "错误") << std::endl;

    // 测试部分元素重复序列
    std::vector<int> partiallyDuplicatedVec = generatePartiallyDuplicatedVector<int>(vectorSize);
    std::vector<int> partiallyDuplicatedVecCopy = partiallyDuplicatedVec;

    start = std::chrono::high_resolution_clock::now();
    heapsort(partiallyDuplicatedVec);
    end = std::chrono::high_resolution_clock::now();
    diff = end - start;
    std::cout << "自定义堆排序（部分元素重复序列）耗时: " << diff.count() << " 秒，排序结果: " << (check(partiallyDuplicatedVec)? "正确" : "错误") << std::endl;

    start = std::chrono::high_resolution_clock::now();
    std::make_heap(partiallyDuplicatedVecCopy.begin(), partiallyDuplicatedVecCopy.end());
    std::sort_heap(partiallyDuplicatedVecCopy.begin(), partiallyDuplicatedVecCopy.end());
    end = std::chrono::high_resolution_clock::now();
    diffStl = end - start;
    std::cout << "std::sort_heap(部分元素重复序列)耗时: " << diffStl.count() << " 秒，排序结果: " << (check(partiallyDuplicatedVecCopy)? "正确" : "错误") << std::endl;

    return 0;
}