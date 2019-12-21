//
// Created by Administator on 2019/12/19.
//
#include <iostream>
#include <vector>

//设定左上角点、右下角点和每个边的方向，设定行列临时值进行判断看是否在正常范围内
//时间复杂度：O(n^2)，运行速度几乎为0
//空间复杂度：O(n^2)
std::vector<std::vector<int>> generateMatrix(int n) {
    if(n==0)
        return std::vector<std::vector<int>>{};
    if(n==1)
        return std::vector<std::vector<int>>{{1}};
    std::vector<std::vector<int>> ret(n,std::vector<int>(n,0));
    std::vector<int> rowDirection{0,1,0,-1};
    std::vector<int> colDirection{1,0,-1,0};
    int rowMin=0,colMin=0,rowMax=n-1,colMax=n-1;
    int row=rowMin,col=colMin,k=0;
    for(int i=1;i<=n*n;i++){
        ret[row][col]=i;
        int rowTmp=row+rowDirection[k];
        int colTmp=col+colDirection[k];
        if(rowTmp>=rowMin && rowTmp<=rowMax && colTmp>=colMin && colTmp<=colMax){
            row=rowTmp;
            col=colTmp;
            if(row==rowMin && col==colMin){
                rowMin++;
                colMin++;
                rowMax--;
                colMax--;
                row=rowMin;
                col=colMin;
            }
        } else{
            k=(k+1)%4;
            row+=rowDirection[k];
            col+=colDirection[k];
        }
    }
    return ret;
}

//分边计算前进方向
//时间复杂度：O(n^2),运行速度4ms
//空间复杂度：O(n^2)
std::vector<std::vector<int>> generateMatrixSide(int n) {
    if(n==0)
        return std::vector<std::vector<int>>{};
    if(n==1)
        return std::vector<std::vector<int>>{{1}};
    std::vector<std::vector<int>> ret(n,std::vector<int>(n,0));
    int rowMin=0,colMin=0,rowMax=n-1,colMax=n-1;
    int row=rowMin,col=colMin;
    for(int i=1;i<=n*n;i++){
        ret[row][col]=i;
        if(row==rowMin && col<colMax)
            col++;
        else if(col==colMax && row<rowMax)
            row++;
        else if(row==rowMax && col>colMin)
            col--;
        else if(col==colMin && row>rowMin)
            row--;
        if(row==rowMin && col==colMin){
            rowMin++;
            colMin++;
            rowMax--;
            colMax--;
            row=rowMin;
            col=colMin;
        }
    }
    return ret;
}

//填完一边缩一边,一层层往内循环
//时间复杂度：O(n^2)，运行速度是generateMatrixSide的两倍
//空间复杂度：O(n^2)
std::vector<std::vector<int>> generateMatrixLayer(int n) {
    if(n==0)
        return std::vector<std::vector<int>>{};
    if(n==1)
        return std::vector<std::vector<int>>{{1}};
    std::vector<std::vector<int>> ret(n,std::vector<int>(n,0));
    int rowMin=0,colMin=0,rowMax=n-1,colMax=n-1;
    for(int i=1;i<=n*n;){
        //固定每条边的横坐标或者纵坐标，填充完一条边之后就把该边往里面缩一层
        for(int index=colMin;index<=colMax;index++)
            ret[rowMin][index]=i++;
        rowMin++;
        for(int index=rowMin; index<=rowMax;index++)
            ret[index][colMax]=i++;
        colMax--;
        for(int index=colMax;index>=colMin;index--)
            ret[rowMax][index]=i++;
        rowMax--;
        for(int index=rowMax;index>=rowMin;index--)
            ret[index][colMin]=i++;
        colMin++;
    }
    return ret;
}

int main(){
    std::vector<std::vector<int>> ret;
    ret=generateMatrixLayer(3);
    for(int i=0;i<ret.size();i++){
        for(int j=0;j<ret[0].size();j++)
            std::cout<<ret[i][j]<<" ";
        std::cout<<std::endl;
    }

}