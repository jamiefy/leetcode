//
// Created by Administator on 2019/12/11.
//
#include <iostream>
#include <vector>

int searchMin(std::vector<std::vector<int>>& intervals){
    int num=intervals.size();
    if(num==0)
        return -1;
    int min=intervals[0][0],minRow=0;
    for(int i=0;i<num;i++){
        if(min>intervals[i][0]){
            min=intervals[i][0];
            minRow=i;
        }
    }
    return minRow;
}

std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) {
    std::vector<std::vector<int>> ret;
    int initialRow=searchMin(intervals);
    std::vector<int> initialVec=intervals[initialRow];
    intervals[initialRow][0]=INT32_MAX;
    ret.emplace_back(initialVec);
    for(int i=1;i<intervals.size();i++){
        int minRow=searchMin(intervals);
        std::vector<int> minVec=intervals[minRow];
    }
}
