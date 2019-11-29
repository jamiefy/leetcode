//
// Created by Administator on 2019/11/26.
//
#include <iostream>
#include <vector>

//双指针 8ms 9.1MB
int maxSubArrayPointer(std::vector<int>& nums) {
    //记录当前有效增益值
    int last=nums[0];
    //记录以往增益值的最大值，其初始值应该为nums[0]而不是INT_32MIN，不然当值为两个的时候最大值比较会漏掉第一个值
    int max=nums[0];
    for(int i=0,j=1;i<j && j<nums.size();){
        //说明last对结果有增益效果
        if(nums[j]<last+nums[j]){
            last=last+nums[j];
            j++;
        } else{//说明last对结果无增益效果
            i=j;
            j=i+1;
            last=nums[i];
        }
        //比较当前值和以往最大值取最大值
        max=std::max(max,last);
    }
    return max;
}

//动态规划 8ms 9.4MB
int maxSubArrayDP(std::vector<int>& nums){
    //记录当前有效增益值和最大值
    int max=nums[0];
    std::vector<int> dp(nums.size(),nums[0]);
    for(int i=1;i<nums.size();i++){
        dp[i]=std::max(dp[i-1]+nums[i],nums[i]);
        max=std::max(dp[i],max);
    }
    return max;
}

//动态规划->整数代替动态数组 4ms 9.1MB
//当最优化问题具有重复子问题和最优子结构的时候，就是动态规划出场的时候了。动态规划算法的核心就是提供了一个memory来缓存重复子问题
//的结果，避免了递归的过程中的大量的重复计算。动态规划算法的难点在于怎么将问题转化为能够利用动态规划算法来解决。当重复子问题的数
//目比较小时，动态规划的效果也会很差。如果问题存在大量的重复子问题的话，那么动态规划对于效率的提高是非常恐怖的。
int maxSubArrayDPInt(std::vector<int>& nums){
    //记录当前有效增益值和最大值
    int max=nums[0];
    int dp=nums[0];
    for(int i=1;i<nums.size();i++){
        dp=std::max(dp+nums[i],nums[i]);
        max=std::max(dp,max);
    }
    return max;
}

//贪心算法:构造当前子问题的最优解 12ms 9.3MB
//贪心算法与动态规划的区别是每一步都会影响结果，不能回退，获取问题的局部最优解而不是全局最优解，所以最终结果不一定是整体的最优解。
int maxSubArrayGreedy(std::vector<int>& nums){
    int max=INT32_MIN;//最大值的比较从第一个数开始所以赋值32位最小整数
    int sum=0;//以往有效增益值赋值0而不是nums[0]
    for(int i=0;i<nums.size();i++){
        sum+=nums[i];
        max=std::max(max,sum);
        if(sum<0)
            sum=0;
    }
    return max;
}

//五大算法：贪心算法，动态规划算法，分治算法，回溯算法以及分支限界算法。
//回溯算法是深度优先策略的典型应用，回溯算法就是沿着一条路向下走，如果此路不同了，则回溯到上一个分岔路，在选一条路走，一直这样递归
//下去，直到遍历万所有的路径。八皇后问题是回溯算法的一个经典问题，还有一个经典的应用场景就是迷宫问题。
//回溯算法是深度优先，那么分支限界法就是广度优先的一个经典的例子。回溯法一般来说是遍历整个解空间，获取问题的所有解，而分支限界法则
//是获取一个解（一般来说要获取最优解）。
//深度优先搜素算法：不全部保留结点，占用空间少；有回溯操作(即有入栈、出栈操作)，运行速度慢。通常深度优先搜索法不全部保留结点，扩展
//完的结点从数据库中弹出删去，这样，一般在数据库中存储的结点数就是深度值，因此它占用空间较少。所以，当搜索树的结点较多，用其它方法
//易产生内存溢出时，深度优先搜索不失为一种有效的求解方法。
//广度优先搜索算法：保留全部结点，占用空间大； 无回溯操作(即无入栈、出栈操作)，运行速度快。广度优先搜索算法，一般需存储产生的所有
//结点，占用的存储空间要比深度优先搜索大得多，因此，程序设计中，必须考虑溢出和节省内存空间的问题。但广度优先搜索法一般无回溯操作，
//即入栈和出栈的操作，所以运行速度比深度优先搜索要快些。
//广度优先搜索最终找到最优解，深度优先搜索能找到解。
//分冶法：把一个大的问题分为若干个子问题，然后在子问题继续向下分，一直到base cases，通过base cases的解决，一步步向上，最终解决
//最初的大问题。分治算法是递归的典型应用，归并排序、快速排序等均用到了分冶算法。
//分冶法 8ms 9.5MB
int maxCrossHelper(std::vector<int>& nums,int left,int right){//查找过中间点的最大值
    int mid=left+(right-left)/2;
    int leftSum=0;
    int leftMax=INT32_MIN;
    //在中间点左边查找跟中间点连续的最大值
    for(int i=mid;i>=left;i--){
        leftSum+=nums[i];
        leftMax=std::max(leftMax,leftSum);
    }
    int rightSum=0;
    int rightMax=INT32_MIN;
    //在中间点右边查找跟中间点连续的最大值
    for(int j=mid+1;j<=right;j++){
        rightSum+=nums[j];
        rightMax=std::max(rightMax,rightSum);
    }
    return leftMax+rightMax;
}

int maxHelper(std::vector<int>& nums,int left,int right){
    if(left==right)
        return nums[left];
    int mid=left+(right-left)/2;
    int leftMax=maxHelper(nums,left,mid);
    int rightMax=maxHelper(nums,mid+1,right);
    int crossMax=maxCrossHelper(nums,left,right);
    int max=std::max(leftMax,rightMax);
    max=std::max(max,crossMax);
    return max;
}

int maxSubArrayDivision(std::vector<int>& nums){
    return maxHelper(nums,0,nums.size()-1);
}

int main(){
    std::vector<int> vec={-1,-2};
    std::cout<<maxSubArrayDivision(vec);
}