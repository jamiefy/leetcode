//
// Created by Administrator on 2019/10/23.
//
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

bool isValidSudoku(std::vector<std::vector<char>>& board) {
    //使用col/row/rec map分别记录col/row/rec中存在的字符
    std::vector<std::map<char,bool>> col(9);
    std::vector<std::map<char,bool>> rec(3);
    for(int i=0;i<9;i++){
        //每行均初始化row
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


//map内部实现了红黑树,自动排序,对于存在有序要求的问题,运行效率更高,但空间占用率高,
//因为每一个节点都需要额外保存父节点，孩子节点以及红/黑性质，使得每一个节点都占用大量的空间;
//unordered_map内部实现了哈希表,无序,查找速度快,但是哈希表的建立比较费时间
//对于unordered_map或者unordered_set容器，其遍历顺序与创建该容器时输入元素的顺序是不一定一致的,
//遍历是按照哈希表从前往后依次遍历的,该题还可以使用hashset即unordered_set,步骤一样.
bool isValidSudokuIndex(std::vector<std::vector<char>>& board) {
    std::vector<std::unordered_map<int,int>> row(9), col(9), block(9);
    for(int i = 0; i < 9; ++ i){
        for(int j = 0; j < 9; ++ j){
            //实现每个3*3矩阵对应一个block的map,运算技巧
            int bindex =  (i / 3)* 3 + j / 3;
            char cur = board[i][j];
            if(cur == '.')  continue;
            //任意map中存在则不是有序的数独.使用count，返回的是被查找元素的个数。
            //如果有，返回1；否则，返回0。注意，map中不存在相同元素，所以返回值只能是1或0。
            if(row[i].count(cur) || col[j].count(cur) || block[bindex].count(cur))  return false;
            row[i][cur] = 1;
            col[j][cur] = 1;
            block[bindex][cur] = 1;
        }
    }
    return true;
}


int main(){
    std::vector<std::vector<char>> sodu{{'.','.','4','.','.','.','6','3','.'},{'.','.','.','.','.','.','.','.','.'},{'5','.','.','.','.','.','.','9','.'},{'.','.','.','5','6','.','.','.','.'},{'4','.','3','.','.','.','.','.','1'},{'.','.','.','7','.','.','.','.','.'},{'.','.','.','5','.','.','.','.','.'},{'.','.','.','.','.','.','.','.','.'},{'.','.','.','.','.','.','.','.','.'}};
    std::cout<<isValidSudoku(sodu)<<std::endl;
}