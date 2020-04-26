//
// Created by anranzhai on 2020/4/26.
//
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
//时间复杂度：O(n)。 n个数字每个会被压栈弹栈各一次。
//空间复杂度：O(n)。用来存放栈中元素。
int largestRectangleArea(std::vector<int>& heights) {
    if(heights.size()==0)
        return 0;
    std::stack<int> s;
    s.emplace(-1);
    int maxArea=INT32_MIN;
    for(int i=0;i<heights.size();i++){
        while(s.top()!=-1&&heights[s.top()]>heights[i]){
            //取到目前最高的高度
            int top=s.top();
            //将目前最高的高度弹出，得到第一个小于他的高度所在的矩阵index
            s.pop();
            maxArea=std::max(maxArea,heights[top]*(i-s.top()-1));
        }
        s.emplace(i);
    }
    //直到到达尾部最后压栈的部分并没有处理
    while(s.top()!=-1){
        int top=s.top();
        s.pop();
        maxArea=std::max(maxArea,heights[top]*((int)heights.size()-s.top()-1));
    }
    return maxArea;
}