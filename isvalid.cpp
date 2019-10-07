//
// Created by anranzhai on 10/4/19.
//
#include <iostream>
#include <stack>

bool isValid(std::string s) {
    std::stack<char> stack;
    for(int i=0;i<s.size();i++){
        if(s[i]=='('||s[i]=='['||s[i]=='{')
            stack.push(s[i]);
        else if(!stack.empty()){
            if(s[i]==')'&&stack.top()=='(')
                stack.pop();
            else if(s[i]==']'&&stack.top()=='[')
                stack.pop();
            else if(s[i]=='}'&&stack.top()=='{')
                stack.pop();
            else
                return false;
        }else
            return false;
    }
    if(stack.empty())
        return true;
    return false;
}