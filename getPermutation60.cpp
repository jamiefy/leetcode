//
// Created by Administator on 2019/12/24.
//
#include <iostream>
#include <vector>

//递归
//时间复杂度：O(n)
//空间复杂度：O(n)
std::string getPermutation(int n, int k,std::vector<int>& visited) {

    //如果使用5个数则可以将总排列分为5组，每组num=4*3*2个，计算k在哪组
    int num=1;
    for(int i=n-1;i>1;i--){
        num*=i;
    }
    //k在第count组
    int count= k%num==0 ? k/num : k/num+1;
    //找出在未使用的数字中的第count组对应的数字,添加到字符串中并标记已使用
    int position=0;
    for(int i=1;i<=count;){
        position++;
        if(!visited[position])
            i++;
    }
    visited[position]=true;
    //k在第count组的第k（计算出来的k）个
    k=k%num==0 ? num : k%num;
    //循环递归
    return n==1 ? std::to_string(position) : std::to_string(position)+getPermutation(n-1,k,visited);
}
std::string getPermutation(int n, int k) {
    //保证输入下面函数的n和k都大于1
    if(n==0 || k==0)
        return "";
    std::string ret;
    //创建visited数组记录从1到n数字是否被使用过，下标对应操作更简单（0下标对应位不用）
    std::vector<int> visited(n+1, false);
    return getPermutation(n,k,visited);
}

int main(){
    std::cout<<getPermutation(3,3)<<std::endl;
}