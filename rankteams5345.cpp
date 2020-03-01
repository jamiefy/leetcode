//
// Created by anranzhai on 2020/3/1.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
char getIndexCount(std::vector<std::string>& votes,char c,int index){
    int times=0;
    for(int i=0;i<votes.size();i++){
        if(votes[i][0]==c)
            times++;
    }
    return (char)times;
}
std::string rankTeams(std::vector<std::string>& votes) {
    if(votes.empty())
        return "";
    int size=votes.size();
    if(size==1)
        return votes[0];
    std::map<char,std::string> teamMap;
    for(auto &c:votes[0]){//对应参加队名
        for(int index=0;index<size;index++){//排位第index的个数
            teamMap[c][index]=getIndexCount(votes,c,index);
        }
    }
    std::stable_sort(teamMap.begin(),teamMap.end(),[=](std::map<char,std::string>::value_type &a,std::map<char,std::string>::value_type &b){
        int index=0;
        while(index<size-1){
            if(a.second[index]==b.second[index])
                index++;
            else
                return a.second[index]<b.second[index];
        }
        return a.second[index]==b.second[index];
    });
    std::string ret;
    for(auto &team:teamMap){
        ret+=team.first;
    }
    return ret;
}

int main(){
    std::vector<std::string> vec{"MYX","MXY","MXY","XYM"};
    std::cout<<rankTeams(vec)<<std::endl;
}
