//
// Created by anranzhai on 2020/2/26.
//
#include <iostream>
std::string addBinary(std::string a, std::string b) {
    if(a.size()==0||b.size()==0)
        return a.size()==0 ? b:a;
    std::string ret;
    auto arbeg=a.rbegin(),brbeg=b.rbegin();
    int carry=0;
    while(arbeg!=a.rend() && brbeg!=b.rend()){
        int num=*arbeg-'0'+*brbeg-'0'+carry;
        ret.insert(ret.begin(),num%2+'0');
        carry= num>=2 ? 1:0;
        arbeg++;
        brbeg++;
    }
    while(arbeg!=a.rend()){
        int num=*arbeg-'0'+carry;
        ret.insert(ret.begin(),num%2+'0');
        carry= num==2 ? 1:0;
        arbeg++;
    }
    while(brbeg!=b.rend()){
        int num=*brbeg-'0'+carry;
        ret.insert(ret.begin(),num%2+'0');
        carry= num==2 ? 1:0;
        brbeg++;
    }

    return carry==1? "1"+ret:ret;
}

std::string addBinarySpaceOptimization(std::string a, std::string b) {
    int ia = a.length() - 1, ib = b.length() - 1;
    std::string r;
    r.reserve(std::max(ia, ib) + 1);
    int c = 0;
    for (; ia >= 0 || ib >= 0 || c == 1; --ia, --ib) {
        if (ia >= 0) c += a[ia] - '0';
        if (ib >= 0) c += b[ib] - '0';
        r.insert(r.begin(), (c & 1) + '0');
        c >>= 1;
    }
    return r;
}

int main(){
    std::string a("11"),b("1");
    std::cout<<addBinarySpaceOptimization(a,b)<<std::endl;
}