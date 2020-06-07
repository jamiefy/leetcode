//
// Created by anranzhai on 2020/6/7.
//
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
//递减单调栈
int trap(vector<int>& height) {
    auto ans=0;
    stack<int> st;
    for(int i=0;i<height.size();){
        while(!st.empty() && height[i]>height[st.top()]){
            auto base=st.top();
            st.pop();
            if(st.empty())
                break;
            else{
                auto high=min(height[st.top()],height[i])-height[base];
                if(high>0)
                    ans+=high*(i-st.top()-1);
            }
        }
        st.emplace(i++);
    }
    return ans;
}
//其他方法：动态编程
//找到数组中从下标 i 到最左端最高的条形块高度left_max。
//找到数组中从下标 i 到最右端最高的条形块高度right_max。
//扫描数组height 并更新答案：
//累加min(max_left[i],max_right[i])−height[i] 到 ansans 上

//双指针
//从动态编程方法的示意图中我们注意到，只要right_max[i]>left_max[i] （元素 0 到元素 6），积水高度将由 left_max 决定，类似地left_max[i]>right_max[i]（元素 8 到元素 11）。
//所以我们可以认为如果一端有更高的条形块（例如右端），积水的高度依赖于当前方向的高度（从左到右）。当我们发现另一侧（右侧）的条形块高度不是最高的，我们则开始从相反的方向遍历（从右到左）。
//我们必须在遍历时维护left_max 和right_max ，但是我们现在可以使用两个指针交替进行，实现 1 次遍历即可完成。
int trapDoublePointers(vector<int>& height)
{
    int left = 0, right = height.size() - 1;
    int ans = 0;
    int left_max = 0, right_max = 0;
    while (left < right) {
        if (height[left] < height[right]) {
            height[left] >= left_max ? (left_max = height[left]) : ans += (left_max - height[left]);
            ++left;
        }
        else {
            height[right] >= right_max ? (right_max = height[right]) : ans += (right_max - height[right]);
            --right;
        }
    }
    return ans;
}

int main(){
    vector<int> vec{2,1,0,2};
    cout<<trap(vec);
}