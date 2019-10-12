//
// Created by anranzhai on 10/2/19.
//
#include <iostream>
#include <vector>
#include <memory>

//自己的错误解法-蛮力不可行-很多情况不能涵盖
bool match(std::string s, std::string p) {
    if((s!=""&&(p==""||p=="*"))||(s==""&&p=="*"))return false;
    if(s==""&&(p==""||p[1]=='*'))return true;
    int curs=0,curp=0;
    for(;curs<s.length()&&curp<p.length();){
        if(s[curs]==p[curp]){
            curs++;
            curp++;
        } else{
            if(p[curp]=='.'){
                curs++;
                curp++;
            }
            else if(p[curp]=='*'&&p[curp-1]==s[curs]){
                if(curp+1>=p.size()){
                    while(++curs<s.size()){
                        if(s[curs]==p[curp-1])continue;
                        else return false;
                    }
                } else{
                    while(curs-1<s.size()&&p[curp-1]==s[curs-1]){
                        if(match(s.substr(curs-1),p.substr(curp+1)))
                            return true;
                        curs++;
                    }
                    if(curs-1<s.size()&&match(s.substr(curs-1),p.substr(curp+1)))return true;
                    return false;
                }


                while(p[curp-1]==s[curs]){
                    curs++;
                    if(curs>=s.length())break;
                }
                curp++;
            }
            else if(p[curp]=='*'&&p[curp-1]=='.'){
                if(curp==p.size()-1)return true;
                else{
                    while(++curs<s.size()){
                        if(match(s.substr(curs),p.substr(curp+1)))
                            return true;
                    }
                    return false;
                }
            }
            //*和前面的字母=前面的字母，所以需要跳过*
            else if(p[curp]=='*'){
                curp++;
            }
            else if(p[curp+1]=='*'){
                curp+=2;
            } else
                return false;
        }
    }
    if(curs>=s.length()&&curp>=p.length())return true;
    else return false;
}

//回溯法
bool isMatchRecursive(std::string s, std::string p) {
    if (p.empty())return s.empty();
    bool firstMatch = !s.empty() && (s[0] == p[0] || p[0] == '.');
    if (p.size() >= 2 && p[1] == '*') {//保证存在两个字符且第二个字符等于*
        return (firstMatch && isMatchRecursive(s.substr(1), p)) || (isMatchRecursive(s, p.substr(2)));
    } else {
        return firstMatch && isMatchRecursive(s.substr(1), p.substr(1));
    }

}


//自顶向下
std::shared_ptr<std::vector<std::vector<bool>>> matchVector;

bool dp(int i,int j,std::string s,std::string p){
    if(matchVector->at(i).at(j)!= NULL)
        return matchVector->at(i).at(j);
    if(j==p.size())
        matchVector->at(i).at(j)= i==s.size();//0个字符到s.size()个字符总共是s.size()+1个字符
    else{
        bool firstMatch=i<s.size() && (p[j]==s[i]||p[j]=='.');

        //保证第二位至少是p的最后一位且等于*
        if(j+1<p.size() && p[j+1]=='*'){
            matchVector->at(i).at(j)=(firstMatch && dp(i+1,j,s,p))||dp(i,j+2,s,p);
        } else{//当前位是p的最后一位 或者 第二位不等于* 那么字符串各前进一位
            matchVector->at(i).at(j)=firstMatch&&dp(i+1,j+1,s,p);
        }
    }
    return matchVector->at(i).at(j);
}

bool isMatchDynamicUpToDown(std::string s, std::string p) {
    std::vector<bool> vector(p.size()+1, false);
    matchVector=std::make_shared<std::vector<std::vector<bool>>>(s.size()+1,vector);
    return dp(0,0,s,p);
}

bool isMatchDynamicDownToUp(std::string s, std::string p) {
    std::vector<bool> vector(p.size()+1);
    std::vector<std::vector<bool>> matchV(s.size()+1,vector);
    matchV[s.size()][p.size()]= true;
    for(int i=s.size();i>=0;i--){
        //当j=p.size()的时候判断时只能根据字符串各前进一位判断
        for(int j=p.size()-1;j>=0;j--){
            bool firstMatch=i<s.size() && (p[j]==s[i]||p[j]=='.');
            if(p[j+1]=='*')
                matchV[i][j]=(firstMatch&&matchV[i+1][j])||matchV[i][j+2];
            else//p[j+1]不等于* 或者 j+1是p的最后一位
                matchV[i][j]=firstMatch&&matchV[i+1][j+1];
        }
    }
    return matchV[0][0];
}

int main(){
    std::cout<<isMatchDynamicUpToDown("aaaaaaaaaaaaab"
                                      ,"a*a*a*a*a*a*a*a*a*a*c")<<std::endl;
}