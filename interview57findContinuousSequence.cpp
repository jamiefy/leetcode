//
// Created by anranzhai on 2020/3/6.
//
#include <iostream>
#include <vector>
#include <math.h>
//枚举+数学优化
//时间复杂度：由于枚举以后只需要 O(1) 的时间判断，所以时间复杂度为枚举起点的复杂度O(\textit{target})O(target) 。
//空间复杂度：O(1) ，除了答案数组只需要常数的空间存放若干变量。
std::vector<std::vector<int>> findContinuousSequence(int target) {
    std::vector<std::vector<int>> vec;
    std::vector<int> res;
    int sum = 0, limit = (target - 1) / 2; // (target - 1) / 2 等效于 target / 2 下取整
    for (int x = 1; x <= limit; ++x) {
        long long delta = 1 - 4 * (x - 1ll * x * x - 2 * target);
        if (delta < 0) continue;
        int delta_sqrt = (int)sqrt(delta + 0.5);//?为什么加0.5
        if (1ll * delta_sqrt * delta_sqrt == delta && (delta_sqrt - 1) % 2 == 0){
            int y = (-1 + delta_sqrt) / 2; // 另一个解(-1-delta_sqrt)/2必然小于0，不用考虑
            if (x < y) {
                res.clear();
                for (int i = x; i <= y; ++i) res.emplace_back(i);
                vec.emplace_back(res);
            }
        }
    }
    return vec;
}

//双指针法
//时间复杂度：由于两个指针移动均单调不减，且最多移动floor⌊2target⌋ 次，即方法一提到的枚举的上界，所以时间复杂度为 O(\textit{target})O(target) 。
//空间复杂度：O(1) ，除了答案数组只需要常数的空间存放若干变量。
std::vector<std::vector<int>> findContinuousSequenceDoublePionter(int target) {
    std::vector<std::vector<int>> vec;
    std::vector<int> res;
    for (int l = 1, r = 2; l < r;){
        int sum = (l + r) * (r - l + 1) / 2;
        if (sum == target){
            res.clear();
            for (int i = l; i <= r; ++i) res.emplace_back(i);
            vec.emplace_back(res);
            l++;
        }
        else if (sum < target) r++;
        else l++;
    }
    return vec;
}

int main(){
    findContinuousSequence(9);
}

