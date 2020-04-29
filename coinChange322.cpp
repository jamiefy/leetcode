//
// Created by anranzhai on 2020/3/8.
//
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void coinChange(std::vector<int>& coins, int amount, int c_index, int count, int& ans)
{
    if (amount == 0)
    {
        ans = std::min(ans, count);
        return;
    }
    if (c_index == coins.size()) return;
    // k + count < ans剪枝必不可少，当当前数量大于现有最小数量的时候停止继续向下进行无意义的运算
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

//递归，正确但超时
int minc=INT32_MAX;
void coinChanget(vector<int>& coins, int amount,int index,int precnt){
    if(amount<=0){
        minc=amount==0?std::min(precnt,minc):minc;
        return;
    }
    if(index==coins.size()){
        return;
    }
    //实现剪枝就不会超时了只需使判断条件为cnt>=0&&cnt+precnt<=min
    for(int cnt=amount/coins[index];cnt>=0;cnt--){
        coinChanget(coins,amount-coins[index]*cnt,index+1,precnt+cnt);
    }
}
int coinChanget(vector<int>& coins, int amount) {
    if(coins.size()==0)
        return -1;
    sort(coins.begin(),coins.end(),greater<int>());
    int coin=coins[0];
    for(int cnt=amount/coin;cnt>=0;cnt--){
        coinChanget(coins,amount-coin*cnt,1,cnt);
    }
    return minc==INT32_MAX?-1:minc;
}

//回溯，不正确，当14=10 1 1 1 1就直接停止运算了但是最优解是14=7 7
int mincnt=INT32_MAX;
bool coinChangetest(vector<int>& coins, int amount,int index,int precnt){
    if(amount==0){
        mincnt=std::min(precnt,mincnt);
        return true;
    }
    if(amount<0)
        return false;
    if(index==coins.size()){
        return true;
    }
    for(int cnt=amount/coins[index];cnt>=0;cnt--){
        if(coinChangetest(coins,amount-coins[index]*cnt,index+1,precnt+cnt))
            return true;
    }
    return false;
}
int coinChangetest(vector<int>& coins, int amount) {
    if(coins.size()==0)
        return -1;
    sort(coins.begin(),coins.end(),greater<int>());
    int coin=coins[0];
    for(int cnt=amount/coin;cnt>=0;cnt--){
        if(coinChangetest(coins,amount-coin*cnt,1,cnt))
            break;
    }
    return mincnt==INT32_MAX?-1:mincnt;
}


int main(){
    std::vector<int> vec{10,3,7};
    std::cout<<coinChange(vec,39);
}