//
// Created by Administrator on 2019/10/24.
//
#include <iostream>
#include <vector>
#include <map>

std::vector<std::map<char,int>> row(9);
std::vector<std::map<char,int>> col(9);
std::vector<std::map<char,int>> rec(9);
std::vector<std::vector<char>> boardNum;
bool solve=false;

void backTracking(int rowIndex,int colIndex);

bool couldPlace(char c,int rowIndex,int colIndex){
    int index=(rowIndex/3)*3+colIndex/3;
    return row[rowIndex][c]+col[colIndex][c]+rec[index][c]==0;
}

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

void removeNum(char c,int rowIndex,int colIndex){
    int index=(rowIndex/3)*3+colIndex/3;
    row[rowIndex][c]--;
    col[colIndex][c]--;
    rec[index][c]--;
    boardNum[rowIndex][colIndex]='.';
}

void backTracking(int rowIndex,int colIndex){
    if(boardNum[rowIndex][colIndex]=='.'){
        for(int i=0;i<10;i++){
            char num=(char)(i+'0');
            if(couldPlace(num,rowIndex,colIndex)){
                placeNum(num,rowIndex,colIndex);
                placeNextNum(rowIndex,colIndex);
            }
            if(!solve)removeNum(num,rowIndex,colIndex);
        }
    }
    else
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