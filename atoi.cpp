//
// Created by anranzhai on 10/2/19.
//
#include <iostream>

int myAtoi(std::string str) {
    int cur=0;
    int64_t tmp=0;
    int sign=1;
    while(str[cur]==' '&& cur<str.size())
        cur++;
    if(str[cur]>='0' && str[cur]<='9'){
        tmp=str[cur++]-48;//str[cur]返回的是数字的ASCALL码值而不是数字本身
        while(str[cur]>='0'&& str[cur]<='9'){
            if(tmp*10-48+str[cur]>=INT32_MAX)return INT32_MAX;
            tmp=tmp*10+str[cur++]-48;
        }
    }
    else if(str[cur]=='+' || str[cur]=='-'){
        sign=str[cur++]=='+'? 1: -1;
        if(!(str[cur]>='0' && str[cur]<='9')) return 0;
        while(str[cur]>='0' && str[cur]<='9'){
            if(sign==1){
                if(tmp*10-48+str[cur]>=INT32_MAX)return INT32_MAX;
            }
            else{
                if(-(tmp*10-48+str[cur])<=INT32_MIN)return INT32_MIN;
            }
            tmp=tmp*10+str[cur++]-48;
        }
    }else
        return 0;
    return (int32_t)sign*tmp;
}

int atoi(std::string str){
    long long res = 0;
    int sign = 1;
    int i = 0;
    // remove front spaces
    while (str[i] == ' ') ++i;
    if (str[i] >= '0' && str[i] <= '9') {
        res += 10 * res + str[i] - '0';
    } else if (str[i] == '+' || str[i] == '-') {
        sign = (str[i] == '+') ? 1 : -1;
    } else {
        return 0;
    }
    // process following chars
    while (++i < str.size() && str[i] >= '0' && str[i] <= '9') {
        res = 10 * res + str[i] - '0';
        if (sign == 1 && res >= INT32_MAX)
            return INT32_MAX;
        if (sign == -1 && res * -1 <= INT32_MIN)
            return INT32_MIN;
    }
    return sign * res;
}

int main(){
    std::cout<<myAtoi("-2147483648");
    return 0;
}
