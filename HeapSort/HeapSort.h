#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
void heapsort(std::vector<T>& vec) {

    // 先建成最大堆
    std::make_heap(vec.begin(), vec.end());

    for (size_t i = vec.size(); i > 1; --i) {
        // 将最大元素（堆顶）移动到末尾,进行排序
        std::pop_heap(vec.begin(), vec.begin() + i);
    }
    
}