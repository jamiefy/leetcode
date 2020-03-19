//
// Created by anranzhai on 2020/3/19.
//
#include <iostream>
#include <vector>
#include <map>
//字符串连接
//时间复杂度： O(N)
//空间复杂度： O(1),说空间复杂度，一般都是说额外空间复杂度，对于需要返回的结果不算
std::vector<std::string> fizzBuzz(int n) {
    std::vector<std::string> ret(n,"");
    for(int i=1;i<=n;i++){
        if(i%3==0)
            ret[i-1]+="Fizz";
        if(i%5==0)
            ret[i-1]+="Buzz";
        if(ret[i-1]=="")
            ret[i-1]=std::to_string(i);
    }
    return ret;
}

//把映射关系放在散列表，更自由的映射关系
//时间复杂度： O(N)
//空间复杂度： O(1),说空间复杂度，一般都是说额外空间复杂度，对于需要返回的结果不算
std::vector<std::string> fizzBuzzHash(int n) {
    std::vector<std::string> ret;
    std::map<int,std::string> nmap{{3,"Fizz"},{5,"Buzz"}};
    for(int i=1;i<=n;i++){
        std::string str="";
        for(auto num:nmap){
            if(i%num.first==0)
                str+=num.second;
        }
        if(str=="")
            str+=std::to_string(i);
        ret.push_back(str);
    }
    return ret;
}

int main(){
    std::vector<std::string> vec=fizzBuzz(1);
    for(std::string num:vec)
        std::cout<<num<<" ";
}
