//
// Created by Administator on 2019/12/17.
//
#include <iostream>

//递归
//时间复杂度：O(n)
//空间复杂度：O(n)
int lengthOfLastWordStringFind(std::string s) {
    if(s.size()==0)
        return 0;
    size_t lastPos=s.find_last_of(' ');
    if(lastPos==s.size()-1){
        return lengthOfLastWordStringFind(s.substr(0,s.size()-1));
    } else
        return lastPos==std::string::npos?s.size():s.size()-1-lastPos;
}

//查找最后一个单词的首尾
//时间复杂度：O(n)
//空间复杂度：O(1)
int lengthOfLastWord(std::string s) {
    if(s.size()==0)
        return 0;
    int end=s.size()-1;
    while(end>=0 && s[end]==' ')end--;
    int start=end;
    while(start>=0 && s[start]!=' ')start--;
    return end-start;
}

//优化,运行速度极大提升
//时间复杂度：O(n)
//空间复杂度：O(1)
int lengthOfLastWordImp(std::string s) {
    if(s.size()==0)
        return 0;
    int end=s.size()-1;
    while(end>=0 && s[end]==' ')end--;
    int ret=0;
    for(int start=end;start>=0 && s[start]!=' ';start--){
        ret++;
    }
    return ret;
}

int main(){
    std::cout<<lengthOfLastWord("a b ");
}