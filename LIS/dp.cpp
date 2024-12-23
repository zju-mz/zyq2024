#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> longestIncreasingSubsequence(const vector<int>& A) {
    int n = A.size();
    if (n == 0) return {};
    
    // length[i] 表示以 A[i] 结尾的最长递增子序列的长度，初始值都为1，即每个元素至少可以组成一个长度为1的子序列
    vector<int> length(n, 1); 
    // pre[i] 用来记录以 A[i] 结尾的最长递增子序列的前一个元素索引，初始值都为-1，即没有前一个元素
    vector<int> pre(n, -1);
    
    // 动态规划计算最长递增子序列的长度
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (A[i] > A[j] && length[i] < length[j] + 1) {
                length[i] = length[j] + 1;
                pre[i] = j;
            }
        }
    }
    
    // 找出 length 数组中的最大值及其对应的索引
    int index = max_element(length.begin(), length.end()) - length.begin();
    
    // 通过 pre 数组重建最长递增子序列
    vector<int> lis;
    while (index != -1) {
        lis.push_back(A[index]);
        index = pre[index];
    }
    
    // 由于是从末尾逆向重建的，所以需要反转结果
    reverse(lis.begin(), lis.end());
    
    return lis;
}

int main() {
    vector<int> A = {8, 9, 2, 5, 3, 7, 18};
    
    vector<int> result = longestIncreasingSubsequence(A);
    
    cout << "The longest increasing subsequence is: ";
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}
