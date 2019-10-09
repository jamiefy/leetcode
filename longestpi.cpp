//
// Created by Administrator on 2019/9/30.
//
#include <string>
#include <iostream>

std::string longestpalindrome(std::string s){
    if(s.length()<1)return "";
    int start=0,end=0,len=0;
    for(int i=0;i<2*s.length();i++){
        len=[](std::string s, int center)->int{
            int L=center,R=center;
            while(L>0 && R<2*s.length() && s.at((L-1)/2)==s.at(R/2)){//L==0 or R==2*s.length()的时候s.at((L-1)/2)==s.at(R/2)会出界
                L--;
                R++;
            }
            return (R-1)/2-L/2+1;//L++ R--才是正确的值
        }(s,i);
        if(len>end-start+1){
            start=(i-1)/2-(len-1)/2;
            end=i/2+(len-1)/2;//len-1不管len是奇数或者偶数都成立
        }
    }
    return s.substr(start,end-start+1);
}

int main(){
    std::string s("ababababa");
    std::cout<<longestpalindrome(s);
}
