//
// Created by anranzhai on 10/2/19.
//
#include <iostream>
#include <vector>
#include <cmath>

int reverse(int x) {
    if(x==0)
        return 0;
    bool  isPositive= x<0? false:true;
    std::vector<int> reverseX;
    int residue=0;
    while(x!=0) {
        residue=x%10;
        reverseX.push_back(residue);
        x/=10;
    }
    long reverseint=reverseX[0];
    int cur=0;
    for(int i=1;i<reverseX.size();i++){
        auto a=(pow(2,31)-reverseX[i])/(double)10;
        //输入超过int范围时int值会发生值的改变，所以提前判断（reverseint*10+reverseX[i]<=pow(2,31)-1同样会出现溢出所以只能反过来判断）
        bool isInLimit=isPositive?reverseint*10+reverseX[i]<=pow(2,31)-1/(double)10:reverseint>=(-pow(2,31)-reverseX[i])/(double)10;
        if(isInLimit){
            reverseint=reverseint*10+reverseX[i];
            cur=i;
        } else{
            reverseint=0;
            break;
        }
    }
    if(cur<reverseX.size()-1)
        return 0;
    return reverseint;
}

int rev(int x){
    int rev=0;
    while(x!=0){
        int pop=x%10;
        x/=10;
        if(rev>INT32_MAX/10 || (rev==INT32_MAX/10 && pop>7))return 0;
        if(rev<INT32_MIN/10 || (rev==INT32_MIN/10 && pop<-8))return 0;
        rev=rev*10+pop;
    }
    return rev;
}

int reverseImp(int x){//不用特意记INT32_MIN/10和INT32_MAX的个位数
    int res = 0;
    while (x != 0) {
        if (res < INT32_MIN/10) return 0;
        if (res > INT32_MAX/10) return 0;
        res *= 10;
        int m = x % 10;
        if (m < 0 && res < INT32_MIN - m) return 0;
        if (m > 0 && res > INT32_MAX - m) return 0;
        res += m;
        x /= 10;
    }
    return res;
}

int reverselong(int x) {
    int64_t result = 0;

    while (x != 0) {
        result = result * 10 + x % 10;
        x /= 10;
    }

    if (result > INT32_MAX || result < INT32_MIN) {
        return 0;
    }

    return (int)result;
}

int main(){
    std::cout<<reverse(1456676767)<<std::endl;
    std::cout<<rev(-123)<<std::endl;
    std::cout<<reverseImp(-123)<<std::endl;
    std::cout<<reverselong(1456676767)<<std::endl;
}