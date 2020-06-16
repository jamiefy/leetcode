//
// Created by anranzhai on 2020/6/16.
//
#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
using std::stack;
using std::string;
using std::reverse;
//单调栈
//对于每个数字，如果该数字小于栈顶部，即该数字的左邻居，则弹出堆栈，即删除左邻居。否则，我们把数字推到栈上。
//我们重复上述步骤（1），直到任何条件不再适用，例如堆栈为空（不再保留数字）。或者我们已经删除了 k 位数字。
//在上述主循环之外，我们需要处理一些情况，以使解决方案更加完整：
//当我们离开主循环时，我们删除了 m 个数字，这比要求的要少，即（m<k）。在极端情况下，我们不会删除循环中单调递增序列的任何数字，即 m==0。在这种情况下，我们只需要从序列尾部删除额外的 k-m 个数字。
//一旦我们从序列中删除 k 位数字，可能还有一些前导零。要格式化最后的数字，我们需要去掉前导零。
//我们最终可能会从序列中删除所有的数字。在这种情况下，我们应该返回零，而不是空字符串。
string removeKdigits(string num, int k) {
    auto size=num.size();
    if(k==0) return num;
    if(size==k||size==0)return "0";
    string st;
    auto index=0;
    while(index<size&&k>0){
        if(st.empty()||st.back()<=num[index]){
            st+=num[index++];
        }else{
            st.pop_back();
            k--;
        }
    }
    // 1. 如果index == size, 则 k 可能不等于0, 移除掉st末尾k个元素.
    // 2. 如果k == 0, 则 index 可能不等于size, 需要加上num中index之后的元素.
    st=st.substr(0,st.size()-k)+num.substr(index);//点睛之笔，牛逼
    auto begin=0;
    // 移除开头的0,在全0的情况下保证至少剩下一个0.
    while(begin<st.size()-1&&st[begin]=='0')begin++;
    return st.substr(begin);
}

int main(){
    std::cout<<removeKdigits("1432219",3);
}