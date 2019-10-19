//
// Created by anranzhai on 2019/10/19.
//
#include <iostream>
#include <vector>

//暴力法  时间复杂度：O(n^2)  空间复杂度：O(n)子字符串的长度最多需要一个深度为n的栈
bool isValid(std::string s){
    std::vector<char> stack;
    for(int i=0;i<s.size();i++){
        if(s[i]=='('){
            stack.push_back('(');
        }
    else if(!stack.empty() && *stack.rbegin()=='('){
        stack.pop_back();
    } else
        return false;
    }
    return stack.empty();
}
int longestValidParentheses(std::string s) {
    int maxlen=0;
    for(int i=0;i<s.size();i++){
        //判断天剑应该时i+j<=s.size()而不是j<s.size()或者i+j<s.size()
        for(int j=2;i+j<=s.size();j+=2){
            //j为从索引值i那个字符开始截取字符的个数
            if(isValid(s.substr(i,j))){
                maxlen=std::max(maxlen,j);
            }
        }
    }
    return maxlen;
}

//把入栈跟双指针结合起来，用前一个指针记录有效字符串的起始索引值
//该方法错误：单用i无法记录起始索引值，当"...()()..."查到第二对"()"时回不到第一对之前的索引值
int longestValidParenthesesStackDoublePointer(std::string s) {//提交错误
    std::vector<char> stack;
    int ans=0;
    for(int i=0,j=0;i<s.size() && j<s.size();j++){
        if(s[j]=='('){
            stack.push_back('(');
            i=j;
        }
        else{
            if(stack.empty())i=j;
            else{
                stack.pop_back();
                i=i==0?0:i-1;
                ans=std::max(ans,j-i);
            }
        }
    }
    return ans;
}

//把索引入栈记录有效字符串的起始索引值，优于前一种方法
//时间复杂度：O(n)  空间复杂度：O(n)栈的大小最大为n
int longestValidParenthesesStack(std::string s) {
    std::vector<int> stack;
    int ans=0;
    //把-1压入栈保证
    stack.push_back(-1);
    for(int i=0;i<s.size();i++){
        if(s[i]=='(')
            //遇到每一个'('把下标放入栈中
            stack.push_back(i);
        else{
            //遇到每一个')'把栈顶元素弹出
            stack.pop_back();
            if(stack.empty())
                //弹出后如果栈为空说明刚弹出的是-1，没有可以配对的'('所以当前字符无效，把当前索引压入栈
                stack.push_back(i);
            else
                //如果不为空说明刚刚配对成功，要更新有效字符串长度
                ans=std::max(ans,i-*stack.rbegin());
        }
    }
    return ans;
}


//动态规划  时间复杂度：O(n)  空间复杂度：O(n)需要一个大小为n的dp数组
int longestValidParenthesesDp(std::string s) {
    //初始化dp的大小和默认值0
    std::vector<int> dp(s.size(),0);
    int ans=0;
    for(int i=1;i<s.size();i++){
        //以'('结尾的子字符串对应的dp 数组位置上的值必定为 0 ,所以只需要更新‘)'在dp数组中对应位置的值
        if(s[i]==')'){
            //s[i]==')'且s[i-1]=='('即形如“....()"的字符串,注意判断i-2大于0的情况下dp满足存在值且值有可能大于0
            if(s[i-1]=='(')dp[i]=(i-2>0?dp[i-2]:0)+2;
                //s[i]==')'且s[i-dp[i-1]-1]=='('即形如“(.....)"的字符串，注意判断i-dp[i-1]-1是否存在即i-dp[i-1]-1>=0是否成立
            else if(i-dp[i-1]-1>=0&&s[i-dp[i-1]-1]=='(')
                //注意判断i-dp[i-1]-2是否存在且值有可能大于0;不带等号是直接在索引为0处不取dp[0]直接取0
                dp[i]=dp[i-1]+((i-dp[i-1]-2)>0?dp[i-dp[i-1]-2]:0)+2;
        }
        //每次计算出一个dp[i]都判断其是否大于有效字符串长度
        ans=std::max(ans,dp[i]);
    }
    return ans;
}

//利用两个计数器 left和right。首先，我们从左到右遍历字符串，对于遇到的每个'('，增加left,
// 对于遇到的每个')'，增加righ。每当left与right相等时，计算当前有效字符串的长度，并且记录
// 目前为止找到的最长子字符串。如果right比left大时，将left和right同时置0 。
//时间和空间消耗最少  时间复杂度：O(n)遍历两遍字符串  空间复杂度：O(1)仅有两个额外的变量left和right
int longestValidParenthesesCounter(std::string s) {
    int left=0,right=0,maxLength=0;
    for(int i=0;i<s.size();i++){
        if(s[i]=='(')
            left++;
        else
            right++;
        if(left==right)
            maxLength=std::max(maxLength,left*2);
        else if(right>left){
            left=0;
            right=0;
        }
    }
    //一定要清零
    left=right=0;
    //从右到左遍历一遍是为了处理从左到右时会有left>right的情况有可能隔断两个有效字符串而不是连成一个更长的字符串
    for(int j=s.size()-1;j>=0;j--){
        if(s[j]=='(')
            left++;
        else
            right++;

        if(left==right)
            maxLength=std::max(maxLength,left*2);
        else if(right<left){
            left=0;
            right=0;
        }
    }
    return maxLength;
}


int main() {
    std::cout << longestValidParentheses("(()") << std::endl;
    return 0;
}
