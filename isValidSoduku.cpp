//
// Created by Administrator on 2019/10/23.
//
#include <iostream>
#include <vector>
#include <map>

bool isValidSudoku(std::vector<std::vector<char>>& board) {
    //使用col/row/rec map分别记录col/row/rec中存在的字符
    std::vector<std::map<char,bool>> col(9);
    std::vector<std::map<char,bool>> rec(3);
    for(int i=0;i<9;i++){
        //每行均将row置零
        std::map<char,bool> row;
        if(i!=0&&i%3==0){
            rec.clear();
            //若只清零，则rec.size()为0，后续下标操作出错
            rec.resize(3);
        }
        for(int j=0;j<9;j++){
            if(board[i][j]!='.'){
                //如果一行中存在该字符则说明不是有效的数独，直接return false否则将该字符记录下来
                if(row.find(board[i][j])->second)
                    return false;
                else
                    row[board[i][j]]=true;
//                TODO:外层没使用引用，程序正常运行
//                for(auto c:col){
//                    char f;//未定义的时候值为 0'\000'
//                    decltype(c) m;//std::map<char,bool>
//                    for(auto d:c){
//                       f=d.first;
//                       decltype(d) c;//std::pair<char const,bool>
//                    }
//                }
                //如果一列中存在该字符则说明不是有效的数独，直接return false否则将该字符记录下来
                if(col[j].find(board[i][j])->second)
                    return false;
                else
                    col[j][board[i][j]]=true;
                //如果一个3*3的矩形中存在该字符则说明不是有效的数独，直接return false否则将该字符记录下来
                //i%3和j/3保证一个3*3的矩阵
                if(rec[j/3].find(board[i][j])->second)
                    return false;
                else
                    rec[j/3][board[i][j]]=true;
            }
        }
    }
    //如果在运行过程中没有return false则说明是有效数独
    return true;
}

int main(){
    std::vector<std::vector<char>> sodu{{'.','.','4','.','.','.','6','3','.'},{'.','.','.','.','.','.','.','.','.'},{'5','.','.','.','.','.','.','9','.'},{'.','.','.','5','6','.','.','.','.'},{'4','.','3','.','.','.','.','.','1'},{'.','.','.','7','.','.','.','.','.'},{'.','.','.','5','.','.','.','.','.'},{'.','.','.','.','.','.','.','.','.'},{'.','.','.','.','.','.','.','.','.'}};
    std::cout<<isValidSudoku(sodu)<<std::endl;
}