//
// Created by Administator on 2019/12/6.
//
#include <iostream>
#include <vector>
#include <algorithm>

//递归：查找第一个零之前的位置能通过跳跃达到的最远的位置，然后就可以从该位置开始新一轮的判断,主要思想是遇见零位置就不能再跳跃，所以要找到能跳过零的位置
//时间复杂度：O(n^2),其中 n 是数组 nums 的元素个数,(1+n)*n/2。
bool search(std::vector<int>::iterator start,std::vector<int>::iterator end,std::vector<int>& nums,int index){
    std::vector<int>::iterator it=std::find(start,end,0);
    if(it==end || it+1==end) return true;
    for(std::vector<int>::iterator iter=start;iter<it;iter++){
        index++;
    }
    int max=0;
    //i>=0表示遍历该零之前所有位置，避免前面跳过的位里能达到更远的地方
    for(int i=index-1;i>=0;i--){
        if(nums[i]>index-i){
            max=std::max(max,nums[i]-index+i);
        }
    }
    if(max){
        it+=max;
        return search(it,end,nums,index+max);
    }
    return false;
}

bool canJump(std::vector<int>& nums) {
    if(nums.size()==0)
        return false;
    return search(nums.begin(),nums.end(),nums,0);
}

//回溯：低效，模拟从第一个位置跳到最后位置的所有方案。从第一个位置开始，模拟所有可以跳到的位置，然后从当前位置重复上述操作，当
//没有办法继续跳的时候，就回溯
//时间复杂度：O(2^n)，最多有 2^n种从第一个位置到最后一个位置的跳跃方式，其中 n 是数组 nums 的元素个数
//空间复杂度：O(n)，回溯法只需要栈的额外空间
//leetcode运行速度超出时间限制
bool backTracking(int position,std::vector<int>& nums){
    if(position==nums.size()-1)
        return true;
    int furthest=std::min((position+nums[position]),(int)(nums.size()-1));
    for(int index=position+1;index<=furthest;index++){
        if(backTracking(index,nums))
            return true;
    }
    return false;
}

bool canJumpBackTracking(std::vector<int>& nums) {
    if(nums.size()==0)
        return false;
    return backTracking(0,nums);
}

//動態規划算法自頂向下，比回溯法多了一个arrived数组记录已经确定能不能到达终点的节点，避免了对同一个节点重复进行判断，但是回溯的任务依然很庞大
//时间复杂度：O(n^2),数组中的每个元素，假设为 i，需要搜索右边相邻的 nums[i] 个元素查找是否有 can 的坐标。 nums[i] 最多为 n，n 是 nums 数组的大小。
//空间复杂度：O(2n)=O(n)，第一个 n 是栈空间的开销，第二个 n 是记忆表的开销。
//leetcode运行超出时间限制
enum is_arrived{Unknown,can,cannot};

bool topToBottom(int position,std::vector<int>& nums,std::vector<is_arrived>& arrived){
    if(arrived[position]!= Unknown)
        return arrived[position]==can;
    int furthest=std::min((position+nums[position]),(int)(nums.size()-1));
    for(int index=position+1;index<=furthest;index++){
        if(topToBottom(index,nums,arrived)){
            arrived[position]=can;
            return true;
        }
    }
    arrived[position]=cannot;
    return false;
}

bool canJumpToptoBottom(std::vector<int>& nums) {
    if(nums.size()==0)
        return false;
    std::vector<is_arrived> arrived(nums.size(), Unknown);
    //最後一個節點肯定能自己到达自己
    arrived[nums.size()-1]=can;
    return topToBottom(0,nums,arrived);
}

//动态规划自底向上，和自顶向下的区别是消除了回溯
bool canJumpBottomtoTop(std::vector<int>& nums) {
    if(nums.size()==0)
        return false;
    std::vector<is_arrived> arrived(nums.size(), Unknown);
    //最後一個節點肯定能自己到达自己
    arrived[nums.size()-1]=can;
    for(int position=nums.size()-2;position>=0;position--){
        int furthest=std::min(position+nums[position],(int)nums.size()-1);
        for(int current=position+1;current<=furthest;current++){
            //当前位置能到达终点说明position位置能到达终点，赋值然后结束关于position位置是否能到达终点的判断
            if(arrived[current]==can){
                arrived[position]=can;
                break;
            }
        }
    }
    return arrived[0]==can;
}


//贪心算法:循环找出最左边可以到达终点的位置
//时间复杂度：O(n)，只需要访问 nums 数组一遍，共 nn 个位置，nn 是 nums 数组的长度。
//空间复杂度：O(1)，不需要额外的空间开销
bool canJumpGreedy(std::vector<int>& nums) {
    if(nums.size()==0)
        return false;
    int lastArrivedPosition=nums.size()-1;
    for(int position=nums.size()-2;position>=0;position--){
        if(position+nums[position]>=lastArrivedPosition)
            lastArrivedPosition=position;
    }
    return lastArrivedPosition==0;
}

//leetcode超出時間限制
bool canJumparrived(std::vector<int>& nums){
    if(nums.size()==0)
        return false;
    std::vector<bool> arrived(nums.size(), false);
    arrived[0]=true;
    for(int i=0;i<nums.size();i++){
        if(arrived[i]){
            for(int j=1;j<=nums[i];j++){
                arrived[i+j]= true;
            }
        }
        if(arrived[nums.size()-1])
            return true;
    }
    return false;
}

int main(){
    std::vector<int> vec{2,5,0,0};
    std::cout<<canJumpGreedy(vec);
}