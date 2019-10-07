#include <iostream>
#include <vector>
#include <algorithm>

std::string convert(std::string s, int numRows) {//提交出错
    if(numRows==1)
        return s;
    int len=s.size();
    numRows=std::min(numRows,len);
    std::vector<std::vector<char>> num(numRows);
    std::string convertString;
    for(int i=0,j=0;i<len;){
        if(j==numRows){
            j=numRows-2;
            while(j && i<len)
                num[j--].push_back(s[i++]);
        }
        if(j==0)
            while(j<numRows && i<len)
                num[j++].push_back(s[i++]);
    }
    for(int i=0;i<numRows;i++){
        for(auto it=num[i].begin();*it!='\0';it++){
            convertString+=*it;
        }
    }
    return convertString;

}

std::string convertString(std::string s, int numRows) {//提交正确
    if(numRows==1)
        return s;
    int len=s.size();
    numRows=std::min(numRows,len);
    std::vector<std::string> num(numRows);
    std::string convertString;
    for(int i=0,j=0;i<len;){
        if(j==numRows){
            j=numRows-2;
            while(j && i<len)
                num[j--]+=s[i++];
        }
        if(j==0)
            while(j<numRows && i<len)
                num[j++]+=s[i++];
    }
    for(int i=0;i<numRows;i++)
        convertString+=num[i];
    return convertString;
}

std::string convertStringImprove(std::string s, int numRows) {//提交正确
    if(numRows==1)return s;
    numRows=std::min(numRows,(int)s.size());
    std::vector<std::string> num(numRows);
    int curRow = 0;
    bool goingDown = false;
    for(char c:s){
        num[curRow]+=c;
        if(curRow==0 || curRow==numRows-1)goingDown=!goingDown;
        curRow+=goingDown?1:-1;
    }
    std::string ret;
    for(auto str:num)
        ret+=str;
    return ret;
}

std::string convertStringImp(std::string s, int numRows) {//提交正确
    int len=s.size();
//    numRows=std::min(numRows,len);//该赋值存在则必须放在 if(numRows==1)return s之前不然在len=1(cyclen=0)时会导致for(int j=0;j+i<len;j+=cyclen)死循环
    if(numRows==1)return s;
    std::vector<std::string> num(numRows);
    int cyclen=2*numRows-2;
    for(int i=0;i<numRows;i++){
        for(int j=0;j+i<len;j+=cyclen){
            num[i]+=s[j+i];
            if(i!=0 && i!=numRows-1 && j+cyclen-i<len){
                num[i]+=s[j+cyclen-i];
            }
        }
    }
    std::string ret;
    for(auto str:num)
        ret+=str;
    return ret;
}

int main() {
    std::string s="A";
    std::cout<<convert(s,3).compare(convertString(s,3))<<std::endl;
    std::cout<<convert(s,3).compare(convertStringImprove(s,3))<<std::endl;
    std::cout<<convert(s,3).compare(convertStringImp(s,3))<<std::endl;
    return 0;
}