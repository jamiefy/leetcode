//
// Created by anranzhai on 2020/6/3.
//
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <functional>
#include <map>
using namespace std;
bool dfs(vector<int>& nums,vector<int>& sum,int index,int side){
    if(index==nums.size())
        return sum[0]==sum[1]&&sum[1]&&sum[2]&&sum[2]==sum[3];

    for(int i=0;i<4;i++){
        if(sum[i]+nums[index]<=side){
            sum[i]+=nums[index];
            if(dfs(nums,sum,index+1,side)){
                return true;
            }
            sum[i]-=nums[index];
        }
    }
    return false;
}

bool makesquaredfs(vector<int>& nums) {
    if(nums.size()==0)
        return false;
    if(accumulate(nums.begin(),nums.end(),0)%4!=0)
        return false;

    vector<int> sum(4,0);
    auto side=accumulate(nums.begin(),nums.end(),0)/4;
    //排序进行剪枝，存在大于1/4总长的火柴直接返回false，或者边长相加大于1/4总长的直接剪枝，不然leetcode会超时
    sort(nums.begin(),nums.end(),greater<int>());
    return dfs(nums,sum,0,side);
}

//回溯+动态规划+位运算状态压缩
map<pair<int,int>,bool> nmap;
bool recurse(vector<int>& nums,int mask,int sidedone,int side){
    auto hasused=0;
    for(int i=nums.size()-1;i>=0;i--){
        if((mask&(1<<i))==0)
            hasused+=nums[nums.size()-1-i];
    }
    //填满一条边的时候sidedone对应+1
    if(hasused>0&&hasused%side==0)
        sidedone++;
    if(sidedone==3)
        return true;

    //若mask时已经有sidedone条边填满 存在于nmap则直接调用记录
    auto maskpair=pair<int,int>(mask,sidedone);
    if(nmap.count(maskpair))
        return nmap[maskpair];

    auto ans=false;
    auto cursidedone=hasused/side;
    //离填满一条边还差rem
    auto rem=(cursidedone+1)*side-hasused;
    for(int i=nums.size()-1;i>=0;i--){
        //该边长度小于应填充长度，且该边可用
        if(nums[nums.size()-1-i]<=rem && (mask&(1<<i))>0){
            //如果返回true说明该mask方式填写能填满四条边，如果返回false说明该mask方式填写不成功则回溯
            if(recurse(nums,mask^(1<<i),sidedone,side)){
                ans=true;
                break;
            }
        }
    }
    nmap[maskpair]=ans;
    return ans;
}

bool makesquare(vector<int>& nums) {
    if(nums.size()==0||nums.size()<4)
        return false;
    if(accumulate(nums.begin(),nums.end(),0)%4!=0)
        return false;

    auto side=accumulate(nums.begin(),nums.end(),0)/4;
    //初始mask=(1<<nums.size())-1,表示所有节点均可用
    return recurse(nums,(1<<nums.size())-1,0,side);
}

int main(){
    vector<int> vec{1,1,2,2,2};
    cout<<makesquare(vec);
}