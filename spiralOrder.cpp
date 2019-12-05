//
// Created by Administator on 2019/11/29.
//
#include <iostream>
#include <vector>

//模拟：绘制螺旋轨迹路径，我们发现当路径超出界限或者进入之前访问过的单元格时，会顺时针旋转方向。
//时间复杂度： O(N)O(N)，其中 N 是输入矩阵所有元素的个数。因为我们将矩阵中的每个元素都添加进答案里。
//空间复杂度： O(N)O(N)，需要两个矩阵 seen 和 ans 存储所需信息。
std::vector<int> spiralOrder(std::vector<std::vector<int>>& matrix) {
    if(matrix.size()==0)
        return std::vector<int>{};
    //四条边对应的方向
    std::vector<int> rowSign{0,1,0,-1};
    std::vector<int> colSign{1,0,-1,0};
    int rowLimit=matrix.size();
    int colLimit=matrix[0].size();
    std::vector<int> ret;
    //记录节点是否被访问过，防止重复访问正常范围内的同一个节点
    std::vector<std::vector<bool>> visited(rowLimit,std::vector<bool>(colLimit, false));
    for(int row=0,col=0,side=0;ret.size()<rowLimit*colLimit;) {
        //把当前节点值压入数组，并设置该节点已经访问过
        ret.push_back(matrix[row][col]);
        visited[row][col]=true;
        //获取按原方向走的候选移动位置
        int rowTmp=row+rowSign[side];
        int colTmp=col+colSign[side];
        //判断该节点是否越界或者已经访问过
        if(0<=rowTmp&&rowTmp<rowLimit&&0<=colTmp&&colTmp<colLimit&&!visited[rowTmp][colTmp]) {
            //原方向在正常范围内，则直接采用候选移动位置
            row=rowTmp;
            col=colTmp;
        } else{
            //原方向越界或者已经访问过则转换方向后得出正确的节点位置
            side=(side+1)%4;
            row+=rowSign[side];
            col+=colSign[side];
        }
    }
    return ret;
}

//按层模拟：答案是最外层所有元素按照顺时针顺序输出，其次是次外层，以此类推。
//时间复杂度： O(N)O(N)，其中 N 是输入矩阵所有元素的个数。因为我们将矩阵中的每个元素都添加进答案里。
//空间复杂度： O(N)O(N)，需要矩阵 ans 存储信息。
std::vector<int> spiralOrderLayer(std::vector<std::vector<int>>& matrix) {
    if(matrix.size()==0)
        return std::vector<int>{};
    //左上角位置(0,0),右下角位置(matrix.size()-1,matrix[0].size()-1)
    int rowLow=0,rowHigh=matrix.size()-1,colLow=0,colHigh=matrix[0].size()-1;
    std::vector<int> ret;
    while(rowLow<=rowHigh&&colLow<=colHigh){
        for(int col=colLow;col<=colHigh;col++)ret.emplace_back(matrix[rowLow][col]);
        for(int row=rowLow+1;row<=rowHigh;row++)ret.emplace_back(matrix[row][colHigh]);
        for(int col=colHigh-1;col>colLow;col--)ret.emplace_back(matrix[rowHigh][col]);
        for(int row=rowHigh;row>rowLow;row--)ret.emplace_back(matrix[row][colLow]);
        rowLow++;
        colLow++;
        rowHigh--;
        colHigh--;
    }
    return ret;
}

int main(){
    std::vector<std::vector<int>> vec={{3},{2}};
    std::vector<int> ret=spiralOrderLayer(vec);
    int k=0;
    while(k<ret.size()){
        std::cout<<ret[k++]<<" ";
    }
}