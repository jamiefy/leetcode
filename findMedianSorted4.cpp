//
// Created by I538989 on 6/23/2020.
//
#include <iostream>
#include <vector>
using namespace std;
//暴力时间复杂度O(m+n)
double findMedianSorted(std::vector<int>& nums1, std::vector<int>& nums2) {
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


//划分数组
//时间复杂度：O(logmin(m,n)))，其中 m 和 n 分别是数组 nums1 和nums2 的长度。查找的区间是[0,m]，而该区间的长度在每次循环之后都会减少为原来的一半。所以，只需要执行 logm 次循环。由于每次循环中的操作次数是常数，所以时间复杂度为 O(logm)。由于我们可能需要交换 nums1 和 nums2 使得 m≤n，因此时间复杂度是 O(logmin(m,n)))。
//空间复杂度：O(1)。
double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    if (nums1.size() > nums2.size()) {
        return findMedianSortedArrays(nums2, nums1);
    }

    int m = nums1.size();
    int n = nums2.size();
    int left = 0, right = m;
    // median1：前一部分的最大值
    // median2：后一部分的最小值
    int median1 = 0, median2 = 0;
    while(left<=right){
        int i=(right-left)/2+left;
        int j=(m+n+1)/2-i;

        int num_lowi=i==0?INT32_MIN:nums1[i-1];
        int num_highi=i==m?INT32_MAX:nums1[i];
        int num_lowj=j==0?INT32_MIN:nums2[j-1];
        int num_highj=j==n?INT32_MAX:nums2[j];

        if(num_lowi<=num_highj){
            median1=std::max(num_lowi,num_lowj);
            median2=std::min(num_highi,num_highj);
            left=i+1;
        } else
            right=i-1;
    }
    return (m+n)%2==0?(median1+median2)/2.0:median1;
}

//二分查找
//时间复杂度：O(log(m+n))，其中 m 和 n 分别是数组 nums1 和 nums2 的长度。初始时有 k=(m+n)/2 或 k=(m+n)/2+1，每一轮循环可以将查找范围减少一半，因此时间复杂度是 O(log(m+n))。
//空间复杂度：O(1)
int getKthElement(const vector<int>& nums1, const vector<int>& nums2, int k) {
    /* 主要思路：要找到第 k (k>1) 小的元素，那么就取 pivot1 = nums1[k/2-1] 和 pivot2 = nums2[k/2-1] 进行比较
     * 这里的 "/" 表示整除
     * nums1 中小于等于 pivot1 的元素有 nums1[0 .. k/2-2] 共计 k/2-1 个
     * nums2 中小于等于 pivot2 的元素有 nums2[0 .. k/2-2] 共计 k/2-1 个
     * 取 pivot = min(pivot1, pivot2)，两个数组中小于等于 pivot 的元素共计不会超过 (k/2-1) + (k/2-1) <= k-2 个
     * 这样 pivot 本身最大也只能是第 k-1 小的元素
     * 如果 pivot = pivot1，那么 nums1[0 .. k/2-1] 都不可能是第 k 小的元素。把这些元素全部 "删除"，剩下的作为新的 nums1 数组
     * 如果 pivot = pivot2，那么 nums2[0 .. k/2-1] 都不可能是第 k 小的元素。把这些元素全部 "删除"，剩下的作为新的 nums2 数组
     * 由于我们 "删除" 了一些元素（这些元素都比第 k 小的元素要小），因此需要修改 k 的值，减去删除的数的个数
     */

    int m = nums1.size();
    int n = nums2.size();
    int index1 = 0, index2 = 0;

    while (true) {
        // 边界情况
        if (index1 == m) {
            return nums2[index2 + k - 1];
        }
        if (index2 == n) {
            return nums1[index1 + k - 1];
        }
        if (k == 1) {
            return min(nums1[index1], nums2[index2]);
        }

        // 正常情况
        int newIndex1 = min(index1 + k / 2 - 1, m - 1);
        int newIndex2 = min(index2 + k / 2 - 1, n - 1);
        int pivot1 = nums1[newIndex1];
        int pivot2 = nums2[newIndex2];
        if(pivot1<=pivot2){
            k-=newIndex1-index1+1;
            index1=newIndex1+1;
        } else{
            k-=newIndex2-index2+1;
            index2=newIndex2+1;
        }
    }
}

double findMedianSortedArraysBi(vector<int>& nums1, vector<int>& nums2) {
    int totalLength = nums1.size() + nums2.size();
    if (totalLength % 2 == 1) {
        return getKthElement(nums1, nums2, (totalLength + 1) / 2);
    }
    else {
        return (getKthElement(nums1, nums2, totalLength / 2) + getKthElement(nums1, nums2, totalLength / 2 + 1)) / 2.0;
    }
}

int main() {
    std::vector<int> a{1,2},b{3,4};
    std::cout << findMedianSortedArrays(a,b)<< std::endl;
    return 0;
}
