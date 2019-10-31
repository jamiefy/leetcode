//
// Created by Administrator on 2019/10/31.
//
#include <iostream>
#include <vector>
#include <map>

//利用矩阵记录每个位置的状态，并存储必要位置的数值
//时间复杂度：O(N^2),空间复杂度：O(n^2)
void rotate(std::vector<std::vector<int>>& matrix) {
    int row=matrix.size();
    //定义数组记录位置（i,j）目前的状态，未操作是-1，取出来是0，已经放进该放的位置是1
    std::vector<std::vector<int>> takeOutOrPutIn(row,std::vector<int>(row,-1));
    //定义map存储位置（i,j）对应数值
    std::map<std::vector<int>,int> tmp;
    for(int i=0;i<row;i++){
        for(int j=0;j<row;j++){
            //当(i,j)->(j,row-1-i)时判断(j,row-1-i)位置的值是否已经取出或者已经放进去该放的位置，如果没
            //进行任何操作则需要先把该位置的数取出来然后再把要放的数放进去，然后takeOutOrPutIn[j][row-1-i]=0
            if(takeOutOrPutIn[j][row-1-i]==-1){
                tmp[std::vector<int>{j,row-1-i}]=matrix[j][row-1-i];
                takeOutOrPutIn[j][row-1-i]=0;
                //当(i,j)->(j,row-1-i)时判断(i,j)位置的值是否进行操作，如果没有则可以直接从该位置取值，
                //如果已经取出来则从tmp中取值，并给takeOutOrPutIn[i][j]赋值1
                matrix[j][row-1-i]=takeOutOrPutIn[i][j]==-1?matrix[i][j]:tmp[std::vector<int>{i,j}];
                takeOutOrPutIn[i][j]=1;
            }//如果已经取出来或者已经放进去该放的位置，那可以直接给(j,row-1-i)位置赋值
            else if(takeOutOrPutIn[j][row-1-i]==0||takeOutOrPutIn[j][row-1-i]==1){
                matrix[j][row-1-i]=takeOutOrPutIn[i][j]==-1?matrix[i][j]:tmp[std::vector<int>{i,j}];
                takeOutOrPutIn[i][j]=1;
            }
        }
    }
}

//最直接的想法是先转置矩阵，然后翻转每一行。这个简单的方法已经能达到最优的时间复杂度O(N^2)。
//时间复杂度：O(N^2),空间复杂度：O(1)由于旋转操作是就地完成的。空间消耗小于rotate
void rotateTransposeExert(std::vector<std::vector<int>>& matrix) {
    int size=matrix.size();
    for(int i=0;i<size-1;i++){//注意是size-1而不是size——细节
        //j=0的时候相当于翻转了两遍，数组没变，j=i的时候相当于利用矩阵右上角翻转一遍
        for(int j=i+1;j<size;j++){//注意是i+1而不是i——细节
//            int tmp=matrix[i][j];
//            matrix[i][j]=matrix[j][i];
//            matrix[j][i]=tmp;
            std::swap(matrix[i][j],matrix[j][i]);
        }
    }
    for(int i=0;i<size;i++){
        //相当于把每行对折
        for(int j=0;j<size/2;j++){
//            int tmp=matrix[i][j];
//            matrix[i][j]=matrix[i][size-1-j];
//            matrix[i][size-1-j]=tmp;
        std::swap(matrix[i][j],matrix[i][size-1-j]);
        }
    }
}


//将原始问题划分为每次旋转四个元素的子问题
//时间复杂度：O(N^2)是两重循环的复杂度。空间复杂度：O(1)由于我们在一次循环中的操作是就地完成的，
//并且我们只用了长度为 4 的临时列表做辅助。空间消耗小于rotate
void rotateElement(std::vector<std::vector<int>>& matrix) {
    int size=matrix.size();
    for(int i=0;i<size/2+size%2;i++){
        for(int j=0;j<size/2;j++){
            std::vector<int> vec;
            int row=i;
            int col=j;
            //把四个元素存储到vec里
            for(int k=0;k<4;k++){
                vec.emplace_back(matrix[row][col]);
                int tmp=row;
                row=col;
                col=size-1-tmp;
            }
            //把存储到vec的四个元素放到该放的位置
            for(int k=0;k<4;k++){
                matrix[row][col]=vec[(k+3)%4];
                int tmp=row;
                row=col;
                col=size-1-tmp;
            }
        }
    }
}

//单次循环中旋转矩阵。该想法和方法 2 相同，但是所有的操作可以在单次循环内完成并且这是更精简的方法
//时间复杂度：O(N^2),空间复杂度：O(1)由于旋转操作是就地完成的。时间消耗大于rotate，空间消耗小于rotate
void rotateElementImp(std::vector<std::vector<int>>& matrix) {
    int n=matrix.size();
    for(int i=0;i<(n+1)/2;i++) {
        for (int j = 0; j < n / 2; j++) {
            int tmp=matrix[i][j];
            matrix[i][j]=matrix[n-1-j][i];
            matrix[n-1-j][i]=matrix[n-1-i][n-1-j];
            matrix[n-1-i][n-1-j]=matrix[j][n-1-i];
            matrix[j][n-1-i]=tmp;
        }
    }
}

int main(){
    std::vector<std::vector<int>> ret={{1,2,3},{4,5,6},{7,8,9}};
    rotateTransposeExert(ret);
    for(int i=0;i<ret.size();i++){
        for(int j=0;j<ret[0].size();j++){
            std::cout<<ret[i][j]<<' ';
        }
        std::cout<<std::endl;
    }
}