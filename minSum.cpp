//
// Created by anranzhai on 2020/8/2.
//
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Bit{
public:
    Bit(int _n):n(_n),bits(n+1){}

    static int lowbit(int x){
        return x&(-x);
    }

    int query(int x){
        int sum=0;
        while(x){
            sum+=bits[x];
            x-=lowbit(x);
        }
        return sum;
    }

    void update(int x,int val){
        while(x<=n){
            bits[x]+=val;
            x+=lowbit(x);
        }
    }

private:
    vector<int> bits;
    int n;
};

int minSum(vector<int>& nums){
    int n=nums.size();
    if(n==0||n==1)
        return 0;
    vector<int> tmp(nums);
    vector<int> index(n,0);
    sort(tmp.begin(),tmp.end());
    for(int i=0;i<n;i++)
        //要得到的是num在排序数组中的index+1，即在离散化树状数组中第几个（从1开始），这样
        //插入之前可以计算它前面的所有值的和，从而得到它在数组中的在它左边的比他小的数的和
        index[i]=lower_bound(tmp.begin(),tmp.end(),nums[i])-tmp.begin()+1;
    Bit bit(n);
    int sum=0;
    for(int i=0;i<n;i++){
        sum+=bit.query(index[i]-1);
        bit.update(index[i],nums[i]);
    }
    return sum;
}

int main(){
    vector<int> nums{1,3,4,2,5};
    int ret=minSum(nums);
    cout<<ret;
}