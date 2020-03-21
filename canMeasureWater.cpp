//
// Created by anranzhai on 2020/3/21.
//
#include <iostream>
#include <algorithm>
#include <stack>
#include <unordered_set>
//找到一对整数 a, b使ax+by=z而只要满足z≤x+y，且这样的 a, b存在，那么我们的目标就是可以达成的。
//ax+by=z 有解当且仅当 z 是 x,y 的最大公约数的倍数。因此我们只需要找到 x,y 的最大公约数并判断 z 是否是它的倍数即可。——裴蜀定理
//时间复杂度：O(log(min(x,y)))，取决于计算最大公约数所使用的辗转相除法。
//空间复杂度：O(1)O(1)，只需要常数个变量。
//0 ms	7.4 MB
bool canMeasureWaterMath(int x, int y, int z) {
    if(z==0)return true;
    if(x+y<z)return false;
    if(x==0||y==0)return x+y==z;
    return z%std::__gcd(x,y)==0;
}

//递归+哈希
//时间复杂度：O(xy)，状态数最多有 (x+1)(y+1) 种，对每一种状态进行深度优先搜索的时间复杂度为O(1)，因此总时间复杂度为O(xy)。
//空间复杂度：O(xy)，由于状态数最多有 (x+1)(y+1) 种，哈希集合中最多会有 (x+1)(y+1) 项，因此空间复杂度为 O(xy)。
//1460 ms	307.8 MB
using PII = std::pair<int, int>;
bool canMeasureWater(int x, int y, int z) {
    std::stack <PII> stk;
    stk.emplace(0,0);
    //哈希函数，定址
    auto hash_function = [](const PII& o) {return std::hash<int>()(o.first) ^ std::hash<int>()(o.second);};
    //构造一个空的unordered_map对象，该对象不包含元素，大小为0
    std::unordered_set<PII, decltype(hash_function)> seen(0, hash_function);
    while(!stk.empty()){
        if(seen.count(stk.top())){
            stk.pop();
            continue;
        }
        auto [remain_x,remain_y]=stk.top();
        seen.emplace(remain_x,remain_y);
        stk.pop();
        //满足以下任一点，则证明能恰好得到z升水
        if (remain_x == z || remain_y == z || remain_x + remain_y == z) {
            return true;
        }
        // 把 X 壶灌满。
        stk.emplace(x, remain_y);
        // 把 Y 壶灌满。
        stk.emplace(remain_x, y);
        // 把 X 壶倒空。
        stk.emplace(0, remain_y);
        // 把 Y 壶倒空。
        stk.emplace(remain_x, 0);
        // 把 X 壶的水灌进 Y 壶，直至灌满或倒空。
        stk.emplace(remain_x -__min(remain_x, y - remain_y), remain_y + __min(remain_x, y - remain_y));
        // 把 Y 壶的水灌进 X 壶，直至灌满或倒空。
        stk.emplace(remain_x+__min(remain_y,x-remain_x),remain_y-__min(remain_y,x-remain_x));
    }
    return false;
}

