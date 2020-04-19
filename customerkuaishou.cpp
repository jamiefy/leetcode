//
// Created by anranzhai on 2020/4/13.
//
//顾客排队，每一个人有两个属性a和b，每个人的满意度是a*（自己前面的人数）+ b*(后面的人数)
//解法：计算每个人的a-b的值，对差进行排序，差大的排在前面
#include<iostream>
#include<string>
#include <stack>
#include <vector>
#include <map>
using namespace std;

class Solution {
public:
    /**
     * 根据顾客属性计算出顾客排队顺序求出最小和a[i]*(pos-1)+b[i]*(n-pos)=(a[i]-b[i])*pos+n*b[i]-a[i]
     * @param a int整型vector 顾客a属性
     * @param b int整型vector 顾客b属性
     * @return int整型vector
     */
    vector<int> WaitInLine(vector<int>& a, vector<int>& b) {
        // 自动排序,tmp按降序序排序
        multimap<int,int,greater<>> diff;
        for(int i=0;i<a.size();i++){
            int temp = a[i]-b[i];
            diff.insert(pair<int,int>(temp,i));
        }
        vector<int> result;
        for(auto i:diff)
            result.push_back(i.second + 1);
        return result;
    }
};

int main(){
    Solution solution;
    vector<int> a{8,9,7};
    vector<int> b{5,8,3};
    vector<int> result;
    result = solution.WaitInLine(a,b);
    for(auto i:result)
        cout<<i<<' ';
}

