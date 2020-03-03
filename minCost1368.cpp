//
// Created by anranzhai on 2020/3/2.
//
#include <vector>
int minCostValue=0;
int arrived(std::vector<std::vector<int>>& grid,int row,int col){
    if(row==0&&col==0)
        return grid.size()-1+grid[0].size()-1;
    while(true){
        int i=0,j=0;
        switch (grid[i][j]){
            case 1:{
                j++;
                break;
            }
            case 2:{
                j--;
                break;
            }
            case 3:{
                i++;
                break;
            }
            case 4:{
                i--;
                break;
            }
        }
        if(i==row && j==col)
            return grid.size()-1-row+grid[0].size()-1-col;
        if(i<0 || i>row || j<0 || j>col)
            break;
    }
    minCostValue=std::min(arrived(grid,row,col-1),arrived(grid,row-1,col));
}
int minCost(std::vector<std::vector<int>>& grid) {
    if(grid.size()==0||grid[0].size()==1)
        return 0;
    arrived(grid,grid.size()-1,grid[0].size()-1);
    return minCostValue;
}
