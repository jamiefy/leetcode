//
// Created by anranzhai on 2020/3/8.
//
#include <iostream>
#include <vector>
#include <algorithm>
void coinChange(std::vector<int>& coins, int amount, int c_index, int count, int& ans)
{
    if (amount == 0)
    {
        ans = std::min(ans, count);
        return;
    }
    if (c_index == coins.size()) return;
    for (int k = amount / coins[c_index]; k >= 0 && k + count < ans; k--)
    {
        coinChange(coins, amount - k * coins[c_index], c_index + 1, count + k, ans);
    }
}
//dfs+剪枝+贪心算法，执行速度贼快，消耗空间减少
int coinChange(std::vector<int>& coins, int amount)
{
    if (amount == 0) return 0;
    sort(coins.rbegin(), coins.rend());
    int ans = INT_MAX;
    coinChange(coins, amount, 0, 0, ans);
    return ans == INT_MAX ? -1 : ans;
}

int main(){
    std::vector<int> vec{10,1,7};
    std::cout<<coinChange(vec,14);
}