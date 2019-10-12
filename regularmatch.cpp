//
// Created by anranzhai on 10/2/19.
//
#include <iostream>

//自己的错误解法-蛮力不可行-很多情况不能涵盖
bool match(std::string s, std::string p) {
    if((s!=""&&(p==""||p=="*"))||(s==""&&p=="*"))return false;
    if(s==""&&(p==""||p[1]=='*'))return true;
    int curs=0,curp=0;
    for(;curs<s.length()&&curp<p.length();){
        if(s[curs]==p[curp]){
            curs++;
            curp++;
        } else{
            if(p[curp]=='.'){
                curs++;
                curp++;
            }
            else if(p[curp]=='*'&&p[curp-1]==s[curs]){
                if(curp+1>=p.size()){
                    while(++curs<s.size()){
                        if(s[curs]==p[curp-1])continue;
                        else return false;
                    }
                } else{
                    while(curs-1<s.size()&&p[curp-1]==s[curs-1]){
                        if(match(s.substr(curs-1),p.substr(curp+1)))
                            return true;
                        curs++;
                    }
                    if(curs-1<s.size()&&match(s.substr(curs-1),p.substr(curp+1)))return true;
                    return false;
                }


                while(p[curp-1]==s[curs]){
                    curs++;
                    if(curs>=s.length())break;
                }
                curp++;
            }
            else if(p[curp]=='*'&&p[curp-1]=='.'){
                if(curp==p.size()-1)return true;
                else{
                    while(++curs<s.size()){
                        if(match(s.substr(curs),p.substr(curp+1)))
                            return true;
                    }
                    return false;
                }
            }
            //*和前面的字母=前面的字母，所以需要跳过*
            else if(p[curp]=='*'){
                curp++;
            }
            else if(p[curp+1]=='*'){
                curp+=2;
            } else
                return false;
        }
    }
    if(curs>=s.length()&&curp>=p.length())return true;
    else return false;
}

bool isMatchRecursive(std::string s, std::string p) {
    if(p.empty())return s.empty();
    bool firstMatch=!s.empty()&&(s[0]==p[0]||p[0]=='.');
    if(p.size()>=2&&p[1]=='*'){
        return (firstMatch&&isMatchRecursive(s.substr(1),p))||(isMatchRecursive(s,p.substr(2)));
    } else{
        return firstMatch&&isMatchRecursive(s.substr(1),p.substr(1));
    }
}

int main(){
    std::cout<<isMatchRecursive("ab",
                       ".*"

    )<<std::endl;
}