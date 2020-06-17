//
// Created by I538989 on 6/17/2020.
//
#include <iostream>
#include <vector>
#include <unordered_map>
using std::vector;
using std::unordered_map;
//动态规划
//时间复杂度空间复杂度均为O(n^2)
int canCompleteCircuitMap(vector<int>& gas, vector<int>& cost) {
    auto size=gas.size();
    vector<unordered_map<int,int>> dp(gas.size(),unordered_map<int,int>());
    for(int i=0;i<gas.size();i++){
        auto ans=0;
        int len=0;
        for(;len<gas.size();len++){
            auto index=(i+len)%size;
            auto pre=ans;
            if(dp[index].count(pre)&&!dp[index][pre])
                break;
            ans+=gas[index]-cost[index];
            if(ans<0){
                dp[index][pre]= false;
                break;
            }
        }
        if(len==size)
            return i;
    }
    return -1;
}

//时间复杂度O(n)
//空间复杂度O(1)
//变量 curr_tank ，记录当前油箱里剩余的总油量。如果在某一个加油站 curr_tank比 0 小，意味着我们无法到达这个加油站。
//下一步我们把这个加油站当做新的起点，并将 curr_tank 重置为 0 ，因为重新出发，油箱中的油为 0 。（从上一次重置的加油站到当前加油站的任意一个加油站出发，到达当前加油站之前， curr_tank 也一定会比 0 小）
//环行过程中邮箱里油的总量：total_tank = sum(gas) - sum(cost) ，如果 total_tank < 0 则返回 -1
//初始化 total_tank 和 curr_tank 为 0 ，并且选择 0 号加油站为起点。
//遍历所有的加油站：
//每一步中，都通过加上 gas[i] 和减去 cost[i] 来更新 total_tank 和 curr_tank 。
//如果在 i + 1 号加油站， curr_tank < 0 ，将 i + 1 号加油站作为新的起点，同时重置 curr_tank = 0 ，让油箱也清空。
//如果 total_tank < 0 ，返回 -1 ，否则返回 starting station。
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    auto size=gas.size();
    auto totalsum=0;
    auto cursum=0;
    auto start=0;
    //验证从start转到0号加油站的可行性->如何确保start能到达start-1号加油站
    //反证法：假设start无法到达k，由题推断k到start的cursum肯定小于0，不然就不是start作为出发点了，而是start
    //前面的点，则start到k的cursum肯定大于零，则start肯定能到达k，与假设矛盾，所以start肯定能到达start-1
    for(int i=0;i<size;i++){
        totalsum+=gas[i]-cost[i];
        cursum+=gas[i]-cost[i];
        //如果i=size-1时cursum<0则totalsum定小于0，所以最后return只需要判断totalsum
        //当前节点之前的cursum只有>0才有必要加到当前节点上
        if(cursum<0){
            auto index=i+1;
            //对于加油站 i ，如果 gas[i] - cost[i] < 0 ，则不可能从这个加油站出发，因为在前往 i + 1 的过程中，汽油就不够了。
            while(index<size&&gas[index]-cost[index]<0){
                index++;
            }
            start=index;
            cursum=0;
        }
    }
    return totalsum>=0?start:-1;
}

int main(){
    vector<int> vec{5,1,2,3,4};
    vector<int> vec2{4,4,1,5,1};
    std::cout<<canCompleteCircuit(vec,vec2);
}