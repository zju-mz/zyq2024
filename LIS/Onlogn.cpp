#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 使用二分查找来找到第一个大于等于当前元素的位置
int erfen(const vector<int>& tails, int target) {
    int left = 0, right = tails.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (tails[mid] >= target) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    return left;
}

vector<int> longestIncreasingSubsequence(const vector<int>& A) {
    int n = A.size();
    if (n == 0) return {};

    vector<int> tails;   // 保存递增子序列的最小尾部元素
    vector<int> pre(n, -1);  // 保存每个元素的前驱元素索引
    vector<int> indices(n);   // 保存每个元素在 tails 中的索引位置

    for (int i = 0; i < n; ++i) {
        int pos = erfen(tails, A[i]);  // 找到元素 A[i] 应该插入的位置

        // 如果 pos 等于 tails.size()，说明 num 比所有现有元素都大，应添加到 tails 的末尾
        if (pos == tails.size()) {
            tails.push_back(A[i]);
        } else {
            // 否则，更新 tails 中第 pos 位置的元素为当前元素
            tails[pos] = A[i];
        }

        // 保存当前元素的前驱索引
        indices[pos] = i;
        
        // 更新前驱元素索引
        if (pos > 0) {
            pre[i] = indices[pos - 1];
        }
    }

    // 回溯得到最长递增子序列
    vector<int> lis;
    int index = indices[tails.size() - 1];  // 从最后一个元素的索引开始回溯
    while (index != -1) {
        lis.push_back(A[index]);
        index = pre[index];  // 回溯到前一个元素
    }

    reverse(lis.begin(), lis.end());  // 由于回溯是从尾部开始的，需要反转

    return lis;
}

int main() {
    vector<int> A = {20,1,3,2,5,7,4,10,9,11};
    
    vector<int> result = longestIncreasingSubsequence(A);
    
    cout << "The longest increasing subsequence is: ";
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}