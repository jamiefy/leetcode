#include <iostream>
#include <vector>
double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
    int len1=nums1.size();
    int len2=nums2.size();
    int median=(len1+len2)/2;
    std::vector<int> nums;
    int i=0,j=0;
    while(i<len1 && j<len2){
        if(nums2[j]>nums1[i])nums.emplace_back(nums1[i++]);
        else if(nums2[j]<nums1[i])nums.emplace_back(nums2[j++]);
        else if(nums2[j]==nums1[i]){
            nums.emplace_back(nums1[i++]);
            nums.emplace_back(nums2[j++]);
        }
        if(nums.size()>median){
            goto end;
        }
    }
    while(i<len1){
        nums.emplace_back(nums1[i++]);
        if(nums.size()>median){
            goto end;
        }
    }
    while(j<len2){
        nums.emplace_back(nums2[j++]);
        if(nums.size()>median){
            goto end;
        }
    }

    end:
    double num;
    if((len1+len2)%2==0)
        num=(nums[median-1]+nums[median])/(double)2;
    else
        num=nums[median];
    return num;
}

int main() {
    std::vector<int> a{1,2},b{3,4};
    std::cout << findMedianSortedArrays(a,b)<< std::endl;
    return 0;
}