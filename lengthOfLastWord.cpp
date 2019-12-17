//
// Created by Administator on 2019/12/17.
//
#include <iostream>

int lengthOfLastWord(std::string s) {
    if(s.size()==0)
        return 0;
    size_t lastPos=s.find_last_of(' ');
    if(lastPos==s.size()-1){
        return lengthOfLastWord(s.substr(0,s.size()-1));
    } else
        return lastPos==std::string::npos?s.size():s.size()-1-lastPos;
}

int main(){
    std::cout<<lengthOfLastWord("a b ");
}