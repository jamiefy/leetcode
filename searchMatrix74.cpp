//
// Created by anranzhai on 2020/2/29.
//
#include <iostream>
#include <vector>
#include <algorithm>
bool searchMatrix(std::vector<std::vector<int>>& matrix, int target) {
    if(matrix.size()==0|| matrix[0].size()==0)
        return false;
    int max_row=matrix.size(),max_col=matrix[0].size();
    int left=0,right=max_row*max_col-1;
    while(left<right){
        int middle=left+(right-left)/2;
        //虚数组的序号可以方便的转化为原矩阵的行和列
        int pivot=matrix[middle/max_col][middle%max_col];
        if(pivot==target){
            return true;
        } else if(pivot>target){
            right=middle-1;
        } else if(pivot<target){
            left=middle+1;
        }
    }
    return matrix[left/max_col][left%max_col]==target;
}

bool searchMatrixGeneric(std::vector<std::vector<int>>& matrix, int target) {
    if(matrix.size()==0|| matrix[0].size()==0)
        return false;
    for(int i=0;i<matrix.size();i++){
        if(std::find(matrix[i].begin(),matrix[i].end(),target)!=matrix[i].end())
            return true;
    }
    return false;
}

int main(){
    std::vector<std::vector<int>> vec{{1,3,5,7},{10,11,16,20},{23,30,34,40}};
    std::cout<<searchMatrix(vec,3)<<std::endl;
}