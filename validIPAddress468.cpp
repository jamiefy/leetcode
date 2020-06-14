//
// Created by anranzhai on 2020/6/14.
//
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>

using std::string;
string validIPAddress(string IP) {
    if(IP.size()==0)
        return "Neither";
    //IPv6
    if(count(IP.begin(),IP.end(),':')==7){
        auto p=std::strtok(const_cast<char*>(IP.c_str()),":");
        auto cnt=0;
        while(p!= nullptr){
            cnt++;
            if(strlen(p)>4)
                return "Neither";
            int i=0;
            //每个字符都是数字
            while(i<strlen(p)){
                if(p[i]-'0'<0||p[i]-'0'>9||p[i]-'a'<0||p[i]-'a'>5||p[i]-'A'<0||p[i]-'A'>5)
                    return "Neither";
                i++;
            }
            p=strtok(nullptr,":");
        }
        return cnt==8?"IPv6":"Neither";
    }if(count(IP.begin(),IP.end(),'.')==3){//IPv4
        auto p=std::strtok(const_cast<char*>(IP.c_str()),".");
        auto cnt=0;
        while(p!= nullptr){
            cnt++;
            int i=0;
            //每个字符都是数字
            while(i<strlen(p)){
                if(p[i]-'0'<0||p[i]-'0'>9)
                    return "Neither";
                i++;
            }
            int index=0;
            while(p[index]-'0'==0){
                index++;
            }
            if(index!=strlen(p)&&index!=0)
                return "Neither";
            int num=atoi(p);
            if(num<=0||num>255)
                return "Neither";
            p=strtok(nullptr,".");
        }
        return cnt==4?"IPv4":"Neither";
    } else
        return "Neither";
}

int main(){
    std::cout<<validIPAddress(
            "20EE:FGb8:85a3:0:0:8A2E:0370:7334");
}