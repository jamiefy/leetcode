//
// Created by anranzhai on 2020/8/2.
//
#include <iostream>
#include <vector>
using namespace std;
//归并排序解决逆序对问题
//时间复杂度：同归并排序O(nlogn)。
//空间复杂度：同归并排序O(n)，因为归并排序需要用到一个临时数组。
int merge(vector<int> &nums,int left,int right){
    if(right-left==0)
        return 0;

    int mid=left+(right-left)/2;
    int cnt=merge(nums,left,mid)+merge(nums,mid+1,right);
    int i=left,j=mid+1,pos=0;
    vector<int> tmp(right-left+1);
    while(i<=mid&&j<=right){
        if(nums[i]<=nums[j]){
            tmp[pos++]=nums[i];
            //找到右边第一个大于或等于nums[i]的数nums[j]，则其前面j-(mid+1)个数均小于nums[i],
            //这些数与nums[i]构成逆序对，同时也与nums[i]之后的所有值构成逆序对，因为
            //nums[i]之后的值均大于nums[i],不能少算入cnt中
            cnt+=j-(mid+1);
            i++;
        }else{
            tmp[pos++]=nums[j];
            //cnt++;错误，不能j往后走一个cnt加一个，因为j往后走一个说明nums[i]之后的值均大于j-1位置的数
            j++;
        }
    }
    while(i<=mid){
        tmp[pos++]=nums[i++];
        cnt+=j-(mid+1);//这一步不能忘了，当j走完，说明nums[i]以及其后面的数大于右边所有的mid+1到right的数
    }
    while(j<=right){
        tmp[pos++]=nums[j++];
    }
    copy(tmp.begin(),tmp.end(),nums.begin()+left);
    return cnt;
}

int reversePairs(vector<int>& nums) {
    if(nums.size()==0)
        return 0;
    return merge(nums,0,nums.size()-1);
}

//离散化树状数组
//时间复杂度：离散化的过程中使用了时间代价为 O(nlogn) 的排序，单次二分的时间代价为 O(logn)，一共有 n 次，总时间代价为 O(n \log n)O(nlogn)；循环执行 nn 次，每次进行 O(\log n)O(logn) 的修改和 O(\log n)O(logn) 的查找，总时间代价为 O(n \log n)O(nlogn)。故渐进时间复杂度为 O(n \log n)O(nlogn)。
//空间复杂度：树状数组需要使用长度为 n 的数组作为辅助空间，故渐进空间复杂度为 O(n)。
class Bit{
public:
    Bit(int _n):n(_n),bits(_n+1){}
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

    void update(int x){
        while(x<=n){
            bits[x]++;
            x+=lowbit(x);
        }
    }
private:
    vector<int> bits;
    int n;
};
int reversePairsTree(vector<int>& nums) {
    int n=nums.size();
    if(n==0||n==1)
        return 0;
    vector<int> tmp(nums);
    sort(tmp.begin(),tmp.end());
    for(auto &num:nums)
        //要得到的是num在排序数组中的index+1，即在离散化树状数组中第几个（从1开始），这样之后插入之前可以计算它前面的所有值得个数和，从而得到它在数组中的逆序对数
        num=lower_bound(tmp.begin(),tmp.end(),num)-tmp.begin()+1;
    Bit bit(n);
    int sum=0;
    //从后往前遍历，动态查询每个数对应的逆序对数
    for(int i=n-1;i>=0;i--){
        //nums[i]是该数在1~n中是第几个，他的逆序对数，就是他排序时前面的数字已经出现的个数
        sum+=bit.query(nums[i]-1);
        //在该排序位置插入该数,更新bits中其他跟该位相关的位
        bit.update(nums[i]);
    }
    return sum;
}

int main(){
    vector<int> nums{7,5,6,4};
    int ret=reversePairs(nums);
    cout<<ret;
}