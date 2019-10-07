//
// Created by anranzhai on 10/2/19.
//
#include <iostream>

bool isMatch(std::string s, std::string p) {
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
                        if(isMatch(s.substr(curs-1),p.substr(curp+1)))
                            return true;
                        curs++;
                    }
                    if(curs-1<s.size()&&isMatch(s.substr(curs-1),p.substr(curp+1)))return true;
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
                        if(isMatch(s.substr(curs),p.substr(curp+1)))
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

int main(){
    std::cout<<isMatch("a",
                       "ab*"

    )<<std::endl;
}