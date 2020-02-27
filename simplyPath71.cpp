//
// Created by anranzhai on 2020/2/27.
//
#include <iostream>
#include <vector>
#include <sstream>
#include <stack>
//用栈时间复杂度O(n),空间复杂度O(n)
std::string simplyPath(std::string path) {
    std::stringstream is(path);
    std::vector<std::string> strs;
    std::string res = "", tmp = "";
    while(getline(is, tmp, '/')) {
        if(tmp == "" || tmp == ".")
            continue;
        else if(tmp == ".." && !strs.empty())
            strs.pop_back();
        else if(tmp != "..")
            strs.push_back(tmp);
    }
    for(std::string str:strs)
        res +=  "/" + str;
    if(res.empty())
        return "/";
    return res;
}

//可以用栈来实现新string的存储，不能直接在原string上进行
//该方法执行时间和空间消耗更多
std::string simplifyPathStack(std::string path) {
    if(path.size()==0 || path[0]!='/')
        return "";
    std::stack<std::string> strStack;
    for(int i=0;i<path.size();){
        if(path[i]=='/'){
            if(strStack.empty()||strStack.top()!="/")
                strStack.push("/");
            i++;
        }
        else if(path[i]=='.'){
            int index=i;
            std::string currString;
            //文件名有可能为"...heoll"
            while(index<path.size()&&path[index]!='/'){
                currString+=path[index];
                index++;
            }
            if(currString==".")
                i++;
            else if(currString==".."&&!strStack.empty()){
                if(strStack.top()=="/")
                    strStack.pop();
                while(!strStack.empty()&&strStack.top()!="/")
                    strStack.pop();
                i+=2;
            } else {
                strStack.push(currString);
                i=index;
            }
            //直接使用else而不是elseif(isalpha(path[i]))判断是不是字母，因为文件名可能是"he_kjsafh"等非字母
        } else{
            strStack.push(std::string({path[i]}));
            i++;
        }
    }
    std::string ret;
    while(!strStack.empty()&&strStack.top()=="/")
        strStack.pop();
    while(!strStack.empty()){
        ret=strStack.top()+ret;
        strStack.pop();
    }
    return ret.empty()?"/":ret;
}

int main(){
    std::cout<<simplifyPathStack("/a/./b/../../c/");
}