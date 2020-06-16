//
// Created by anranzhai on 2020/6/14.
//
#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
#include <regex>

using std::string;
using std::regex_match;
//分治法 时间复杂度和空间复杂度均是O(1)
string validIPAddress(string IP) {
    if(IP.size()==0)
        return "Neither";
    //IPv6
    if(count(IP.begin(),IP.end(),':')==7){
        auto p=std::strtok(const_cast<char*>(IP.c_str()),":");
        auto cnt=0;
        while(p!= nullptr){
            cnt++;
            //检查长度为1-4
            if(strlen(p)>4||strlen(p)==0)
                return "Neither";
            int i=0;
            //每个字符都是数字或是a-f或A-F
            while(i<strlen(p)){
                if((p[i]-'0'>=0&&p[i]-'0'<=9)||(p[i]-'a'>=0&&p[i]-'a'<=5)||(p[i]-'A'>=0&&p[i]-'A'<=5))
                    i++;
                else
                    return "Neither";
            }
            p=strtok(nullptr,":");
        }
        return cnt==8?"IPv6":"Neither";
    }if(count(IP.begin(),IP.end(),'.')==3){//IPv4
        auto p=std::strtok(const_cast<char*>(IP.c_str()),".");
        auto cnt=0;
        while(p!= nullptr){
            cnt++;
            //不能以0开头，除了单个0;两个‘.'之间为空；两点之间数字长度大于3
            if((p[0]-'0'==0&&strlen(p)>1)||strlen(p)==0||strlen(p)>3)
                return "Neither";
            int i=0;
            //每个字符都是数字
            while(i<strlen(p)){
                if(p[i]-'0'<0||p[i]-'0'>9)
                    return "Neither";
                i++;
            }
            //范围在0-255之间
            int num=atoi(p);
            if(num<0||num>255)
                return "Neither";
            p=strtok(nullptr,".");
        }
        return cnt==4?"IPv4":"Neither";
    } else
        return "Neither";
}

//正则表达式
string validIPAddressRegex(string IP) {
    if (IP.size() == 0)
        return "Neither";
    string ipv4="([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])";
    std::regex IPv4("^("+ipv4+"\\.){3}"+ipv4+"$");
    string ipv6="([0-9a-fA-F]{1,4})";
    std::regex IPv6("^("+ipv6+"\\:){7}"+ipv6+"$");

    if (count(IP.begin(),IP.end(),'.')==3)
        return std::regex_match(IP,IPv4)?"IPv4":"Neither";
    if(count(IP.begin(),IP.end(),':')==7)
        return regex_match(IP,IPv6)?"IPv6":"Neither";
    return "Neither";
}

int main(){
    std::cout<<validIPAddressRegex(
            "00.0.0.0");
}