//
// Created by anranzhai on 2020/4/13.
//
#include <iostream>
#include <vector>
using namespace std;
//压缩状态动态规划
//参数为行列数
vector<vector<int>> memory(3,vector<int>(1<<5,-1));
vector<int> compressed_seats;

int compress(vector<char> &row){
    int ans=0;
    for(auto c:row){
        ans<<=1;
        if(c=='.')
            ++ans;
    }
    return ans;
}

int getmax(int rowarrange,int row,int colnum){
    if(memory[row][rowarrange]!=-1)
        return memory[row][rowarrange];
    //记录每行所有模式中的最大学生数
    int ans=0;
    //判断每行的所有可能的学生坐法
    for(int scheme=1;scheme<(scheme<<colnum);scheme++){
        //当前学生安排与可坐学生位置冲突或存在左右相邻学生时直接跳过
        if(scheme&~rowarrange || scheme&(scheme<<1))
            continue;
        int curans = 0;
        //如果当前座位坐着学生就在当前入座学生数上加1
        for (int j = 0; j <colnum; ++j)
            if ((1 << j) & scheme)
                ++curans;
        if(row==compressed_seats.size()-1){
            ans=max(ans,curans);
        } else{
            int nextscheme=compressed_seats[row+1];
            nextscheme&=~scheme;
            ans=max(ans,curans+getmax(nextscheme,row+1,colnum));
        }
    }
    //确定该行此可做学生座位rowarrange的情况下（包括该行以及下面各行的安排）可安排的最大学生数
    memory[row][rowarrange]=ans;
    return ans;
}

int maxStudents(vector<vector<char>>& seats) {
    for (auto row: seats)
        compressed_seats.push_back(compress(row));
    return getmax(compressed_seats[0], 0, seats[0].size());
}

int main(){
    vector<char> one{'#','.','#','.','#'};
    vector<char> two{'.','.','.','.','#'};
    vector<char> thr{'.','.','#','.','.'};
    vector<vector<char>> vec{one,two,thr};
    cout<<maxStudents(vec);
}