//
// Created by anranzhai on 10/3/19.
//
#include <iostream>
#include <vector>
#include <map>
std::map<int,std::string> map{{2,"abc"},{3,"def"},{4,"ghi"},
                              {5,"jkl"},{6,"mno"},{7,"pqrs"},
                              {8,"tuv"},{9,"wxyz"}};

void back(std::string combination,std::string next_digits,std::vector<std::string> &ret){
    if(next_digits.size()==0)
        ret.emplace_back(combination);
    else{
        int num=next_digits[0]-'0';
        std::string choose=map.find(num)->second;
        for(int i=0;i<choose.size();i++) {
            back(combination+choose[i],next_digits.substr(1),ret);
        }
    }

}

//每次循环个数不一定无法直接采用循环，可采用嵌套和递归
std::vector<std::string> letterCombinations(std::string digits) {
    std::vector<std::string> ret;
    if(digits.size()!=0)
        back("",digits,ret);
    return ret;
}



//std::string mapfill[10]={"","","abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
std::string mapfill[10]={"abc","def","ghi","jkl","mno","pqrs","tuv","wxyz"};
std::vector<std::string> vector;

void backindex(std::string combination,std::string next_digits){
    if(next_digits.size()==0)
        vector.emplace_back(combination);
    else{
        int num=next_digits[0]-'0';
        //std::string choose=mapfill[next_digits[0]-'0'];
        std::string choose=mapfill[next_digits[0]-'2'];
        for(int i=0;i<choose.size();i++) {
            backindex(combination+choose[i],next_digits.substr(1));
        }
    }
}

std::vector<std::string> combinations(std::string digits) {
    std::vector<std::string> ret;
    if(digits.size()!=0)
        backindex("",digits);
    return vector;
}