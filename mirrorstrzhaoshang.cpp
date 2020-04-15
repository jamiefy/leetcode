//
// Created by anranzhai on 2020/4/15.
//
#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;
//《镜像回文字符串》
//1 <==> 1
//2 <==> 5
//3 <==> 8
//4 <==> 7
//6 <==> 9
//【输入】
//2（代表输入个数）
//69
//6996
//【输出】
//YES
//NO
//奇数个时只有中间位为1才是镜像回文字符串
int main(){
    long long n;
    cin>>n;
    vector<string> ret;
    unordered_map<char,char> cmap{{'1','1'},{'2','5'},{'3','8'},{'4','7'},{'6','9'},{'5','2'},
                                  {'8','3'},{'7','4'},{'9','6'}};
    for(long long i=0;i<n;i++){
        string nums;
        cin>>nums;
        long long left=0,right=nums.size()-1;
        while(left<=right){
            if(nums[left]==cmap[nums[right]]){
                left++;
                right--;
            } else{
                ret.emplace_back("NO");
                break;
            }
        }
        if(left>right)
            ret.emplace_back("YES");
    }
    for(auto r:ret)
        cout<<r<<endl;
    return 0;
}
