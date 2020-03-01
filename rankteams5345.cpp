//
// Created by anranzhai on 2020/3/1.
//
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
int getIndexCount(std::vector<std::string>& votes,char c,int index){
    int times=0;
    for(int i=0;i<votes.size();i++){
        if(votes[i][index]==c)
            times++;
    }
    return times;
}

std::string rankTeams(std::vector<std::string>& votes) {
    if(votes.empty())
        return "";
    int size=votes.size();//评委数
    if(size==1)
        return votes[0];
    std::map<char,std::vector<int>> teamMap;
    for(auto &c:votes[0]){//对应参加队名
        for(int index=0;index<votes[0].size();index++){//在所有评委中排名中在第index位置所占的次数
            teamMap[c].push_back(getIndexCount(votes,c,index));
        }
    }
    std::multimap<std::vector<int>,char> sortMap;
    for(auto it=teamMap.rbegin();it!=teamMap.rend();it++){
        sortMap.emplace(it->second,it->first);
    }
    //map不是线性序列不能用std::sort直接排序，把pair放入vector也不能排序
    std::string ret;
    for(auto it=sortMap.rbegin();it!=sortMap.rend();it++){
        ret+=it->second;
    }
    return ret;
}

//因为只有A-Z 26个队伍，那排名也就只有26个,完全可以弄一个 [27][27]的数组存放，每个队伍的排名数据.
//当然，还有额外条件，如果全部的名次都相同，会按照队伍的字符排序，
//既然这样的话，我们就将每个队伍的最后一个空格，填上 26-(队伍名-'A')
//如果是A队的话 就是 26,B队就是 25
//sort里面的默认排序是less，我们需要使用greater
//如果在排二维数组的时候，它的特性就是首先对比第二维数组中的第一个数的大小，如果相同就回去比第二个，第三个.....
std::string rankTeamsImp(std::vector<std::string>& votes) {
    if(votes.empty())
        return "";
    int size=votes.size();//评委数
    if(size==1)
        return votes[0];
    std::vector<std::vector<int>> rank(27,std::vector<int>(27,0));
    for(auto &p:votes){//p代表每个评委给出的排名
        for(int index=0;index<votes[0].size();index++){//评委p给出的排名中第index位
            rank[p[index]-'A'][index]++;
            rank[p[index]-'A'].back()=26-(p[index]-'A');
        }
    }
    //用vector和map的区别就是vector不能自己排序，map可以
    std::sort(rank.begin(),rank.end(),std::greater<std::vector<int>>());//注意函数用法
    std::string ret;
    for(auto &p:rank){
        if(p.back()!=0)
            ret+=26-p.back()+'A';
    }
    return ret;
}

