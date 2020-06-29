//
// Created by I538989 on 6/24/2020.
//
#include <iostream>
#include <stack>
#include <cmath>

using std::string;
using std::stack;

//栈+反转字符串
int calculate(stack<int>& sti,stack<char>& stc){
    int res=0;
    //实现a+b而不是+a
    if(!sti.empty()){
        res=sti.top();
        sti.pop();
    }
    while(!stc.empty()&&stc.top()!=')'){
        char ch = stc.top();
        stc.pop();
        if(ch=='+'){
            res+=sti.top();
        }
        else {
            res -= sti.top();
        }
        sti.pop();
    }
    return res;
}
//时间复杂度：O(N)，其中 N 指的是字符串的长度。
//空间复杂度：O(N)，其中 N 指的是字符串的长度。
int calculateR(string s) {
    stack<char> stc;
    stack<int> sti;
    int operand=0;
    int n=0;
    //将字符串反转->先压入b再压入-在压入a，取的时候从左到右是心啊a-b
    for (int i = s.length() - 1; i >= 0; i--) {
        char ch = s[i];
        if(isdigit(ch)){
            operand+=pow(10,n)*(ch-'0');
            n++;
        }else if (ch != ' ') {
            if(n!=0){
                sti.push(operand);
                n=0;
                operand=0;
            }
            if(ch=='('){
                int res=calculate(sti,stc);
                //弹出‘)’
                stc.pop();
                sti.emplace(res);
            } else
                stc.push(ch);
        }
    }
    //当最后没有括号时，需要把最后计算的operand入栈
    if(n!=0){
        sti.push(operand);
    }
    return calculate(sti,stc);
}

//栈+非反转字符串
//时间复杂度：O(N)，其中 N 指的是字符串的长度。这种方法与前一种方法的区别在于，这种方法的每个字符都将被精确的处理一次。但是前面的方法中，每个字符可能被处理两次，一次是被添加到栈上，另一次是被弹出处理最终结果。这就是为什么这种方法更快的原因。
//空间复杂度：O(N)，其中 N 指的是字符串的长度。
//正序迭代字符串。
//操作数可以由多个字符组成，字符串 "123" 表示数字 123，它可以被构造为：123 >> 120 + 3 >> 100 + 20 + 3。如果我们读取的字符是一个数字，则我们要将先前形成的操作数乘以 10 并于读取的数字相加，形成操作数。
//每当我们遇到 + 或 - 运算符时，我们首先将表达式求值到左边，然后将正负符号保存到下一次求值。
//如果字符是左括号 (，我们将迄今为止计算的结果和符号添加到栈上，然后重新开始进行计算，就像计算一个新的表达式一样。
//如果字符是右括号 )，则首先计算左侧的表达式。则产生的结果就是刚刚结束的子表达式的结果。如果栈顶部有符号，则将此结果与符号相乘。
int calculate(string s) {
    stack<int> st;
    int operand=0;
    int sign=1;
    int result=0;
    for(int i=0;i<s.size();i++){
        char c=s[i];
        if(isdigit(c)){
            operand=operand*10+(c-'0');
        }else if(c!=' '){
            if(c=='+'){
                result+=sign*operand;
                operand=0;
                sign=1;
            } else if(c=='-'){
                result+=sign*operand;
                operand=0;
                sign=-1;
            }else if(c=='('){
                //保存状态
                st.push(result);
                st.push(sign);

                //从头开始
                operand=0;
                result=0;
                sign=1;
            }else if(c==')'){
                //弹出状态，继续进行
                result+=sign*operand;
                sign=st.top();
                st.pop();
                result=result*sign+st.top();
                st.pop();
                operand=0;
            }
        }
    }
    return result+sign*operand;
}

int main(){
    std::cout<<calculate("1 + 1");
}