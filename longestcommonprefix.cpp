//
// Created by anranzhai on 10/3/19.
//

#include <iostream>
#include <vector>

std::string longestCommonPrefix(std::vector<std::string>& strs) {
    std::string ret;
    if(strs.size()==0)return "";
    for(int i=0;i<strs[0].size();i++){
        char c=strs[0][i];
        for(auto s:strs){
            if(i<s.size())
                if(c==s[i])
                    continue;
            return ret;
        }
        ret+=c;//此处不能用ret[i]=c,ret刚开始没初始化大小
    }
    return ret;
}

int main(){
    std::vector<std::string> vector{"fjabcj","fjabdee"};
    std::cout<<longestCommonPrefix(vector)<<std::endl;
}