int main(){
    std::vector<std::string> vec{"YEQG","QYGE","QYGE","GEQY","QYEG","EYGQ","GYQE","EQGY","QYGE","GQYE","YGEQ","GQYE","EGQY","YEGQ","GEQY","YGEQ","EYQG","EGYQ","GYQE","GEYQ","EGYQ","YEGQ","YEQG","QGEY","QYEG","YQGE","GQYE","EQYG","EYGQ","EQGY","QGYE","QYGE","GQEY","YGEQ","QEGY","YQEG","GYQE","QYGE","QYGE","EYGQ","EGYQ","QEGY","YEGQ","GQEY","GYEQ","EQYG","QGYE","QEGY","YQGE","QEYG","GQEY","YGEQ","GQYE","YEQG","QGEY","GEYQ","GYQE","EQYG","EQYG","GQEY","GEQY","YGEQ","GYQE","GQEY","GQEY","YEQG","EYQG","YGEQ","YGQE","YGEQ","EGQY","GQYE","EGYQ","QEYG","GYQE","GYQE","YQGE","YEQG","GQEY","YGQE","GQYE","GYEQ","QGYE","EGYQ","YEGQ","EQYG","QEGY","YEGQ","YEGQ","EYQG","YEQG","EQYG","EQYG","YEQG","GYEQ","GQYE","EQYG","YQGE","QGYE","EYQG","EQYG","GQYE","GYEQ","EYQG","GQYE","EYQG","EYGQ","QGEY","GEYQ","GYQE","QYEG","QEGY","YEQG","YEQG","YEGQ","GQYE","GYEQ","EGQY","EQGY","QEGY","GEYQ","YQGE","YQGE","YEGQ","GYQE","GQYE","QGEY","EQGY","QEGY","GYEQ","EGQY","YEQG","QGYE","QEYG","QYGE","EQYG","YGEQ","YGQE","GYEQ","YGEQ","QYEG","QGYE","EQYG","YGQE","QEYG","EYGQ","QGYE","YQEG","GQEY","GQEY","GQYE","GYQE","EGQY","YGEQ","YQGE","GEQY","QYGE","YEQG","QEYG","EQYG","GQYE","EQGY","GQYE","QGYE","GYQE","QGEY","QGYE","EQGY","QYGE","GEYQ","GEYQ","YQGE","EGYQ","GYEQ","QGEY","GQYE","GYQE","QEGY","QGYE","GEQY","GQYE","EGYQ","GYQE","GQYE","EQGY","GQYE","EQYG","QYGE","QGEY","GYEQ","EGYQ","YQEG","YGEQ","EQYG","QGEY","QYEG","GQYE","EGYQ","GQEY","EGYQ","YEQG","YQEG","EQYG","QGYE","GQEY","GQEY","GEQY","QYEG","EGQY","GEQY","YEGQ","GQYE","GYQE","YEQG","YGEQ","YQGE","QEGY","YGEQ","YGEQ","QEGY","EQYG","EGQY","EYGQ","YQEG","YEGQ","EGQY","QEYG","GYQE","YEQG","QYEG","EYGQ","GEYQ","YGEQ","QGEY","EGYQ","GEQY","EGYQ","GQEY","YQEG","YEGQ","YEGQ","QEYG","YEGQ","EQGY","EQGY","QEYG","EYQG","EGYQ","YQGE","YQEG","GEQY","YGEQ","EYQG","QEYG","YEQG","YQEG","YGQE","YEQG","YGQE","GYEQ","QGYE","GYEQ","EGQY","YEQG","YEQG","GQEY","QEGY","EGQY","YQEG","EYGQ","GEQY","GQEY","QGYE","YQEG","QEYG","YEGQ","EGYQ","QGYE","EQGY","GEQY","QEYG","QGYE","EGYQ","YEQG","QYGE","EGYQ","EYQG","QEYG","YEGQ","GEQY","QYGE","GYEQ","YGQE","QGEY","YEGQ","QGEY","QEYG","YEGQ","GYEQ","GQEY","QGYE","YEGQ","EGYQ","GEQY","YQGE","QGEY","GYEQ","GQEY","EGQY","YEGQ","QEYG","EGQY","GQEY","YEGQ","YGQE","YQEG","QYEG","YQEG","QGEY","QGYE","GQEY","GEQY","QYGE","QEYG","EGYQ","EQGY","YEGQ","EGYQ","QGEY","YEGQ","QGYE","GYEQ","QEYG","YQEG","GYEQ","YQGE","GEQY","YGQE","GQYE","QEYG","GEYQ","GYEQ","YGEQ","YEQG","YEQG","YGEQ","YEQG","GYQE","YGQE","YQEG","EGYQ","GYQE","GQYE","EQGY","YQEG","EQYG","YEQG","EQYG","EGQY","YEGQ","EYQG","QEGY","GEQY","YGQE","GQEY","GEYQ","EQGY","EYQG","GYQE","YEQG","YEQG","QEYG","EGYQ","GYQE","EGQY","YGEQ","YQEG","EGYQ","EYQG","QGYE","QGYE","YEQG","YEGQ","YEQG","GEYQ","GEQY","EGQY","GYEQ","QEGY","EGQY","YGQE","GEQY","EQYG","YQEG","YEGQ","EGYQ","QGEY","GYQE","EGQY","QGYE","GEQY","GYEQ","YEQG","YQEG","QYEG","GEYQ","YGEQ","GYQE","YEGQ","QEGY","QGYE","YQGE","EGQY","YQEG","QYGE","GYEQ","EGQY","EYGQ","QYEG","QEGY","EGQY","EGYQ","GQYE","GQEY","YQGE","YGEQ","EGYQ","EQGY","EGQY","GQYE","EQGY","QYGE","GEYQ","EQYG","QEGY","EGYQ","EQYG","GQYE","QEGY","QGEY","QYEG","QYEG","GEYQ","QGYE","GEQY","GYEQ","EYGQ","QEYG","EGQY","EQYG","EYGQ","QEGY","QYGE","GEQY","YEQG","EYGQ","YEGQ","YGQE","YGQE","EGQY","GEQY","GEQY","EYQG","YQEG","QEGY","GEYQ","QYEG","EQGY","QGYE","GQEY","EGQY","YGEQ","EYQG","YQEG","QEYG","EGYQ","YEGQ","YEQG","QGYE","GQYE","YQGE","GYQE","QGYE","QYGE","YQEG","EGQY","QEYG","QEGY","GYEQ","QEGY","EYQG","QEYG","GEYQ","GEYQ","QGYE","QYEG","YEQG","GQYE","GQEY","YEGQ","QEGY","GQEY","EQGY","QGEY","YGQE","GQYE","QEGY","YGEQ","QGYE","QEGY","YGQE","EGYQ","QGYE","EYGQ","GQEY","EQYG","EGYQ","EGYQ","EYGQ","EYGQ","GYQE","QGEY","YEGQ","GYQE","YGQE","QEYG","YQGE","GEYQ","GQEY","YQEG","YQGE","EYQG","YGEQ","GYQE","YQEG","GQYE","QEYG","EQYG","EQGY","GQEY","EYQG","YEGQ","YEGQ","EQYG","EYQG","YQEG","QYGE","YEQG","QYGE","QGYE","GYQE","EQYG","GEQY","YQGE","GYQE","EYGQ","EQYG","GQEY","GYQE","QEYG","YQEG","EYQG","QGYE","YQEG","GEYQ","GYEQ","QEYG","EQGY","GYEQ","GQEY","EGQY","YQGE","GEQY","GYQE","QGYE","QGYE","GQYE","EYQG","QGYE","YEQG","EGQY","GQEY","QEYG","YGQE","EYQG","YGQE","YGQE","GYEQ","YEQG","QGYE","GYQE","QGYE","QYEG","GYEQ","QYGE","QEGY","EYQG","YGQE","GYEQ","GEYQ","GEQY","EGQY","YGQE","YGEQ","EQGY","QYGE","EQYG","YEQG","QYGE","EQYG","YQGE","EQGY","GEQY","YGEQ","EQGY","YEGQ","YEGQ","EGYQ","GQEY","QGEY","QYEG","QGEY","EYQG","EQYG","GYEQ","YGQE","GYQE","GEYQ","QGEY","EYGQ","QEYG","YQEG","EYQG","QEYG","QYEG","EQGY","QEGY","YEQG","QEYG","GQEY","EYGQ","GQEY","EYGQ","YEGQ","QEGY","GQYE","GEQY","YQEG","EQYG","EQGY","EQGY","QYEG","EGYQ","YQEG","GYQE","GQEY","QEYG","YGEQ","GYQE","GYQE","EYQG","EYGQ","EYQG","YQGE","YQGE","EGYQ","QYEG","GYQE","EQYG","QYGE","GYQE","YGEQ","YQGE","QEYG","YEGQ","QGEY","QEYG","YQEG","GQEY","GYQE","YQGE","QYEG","QGYE","QEGY","YEQG","YQEG","GEYQ","EGQY","GQYE","YGQE","QGEY","EYQG","EGQY","YQGE","QEYG","EQGY","YEQG","QEGY","QGYE","QEYG","EGQY","YEGQ","EGQY","GQEY","EGQY","GYQE","EYQG","GEQY","YGQE","YGQE","YGQE","GEYQ","QGEY","YEGQ","YEQG","EYQG","EGQY","YEGQ","QEGY","GEYQ","EQYG","QGYE","YGEQ","EQGY","QEYG","EGQY","EYGQ","GYQE","EGQY","YQEG","QYEG","EQGY","GQEY","QGYE","GQYE","YEGQ","GQEY","QEGY","GEYQ","YEGQ","YGEQ","YGEQ","YQEG","YGEQ","EYQG","YQGE","QGYE","EGYQ","EGYQ","QEYG","YEGQ","GEYQ","QEYG","YGEQ","GYQE","YGQE","GYEQ","GQEY","QGYE","QYEG","YEQG","YEGQ","EGYQ","YEQG","GQEY","QGYE","EYGQ","EYQG","EYGQ","YQGE","EYQG","GQEY","GYQE","YEGQ","QYGE","YGEQ","GYQE","GQYE","EGYQ","YGEQ","EQGY","YQEG","QYGE","EQGY","YGQE","EGQY","QEGY","QYGE","GEQY","GYQE","YEQG","EYGQ","EQYG","EYGQ","GEQY","YGEQ","YGQE","YGEQ","GEYQ","EYQG","YEGQ","EQYG","EQGY","GEYQ","YEGQ","GEQY","QYGE","EGYQ","QEGY","QEYG","QGYE","YEQG","QGEY","QGYE","GYQE","GYQE","EQYG","QGEY","QEYG","EYGQ","YQGE","QYEG","QYGE","GEQY","YQEG","GYQE","GYQE","YQGE","GYEQ","EQGY","EYQG","EQYG","GQYE","EYQG","YQGE","QEGY","QEYG","EQYG","YQGE","EQYG","EQYG","GQEY","GQYE","EYQG","QYEG","GQYE","EGQY","EYGQ","EGQY","EGYQ","EYQG","GQYE","EQYG","QGYE","GEYQ","EQYG","YGQE","YQGE","EYGQ","QEYG","EQYG","YEGQ","EYGQ","GQEY","EQGY","GEYQ","YGEQ","EQGY","EQYG","YEGQ","GEQY","EGQY","EQYG","EGYQ","GQYE","GEYQ","YQGE","GQEY","GQYE","EQYG","GEQY","QYEG","EGQY","EYGQ","EQGY","GEQY","YQGE","GYQE","EQYG","EQGY","YGEQ","EYQG","YGEQ","YGEQ","GYQE","QYEG","GQEY","EQYG","YGQE","QEYG","EYGQ","EGYQ","EQGY","EYGQ","EGYQ","EYQG","QYEG","GYEQ","GQEY","EQGY","YQGE","EYQG","YQEG","GQEY","GEQY","EYQG","EQYG","QYGE","GYEQ","QEYG","EQGY","QYGE","GEYQ","GEYQ","EYGQ","QYEG","QEGY","GYQE","YQEG","GYQE","QYGE","YQGE","EGYQ","GQEY","GQEY","YEQG","YEGQ","QGYE","GYQE","YEQG","GYQE","GQEY","YQEG","GYQE","EQYG","EGQY","YGEQ","GYQE","EQYG","GEQY","GQEY","EYGQ","YQEG","QGYE","GQYE","YQEG","EYGQ","EQGY","QYEG","EYGQ","YQGE","YGQE","EYQG","YGEQ","EGQY","GEYQ","EGQY","QYEG","GEQY","QEYG","QYEG","YQGE","QEGY","YQGE","GQEY","YEGQ","YGQE","QGEY","YGQE","GQEY","EYQG","GQEY","YQEG","YQEG","EQYG","EYQG","EGYQ","EGQY","GQEY","GQYE","GQYE","QEGY","YGQE","GEQY","GQEY"};
    std::cout<<rankTeamsImp(vec)<<std::endl;
}
