//
// Created by anranzhai on 2019/10/13.
//
#include <iostream>
#include <vector>
#include <map>
#include <iterator>

std::string countAndSay(int n) {
    //把第一个报数序列在初始化的时候填进vector
    std::vector<std::string> countSequenceVector(1,"1");

    //n个报数序列循环n-1次
    for(int i=1;i<n;i++){
        //初始化该报数序列为空
        std::string s;
        //对于该报数序列循环从头countSequenceindex=0开始,依次对每个字符进行处理,当索引=该报数序列的长度-1时循环停止
        for(int countSequenceindex=0;countSequenceindex<countSequenceVector[i-1].size();){
            //记录每组相同字符和字符数,字符改变则charCount从空开始
            std::map<char,int> charCount;
            //每组相同字符用tmp=第一个字符进行记录
            char tmp=countSequenceVector[i-1][countSequenceindex];
            //在该报数序列长度范围内遍历相邻的相同字符直到字符发生改变,此时countcountSequenceindex指向发生改变的字符
            while(countSequenceindex<countSequenceVector[i-1].size()&&tmp==countSequenceVector[i-1][countSequenceindex]){
                charCount[tmp]=charCount.find(tmp)==charCount.end()?1:charCount[tmp]+1;
                countSequenceindex++;
            }
            //在报数序列末尾依次添上每组相同字符数和字符
            s+=std::to_string(charCount[tmp])+tmp;
        }
        //在报数序列vector中填进去索引=i(实际上为第i+1个报数序列)的字符串
        countSequenceVector.emplace_back(s);
    }
    //返回最后一个报数序列
    return countSequenceVector[n-1];
}

//上面方法的简化，把vector换成前一个string和当前string
std::string countAndSaySimple(int n) {
    //初始化第一个报数序列
    std::string preCountSequence="1";

    //n个报数序列循环n-1次
    for(int i=1;i<n;i++){
        //初始化第二个报数序列为空
        std::string s;
        //记录每组相同字符和字符数,字符改变则charCount从空开始
        int charCount=0;
        //对于该报数序列循环从头countSequenceindex=0开始,依次对每个字符进行处理,当索引=该报数序列的长度-1时循环停止
        for(int countSequenceindex=0;countSequenceindex<preCountSequence.size();countSequenceindex++){

            //在该报数序列长度范围内遍历相邻的相同字符,当字符发生改变从头开始计数,此时countcountSequenceindex指向发生改变的字符
            if(countSequenceindex==0||preCountSequence[countSequenceindex-1]==preCountSequence[countSequenceindex])
                charCount+=1;
            else{
                //在报数序列末尾依次添上每组相同字符数和字符
                s+=std::to_string(charCount)+preCountSequence[countSequenceindex-1];
                charCount=1;
            }
            //与前一位相等时最后一组的charCount和tmp未插入字符串;
            //与前一位不相等时当前位的charCount和tmp未插入字符串
            if(countSequenceindex==preCountSequence.size()-1)
                s+=std::to_string(charCount)+preCountSequence[countSequenceindex];
            }
        preCountSequence=s;
    }
    //返回最后一个报数序列
    return preCountSequence;
}

std::string countAndSayLine(std::string preCountSequence){
    //初始化第二个报数序列为空
    std::string s;
    //记录每组相同字符和字符数,字符改变则charCount从空开始
    int charCount=0;
    //对于该报数序列循环从头countSequenceindex=0开始,依次对每个字符进行处理,当索引=该报数序列的长度-1时循环停止
    for(int countSequenceindex=0;countSequenceindex<preCountSequence.size();countSequenceindex++){

        //在该报数序列长度范围内遍历相邻的相同字符,当字符发生改变从头开始计数,此时countcountSequenceindex指向发生改变的字符
        if(countSequenceindex==0||preCountSequence[countSequenceindex-1]==preCountSequence[countSequenceindex])
            charCount+=1;
        else{
            //在报数序列末尾依次添上每组相同字符数和字符
            s+=std::to_string(charCount)+preCountSequence[countSequenceindex-1];
            charCount=1;
        }
        //与前一位相等时最后一组的charCount和tmp未插入字符串;
        //与前一位不相等时当前位的charCount和tmp未插入字符串
        if(countSequenceindex==preCountSequence.size()-1)
            s+=std::to_string(charCount)+preCountSequence[countSequenceindex];
    }
    return s;
}

std::string countAndSayRecursive(int n){
        if (n == 1) {
            return "1";
        }
        return countAndSayLine(countAndSay(n - 1));
}

int main(){
    std::cout<<countAndSayRecursive(4)<<std::endl;
}