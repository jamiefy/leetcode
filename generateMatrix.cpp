//
// Created by Administator on 2019/12/19.
//
#include <iostream>
#include <vector>

//设定左上角点、右下角点和每个边的方向
//时间复杂度：O(n^2)
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

int main(){
    std::vector<std::vector<int>> ret;
    ret=generateMatrix(2);
    for(int i=0;i<ret.size();i++){
        for(int j=0;j<ret[0].size();j++)
            std::cout<<ret[i][j]<<" ";
        std::cout<<std::endl;
    }

}