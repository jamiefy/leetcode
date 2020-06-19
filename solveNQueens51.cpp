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
    for(auto c:v){
        if(i==c.second||abs(currow-c.first)==abs(i-c.second))
            return false;
    }
    return true;
}

void solveNQ(int n,vector<pair<int,int>> &v,int currow,vector<vector<string>> &ret){
    if(currow==n){
        vector<string> r(n,string(n,'.'));
        for(auto c:v){
            r[c.first][c.second]='Q';
        }
        ret.push_back(r);
        return;
    }

    for(int i=0;i<n;i++){
        if(v.empty()||valid(v,currow,i)){
            v.emplace_back(currow,i);
            solveNQ(n,v,currow+1,ret);
            v.pop_back();
            }
        }
}

vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ret;
        vector<pair<int,int>> v;
        solveNQ(n,v,0,ret);
        return ret;
}


//使用整型中各个位来表示状态，比如一行 8 个格子，我们使用 8 位来表示是否放置棋子
//如： 0000 1111 表示后 4 位都有棋子
//位运算：
// x | y 按位或，对每一位来说，x 和 y 中只要有一边有 1 就是 1
//如： 1100 0000 | 0000 0011 --> 1100 0011
//
//x & y 按位与，对每一位来说，x 和 y 中必须都是 1 才是 1
//如： 1100 1111 & 0011 1111 --> 0000 1111
//
//~x 按位取反，对每一位来说，0 变 1， 1 变 0
//如： 1111 0000 --> 0000 1111
//
//x << n 左移，用来将一个数的各二进制位全部左移 n 位，右补 0
//如： 1111 0000 << 2 --> 1100 0000
//
//x >> n 右移，用来将一个数的各二进制位全部右移 n 位，无符号数左补 0
//如： 1111 0000 >> 2 --> 0011 1100
//
//高级位运算
// x & -x 可以将最后一位的 1 保留，其它位全部为 0
//如： 0000 1100 --> 0000 0100
//
//x & (x - 1) 可以将最后一位 1 变成 0
//如： 0000 1100 --> 0000 1000
//
//以此特点，我们可以将所有可能的棋子表示为 1111 1111，然后使用 x & -x ，选择最右边的一个
//如： 1111 1111 --> 0000 0001
//
//进行计算之后，在回溯的时候，对所有可能的棋子状态使用 x & (x - 1)，这样就排除了本次选择的那一个
//如： 1111 1111 --> 1111 1110
//
//如此循环即可将所有可能的棋子都选择进入尝试
//接下来在 dfs 的时候，由于已选的棋子会产生不可使用的格子，要把这个状态传进去
//使用 col 表示这一竖行
//使用 ld 和 rd 表示左斜和右斜，注意这个标志只表示下一行中被斜线穿过的格子
//在图形上是向左 / 右下一格，因为按行回溯，传递到下一层的是下一行的状态
//那么对于当前行选中的格子，下一行就是其向左 / 右移动的那一格
//即：(ld | pick[row]) << 1 和 (rd | pick[row]) >> 1
//最后，就是在命中的时候，把 pick 中保存的状态转换出来存成字符串
void dfs(int n, int row, int col, int ld, int rd, vector<int>& pick, vector<vector<string>>& ans)
{
    if (row == n)
    {
        vector<string> str(n, string(n, '.'));
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (pick[i] & (1 << j))
                {
                    str[i][j] = 'Q';
                    break;
                }
            }
        }
        ans.push_back(str);
        return;
    }

    //col|ld| rd中为1的位表示上面层导致不可使用的位，取反得到还可以使用的位
    int pos = ~(col | ld | rd) & ((1 << n) - 1);
    while (pos != 0)
    {
        //得到可用位中最右边的那个位,pick[i]保存当前行使用的位的状态码
        pick[row] = (pos & -pos);
        //上次迭代过来竖着不可使用的位col或上当前占用的位可得到下层不可使用的列
        //ld上次迭代过来向左斜不可使用的位或上当前占用的位  左移一位得到下层由上层所有层左斜导致不可使用的位;同理rd
        dfs(n, row + 1, (col | pick[row]), ((ld | pick[row]) << 1), ((rd | pick[row]) >> 1), pick, ans);
        //将可用位中最右边的位置0
        pos &= (pos - 1);
    }
}

//dfs+状态压缩（位运算）
vector<vector<string>> solveNQueensBit(int n)
{
    vector<vector<string>> ans;
    vector<int> pick(n, 0);
    dfs(n, 0, 0, 0, 0, pick, ans);
    return ans;
}

int main(){
    auto v=solveNQueens(4);
    cout<<1;
}