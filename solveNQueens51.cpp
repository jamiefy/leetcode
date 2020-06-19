//
// Created by I538989 on 6/19/2020.
//
#include <iostream>
#include <vector>
using namespace std;
//暴力迭代不仅时间超时还没把斜着的冲突处理
vector<vector<string>> solveNQueensbaoli(int n) {
    for(int index=0;index<n;index++){
        vector<vector<int>> dp(n,vector<int>(n,0));
        fill(dp[0].begin(),dp[0].end(),1);
        for(int k=0;k<n;k++){
            dp[k][index]=1;
        }
        int i=1;
        for(;i<n;i++){
            int j=0;
            for(;j<n;j++){
                if(dp[i][j]==0){
                    dp[i][j]=1;
                    fill(dp[i].begin(),dp[i].end(),1);
                    for(int k=0;k<n;k++){
                        dp[k][j]=1;
                    }
                    break;
                }
            }
            if(j==n)break;
        }
        if(i==n){
            vector<vector<string>> str;
            for(int m=0;m<n;m++){
                for(int c=0;c<n;c++){
                    str[m].push_back(dp[m][c]?"Q":".");
                }
            }
            return str;
        }
    }
    return vector<vector<string>>();
}

bool valid(vector<pair<int,int>> &v,int currow,int i){

}

bool solveNQ(int n,vector<pair<int,int>> &v,int currow,vector<vector<string>> &ret){
    for(int i=0;i<n;i++){
        if(v.empty()||valid(v,currow,i)){

        }
    }
}

vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ret;
        vector<pair<int,int>> v;
        solveNQ(n,v,0,ret);
        return ret;
}