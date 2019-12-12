//
// Created by Administator on 2019/12/11.
//
#include <iostream>
#include <vector>
#include <algorithm>

//左边界排序，按左边界从小到大的顺序取区间进行判断，已知压进ret的区间满足后进的区间左边界大于前面区间的右边界，以此类推，所以每次
//判断是否能进栈只需要拿欲进栈区间左边界跟栈顶区间右边界比较
//时间复杂度：O(n^2)
//空间复杂度：O(n)
int searchMin(std::vector<std::vector<int>>& intervals){
    int min=intervals[0][0],minRow=0;
    for(int i=0;i<intervals.size();i++){
        if(intervals[i][0]!=INT32_MAX && min>intervals[i][0]){
            min=intervals[i][0];
            minRow=i;
        }
    }
    return minRow;
}

std::vector<std::vector<int>> merge(std::vector<std::vector<int>>& intervals) {
    int num=intervals.size();
    if(num==0)
        return intervals;
    std::vector<std::vector<int>> ret;
    int initialRow=searchMin(intervals);
    std::vector<int> initialVec=intervals[initialRow];
    intervals[initialRow][0]=INT32_MAX;
    ret.emplace_back(initialVec);
    for(int i=1;i<intervals.size();i++){
        int minRow=searchMin(intervals);
        std::vector<int> minVec=intervals[minRow];
        intervals[minRow][0]=INT32_MAX;
        if(ret[ret.size()-1][1]>=minVec[0])
            ret[ret.size()-1][1]=std::max(ret[ret.size()-1][1],minVec[1]);
        else
            ret.emplace_back(minVec);
    }
    return ret;
}

//代码简化： 1.排序自定义比较函数 2.原地合并
//时间复杂度：O(nlgn),除去 sort 的开销，我们只需要一次线性扫描，所以主要的时间开销是排序的 O(nlgn)
//空间复杂度：O(1)
//实际运行速度是上面未简化代码的2倍
std::vector<std::vector<int>> mergeSort(std::vector<std::vector<int>>& intervals) {
    int num=intervals.size();
    if(num==0)
        return intervals;
    //(std::vector<int>& interval1,std::vector<int>& interval2)比(std::vector<int> interval1,std::vector<int> interval2)会使整个代码优化一倍的时间
    std::sort(intervals.begin(),intervals.end(),[](std::vector<int>& interval1,std::vector<int>& interval2){
        return interval1[0]<interval2[0];
    });
    for(auto it=intervals.begin();it+1!=intervals.end();){
        if(it->at(1)>=(it+1)->at(0)){
            it->at(1)=std::max(it->at(1),(it+1)->at(1));
            intervals.erase(it+1);
        } else
            it++;
    }
    return intervals;
}



int main(){
    std::vector<std::vector<int>> intervals{{1,2},{3,4},{2,6},{5,7}};
    std::vector<std::vector<int>> ret=mergeSort(intervals);
    for(int i=0;i<ret.size();i++){
        std::cout<<ret[i][0]<<" "<<ret[i][1]<<std::endl;
    }
}