//
// Created by Administrator on 2019/10/31.
//
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>

//时间复杂度：O(NKlogK)，其中 N是strs的长度，而K是strs中字符串的最大长度。当我们遍历每个字符串时，外部循环具有的复杂度为 O(N)。
//然后，我们在O(KlogK)的时间内对每个字符串排序。空间复杂度：O(NK)，排序存储在 ans 中的全部信息内容。
std::vector<std::vector<std::string>> groupAnagramsSort(std::vector<std::string>& strs) {
    std::vector<std::vector<std::string>> ret(strs.size());
    std::map<std::vector<char>,int> group;
    int index=0;
    for(auto str:strs){
        std::vector<char> cvec;
        for(int i=0;i<str.size();i++){
            cvec.emplace_back(str[i]);
        }
        //cvec不能使用set代替，因为set不存放重复元素，可以把vec排序实现set自动排序的功能
        std::sort(cvec.begin(),cvec.end());
        if(group.find(cvec)==group.end()){
            group[cvec]=index;
            ret[index].emplace_back(str);
            index++;
        } else{
            ret[group.find(cvec)->second].emplace_back(str);
        }
    }
    ret.resize(index);
    return ret;
}

//算法优化，完全可以直接排序string，直接把排序好的string作为vec，映射std::vector<std::string>
//时间复杂度：O(NKlogK)，其中 N是strs的长度，而K是strs中字符串的最大长度。当我们遍历每个字符串时，外部循环具有的复杂度为 O(N)。
//然后，我们在O(KlogK)的时间内对每个字符串排序。空间复杂度：O(NK),排序存储在 ans 中的全部信息内容。
std::vector<std::vector<std::string>> groupAnagramsSortImp(std::vector<std::string>& strs) {
    std::vector<std::vector<std::string>> ret;
    std::map<std::string,std::vector<std::string>> group;
    for(auto str:strs) {
        std::string tmp = str;
        std::sort(tmp.begin(), tmp.end());
        group[tmp].emplace_back(str);
    }
    for(auto m:group){
        ret.emplace_back(m.second);
    }
    return ret;
}

//时间复杂度：O(NK)，其中 N是strs的长度，而K是strs中字符串的最大长度。计算每个字符串的字符串
//大小是线性的，我们统计每个字符串。空间复杂度：O(NK)，排序存储在 ans 中的全部信息内容。
//采用对每个字符串进行26个字母计数，虽然时间复杂度降低但是时间消耗增加一倍，空间消耗增加1/2
std::vector<std::vector<std::string>> groupAnagrams(std::vector<std::string>& strs){
    std::map<std::string,std::vector<std::string>> group;
    std::vector<std::vector<std::string>> ret;
    for(auto str:strs) {
        //把std::sort(tmp.begin(), tmp.end())替换成计数
        std::vector<int> count(26,0);
        for(auto c:str){
            count[c-'a']++;
        }
        std::string countStr;
        for(int i=0;i<26;i++){
            countStr+='#';
            //不能直接countStr+=count[i]，要先把count[i]转换成string，不然加进去的所有值都是 #\000 形式
            countStr+=std::to_string(count[i]);
        }
        group[countStr].emplace_back(str);
    }
    for(auto m:group){
        ret.emplace_back(m.second);
    }
    return ret;

}

//最优化编程形式，时间空间消耗极大幅度减小。细节决定成败
std::vector<std::vector<std::string>> groupAnagramsBest(std::vector<std::string>& strs) {
    std::vector<std::vector<std::string>> res;
    std::unordered_map<std::string,std::vector<std::string>> m;
    for(auto str:strs){
        std::string t = str;
        //使用自定义lambda表达式排序和直接使用sort效率不相上下
        sort(t.begin(),t.end(),[&] (char &a, char &b){ return a>=b;});
        m[t].push_back(str);
    }
    //采用引用在时间和空间上均优于直接auto pair:m
    for(auto& pair:m){
        //采用move在时间和空间上均优于直接res.emplace_back(pair.second),相当于把指向pair.second的指针偷过来
        //直接用，move之后pair.second为空,std::move执行到右值的无条件转换，避免不必要的拷贝操作。
        //std::move是为性能而生。
        //std::move是将对象的状态或者所有权从一个对象转移到另一个对象，只是转移，没有内存的搬迁或者内存拷贝。
        res.push_back(std::move(pair.second));
        //std::cout<<pair.second.empty()<<std::endl;输出1
    }
    return res;
}


int main(){
    std::vector<std::string> vec{"deb","ebd","hos","boo","nay","wow","bop","bob","brr","hey","rye","eve","elf",
                                  "pup","bum","iva","lyx","yap","ugh","hem","rod","aha","nam","gap","yea",
                                  "doc","pen","job","dis","max","oho","jed","lye","ram","pup","qua","ugh",
                                  "mir","nap","deb","hog","let","gym","bye","lon","aft","eel","sol","jab"};
    std::vector<std::vector<std::string>> ret=groupAnagramsBest(vec);
    for(int i=0;i<ret.size();i++){
        for(auto str:ret[i]){
            std::cout<<str<<' ';
        }
        std::cout<<std::endl;
    }
}