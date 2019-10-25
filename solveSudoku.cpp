//
// Created by Administrator on 2019/10/24.
//
#include <iostream>
#include <vector>
#include <map>
//固定大小可采用数组,更简便一些
//全局变量可直接初始化,但是在类里函数外的变量不能直接初始化,声明和定义要分开,除非是及其简单的函数eg:int/bool等
std::vector<std::map<char,int>> row(9);
std::vector<std::map<char,int>> col(9);
std::vector<std::map<char,int>> rec(9);
std::vector<std::vector<char>> boardNum;
bool solve=false;
//函数互相调用要提前声明在后面的函数,但是如果是在类里面则不需要声明
void backTracking(int rowIndex,int colIndex);
//判断行列以及子方块内是否存在相同的数字,若存在则不能放置,不存在则能
bool couldPlace(char c,int rowIndex,int colIndex){
    int index=(rowIndex/3)*3+colIndex/3;
    return row[rowIndex][c]+col[colIndex][c]+rec[index][c]==0;
}
//在数独上放置数字,把相应行列和子方块的map对应数字关键字的个数置为1
void placeNum(char c,int rowIndex,int colIndex){
    int index=(rowIndex/3)*3+colIndex/3;
    row[rowIndex][c]++;
    col[colIndex][c]++;
    rec[index][c]++;
    boardNum[rowIndex][colIndex]=c;
}

void placeNextNum(int rowIndex,int colIndex){
    if(rowIndex==8&&colIndex==8)
        solve=true;
    else{
        if(colIndex==8)
            backTracking(rowIndex+1,0);
        else
            backTracking(rowIndex,colIndex+1);
    }
}
//在数独上移除数字,把相应行列和子方块的map对应数字关键字的个数置为0
void removeNum(char c,int rowIndex,int colIndex){
    int index=(rowIndex/3)*3+colIndex/3;
    row[rowIndex][c]--;
    col[colIndex][c]--;
    rec[index][c]--;
    boardNum[rowIndex][colIndex]='.';
}
//回溯,每个需要填写数字的位置均从1到9进行判断是否合适填入该位置,若合适则放进去直到成功填完(8,8)或者填到某位置无数可填
void backTracking(int rowIndex,int colIndex){
    if(boardNum[rowIndex][colIndex]=='.'){
        for(int i=1;i<10;i++){
            char num=(char)(i+'0');
            if(couldPlace(num,rowIndex,colIndex)){
                placeNum(num,rowIndex,colIndex);
                placeNextNum(rowIndex,colIndex);
                if(!solve)removeNum(num,rowIndex,colIndex);
            }
        }
        //从0到9没有合适填入的则停止函数调用返回上一层placeNextNum结束,继续运行上一层的if(!solve),由于没有
        //成功填完则solve依然为false,进入if处理,移除上一层填进去的数,继续上一层的循环,换一个数填进去或结束循环
    }
    else
        //如果该位置已经有数,则继续下一个位置
        placeNextNum(rowIndex,colIndex);
}



void solveSudoku(std::vector<std::vector<char>>& board) {
    boardNum=board;
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++){
            if(board[i][j]!='.'){
                int index=(i/3)*3+j/3;
                row[i][board[i][j]]++;
                col[j][board[i][j]]++;
                rec[index][board[i][j]]++;
            }
        }
    }
    backTracking(0,0);
}

int main(){
    std::vector<std::vector<char>> sodu{{'5','3','.','.','7','.','.','.','.'},{'6','.','.','1','9','5','.','.','.'},{'.','9','8','.','.','.','.','6','.'},{'8','.','.','.','6','.','.','.','3'},{'4','.','.','8','.','3','.','.','1'},{'7','.','.','.','2','.','.','.','6'},{'.','6','.','.','.','.','2','8','.'},{'.','.','.','4','1','9','.','.','5'},{'.','.','.','.','8','.','.','7','9'}};
    solveSudoku(sodu);
    for(int i=0;i<9;i++) {
        for (int j = 0; j < 9; j++) {
            std::cout<<boardNum[i][j]<<' ';
        }
        std::cout<<std::endl;
    }
}