//
// Created by anranzhai on 2020/6/20.
//
#include <iostream>
#include <vector>
using namespace std;
//位运算 df
//cnt一定要用&,不然改变的只是产生的临时对象，对cnt本身无影响（一般将cnt设为全局变量）
void dfs(int n,int row,int col,int ld,int rd,int& cnt,vector<int> &pick){
    if(row==n){
        cnt++;
        return;
    }
    //test
    //必须加& ((1<<n)-1)，因为int: 4byte =  32 bit 有符号signed范围：
    //2^31-1 ~ -2^31即：2147483647 ~ -2147483648,当为最小负数时无法取反
    //Line 10: Char 29: runtime error: negation of -2147483648 cannot be represented in type 'int'; cast to an unsigned type to negate this value to itself
    int pos= ~(col|ld|rd) & ((1<<n)-1);
    while(pos!=0){
        pick[row]= pos&(-pos);
        dfs(n,row+1,col|pick[row],(ld|pick[row])<<1,(rd|pick[row])>>1,cnt,pick);
        pos&=(pos-1);
    }
}
int totalNQueens(int n) {
    int cnt=0;
    vector<int> pick(n,0);
    dfs(n,0,0,0,0,cnt,pick);
    return cnt;
}

int main(){
    cout<<totalNQueens(4);
}