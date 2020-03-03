//
// Created by anranzhai on 2020/3/2.
//
#include <vector>
int minCostValue=0;
bool arrived(std::vector<std::vector<int>>& grid,int index){
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
        if(i==grid.size()-index && j==grid[0].size()-index)
            return index-1;
        else
            minCostValue=std::min(arrived(grid,index+1),arrived(grid,index+1));
        if(i<0 || i>grid.size()-index || j<0 || j>grid[0].size()-index)
            break;
    }
}
int minCost(std::vector<std::vector<int>>& grid) {
    if(grid.size()==0||grid[0].size()==1)
        return 0;
    return arrived(grid,1);
}
