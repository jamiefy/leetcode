//
// Created by anranzhai on 10/3/19.
//
#include <iostream>
#include <vector>
#include <algorithm>

int maxArea(std::vector<int>& height) {
    int maxArea=0;
    for(int start=0;start<height.size()-1;start++){
        for(int end=start+1;end<height.size();end++){
            maxArea=std::max(maxArea,std::min(height[start],height[end])*(end-start));
        }
    }
    return maxArea;
}

int maxA(std::vector<int>& height) {
    int maxArea=0,h=0;
    int len=height.size();
    for(int w=len-1;w>=1;w--){
        for(int start=0,end=start+w;end<len;start++,end++){
            if(std::min(height[end],height[start])>h){
                h=std::min(height[end],height[start]);
                maxArea=std::max(maxArea,w*h);
            }
        }
        h=0;
    }
    return maxArea;
}

int maxAreaImp(std::vector<int>& height) {
    int maxArea=0,l=0,r=height.size()-1;
    while(l<r){
        maxArea=std::max(maxArea,std::min(height[l],height[r])*(r-l));
        if(height[l]<height[r]){
            l++;
        } else{
            r--;
        }
    }
    return maxArea;
}

int main(){
    std::vector<int> vector{2,1,4,2};
    std::cout<<maxAreaImp(vector)<<std::endl;
}