//
// Created by anranzhai on 10/2/19.
//
#include <iostream>

bool isPalindrome(int x) {
    int initial=x;
    long reverse=0;
    if(x<0|| (x % 10 == 0 && x != 0))return false;
    while(x!=0){
        reverse=reverse*10+x%10;
        x/=10;
    }
    if(reverse==initial)
        return true;
    else
        return false;
}

bool isPalindromeImp(int x) {
    int reverse=0;
    if(x<0|| (x % 10 == 0 && x != 0))return false;
    while(x>reverse){
        reverse=reverse*10+x%10;
        x/=10;
    }
    return x==reverse||x==reverse/10;
}

int main(){
    std::cout<<isPalindrome(2147483647)<<std::endl;
}

