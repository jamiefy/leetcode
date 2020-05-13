//
// Created by anranzhai on 2020/5/10.
//
#include <iostream>
#include <vector>
using namespace std;
int count(int n){
    return n*(n+1)/2;
}
int candy(vector<int>& ratings) {
    auto n=ratings.size();
    if(n==0)return 0;
    if(n==1)return 1;
    auto prestate=ratings[1]>ratings[0]?1:ratings[1]==ratings[0]?0:-1;
    auto up=prestate==1?1:0;
    auto down=prestate==-1?1:0;
    //当第二个等于第一个的时候up和down都为0,相当于第一个点未被计算在第一座山里，所以sum直接+1把0位置的点计算进去
    int sum=up==0&&down==0?1:0;
    for(auto i=1;i<n-1;i++){
        auto curstate=ratings[i]<ratings[i+1]?1:ratings[i]==ratings[i+1]?0:-1;
        if((prestate<0&&curstate>=0)||prestate>0&&curstate==0){
            sum+=count(up)+count(down)+max(up,down);
            up=0;
            down=0;
        }
        if(curstate==1)
            up++;
        else if(curstate==-1)
            down++;
        else if(curstate==0)
            sum++;
        prestate=curstate;
    }
    sum+=count(up)+count(down)+max(up,down)+1;
    return sum;
}

int candyImp(vector<int>& ratings) {
    auto n=ratings.size();
    if(n==0)return 0;
    if(n==1)return 1;
    //初始值都设为0对下一座山无影响
    auto prestate=0;
    auto up=0;
    auto down=0;
    auto sum=0;
    for(auto i=1;i<=n-1;i++){
        auto curstate=ratings[i]>ratings[i-1]?1:ratings[i]==ratings[i+1]?0:-1;
        if((prestate<0&&curstate>=0)||prestate>0&&curstate==0){
            sum+=count(up)+count(down)+max(up,down);
            up=0;
            down=0;
        }
        if(curstate==1)
            up++;
        else if(curstate==-1)
            down++;
        else if(curstate==0)
            sum++;
        prestate=curstate;
    }
    //因为所有开始节点都算在了后一座山里，所以出循环后要计算最后一个节点的数量即+1
    sum+=count(up)+count(down)+max(up,down)+1;
    return sum;
}

int main(){
    vector<int> ratings{10,10,10,10,10,10};
    cout<<candy(ratings);
}