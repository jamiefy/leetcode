//
// Created by anranzhai on 10/7/19.
//
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <map>
using namespace std;
//递归提交leetcode超出时间限制
std::vector<std::string> out;
void connectSubstring(std::vector<std::string> words,std::string str,int index){
    if(index!=-1){
        words[index]=words[words.size()-1];
        words.pop_back();
    }
    if(words.size()==1){
        out.emplace_back(str+words[0]);
        return;
    }
    for(int i=0;i<words.size();i++) {
        std::string s=str+words[i];
        //必须把str提前添加words[i]，直接填到connectSubstring函数里会出现指针异常
        connectSubstring(words,s,i);
    }
}
std::vector<int> findSubstr(std::string s, std::vector<std::string>& words) {
    std::vector<int> ret;
    connectSubstring(words,"",-1);
    for(int i=0;i<out.size();i++){
        int indexfirst=s.find(out[i]);
        while(indexfirst!=-1&&indexfirst<s.size()){
            ret.emplace_back(indexfirst);
            if(indexfirst<s.size()-out[i].size())
                indexfirst=s.find(out[i],indexfirst+1);
            else
                break;
        }
    }
    std::sort(ret.begin(),ret.end());
    ret.erase(std::unique(ret.begin(),ret.end()),ret.end());
    return ret;
}

//时间复杂度O(n*m),n为字符串s的长度，m为vector words的长度
std::vector<int> findSubstring(std::string s, std::vector<std::string>& words) {
    std::vector<int> retIndex;
    int len=s.size();
    int allNum=words.size();
    if(allNum==0||len==0||s=="")return retIndex;
    int oneWord=words[0].size();
    int allWord=oneWord*allNum;
    std::map<std::string,int> allmap;
    for(int i=0;i<allNum;i++){
        if(allmap.find(words[i])!=allmap.end())
            allmap.find(words[i])->second+=1;
        else
            allmap.emplace(words[i],1);
    }
    for(int cur=0;cur<=len-allWord;cur++){
        std::string tmpS=s.substr(cur,allWord);
        std::map<std::string,int> hasmap;
        for(int j=0;j<allWord;j+=oneWord){
            std::string tmpWord=tmpS.substr(j,oneWord);
            if(allmap.find(tmpWord)!=allmap.end()){
                if(hasmap.find(tmpWord)!=hasmap.end())
                    hasmap.find(tmpWord)->second+=1;
                else
                    hasmap.emplace(tmpWord,1);
            }
            else
                break;
            if(hasmap.find(tmpWord)->second>allmap.find(tmpWord)->second)
                break;
        }
        if(hasmap==allmap)
            retIndex.emplace_back(cur);
    }
    return  retIndex;
}

//滑动窗口+双指针，时间消耗为O(oneWord*len),极大的优化了执行用时和内存消耗
std::vector<int> findSubstringImp(std::string s, std::vector<std::string>& words) {
    std::vector<int> retIndex;
    int len=s.size();
    int allNum=words.size();
    if(allNum==0||len==0||s=="")return retIndex;
    int oneWord=words[0].size();
    int allWord=oneWord*allNum;
    std::map<std::string,int> allmap;
    for(int i=0;i<allNum;i++){
        if(allmap.find(words[i])!=allmap.end())
            allmap.find(words[i])->second+=1;
        else
            allmap.emplace(words[i],1);

    }
    for(int i=0;i<oneWord;i++){
        int left=i,right=i,count=0;
        std::map<std::string,int> hasmap;
        while(right+oneWord<=len){
            std::string tmpWord=s.substr(right,oneWord);
            if(allmap.find(tmpWord)!=allmap.end()){
                if(hasmap.find(tmpWord)!=hasmap.end())
                    hasmap.find(tmpWord)->second+=1;
                else
                    hasmap.emplace(tmpWord,1);
                count++;
                right+=oneWord;
                while(hasmap.find(tmpWord)->second>allmap.find(tmpWord)->second){
                    std::string eraseStr=s.substr(left,oneWord);
                    hasmap.find(eraseStr)->second--;
                    left=left+oneWord;
                    count--;
                }
            } else{
                hasmap.clear();
                right+=oneWord;
                left=right;
                count=0;
            }
            if(count==allNum)
                retIndex.emplace_back(left);
        }
    }
    return retIndex;
}

vector<int> findSubstringtwice(string s, vector<string>& words) {
    if(words.size()==0||s.size()==0)
        return vector<int>();
    int sublen=words[0].size();
    map<string,int> nset;
    if(s.size()<sublen*words.size())
        return vector<int>();
    for(int i=0;i<words.size();i++){
        if(nset.count(words[i]))
            nset[words[i]]++;
        else
            nset[words[i]]=1;
    }
    vector<int> ret;
    map<string,int> nmap=nset;
    //如果使用`st<n`来作为终结条件， 那么s中`n-totalWordsLength`后所有的遍历实际上都是无意义  --而这是这些大量的无意义的遍历造成了一种形态的超时
    //故改st终止条件为`st <= n-totalWordsLength`
    for(int i=0;i<=s.size()-words.size()*sublen;){
        int j=i;
        for(;j<i+words.size()*sublen&&j+sublen<=s.size();j+=sublen){
            string tmp=s.substr(j,sublen);
            if(nmap.count(tmp)&&!nmap[tmp]==0){
                nmap[tmp]--;
            } else
                break;
        }
        nmap=nset;
        if(j>=words.size()*sublen+i) {
            ret.emplace_back(i);
            while(j<=s.size()-words.size()*sublen
            &&s.substr(j,sublen)==s.substr(i,sublen)){
                ret.emplace_back(i+=sublen);
                j+=sublen;
            }
        }
        i++;
    }
    return ret;
}

int main(){
    std::vector<std::string> words{"word","good","best","good"};
    std::vector<int> ret=findSubstringtwice("wordgoodgoodgoodbestword",words);
    for(int i=0;i<ret.size();i++){
        std::cout<<ret[i]<<std::endl;
    }
}
